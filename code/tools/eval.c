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
#include <stdio.h>
#include "genrand.h"
#include "eval.h"
#include "expr.h"
#include "substitution.h"
#include "error_msg.h"
#include "tdefs.h"
#include "tables.h"
#include "build_support.h"
#include "scaling.h"
#include "y.tab.h"
#include "permute.h"
#include "keywords.h"
#include "permute.h"
#include "dcomp.h"
#include "StringBuffer.h"
#include "utility.h"

extern int g_nQueryNumber, g_nStreamNumber;
extern StringBuffer_t *g_sbTemplateName;
extern int g_param_dist;

/*
* Routine: void EvalArithmetic()
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
*/
int
EvalArithmetic(expr_t *pExpr, Expr_Val_t *pValue, Expr_Val_t *pParams)
{
	int nOp;
	char szInteger[16];

	nOp = (int)pExpr->Value.nValue;

	switch(nOp)
	{
	case OP_ADD:
		if (pParams[0].bUseInt & pParams[1].bUseInt)
		{
			pValue->bUseInt	= 1;
			pValue->nValue = pParams[0].nValue  + pParams[1].nValue;
		}
		else
		{
			pValue->bUseInt = 0;
			if (pParams[0].bUseInt)
			{
				sprintf(szInteger, HUGE_FORMAT, pParams[0].nValue);
				AddBuffer(pValue->pBuf, szInteger);
			}
			else
				AddBuffer(pValue->pBuf, GetBuffer(pParams[0].pBuf));
			if (pParams[1].bUseInt)
			{
				sprintf(szInteger, HUGE_FORMAT, pParams[1].nValue);
				AddBuffer(pValue->pBuf, szInteger);
			}
			else
				AddBuffer(pValue->pBuf, GetBuffer(pParams[1].pBuf));
		}
		break;
	case OP_SUBTRACT:
		pValue->bUseInt	= 1;
		pValue->nValue = pParams[0].nValue - pParams[1].nValue;
		break;
	case OP_MULTIPLY:
		pValue->bUseInt	= 1;
		pValue->nValue = pParams[0].nValue * pParams[1].nValue;
		break;
	case OP_DIVIDE:
		pValue->bUseInt	= 1;
		pValue->nValue = pParams[0].nValue / pParams[1].nValue;
		break;
	}

	return(pValue->bUseInt?DT_INT:DT_STR);
}

