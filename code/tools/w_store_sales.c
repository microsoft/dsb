/*
 * Legal Notice
 *
 * This document and associated source code (the "Work") is a part of a
 * benchmark specification maintained by the TPC.
 *
 * The TPC reserves all right, title, and interest to the Work as provided
 * under U.S. and international laws, including without limitation all patent
 * and trademark rights therein.
 *
 * No Warranty
 *
 * 1.1 TO THE MAXIMUM EXTENT PERMITTED BY APPLICABLE LAW, THE INFORMATION
 *     CONTAINED HEREIN IS PROVIDED "AS IS" AND WITH ALL FAULTS, AND THE
 *     AUTHORS AND DEVELOPERS OF THE WORK HEREBY DISCLAIM ALL OTHER
 *     WARRANTIES AND CONDITIONS, EITHER EXPRESS, IMPLIED OR STATUTORY,
 *     INCLUDING, BUT NOT LIMITED TO, ANY (IF ANY) IMPLIED WARRANTIES,
 *     DUTIES OR CONDITIONS OF MERCHANTABILITY, OF FITNESS FOR A PARTICULAR
 *     PURPOSE, OF ACCURACY OR COMPLETENESS OF RESPONSES, OF RESULTS, OF
 *     WORKMANLIKE EFFORT, OF LACK OF VIRUSES, AND OF LACK OF NEGLIGENCE.
 *     ALSO, THERE IS NO WARRANTY OR CONDITION OF TITLE, QUIET ENJOYMENT,
 *     QUIET POSSESSION, CORRESPONDENCE TO DESCRIPTION OR NON-INFRINGEMENT
 *     WITH REGARD TO THE WORK.
 * 1.2 IN NO EVENT WILL ANY AUTHOR OR DEVELOPER OF THE WORK BE LIABLE TO
 *     ANY OTHER PARTY FOR ANY DAMAGES, INCLUDING BUT NOT LIMITED TO THE
 *     COST OF PROCURING SUBSTITUTE GOODS OR SERVICES, LOST PROFITS, LOSS
 *     OF USE, LOSS OF DATA, OR ANY INCIDENTAL, CONSEQUENTIAL, DIRECT,
 *     INDIRECT, OR SPECIAL DAMAGES WHETHER UNDER CONTRACT, TORT, WARRANTY,
 *     OR OTHERWISE, ARISING IN ANY WAY OUT OF THIS OR ANY OTHER AGREEMENT
 *     RELATING TO THE WORK, WHETHER OR NOT SUCH AUTHOR OR DEVELOPER HAD
 *     ADVANCE NOTICE OF THE POSSIBILITY OF SUCH DAMAGES.
 *
 * Contributors:
 * Gradient Systems
 */
#include "config.h"
#include "porting.h"
#include "decimal.h"
#include "w_store_sales.h"
#include "w_store_returns.h"
#include "genrand.h"
#include "columns.h"
#include "build_support.h"
#include "joint_distribution.h"
#include "tables.h"
#include "constants.h"
#include "joint_distribution.h"
#include "print.h"
#include "nulls.h"
#include "tdefs.h"
#include "scaling.h"
#include "permute.h"
#include "scd.h"
#include "parallel.h"
#ifdef JMS
extern rng_t Streams[];
#endif

struct W_STORE_SALES_TBL g_w_store_sales;
ds_key_t skipDays(int nTable, ds_key_t *pRemainder);
static int *pItemPermutation,
   nItemCount,
	nItemIndex;
static ds_key_t jDate,
   kNewDateIndex;

static int nCustomerCount;

static ds_key_t * pPromotionPermutation;
static ds_key_t * pCustomerPermutation;
static ds_key_t * pStorePermutation;

static int ** pPricingPermutations;
static int * pricingBucketCounts;

static int * pDatePermutation = NULL;
static int dateBucket;
static int dateBucketCount;

static struct ATTRIBUTE_KEY_MAP * pItemCategoryMap;
static int * pItemCategoryPermutation;

static struct ATTRIBUTE_KEY_MAP * pItemColorMap;
static int * pItemColorPermutation;

static struct ATTRIBUTE_KEY_MAP * pCustomerCountyMap;
static int * pCustomerCountyPermutation;

static struct ATTRIBUTE_KEY_MAP * pCustomerStateMap;
static int * pCustomerStatePermutation;

static int * pWholesaleCostPermutation;
static int * pMarkupPermutation;
static int * pDiscountPermutation;

