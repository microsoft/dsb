#include "config.h"
#include "porting.h"
#include "utility.h"

unsigned int addIntToHash(unsigned int hash, int val)
{
	return (hash * HASH_MULTIPLIER + val) % MAXINT;
}

int intcmp(const void *aa, const void *bb)
{
	const int *a = aa, *b = bb;
	return (*a < *b) ? -1 : (*a > *b);
}

int keycmp(const void *aa, const void *bb)
{
	const ds_key_t *a = aa, *b = bb;
	return (*a < *b) ? -1 : (*a > *b);
}