/*
* Routine: void EvalTextExpr(expr_t *pExpr)
* Purpose: set the values to be used to replace a given tag for this query generation
* Algorithm:
* Data Structures:
*
* Params:
* Returns:
* Called By:
* Calls:
* Assumptions:
* Side Effects:
*/
int
EvalTextExpr(expr_t *pExpr, Expr_Val_t *pBuf, Expr_Val_t *pParams, int bIsParam)
{
	int i,
		j,
		nWeightTotal = 0,
		nModifierArg;
	expr_t *pReplacement;


	switch (pExpr->nFlags & EXPR_FL_SUFFIX_MASK)
	{
	case EXPR_FL_LIST:	/* return a set of values */
		if (bIsParam)
			ReportError(QERR_MODIFIED_PARAM, NULL, 1);
		nModifierArg = (int)pParams[1].nValue;
		for (i=0; i < nModifierArg; i++)
		{
			genrand_integer(&j, DIST_UNIFORM, 1, length(pExpr->ArgList), 0, 0);
			pReplacement = getItem(pExpr->ArgList, j);
			AddBuffer(pBuf[i].pBuf, GetBuffer(pReplacement->Value.pBuf));
			pBuf[i].bUseInt = 0;
			// Update paramter hash.
			//		pExpr->paramHash = addIntToHash(pExpr->paramHash, j);
		}
		break;
	case EXPR_FL_SLIST:	/* return a sorted list of values */
		if (bIsParam)
			ReportError(QERR_MODIFIED_PARAM, NULL, 1);
		nModifierArg = (int)pParams[1].nValue;
		int startIdx = 1; // Ensure the values are generated in a sorted order.
		for (i = 0; i < nModifierArg; i++)
		{
			genrand_integer(&j, DIST_UNIFORM, startIdx, length(pExpr->ArgList), 0, 0);
			pReplacement = getItem(pExpr->ArgList, j);
			AddBuffer(pBuf[i].pBuf, GetBuffer(pReplacement->Value.pBuf));
			pBuf[i].bUseInt = 0;
			startIdx = j;
		}
		break;
	case EXPR_FL_ULIST:     /* return a unique set of values */
		if (bIsParam)
			ReportError(QERR_MODIFIED_PARAM, NULL, 1);
		nModifierArg = (int)pParams[1].nValue;
		pExpr->pPermute = makePermutation(pExpr->pPermute, length(pExpr->ArgList) - 1, 0);
		for (i=0; i < nModifierArg; i++)
		{
			pReplacement = getItem(pExpr->ArgList, getPermutationEntry(pExpr->pPermute, i + 1));
			AddBuffer(pBuf[i].pBuf, GetBuffer(pReplacement->Value.pBuf));
			pBuf[i].bUseInt = 0;
		}
		break;
	case EXPR_FL_SULIST:     /* return a sorted list of unique values */
		if (bIsParam)
			ReportError(QERR_MODIFIED_PARAM, NULL, 1);
		nModifierArg = (int)pParams[1].nValue;
		int * idx = (int *)malloc(nModifierArg * sizeof(int));
		pExpr->pPermute = makePermutation(pExpr->pPermute, length(pExpr->ArgList) - 1, 0);
		// First get all the indexes. Use pBuf[i].bUseInt to store the information.
		for (i = 0; i < nModifierArg; i++)
		{
			idx[i] = getPermutationEntry(pExpr->pPermute, i + 1);
		}
		qsort(idx, nModifierArg, sizeof(int), intcmp);
		// Sort the indexes to ensure the list is sorted.

		for (i = 0; i < nModifierArg; i++)
		{
			pReplacement = getItem(pExpr->ArgList, idx[i]);
			AddBuffer(pBuf[i].pBuf, GetBuffer(pReplacement->Value.pBuf));
			pBuf[i].bUseInt = 0;

			// Update paramter hash.
		//	pExpr->paramHash = addIntToHash(pExpr->paramHash, getPermutationEntry(pExpr->pPermute, i + 1));
		}
		free(idx);
		break;
	case EXPR_FL_RANGE:
	case EXPR_FL_RANGE|EXPR_FL_LIST: /* only list() is permissible here */
	case EXPR_FL_RANGE|EXPR_FL_ULIST: /* only list() is permissible here */
	case EXPR_FL_LIST|EXPR_FL_ULIST: /* only list() is permissible here */
		ReportError(QERR_RANGE_LIST, NULL, 1);
		break;
	default:
		/* 1. find a substitution from the weighted distribtuion */
		for (pReplacement = (expr_t *)getHead(pExpr->ArgList);
		pReplacement;
		pReplacement = (expr_t *)getNext(pExpr->ArgList))
			nWeightTotal += (int)pReplacement->Value.nValue;
		i = genrand_integer(NULL, DIST_UNIFORM, 1, nWeightTotal, 0, 0);
		for (pReplacement = (expr_t *)getHead(pExpr->ArgList);
		pReplacement;
		pReplacement = (expr_t *)getNext(pExpr->ArgList))
		{
			if (i <= (int)pReplacement->Value.nValue)
				break;
			i -= (int)pReplacement->Value.nValue;
		}

		/* 2. get the appropraite string */
		AddBuffer(pBuf->pBuf, GetBuffer(pReplacement->Value.pBuf));

		// Update paramter hash.
		//pExpr->paramHash = addIntToHash(pExpr->paramHash, (int)pReplacement->Value.nValue);

		break;
	}

	return(DT_STR);
}