// Selectivity on the fact table.
static struct ATTRIBUTE_KEY_RECORD * pCustomerCountyRecord;
static struct ATTRIBUTE_KEY_RECORD * pCustomerStateRecord;
static struct ATTRIBUTE_KEY_RECORD * pItemColorRecord;
static struct ATTRIBUTE_KEY_RECORD * pItemCategoryRecord;

/*
* mk_store_sales
*/
static void
mk_master (void *row, ds_key_t index)
{
	struct W_STORE_SALES_TBL *r;
	static decimal_t dMin,
		dMax;
	static int bInit = 0,
		nMaxItemCount;
	static ds_key_t kNewDateIndex = 0;

	static date_t startDate, endDate;
	int daysMin, daysMax;
	int totalDays;

	if (row == NULL)
		r = &g_w_store_sales;
	else
		r = row;

	static int nCustomerCountyCount;
	static int nItemColorCount;

	if (!bInit)
	{
      strtodec (&dMin, "1.00");
      strtodec (&dMax, "100000.00");
		nMaxItemCount = 20;
		jDate = skipDays(STORE_SALES, &kNewDateIndex);
		pItemPermutation = makePermutation(NULL, nItemCount = (int)getIDCount(ITEM), SS_PERMUTATION);

		pCustomerPermutation = makeKeyPermutation(NULL, nCustomerCount = (int)get_rowcount(CUSTOMER), SS_SOLD_CUSTOMER_SK);
		pPromotionPermutation = makeKeyPermutation(NULL, get_rowcount(PROMOTION), SS_SOLD_PROMO_SK);
		pStorePermutation = makeKeyPermutation(NULL, get_rowcount(STORE), SS_SOLD_STORE_SK);

		strtodt(&startDate, DATA_START_DATE);
		strtodt(&endDate, DATA_END_DATE);
		daysMin = dttoj(&startDate);
		daysMax = dttoj(&endDate);
		totalDays = daysMax - daysMin + 1;
		// Initialize buckets for dates.
		makeBucket(&dateBucket, &dateBucketCount, DATE_BUCKET_COUNT, totalDays);
		pDatePermutation = makePermutation(NULL, dateBucketCount, D_DATE_SK);
		if (is_set("VERBOSE"))
			printf("store_sales date permutation: count %d, bucket %d, bucket count %d\n", totalDays, dateBucket, dateBucketCount);

		// Add skewed distribution to pricing.
		pWholesaleCostPermutation = makePermutation(NULL, WHOLESALE_COST_BUCKET_COUNT, STORE_SALES);
		pMarkupPermutation = makePermutation(NULL, MARKUP_BUCKET_COUNT, STORE_SALES);
		pDiscountPermutation = makePermutation(NULL, DISCOUNT_BUCKET_COUNT, STORE_SALES);

		// Load data for joint distribution.
		pItemCategoryMap = deserializeAttributeKeyMap("item_category");
		pItemCategoryPermutation = makePermutation(NULL, pItemCategoryMap->attributeCount, SS_SOLD_ITEM_SK);
		pCustomerCountyMap = deserializeAttributeKeyMap("customer_county");
		pCustomerCountyPermutation = makePermutation(NULL, pCustomerCountyMap->attributeCount, SS_SOLD_CUSTOMER_SK);
		pCustomerStateMap = deserializeAttributeKeyMap("customer_state");
		pCustomerStatePermutation = makePermutation(NULL, pCustomerStateMap->attributeCount, SS_SOLD_CUSTOMER_SK);

		// Initialize data struture to keep track of selectivity on the fact table.
		pItemCategoryRecord = initializeAttributeKeyRecordCountOnly(pItemCategoryMap->attributeCount);
		pCustomerCountyRecord = initializeAttributeKeyRecordCountOnly(pCustomerCountyMap->attributeCount);
		pCustomerStateRecord = initializeAttributeKeyRecordCountOnly(pCustomerStateMap->attributeCount);

		bInit = 1;
	}


   while (index > kNewDateIndex)	/* need to move to a new date */
   {
      jDate += 1;
      kNewDateIndex += dateScalingPermutation(STORE_SALES, jDate, pDatePermutation);
   }
		r->ss_sold_store_sk = mk_join_permutation (SS_SOLD_STORE_SK, STORE, 1, pStorePermutation);
		r->ss_sold_time_sk = mk_join (SS_SOLD_TIME_SK, TIME, 1);
		//r->ss_sold_date_sk = mk_join (SS_SOLD_DATE_SK, DATE, 1); This is a bug.
		r->ss_sold_date_sk = jDate;

		//r->ss_sold_customer_sk = mk_join_permutation (SS_SOLD_CUSTOMER_SK, CUSTOMER, 1, pCustomerPermutation);

		ds_key_t tmp;

		// Add joint distribution between item and customer.
		genrandExpJointDistribution(pItemCategoryMap, pCustomerStateMap,
			pItemCategoryPermutation, pCustomerStatePermutation,
			DIST_EXP_RANK_LOW, DIST_EXP_RANK_LOW,
			SS_SOLD_CUSTOMER_SK,
			&tmp, &r->ss_sold_customer_sk);

		nItemIndex = (int)tmp;

		r->ss_sold_cdemo_sk = mk_join (SS_SOLD_CDEMO_SK, CUSTOMER_DEMOGRAPHICS, 1);
		r->ss_sold_hdemo_sk = mk_join (SS_SOLD_HDEMO_SK, HOUSEHOLD_DEMOGRAPHICS, 1);
		r->ss_sold_addr_sk = mk_join (SS_SOLD_ADDR_SK, CUSTOMER_ADDRESS, 1);
		r->ss_ticket_number = index;

    return;
}


