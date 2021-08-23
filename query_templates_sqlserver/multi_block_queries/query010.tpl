--
-- Legal Notice
--
-- This document and associated source code (the "Work") is a part of a
-- benchmark specification maintained by the TPC.
--
-- The TPC reserves all right, title, and interest to the Work as provided
-- under U.S. and international laws, including without limitation all patent
-- and trademark rights therein.
--
-- No Warranty
--
-- 1.1 TO THE MAXIMUM EXTENT PERMITTED BY APPLICABLE LAW, THE INFORMATION
--     CONTAINED HEREIN IS PROVIDED "AS IS" AND WITH ALL FAULTS, AND THE
--     AUTHORS AND DEVELOPERS OF THE WORK HEREBY DISCLAIM ALL OTHER
--     WARRANTIES AND CONDITIONS, EITHER EXPRESS, IMPLIED OR STATUTORY,
--     INCLUDING, BUT NOT LIMITED TO, ANY (IF ANY) IMPLIED WARRANTIES,
--     DUTIES OR CONDITIONS OF MERCHANTABILITY, OF FITNESS FOR A PARTICULAR
--     PURPOSE, OF ACCURACY OR COMPLETENESS OF RESPONSES, OF RESULTS, OF
--     WORKMANLIKE EFFORT, OF LACK OF VIRUSES, AND OF LACK OF NEGLIGENCE.
--     ALSO, THERE IS NO WARRANTY OR CONDITION OF TITLE, QUIET ENJOYMENT,
--     QUIET POSSESSION, CORRESPONDENCE TO DESCRIPTION OR NON-INFRINGEMENT
--     WITH REGARD TO THE WORK.
-- 1.2 IN NO EVENT WILL ANY AUTHOR OR DEVELOPER OF THE WORK BE LIABLE TO
--     ANY OTHER PARTY FOR ANY DAMAGES, INCLUDING BUT NOT LIMITED TO THE
--     COST OF PROCURING SUBSTITUTE GOODS OR SERVICES, LOST PROFITS, LOSS
--     OF USE, LOSS OF DATA, OR ANY INCIDENTAL, CONSEQUENTIAL, DIRECT,
--     INDIRECT, OR SPECIAL DAMAGES WHETHER UNDER CONTRACT, TORT, WARRANTY,
--     OR OTHERWISE, ARISING IN ANY WAY OUT OF THIS OR ANY OTHER AGREEMENT
--     RELATING TO THE WORK, WHETHER OR NOT SUCH AUTHOR OR DEVELOPER HAD
--     ADVANCE NOTICE OF THE POSSIBILITY OF SUCH DAMAGES.
--
-- Contributors:
--
 define COUNTY = sulist(dist(fips_county,2,1),5);
 define MONTH = random(1,9,uniform);
 define YEAR = random(1998,2002,uniform);
 define BIRTH_MONTH = sulist(random(1, 12, uniform), 2);
 define CATEGORY = sulist(dist(categories,1,1), 3);
 define DISCOUNT = RANGE(RANDOM (0, 100, UNIFORM), 10);
 define MANAGER=range(random(1, 100,uniform), 10);
 define MS= list(dist(marital_status, 1, 1), 3);
 define ES= list(dist(education, 1, 1), 3);
 define GEN= dist(gender, 1, 1);

 define _LIMIT=100;

 [_LIMITA] select [_LIMITB]
  cd_gender,
  cd_marital_status,
  cd_education_status,
  count(*) cnt1,
  cd_purchase_estimate,
  count(*) cnt2,
  cd_credit_rating,
  count(*) cnt3,
  cd_dep_count,
  count(*) cnt4,
  cd_dep_employed_count,
  count(*) cnt5,
  cd_dep_college_count,
  count(*) cnt6
 from
  customer c,customer_address ca,customer_demographics
 where
  c.c_current_addr_sk = ca.ca_address_sk and
  ca_county in ('[COUNTY.1]','[COUNTY.2]','[COUNTY.3]','[COUNTY.4]','[COUNTY.5]') and
  c.c_birth_month in ([BIRTH_MONTH.1], [BIRTH_MONTH.2]) and
  cd_demo_sk = c.c_current_cdemo_sk
  and cd_marital_status in ('[MS.1]', '[MS.2]', '[MS.3]')
  and cd_education_status in ('[ES.1]', '[ES.2]', '[ES.3]')
  and cd_gender = '[GEN]' and
  exists (select *
          from store_sales,date_dim, item
          where c.c_customer_sk = ss_customer_sk and
                ss_sold_date_sk = d_date_sk and
                d_year = [YEAR] and
                d_moy between [MONTH] and [MONTH]+3 and
                ss_item_sk = i_item_sk and
                i_category in ('[CATEGORY.1]', '[CATEGORY.2]', '[CATEGORY.3]')
                and ss_sales_price / ss_list_price BETWEEN [DISCOUNT.begin] * 0.01 AND [DISCOUNT.end] * 0.01
                and i_manager_id BETWEEN [MANAGER.begin] and [MANAGER.end]
                ) and
   (exists (select *
            from web_sales,date_dim, item
            where c.c_customer_sk = ws_bill_customer_sk and
                  ws_sold_date_sk = d_date_sk and
                  d_year = [YEAR] and
                  d_moy between [MONTH] ANd [MONTH]+3 and
                  ws_item_sk = i_item_sk and
                  i_category in ('[CATEGORY.1]', '[CATEGORY.2]', '[CATEGORY.3]')
                  and i_manager_id BETWEEN [MANAGER.begin] and [MANAGER.end]
                  and ws_sales_price / ws_list_price BETWEEN [DISCOUNT.begin] * 0.01 AND [DISCOUNT.end] * 0.01
                  ) or
    exists (select *
            from catalog_sales,date_dim, item
            where c.c_customer_sk = cs_ship_customer_sk and
                  cs_sold_date_sk = d_date_sk and
                  d_year = [YEAR] and
                  d_moy between [MONTH] and [MONTH]+3 and
                  cs_item_sk = i_item_sk and
                  i_category in ('[CATEGORY.1]', '[CATEGORY.2]', '[CATEGORY.3]')
                  and i_manager_id BETWEEN [MANAGER.begin] and [MANAGER.end]
                  and cs_sales_price / cs_list_price BETWEEN [DISCOUNT.begin] * 0.01 AND [DISCOUNT.end] * 0.01
                  ))
 group by cd_gender,
          cd_marital_status,
          cd_education_status,
          cd_purchase_estimate,
          cd_credit_rating,
          cd_dep_count,
          cd_dep_employed_count,
          cd_dep_college_count
 order by cd_gender,
          cd_marital_status,
          cd_education_status,
          cd_purchase_estimate,
          cd_credit_rating,
          cd_dep_count,
          cd_dep_employed_count,
          cd_dep_college_count
[_LIMITC];