/*
* Routine: int EvalRandomExpr(expr_t *pExpr, Expr_Val_t *pBuf, Expr_Val_t *pParams, int bIsParam)
* Purpose: set the values to be used to replace a given tag for this query generation
* Algorithm:
* Data Structures:
*
* Params:
* Returns:
* Called By:
* Calls:
* Assumptions:
* Side Effects:
* TODO:
*/
int
EvalRandomExpr(expr_t *pExpr, Expr_Val_t *pBuf, Expr_Val_t *pParams, int bIsParam)
{
	ds_key_t nMin,
		nMax,
		nTotal,
      		nTemp;
	int nModifierArg,
		i,
		nDirection,
		nDistribution;

	nMin = pParams->nValue;
	nMax = pParams[1].nValue;
	nDistribution = (int)pParams[2].nValue;

	if (is_set("VERBOSE"))
		printf("parameter: min %d, max %d\n", (int)nMin, (int)nMax);
	switch (pExpr->nFlags & EXPR_FL_SUFFIX_MASK)
	{
	case EXPR_FL_LIST:	/* return a set of unique values */
		if (bIsParam)
			ReportError(QERR_MODIFIED_PARAM, NULL, 1);
		nModifierArg = (int)pParams[3].nValue;
		for (i = 0; i < nModifierArg; i++)
		{
			genrand_key(&nTemp, DIST_UNIFORM, nMin, nMax, 0, 0);
			pBuf[i].nValue = (nTemp % (nMax - nMin + 1)) + nMin;
			pBuf[i].bUseInt = 1;
			printf("[DEBUG] EvalRandomExpr: list nTemp %lld, value %lld\n", nTemp, pBuf[i].nValue);
		}
		break;
	case EXPR_FL_SLIST:	/* return a sorted list of values */
		if (bIsParam)
			ReportError(QERR_MODIFIED_PARAM, NULL, 1);
		nModifierArg = (int)pParams[3].nValue;
		ds_key_t startIdx = nMin;
		for (i = 0; i < nModifierArg; i++)
		{
			genrand_key(&nTemp, DIST_UNIFORM, startIdx, nMax, 0, 0);
			pBuf[i].nValue = (nTemp % (nMax - nMin + 1)) + nMin;
			pBuf[i].bUseInt = 1;
			printf("[DEBUG] EvalRandomExpr: slist nTemp %lld, startIdx %lld, value %lld\n", nTemp, startIdx, pBuf[i].nValue);
			startIdx = nTemp;
		}
		break;
	case EXPR_FL_ULIST:	/* return a set of unique values */
		if (bIsParam)
			ReportError(QERR_MODIFIED_PARAM, NULL, 1);
		nModifierArg = (int)pParams[3].nValue;
		pExpr->pPermuteKey = makeKeyPermutation(pExpr->pPermuteKey, nMax - nMin + 1, 0);
		/*
		 * the permutation is controlled by the number of values that are needed
		 * once it is populated, than adjust the returned result based on the range of values that is permissible
		 */
		for (i = 0; i < nModifierArg; i++)
		{
			pBuf[i].nValue = (getPermutationEntry(pExpr->pPermuteKey, i + 1) % (nMax - nMin + 1)) + nMin;
			pBuf[i].bUseInt = 1;
		}
		break;
	case EXPR_FL_SULIST:	/* return a sorted list of unique values */
		if (bIsParam)
			ReportError(QERR_MODIFIED_PARAM, NULL, 1);
		nModifierArg = (int)pParams[3].nValue;
		pExpr->pPermuteKey = makeKeyPermutation(pExpr->pPermuteKey, nMax - nMin + 1, 0);
		// First get all the numbers.
		ds_key_t * idx = (ds_key_t *)malloc(sizeof(ds_key_t) * nModifierArg);
		for (i = 0; i < nModifierArg; i++)
		{
			idx[i] = (getPermutationEntry(pExpr->pPermuteKey, i + 1) % (nMax - nMin + 1)) + nMin;
		}
		qsort(idx, nModifierArg, sizeof(ds_key_t), keycmp);

		/*
		 * the permutation is controlled by the number of values that are needed
		 * once it is populated, than adjust the returned result based on the range of values that is permissible
		 */
		for (i = 0; i < nModifierArg; i++)
		{
			pBuf[i].nValue = idx[i];
			pBuf[i].bUseInt = 1;
		}
		free(idx);
		break;
	case EXPR_FL_RANGE:	/* return end points of a range */
		if (bIsParam)
			ReportError(QERR_MODIFIED_PARAM, NULL, 1);
		nModifierArg = (int)pParams[3].nValue;

		genrand_key(&nTemp, DIST_UNIFORM, nMin, nMax, nDistribution, 0);
		pBuf->nValue = nTemp;
		pBuf->bUseInt = 1;
		pBuf[1].nValue = pBuf->nValue;
		pBuf[1].bUseInt = 1;

		nDirection = 1;
		nTotal = nMax - nMin;
		nTotal *= nModifierArg;
		nTotal /= 100;

		while (nTotal)
		{
			if (nDirection == 1)
			{
				pBuf[1].nValue += 1;
				nTotal -= 1;
				if (pBuf[1].nValue == nMax)
					nDirection = -1;
			}
			else
			{
				pBuf->nValue -= 1;
				nTotal -= 1;
			}
		}
		break;
	case EXPR_FL_RANGE|EXPR_FL_LIST:	/* cannot use them both */
	case EXPR_FL_RANGE|EXPR_FL_ULIST:	/* cannot use them both */
	case EXPR_FL_LIST|EXPR_FL_ULIST:	/* cannot use them both */
		ReportError(QERR_RANGE_LIST, NULL, 1);
		break;
	default:
		genrand_key(&nTemp, DIST_UNIFORM, nMin, nMax, nDistribution, 0);
		pBuf->nValue = nTemp;
		pBuf->bUseInt = 1;
		break;
	}


	return(DT_INT);
}

/*
* Routine: EvalRownCountExpr(expr_t *pExpr, StringBuffer_t *pBuf);
* Purpose: set the values to be used to replace a given tag for this query generation
* Algorithm:
* Data Structures:
*
* Params:
* Returns:
* Called By:
* Calls:
* Assumptions:
* Side Effects:
* TODO:
*/
int
EvalRownCountExpr(expr_t *pExpr, Expr_Val_t *pBuf, Expr_Val_t *pParams)
{
	char szBuf[20],
	   szTable[40],
      *szName;
	int i;

	szName = GetBuffer(pParams->pBuf);

	if (pExpr->nFlags & EXPR_FL_TABLENAME)
	{
      for (i=1; i <= distsize("rowcounts"); i++)
      {
         dist_member(szTable, "rowcounts", i, 1);
         if (strcasecmp(szTable, szName) == 0)
            break;
      }
      if (i > distsize("rowcounts"))
         ReportError(QERR_BAD_NAME, szName, 1);
      sprintf(szBuf, HUGE_FORMAT, get_rowcount(i));
	}
	else
		sprintf(szBuf, "%d", distsize(szName));
	AddBuffer(pBuf->pBuf, szBuf);

	return(DT_INT);
}