static void
mk_detail (void *row, int bPrint)
{
int nTemp;
struct W_STORE_RETURNS_TBL ReturnRow;
struct W_STORE_SALES_TBL *r;
tdef *pT = getSimpleTdefsByNumber(STORE_SALES);

	if (row == NULL)
		r = &g_w_store_sales;
	else
		r = row;

   nullSet(&pT->kNullBitMap, SS_NULLS);
	/*
	 * items need to be unique within an order
	 * use a sequence within the permutation
	 */
	if (++nItemIndex > nItemCount)
      nItemIndex = 1;
	r->ss_sold_item_sk = matchSCDSK(getPermutationEntry(pItemPermutation, nItemIndex), r->ss_sold_date_sk, ITEM);
	r->ss_sold_promo_sk = mk_join_permutation (SS_SOLD_PROMO_SK, PROMOTION, 1, pPromotionPermutation);
	// Add skews to data
	set_pricing_permutation(WS_PRICING, &r->ss_pricing, pWholesaleCostPermutation, WHOLESALE_COST_BUCKET_COUNT,
		pMarkupPermutation, MARKUP_BUCKET_COUNT, pDiscountPermutation, DISCOUNT_BUCKET_COUNT);

	/**
	* having gone to the trouble to make the sale, now let's see if it gets returned
	*/
	genrand_integer(&nTemp, DIST_UNIFORM, 0, 99, 0, SR_IS_RETURNED);
	if (nTemp < SR_RETURN_PCT)
	{
		mk_w_store_returns(&ReturnRow, 1);
      if (bPrint)
         pr_w_store_returns(&ReturnRow);
	}

   if (bPrint)
      pr_w_store_sales(NULL);

   // Update the selectivity.
   // Note the ss_sold_item_sk and ss_sold_customer_sk use 1-based index.
   updateAttributeKeyRecordCountOnly(pItemCategoryRecord, pItemCategoryMap->attribute[r->ss_sold_item_sk - 1]);
   updateAttributeKeyRecordCountOnly(pCustomerCountyRecord, pCustomerCountyMap->attribute[r->ss_sold_customer_sk - 1]);
   updateAttributeKeyRecordCountOnly(pCustomerStateRecord, pCustomerStateMap->attribute[r->ss_sold_customer_sk - 1]);

	return;
}

