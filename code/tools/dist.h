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
#ifndef R_DIST_H
#define R_DIST_H

#define D_NAME_LEN	20

typedef struct DIST_T {
	int *type_vector; // type of value sets.
	int **weight_sets;
	int *maximums; // the sum of the weights per weight set.
	int **value_sets;
	char *strings;
	char *names;
	int	size;
	} dist_t;

typedef struct D_IDX_T {
	char name[D_NAME_LEN + 1];
	int index;
	int nAllocatedLength;
	int nRemainingStrSpace;
	int offset;
	int str_space;
	int name_space;
	int length;
	int w_width;
	int v_width;
	int flags;
	dist_t *dist;
} d_idx_t;

typedef struct DISTINDEX_T {
	int nDistCount;
	int nAllocatedCount;
	d_idx_t *pEntries;
	} distindex_t;

/* must match WriteDist() in dcomp.c */
#define IDX_SIZE	(D_NAME_LEN + 7 * sizeof(int))

void	print_dist(d_idx_t * t);
void	print_dist_index(distindex_t * t);
int	dist_op(void *dest, int op, char *d_name, int vset, int wset, int stream);
int	dist_op_permutation(void *dest, int op, char *d_name, int vset, int wset, int stream, int * pPermutation);
int	dist_op_permutation_with_count(void *dest, int op, char *d_name, int vset, int wset, int stream, int * pPermutation, int count);
#define pick_distribution(dest, dist, v, w, s)	dist_op(dest, 0, dist, v, w, s)
#define pick_distribution_permutation(dest, dist, v, w, s, p) dist_op_permutation(dest, 0, dist, v, w, s, p)
#define pick_distribution_permutation_with_count(dest, dist, v, w, s, p, count) dist_op_permutation_with_count(dest, 0, dist, v, w, s, p, count)
#define dist_member(dest, dist, v, w)		dist_op(dest, 1, dist, v, w, 0)
#define	dist_max(dist, w)		dist->maximums[w - 1]
int distItemCount(char *name);
int dist_weight(int *dest, char *d, int index, int wset);
int distsize(char *szDistname);
int dist_type(char *szDistName, int vset);
d_idx_t *find_dist(char *name);
int IntegrateDist(char *szDistName, int nPct, int nStartIndex, int nWeightSet);
void dump_dist(char *szName);
int dist_active(char *szName, int nWeightSet);
int DistNameIndex(char *szDist, int nNameType, char *szName);
int DistSizeToShiftWidth(char *szDist, int nWeightSet);
int MatchDistWeight(void *dest, char *szDist, int nWeight, int nWeightSet, int ValueSet);
int findDistValue(char *szValue, char *szDistName, int ValueSet);
int di_compare(const void *op1, const void *op2);


#define DIST_UNIFORM		0x0001
#define DIST_EXPONENTIAL	0x0002
#define DIST_EXP_RANK_LOW		0x1024 // The constant should be larger than the widest weight set.
#define DIST_EXP_RANK_HIGH		0x0512 // The constant should be larger than the widest weight set.
#define DIST_NORMAL				0x0256 // The constant should be larger than the widest weight set.
#define DIST_EXP_LAMBDA_HIGH		0.5
#define DIST_EXP_LAMBDA_LOW		0.1
#define DIST_EXP_X_MIN		0.01
#define DIST_EXP_X_MAX		20

/* sales and returns are special; they must match calendar.dst */
#define DIST_SALES			3
#define DIST_RETURNS		5
#define DIST_CHAR			0x0004
#define DIST_INT            0x0008
#define DIST_NAMES_SET		0xff00

/* DistNameIndex needs to know what sort of name we are trying to match */
#define VALUE_NAME			0x0000
#define WEIGHT_NAME			0x0001
#endif /* R_DIST_H */