/*
* Routine: EvalDistopExpr(expr_t *pExpr, StringBuffer_t *pBuf);
* Purpose: set the values to be used to replace a given tag for this query generation
* Algorithm:
* Data Structures:
*
* Params:
* Returns:
* Called By:
* Calls:
* Assumptions:
* Side Effects:
* TODO:
*/
int
EvalDistExpr(expr_t *pExpr, Expr_Val_t *pBuf, Expr_Val_t *pParams, int bIsParam)
{
	char *szName,
		*pChar = NULL;
	int nRow,
		nCol,
		nDataType,
		nOffset,
		nModifierArg,
		i, j, k,
		nCount,
      nTemp;

	szName = GetBuffer(pParams->pBuf);
	if (pParams[1].bUseInt)
		nRow = (int)pParams[1].nValue;
	else
		nRow = DistNameIndex(szName, VALUE_NAME, GetBuffer(pParams[1].pBuf));
	// Set the weight set for Gaussian distribution.
	if (g_param_dist == DIST_NORMAL && pParams[2].bUseInt
		// Look up the value of a value set.
		&& pExpr->Value.nValue != KW_DISTMEMBER) {
		// Assume the Gaussian distribution has been populated in the last weight set using dcomp.
		nCol = find_dist(szName)->w_width; // base index starts at 1.
		if (is_set("VERBOSE"))
			printf("EvalDistExpr: dist name %s, weight col %d, last weight %d\n", szName, nCol, find_dist(szName)->dist->weight_sets[nCol - 1]);
	}
	else if (pParams[2].bUseInt)
		nCol = (int)pParams[2].nValue;
	else
		nCol = DistNameIndex(szName, WEIGHT_NAME, GetBuffer(pParams[2].pBuf));

	if (is_set("VERBOSE"))
		printf("parameter: szName %s, size %d, expr->value.nValue %I64d, nRow %d, useInt1 %d, nCol %d, useInt2 %d\n", szName, distsize(szName),
		pExpr->Value.nValue, nRow, pParams[1].bUseInt, nCol, pParams[2].bUseInt);
	switch(pExpr->Value.nValue)
	{
	case KW_DISTMEMBER:
		nDataType =
			(dist_type(szName, nCol) == TKN_INT)?DT_INT:DT_STR;
		if (nDataType == DT_STR)
		{
			dist_member(&pChar, szName, nRow, nCol);
			AddBuffer(pBuf->pBuf, pChar);
			if (is_set("VERBOSE")) {
				printf("distmember: %s\n", GetBuffer(pBuf->pBuf));
			}
		}
		else
		{
			dist_member(&nTemp, szName, nRow, nCol);
			pBuf->nValue = nTemp;
			pBuf->bUseInt = 1;
		}
		break;
	case KW_DISTWEIGHT:
		dist_weight(&nTemp, szName, nRow, nCol);
		pBuf->nValue = nTemp;
		pBuf->bUseInt = 1;
		nDataType = DT_INT;
		break;
	default:	/* regular call to DIST() */
		nDataType =	(dist_type(szName, nRow) == TKN_INT)?DT_INT:DT_STR;
		switch (pExpr->nFlags & EXPR_FL_SUFFIX_MASK)
		{
		case EXPR_FL_RANGE:
			if (bIsParam)
				ReportError(QERR_MODIFIED_PARAM, NULL, 1);
			nModifierArg = (int)pParams[3].nValue;
			i = pick_distribution(NULL, szName, nRow, nCol, 0);
			if (is_set("VERBOSE")) {
				printf("value %d\n", i);
			}
			nOffset = IntegrateDist(szName, nModifierArg, i, nCol);
			if (nDataType == DT_INT)
			{
				pBuf->bUseInt = 1;
				dist_member(&nTemp, szName, i, nRow);
				pBuf->nValue = nTemp;
				dist_member(&nTemp, szName, nOffset, nRow);
				pBuf[1].nValue = nTemp;
			}
			else
			{
				dist_member(pChar, szName, i, nRow);
				AddBuffer(pBuf->pBuf, pChar);
				dist_member(pChar, szName, nOffset, nRow);
				AddBuffer(pBuf[1].pBuf, pChar);
			}
			break;
		case EXPR_FL_LIST:
			if (bIsParam)
				ReportError(QERR_MODIFIED_PARAM, NULL, 1);
			nModifierArg = (int)pParams[3].nValue;

			/* pick n entries */
			for (i = 0; i < nModifierArg; ++i)
			{
				if (nDataType == DT_INT)
				{
					pick_distribution(&nTemp, szName, nRow, nCol, 0);
					pBuf[i].nValue = nTemp;
					pBuf[i].bUseInt = 1;
				}
				else
				{
					pick_distribution(&pChar, szName, nRow, nCol, 0);
					AddBuffer(pBuf[i].pBuf, pChar);
				}
			}

			if (is_set("VERBOSE"))
			{
				printf("list: ");
				if (nDataType == DT_INT)
				{
					for (i = 0; i < nModifierArg; ++i)
					{
						printf("%d, ", pBuf[i].nValue);
					}
				}
				else
				{
					for (i = 0; i < nModifierArg; ++i)
					{
						printf("%s, ", GetBuffer(pBuf[i].pBuf));
					}
				}
				printf("\n");
			}
			break;
		case EXPR_FL_SLIST: // return a list of sorted values.
			if (bIsParam)
				ReportError(QERR_MODIFIED_PARAM, NULL, 1);
			nModifierArg = (int)pParams[3].nValue;

			/* pick n entries */
			for (i = 0; i < nModifierArg; ++i)
			{
				if (nDataType == DT_INT)
				{
					pick_distribution(&nTemp, szName, nRow, nCol, 0);
					pBuf[i].nValue = nTemp;
					pBuf[i].bUseInt = 1;
				}
				else
				{
					pick_distribution(&pChar, szName, nRow, nCol, 0);
					AddBuffer(pBuf[i].pBuf, pChar);
				}
			}

			if (nDataType == DT_INT)
			{
				SortBufInt(pBuf, nModifierArg);
			}
			else
			{
				SortBufStr(pBuf, nModifierArg);
			}

			if (is_set("VERBOSE"))
			{
				printf("sorted list: ");
				if (nDataType == DT_INT)
				{
					for (i = 0; i < nModifierArg; ++i)
					{
						printf("%d, ", pBuf[i].nValue);
					}
				}
				else
				{
					for (i = 0; i < nModifierArg; ++i)
					{
						printf("%s, ", GetBuffer(pBuf[i].pBuf));
					}
				}
				printf("\n");
			}
			break;
		case EXPR_FL_ULIST: /* exclude duplicates from the returned list */
			if (bIsParam)
				ReportError(QERR_MODIFIED_PARAM, NULL, 1);
			nModifierArg = (int)pParams[3].nValue;

			if (nModifierArg > distsize(szName))
				ReportError(QERR_RANGE_ERROR, "", 1);

			/* get n unique entries */
			i = 0;
			while (i < nModifierArg)
			{
				int duplicate = 0;
				if (nDataType == DT_INT)
				{
					pick_distribution(&nTemp, szName, nRow, nCol, 0);
					for (k = 0; k < i; ++k)
					{
						if (pBuf[k].nValue == nTemp)
						{
							duplicate = 1;
							break;
						}
					}
					if (!duplicate)
					{
						pBuf[i].nValue = nTemp;
						pBuf[i].bUseInt = 1;
						++i;
					}
				}
				else
				{
					pick_distribution(&pChar, szName, nRow, nCol, 0);
					for (k = 0; k < i; ++k)
					{
						if (strcmp(GetBuffer(pBuf[k].pBuf), pChar) == 0)
						{
							duplicate = 1;
							break;
						}
					}
					if (!duplicate)
					{
						AddBuffer(pBuf[i].pBuf, pChar);
						++i;
					}
				}
			}

			if (is_set("VERBOSE"))
			{
				printf("unique list: ");
				if (nDataType == DT_INT)
				{
					for (i = 0; i < nModifierArg; ++i)
					{
						printf("%d, ", pBuf[i].nValue);
					}
				}
				else
				{
					for (i = 0; i < nModifierArg; ++i)
					{
						printf("%s, ", GetBuffer(pBuf[i].pBuf));
					}
				}
				printf("\n");
			}
			break;
		case EXPR_FL_SULIST: /* exclude duplicates from the returned sorted list */
			if (bIsParam)
				ReportError(QERR_MODIFIED_PARAM, NULL, 1);
			nModifierArg = (int)pParams[3].nValue;

			/* permute it */
			if (nModifierArg > distsize(szName))
				ReportError(QERR_RANGE_ERROR, "", 1);

			/* get n unique entries */
			i = 0;
			while (i < nModifierArg)
			{
				int duplicate = 0;
				if (nDataType == DT_INT)
				{
					pick_distribution(&nTemp, szName, nRow, nCol, 0);
					for (k = 0; k < i; ++k)
					{
						if (pBuf[k].nValue == nTemp)
						{
							duplicate = 1;
							break;
						}
					}
					if (!duplicate)
					{
						pBuf[i].nValue = nTemp;
						++i;
					}
				}
				else
				{
					pick_distribution(&pChar, szName, nRow, nCol, 0);
					for (k = 0; k < i; ++k)
					{
						if (strcmp(GetBuffer(pBuf[k].pBuf), pChar) == 0)
						{
							duplicate = 1;
							break;
						}
					}
					if (!duplicate)
					{
						AddBuffer(pBuf[i].pBuf, pChar);
						++i;
					}
				}
			}
			if (nDataType == DT_INT)
			{
				SortBufInt(pBuf, nModifierArg);
			}
			else
			{
				SortBufStr(pBuf, nModifierArg);
			}

			if (is_set("VERBOSE"))
			{
				printf("sorted unique list: ");
				if (nDataType == DT_INT)
				{
					for (i = 0; i < nModifierArg; ++i)
					{
						printf("%d, ", pBuf[i].nValue);
					}
				}
				else
				{
					for (i = 0; i < nModifierArg; ++i)
					{
						printf("%s, ", GetBuffer(pBuf[i].pBuf));
					}
				}
				printf("\n");
			}
			break;
		case EXPR_FL_LIST | EXPR_FL_RANGE:
		case EXPR_FL_ULIST | EXPR_FL_RANGE:
		case EXPR_FL_ULIST | EXPR_FL_LIST:
			ReportError(QERR_RANGE_LIST, NULL, 1);
			break;
		default:
			if (nDataType == DT_STR)
			{
				pick_distribution(&pChar, szName, nRow, nCol, 0);
				AddBuffer(pBuf->pBuf, pChar);
			}
			else
			{
				pick_distribution(&nTemp,  szName, nRow, nCol, 0);
				pBuf->nValue = nTemp;
				pBuf->bUseInt = 1;
			}
			break;
		}	/* end of generic DIST() switch case */
		break;
	}

	return(nDataType);
}