/*
* Routine:
* Purpose:
* Algorithm:
* Data Structures:
*
* Params:
* Returns:
* Called By:
* Calls:
* Assumptions:
* Side Effects:
* TODO: None
*/
int
pr_w_store_sales(void *row)
{
	struct W_STORE_SALES_TBL *r;

	if (row == NULL)
		r = &g_w_store_sales;
	else
		r = row;

	print_start(STORE_SALES);
	print_key(SS_SOLD_DATE_SK, r->ss_sold_date_sk, 1);
	print_key(SS_SOLD_TIME_SK, r->ss_sold_time_sk, 1);
	print_key(SS_SOLD_ITEM_SK, r->ss_sold_item_sk, 1);
	print_key(SS_SOLD_CUSTOMER_SK, r->ss_sold_customer_sk, 1);
	print_key(SS_SOLD_CDEMO_SK, r->ss_sold_cdemo_sk, 1);
	print_key(SS_SOLD_HDEMO_SK, r->ss_sold_hdemo_sk, 1);
	print_key(SS_SOLD_ADDR_SK, r->ss_sold_addr_sk, 1);
	print_key(SS_SOLD_STORE_SK, r->ss_sold_store_sk, 1);
	print_key(SS_SOLD_PROMO_SK, r->ss_sold_promo_sk, 1);
	print_key(SS_TICKET_NUMBER, r->ss_ticket_number, 1);
	print_integer(SS_PRICING_QUANTITY, r->ss_pricing.quantity, 1);
	print_decimal(SS_PRICING_WHOLESALE_COST, &r->ss_pricing.wholesale_cost, 1);
	print_decimal(SS_PRICING_LIST_PRICE, &r->ss_pricing.list_price, 1);
	print_decimal(SS_PRICING_SALES_PRICE, &r->ss_pricing.sales_price, 1);
	print_decimal(SS_PRICING_COUPON_AMT, &r->ss_pricing.coupon_amt, 1);
	print_decimal(SS_PRICING_EXT_SALES_PRICE, &r->ss_pricing.ext_sales_price, 1);
	print_decimal(SS_PRICING_EXT_WHOLESALE_COST, &r->ss_pricing.ext_wholesale_cost, 1);
	print_decimal(SS_PRICING_EXT_LIST_PRICE, &r->ss_pricing.ext_list_price, 1);
	print_decimal(SS_PRICING_EXT_TAX, &r->ss_pricing.ext_tax, 1);
	print_decimal(SS_PRICING_COUPON_AMT, &r->ss_pricing.coupon_amt, 1);
	print_decimal(SS_PRICING_NET_PAID, &r->ss_pricing.net_paid, 1);
	print_decimal(SS_PRICING_NET_PAID_INC_TAX, &r->ss_pricing.net_paid_inc_tax, 1);
	print_decimal(SS_PRICING_NET_PROFIT, &r->ss_pricing.net_profit, 0);
	print_end(STORE_SALES);

	return(0);
}


/*
* Routine:
* Purpose:
* Algorithm:
* Data Structures:
*
* Params:
* Returns:
* Called By:
* Calls:
* Assumptions:
* Side Effects:
* TODO: None
*/
int
ld_w_store_sales(void *pSrc)
{
	struct W_STORE_SALES_TBL *r;

	if (pSrc == NULL)
		r = &g_w_store_sales;
	else
		r = pSrc;

	return(0);
}

/*
* mk_store_sales
*/
int
mk_w_store_sales (void *row, ds_key_t index)
{
	int nLineitems,
		i;

   /* build the static portion of an order */
	mk_master(row, index);

   /* set the number of lineitems and build them */
	genrand_integer(&nLineitems, DIST_UNIFORM, 8, 16, 0, SS_TICKET_NUMBER);
   for (i = 1; i <= nLineitems; i++)
   {
	   mk_detail(NULL, 1);
   }

   /**
   * and finally return 1 since we have already printed the rows
   */
   return (1);
}


/*
* Routine:
* Purpose:
* Algorithm:
* Data Structures:
*
* Params:
* Returns:
* Called By:
* Calls:
* Assumptions:
* Side Effects:
* TODO: None
*/
int
vld_w_store_sales(int nTable, ds_key_t kRow, int *Permutation)
{
	int nLineitem,
		nMaxLineitem,
		i;

	row_skip(nTable, kRow - 1);
	row_skip(STORE_RETURNS, kRow - 1);
	jDate = skipDays(STORE_SALES, &kNewDateIndex);
	mk_master(NULL, kRow);
	genrand_integer(&nMaxLineitem, DIST_UNIFORM, 8, 16, 9, SS_TICKET_NUMBER);
	genrand_integer(&nLineitem, DIST_UNIFORM, 1, nMaxLineitem, 0, SS_PRICING_QUANTITY);
	for (i = 1; i < nLineitem; i++)
	{
		mk_detail(NULL, 0);
	}
	mk_detail(NULL, 1);

	return(0);
}

/*
* Serialize metadata for generating joint distribution across tables
*/
int
post_w_store_sales()
{
	serializeAttributeKeyRecordCountOnly("store_sales_item_category", pItemCategoryRecord);
	serializeAttributeKeyRecordCountOnly("store_sales_customer_county", pCustomerCountyRecord);
	serializeAttributeKeyRecordCountOnly("store_sales_customer_state", pCustomerStateRecord);
	return 0;
}