/*
* Routine: void EvalDateExpr(expr_t *pExpr, StringBuffer_t *pBuf)
* Purpose: set the values to be used to replace a given tag for this query generation
* Algorithm:
* Data Structures:
*
* Params:
* Returns:
* Called By:
* Calls:
* Assumptions:
* Side Effects:
* TODO:
*/
int
EvalDateExpr(expr_t *pExpr, Expr_Val_t *pBuf, Expr_Val_t *pParams, int bIsParam)
{
	date_t dBegin,
		dEnd,
		dResult;
	int nDay,
		nDay2,
		nDistributionType,
		nModifierArg,
		i, j,
		*pPermute = NULL,
		nTotal = 0,
		nDirection;

	/* pull the parameters from pParams */
	strtodt(&dBegin, GetBuffer(pParams->pBuf));
	strtodt(&dEnd, GetBuffer(pParams[1].pBuf));
	nDistributionType = pParams[2].nValue;

	if (is_set("VERBOSE"))
		printf("parameter: begin date %d, end date %d\n", dBegin.julian, dEnd.julian);
	/* and then check to see if more are required */
	switch (pExpr->nFlags & EXPR_FL_SUFFIX_MASK)
	{
	case EXPR_FL_LIST:	/* return a set of values */
		if (bIsParam)
			ReportError(QERR_MODIFIED_PARAM, NULL, 1);
		nModifierArg = pParams[3].nValue;
		nTotal = dEnd.julian - dBegin.julian;
		if (nModifierArg > nTotal)
		{
			nModifierArg = nTotal;
			ReportError(QERR_RANGE_OVERRUN, NULL, 0);
		}
		for (i=0; i < nModifierArg; i++)
		{
         		genrand_integer(&j, DIST_UNIFORM, 1, nTotal, 0, 0);
			jtodt(&dResult, dBegin.julian + j - 1);
			AddBuffer(pBuf[i].pBuf, dttostr(&dResult));


		}
		break;
	case EXPR_FL_SLIST:	/* return a list of sorted values */
		if (bIsParam)
			ReportError(QERR_MODIFIED_PARAM, NULL, 1);
		nModifierArg = pParams[3].nValue;
		nTotal = dEnd.julian - dBegin.julian;
		if (nModifierArg > nTotal)
		{
			nModifierArg = nTotal;
			ReportError(QERR_RANGE_OVERRUN, NULL, 0);
		}
		int startIdx = 1;
		for (i = 0; i < nModifierArg; i++)
		{
			genrand_integer(&j, DIST_UNIFORM, startIdx, nTotal, 0, 0);
			jtodt(&dResult, dBegin.julian + j - 1);
			AddBuffer(pBuf[i].pBuf, dttostr(&dResult));
			startIdx = j;
		}
		break;
	case EXPR_FL_ULIST:	/* return a unique set of values */
		if (bIsParam)
			ReportError(QERR_MODIFIED_PARAM, NULL, 1);
		nModifierArg = pParams[3].nValue;
		i = dBegin.julian - dBegin.julian;
		if (nModifierArg > i)
		{
			nModifierArg = i;
			ReportError(QERR_RANGE_OVERRUN, NULL, 0);
			pPermute = makePermutation(pPermute, i, 0);
		}
		for (i=0; i < nModifierArg; i++)
		{
			jtodt(&dResult, dBegin.julian + getPermutationEntry(pPermute, i + 1) - 1);
			AddBuffer(pBuf[i].pBuf, dttostr(&dBegin));
		}
		free(pPermute);
		break;
	case EXPR_FL_SULIST:	/* return a list of sorted unique values */
		if (bIsParam)
			ReportError(QERR_MODIFIED_PARAM, NULL, 1);
		nModifierArg = pParams[3].nValue;
		i = dBegin.julian - dBegin.julian;
		if (nModifierArg > i)
		{
			nModifierArg = i;
			ReportError(QERR_RANGE_OVERRUN, NULL, 0);
			pPermute = makePermutation(pPermute, i, 0);
		}
		int * idx = (int *)malloc(sizeof(int) * nModifierArg);
		for (i = 0; i < nModifierArg; i++)
		{
			idx[i] = getPermutationEntry(pPermute, i + 1);
		}
		qsort(idx, nModifierArg, sizeof(int), intcmp);

		for (i = 0; i < nModifierArg; i++)
		{
			jtodt(&dResult, dBegin.julian + idx[i] - 1);
			AddBuffer(pBuf[i].pBuf, dttostr(&dBegin));
		}
		free(pPermute);
		free(idx);
		break;
	case EXPR_FL_RANGE:	/* return end points of a range */
		if (bIsParam)
			ReportError(QERR_MODIFIED_PARAM, NULL, 1);
		nModifierArg = pParams[3].nValue;

		for (i=dBegin.julian; i < dEnd.julian; i++)
			nTotal += getDateWeightFromJulian(i, nDistributionType);
		nTotal *= nModifierArg;
		nTotal /= 100;

		genrand_date(&dResult, nDistributionType, &dBegin, &dEnd, NULL, 0);
		nDay = dResult.julian;
		nDay2 = nDay;

		nDirection = 1;
		while (nTotal > 0)
		{
			if (nDirection == 1)
			{
				nDay2 += 1;
				nTotal -= getDateWeightFromJulian(nDay2, nDistributionType);
				if (nDay2 == dEnd.julian)
					nDirection = -1;
			}
			else
			{
				nDay -= 1;
				nTotal -= getDateWeightFromJulian(nDay, nDistributionType);
			}
		}

		jtodt(&dResult, nDay);
		AddBuffer(pBuf->pBuf, dttostr(&dResult));
		jtodt(&dResult, nDay2);
		AddBuffer(pBuf[1].pBuf , dttostr(&dResult));
		break;
	case EXPR_FL_RANGE|EXPR_FL_LIST:	/* cannot use them both */
	case EXPR_FL_RANGE|EXPR_FL_ULIST:	/* cannot use them both */
	case EXPR_FL_ULIST|EXPR_FL_LIST:	/* cannot use them both */
		ReportError(QERR_RANGE_LIST, NULL, 1);
		break;
	default:
		/* just do "normal" random date with a single return value */
		genrand_date(&dResult, nDistributionType, &dBegin, &dEnd, NULL, 0);
		AddBuffer(pBuf->pBuf, dttostr(&dResult));
		pBuf->bUseInt = 0;
		break;
	}


	return(DT_DATE);
}

	/*
	* Routine: void EvalKeywordExpr(expr_t *pExpr, StringBuffer_t *pBuf)
	* Purpose: set the values to be used to replace a given tag for this query generation
	* Algorithm:
	* Data Structures:
	*
	* Params:
	* Returns:
	* Called By:
	* Calls:
	* Assumptions:
	* Side Effects:
	* TODO:
	*/
	int
	EvalKeywordExpr(expr_t *pExpr, Expr_Val_t *pV)
	{
		char szMessage[1024];
		char *cp;
		substitution_t *pSub;

		switch (pExpr->Value.nValue)
		{
		case KW_QUERY:
			pV->nValue = g_nQueryNumber;
			pV->bUseInt = 1;
			break;
		case KW_TEMPLATE:
			AddBuffer(pV->pBuf, GetBuffer(g_sbTemplateName));
			pV->bUseInt = 0;
			break;
		case KW_STREAM:
			pV->nValue = g_nStreamNumber;
			pV->bUseInt = 1;
			break;
		case KW_SEED:
			pV->nValue = Streams[0].nSeed;
			pV->bUseInt = 1;
			break;
		case KW_SALES:
			pV->nValue = DIST_SALES;
			pV->bUseInt = 1;
			break;
		case KW_RETURNS:
			pV->nValue = DIST_RETURNS;
			pV->bUseInt = 1;
			break;
		case KW_UNIFORM:
			pV->nValue = DIST_UNIFORM;
			pV->bUseInt = 1;
			break;
		case KW_LIMIT:
			pV->nValue = atoi(GetBuffer(pExpr->Value.pBuf));
			pV->bUseInt = 1;
         break;
		case KW_LIMITA:
		case KW_LIMITB:
		case KW_LIMITC:
			sprintf(szMessage, "__LIMIT%c", (int)pExpr->Value.nValue - KW_LIMITA + 'A');
			pSub = findSubstitution(pCurrentQuery, szMessage, 0);
         EvalExpr(pSub->pAssignment, pV, 0, g_nQueryNumber);
         if (strlen(cp = GetBuffer(pV->pBuf)))
            {
            if (strchr(cp, '%'))
               {
               pSub = findSubstitution(pCurrentQuery, "_LIMIT", 0);
               sprintf(szMessage, GetBuffer(pV->pBuf), atoi(GetBuffer(pSub->pAssignment->Value.pBuf)));
               ResetBuffer(pV->pBuf);
               AddBuffer(pV->pBuf, szMessage);
               }
            }
			break;
		default:
			ReportError(QERR_SYNTAX, NULL, 1);
			break;
		}

		return((pV->bUseInt)?EXPR_FL_INT:EXPR_FL_CHAR);
	}


	/*
	* Routine: EvalExpr(expr_t *)
	* Purpose: return the value of the expression as a string
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
	EvalExpr(expr_t *pExpr, Expr_Val_t *pValue, int bIsParam, int nQueryNumber)
	{
		int i,
			nDataType = 0,
			nArgCnt,
			nUseCount;
		expr_t *pArg;
		substitution_t *pSub;
		Expr_Val_t arParams[MAX_ARGS],
			*pExistingValue;

		for (i=0; i < MAX_ARGS; i++)
		{
			memset(&arParams[i], 0, sizeof(struct EXPR_VAL_T));
			arParams[i].pBuf = InitBuffer(10, 10);
		}

		if (pExpr->Value.pBuf == NULL)
			pExpr->Value.pBuf = InitBuffer(15, 15);

		/* handle the constants */
		if (pExpr->nFlags & EXPR_FL_CONST)
		{
			switch(i = pExpr->nFlags & EXPR_TYPE_MASK )
			{
			case EXPR_FL_INT|EXPR_FL_KEYWORD:
			case EXPR_FL_CHAR|EXPR_FL_KEYWORD:
				nDataType = EvalKeywordExpr(pExpr, pValue);
				break;
			case EXPR_FL_INT:
				pValue->nValue = pExpr->Value.nValue;
				nDataType = EXPR_FL_INT;
				pValue->bUseInt = 1;
				break;
			case EXPR_FL_CHAR:
				AddBuffer(pValue->pBuf, GetBuffer(pExpr->Value.pBuf));
				nDataType = EXPR_FL_CHAR;
				pValue->bUseInt = 0;
				break;
			default:
				fprintf(stderr, "INTERNAL ERROR: unknown constant type %d\n", i);
				exit(1);
			}

			pValue->nQueryNumber = nQueryNumber;
			return(nDataType);
		}
      /* expressions get evaluated once per query; test is done here
         to avoid a problem with constant values (e.g., LIMITB)
      */
		if (pValue->nQueryNumber == nQueryNumber)
			return(pValue->bUseInt?DT_INT:DT_STR);

		/* handle the parameterized expressions */
		switch(pExpr->nFlags & EXPR_FUNC_MASK)
		{
		case EXPR_FL_REPL:
			pValue->nValue = pExpr->Value.nValue;
			AddBuffer(pValue->pBuf, GetBuffer(pExpr->Value.pBuf));
			nDataType = EXPR_FL_CHAR;
			break;
		case EXPR_FL_SUBST:
			pSub = findSubstitution(pCurrentQuery, GetBuffer(pExpr->Value.pBuf), &nUseCount);
			if (pSub == NULL)
				ReportError(QERR_BAD_NAME, GetBuffer(pExpr->Value.pBuf), 1);
			if (pSub->nQueryNumber != nQueryNumber)	/* we've not set a value; do so*/
			{
				pSub->nDataType = EvalExpr(pSub->pAssignment, pSub->arValues, 0, nQueryNumber);
			}
			/*
			pExistingValue = pSub->arValues;
			pExistingValue += pSub->nSubParts * (nUseCount - 1);
			*/
			pExistingValue = &pSub->arValues[pExpr->nSubElement - 1];
			memcpy(pValue, pExistingValue, sizeof(struct EXPR_VAL_T));
			if (pExistingValue->bUseInt)
				nDataType = DT_INT;
			else
				nDataType = DT_CHR;
			pSub->nQueryNumber = nQueryNumber;
			break;
		case EXPR_FL_FUNC:
		/* walk the argument list and put them in the appropriate arXXXArgs location
		* based on data type
			*/
			nArgCnt = 0;
			for (pArg = (expr_t *)getHead(pExpr->ArgList); pArg; pArg = (expr_t *)getNext(pExpr->ArgList))
			{
				if (nArgCnt >= MAX_ARGS)
					ReportError(QERR_ARG_OVERFLOW, NULL, 1);
				ResetBuffer(arParams[nArgCnt].pBuf);
				if (EvalExpr(pArg, &arParams[nArgCnt], 1, nQueryNumber) == DT_INT)
					arParams[nArgCnt].bUseInt = 1;
				nArgCnt += 1;

			}

			/* invoke each function */
			switch(pExpr->Value.nValue)
			{
			case KW_TEXT:
				nDataType = EvalTextExpr(pExpr, pValue, arParams, bIsParam);
				break;
			case KW_DATE:
				nDataType = EvalDateExpr(pExpr, pValue, arParams, bIsParam);
				break;
			case KW_DISTWEIGHT:
			case KW_DISTMEMBER:
			case KW_DIST:
				nDataType = EvalDistExpr(pExpr, pValue, arParams, bIsParam);
				break;
			case KW_RANDOM:
				nDataType = EvalRandomExpr(pExpr, pValue, arParams, bIsParam);
				break;
			case OP_ADD:
			case OP_SUBTRACT:
			case OP_MULTIPLY:
			case OP_DIVIDE:
				nDataType = EvalArithmetic(pExpr, pValue, arParams);
				break;
			default:
				ReportError(QERR_BAD_NAME, KeywordText((int)pExpr->Value.nValue), 1);
				break;
			}
			break;
			default:
				fprintf(stderr, "INTERNAL ERROR: unknown expression type %x\n", pExpr->nFlags);
				exit(1);
		}

		pValue->nQueryNumber = nQueryNumber;
		return(nDataType);

}