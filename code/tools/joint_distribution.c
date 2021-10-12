#include <stdio.h>
#include "genrand.h"
#include "joint_distribution.h"
#include "permute.h"
#include "r_params.h"

#define JOINT_DISTRIBUTION_BUCKET_COUNT 100

/*
* Add the attribute of a key. The attribute id is 1-based index.
*/
void updateAttributeKeyRecord(struct ATTRIBUTE_KEY_RECORD * record, int attribute_id)
{
	if (record->firstKey[attribute_id - 1] == -1)
	{
		record->firstKey[attribute_id - 1] = record->curKeyCount;
	}
	if (record->curKey[attribute_id - 1] != -1)
	{
		record->nextKey[record->curKey[attribute_id - 1]] = record->curKeyCount;
	}
	record->curKey[attribute_id - 1] = record->curKeyCount;
	++record->attributeKeyCount[attribute_id - 1];
	++record->curKeyCount;
}

/*
* Add the attribute of a key. The attribute id is 1-based index.
* Only update counts to keep track of selectivity.
*/
void updateAttributeKeyRecordCountOnly(struct ATTRIBUTE_KEY_RECORD * record, int attribute_id)
{
	++record->attributeKeyCount[attribute_id - 1];
	++record->curKeyCount;
}

/*
* Find the attribute ID of the attribute value. If the value does not exist, add it
* to the list.
* The attribute ID starts with 1.
*/
int searchAttributeId(struct ATTRIBUTE_KEY_RECORD * record, char * attribute_value)
{
	for (int i = 0; i < record->attributeCount; ++i) {
		if (strcmp(attribute_value, record->attributeValue[i]) == 0) {
			return i + 1;
		}
	}
	int len = strlen(attribute_value);
	record->attributeValue[record->attributeCount] = (char *)malloc((len + 1) * sizeof(char));
	MALLOC_CHECK(record->attributeValue[record->attributeCount]);
	strcpy(record->attributeValue[record->attributeCount], attribute_value);
	++record->attributeCount;
	return record->attributeCount;
}

/*
* Add the attribute of a key. The attribute value is a string.
*/
void updateCharAttributeKeyRecord(struct ATTRIBUTE_KEY_RECORD * record, char * attribute_value)
{
	int attribute_id = searchAttributeId(record, attribute_value);
	updateAttributeKeyRecord(record, attribute_id);
}

/*
* Initialize the attribute key record with string attribute values, i.e., state.
*/
struct ATTRIBUTE_KEY_RECORD * initializeCharAttributeKeyRecord(int maxAttributeCount, int keyCount)
{
	struct ATTRIBUTE_KEY_RECORD * record;
	record = (struct ATTRIBUTE_KEY_RECORD *)malloc(sizeof(struct ATTRIBUTE_KEY_RECORD));
	MALLOC_CHECK(record);

	record->maxAttributeCount = maxAttributeCount;
	record->attributeCount = 0;
	record->keyCount = keyCount;
	record->curKeyCount = 0;

	record->attributeKeyCount = (int *)malloc(record->maxAttributeCount * sizeof(int));
	MALLOC_CHECK(record->attributeKeyCount);
	memset(record->attributeKeyCount, 0, record->maxAttributeCount * sizeof(int));

	record->attributeValue = (char **)malloc(record->maxAttributeCount * sizeof(char *));
	MALLOC_CHECK(record->attributeValue);
	memset(record->attributeKeyCount, 0, record->maxAttributeCount * sizeof(char *));

	record->firstKey = (ds_key_t *)malloc(record->maxAttributeCount * sizeof(ds_key_t));
	MALLOC_CHECK(record->firstKey);
	memset(record->firstKey, 0, record->maxAttributeCount * sizeof(ds_key_t));
	for (int i = 0; i < record->maxAttributeCount; ++i)
		record->firstKey[i] = -1;

	record->curKey = (ds_key_t *)malloc(record->maxAttributeCount * sizeof(ds_key_t));
	MALLOC_CHECK(record->curKey);
	memset(record->curKey, 0, record->maxAttributeCount * sizeof(ds_key_t));
	for (int i = 0; i < record->maxAttributeCount; ++i)
		record->curKey[i] = -1;

	record->nextKey = (ds_key_t *)malloc(record->keyCount * sizeof(ds_key_t));
	MALLOC_CHECK(record->nextKey);
	memset(record->nextKey, 0, record->keyCount * sizeof(ds_key_t));
	for (int i = 0; i < record->keyCount; ++i)
		record->nextKey[i] = -1;

	return record;
}

/*
* Space allocation for attribute key record.
*/
struct ATTRIBUTE_KEY_RECORD * initializeAttributeKeyRecord(int attributeCount, int keyCount)
{
	struct ATTRIBUTE_KEY_RECORD * record;
	record = (struct ATTRIBUTE_KEY_RECORD *)malloc(sizeof(struct ATTRIBUTE_KEY_RECORD));
	MALLOC_CHECK(record);

	record->attributeCount = attributeCount;
	record->keyCount = keyCount;
	record->curKeyCount = 0;

	record->attributeKeyCount = (int *)malloc(record->attributeCount * sizeof(int));
	MALLOC_CHECK(record->attributeKeyCount);
	memset(record->attributeKeyCount, 0, record->attributeCount * sizeof(int));

	record->firstKey = (ds_key_t *)malloc(record->attributeCount * sizeof(ds_key_t));
	MALLOC_CHECK(record->firstKey);
	memset(record->firstKey, 0, record->attributeCount * sizeof(ds_key_t));
	for (int i = 0; i < record->attributeCount; ++i)
		record->firstKey[i] = -1;

	record->curKey = (ds_key_t *)malloc(record->attributeCount * sizeof(ds_key_t));
	MALLOC_CHECK(record->curKey);
	memset(record->curKey, 0, record->attributeCount * sizeof(ds_key_t));
	for (int i = 0; i < record->attributeCount; ++i)
		record->curKey[i] = -1;

	record->nextKey = (ds_key_t *)malloc(record->keyCount * sizeof(ds_key_t));
	MALLOC_CHECK(record->nextKey);
	memset(record->nextKey, 0, record->keyCount * sizeof(ds_key_t));
	for (int i = 0; i < record->keyCount; ++i)
		record->nextKey[i] = -1;

	return record;
}


/*
* Space allocation for attribute key record for counts only.
* This is used to record selectivity of attribute values.
*/
struct ATTRIBUTE_KEY_RECORD * initializeAttributeKeyRecordCountOnly(int attributeCount)
{
	struct ATTRIBUTE_KEY_RECORD * record;
	record = (struct ATTRIBUTE_KEY_RECORD *)malloc(sizeof(struct ATTRIBUTE_KEY_RECORD));
	MALLOC_CHECK(record);

	record->attributeCount = attributeCount;

	record->attributeKeyCount = (int *)malloc(record->attributeCount * sizeof(int));
	MALLOC_CHECK(record->attributeKeyCount);
	memset(record->attributeKeyCount, 0, record->attributeCount * sizeof(int));

	return record;
}

/*
* Space allocation for attribute key map.
*/
struct ATTRIBUTE_KEY_MAP * initializeAttributeKeyMap(int attributeCount, int keyCount)
{
	struct ATTRIBUTE_KEY_MAP * map;
	map = (struct ATTRIBUTE_KEY_MAP *)malloc(sizeof(struct ATTRIBUTE_KEY_MAP));
	MALLOC_CHECK(map);

	map->attributeCount = attributeCount;
	map->keyCount = keyCount;

	map->attributeKeyCount = (int *)malloc(map->attributeCount * sizeof(int));
	MALLOC_CHECK(map->attributeKeyCount);
	memset(map->attributeKeyCount, 0, map->attributeCount * sizeof(int));

	map->firstKeyIndex = (ds_key_t *)malloc(map->attributeCount * sizeof(ds_key_t));
	MALLOC_CHECK(map->firstKeyIndex);
	memset(map->firstKeyIndex, 0, map->attributeCount * sizeof(ds_key_t));
	for (int i = 0; i < map->attributeCount; ++i)
		map->firstKeyIndex[i] = -1;

	map->key = (ds_key_t *)malloc(map->keyCount * sizeof(ds_key_t));
	MALLOC_CHECK(map->key);
	memset(map->key, 0, map->keyCount * sizeof(ds_key_t));
	for (int i = 0; i < map->keyCount; ++i)
		map->key[i] = -1;

	map->attribute = (int *)malloc(map->keyCount * sizeof(int));
	MALLOC_CHECK(map->attribute);
	memset(map->attribute, 0, map->keyCount * sizeof(int));
	for (int i = 0; i < map->keyCount; ++i)
		map->attribute[i] = -1;

	return map;
}

/*
* Generate a pair of attribute values with positive correlation.
* The first attribute value are given.
*/
void
genrandCorrelatedKeyDistribution(int driveAttributeCount, ds_key_t driveAttributeId,
	int attributeCount,
	ds_key_t * attributePermutation,
	int dist, double radius,
	int stream,
	ds_key_t * attributeId)
{
	double ratio = 1.0 * (driveAttributeId + 1) / driveAttributeCount;
	// Map this value to the second attribute.
	// The second attribute value is drawn from an exponential distribution
	// from the mapped value.
	ds_key_t tmpMin = (ds_key_t)(attributeCount * ratio);
	if (tmpMin < 1)
		tmpMin = 1;
	ds_key_t tmpMax = (ds_key_t)(attributeCount * (ratio + radius));
	if (tmpMax < 1)
		tmpMax = 1;
	ds_key_t tmp2;
	genrand_key(&tmp2, dist, tmpMin, tmpMax, 0, stream);
	// Wrap around if the number is larger than the max.
	tmp2 = tmp2 % attributeCount + 1;
	mapKeyPermutation(&tmp2, attributePermutation);
	// Roll over to the next attribute if the corresponding attribute has 0 keys.
	*attributeId = tmp2;
}

/*
* Generate a pair of keys with positive correlation.
*/
void
genrandCorrelatedJointDistribution(struct ATTRIBUTE_KEY_MAP * map1, struct ATTRIBUTE_KEY_MAP * map2,
	int * attributePermutation1, int * attributePermutation2,
	int distAttribute1, int distAttribute2, double radius,
	int stream,
	ds_key_t * key1, ds_key_t * key2)
{
	// Generate an attribute value in map1.
	int tmp1;
	genrand_integer(&tmp1, distAttribute1, 1, map1->attributeCount, 0, stream);
	// Map this value to the second attribute.
	// The second attribute value is drawn from an exponential distribution
	// from the mapped value.
	double ratio = 1.0 * tmp1 / map1->attributeCount;
	int tmpMin = (int)(map2->attributeCount * ratio);
	if (tmpMin < 1)
		tmpMin = 1;
	int tmpMax = (int)(map2->attributeCount * (ratio + radius));
	if (tmpMax < 1)
		tmpMax = 1;
	int tmp2;
	genrand_integer(&tmp2, distAttribute2, tmpMin, tmpMax, 0, stream);
	// Wrap around if the number is larger than the max.
	tmp2 = tmp2 % map2->attributeCount + 1;
	mapPermutation(&tmp1, attributePermutation1);
	mapPermutation(&tmp2, attributePermutation2);
	// Roll over to the next attribute if the corresponding attribute has 0 keys.
	while (map1->attributeKeyCount[tmp1 - 1] == 0) {
		tmp1 = (tmp1 + 1) % map1->attributeCount;
	}
	while (map2->attributeKeyCount[tmp2 - 1] == 0) {
		tmp2 = (tmp2 + 1) % map2->attributeCount;
	}
	*key1 = genrandKeyWithAttribute(map1, DIST_UNIFORM, tmp1, stream);
	*key2 = genrandKeyWithAttribute(map2, DIST_UNIFORM, tmp2, stream);
}

/*
* Generate a pair of keys with positive correlation.
* The first key and attribute value are given.
*/
void
genrandSingleTableOneSidedCorrelatedJointDistribution(int driveAttributeCount, int driveAttributeId,
	struct ATTRIBUTE_KEY_MAP * map,
	ds_key_t * attributePermutation, // Use ds_key_t for foreign keys, however, the attribute value domain size is not intended to be used beyond int.
	int dist, double radius,
	int stream,
	ds_key_t * key)
{
	double ratio = 1.0 * (driveAttributeId + 1) / driveAttributeCount;
	// Map this value to the second attribute.
	// The second attribute value is drawn from an exponential distribution
	// from the mapped value.
	int tmpMin = (int)(map->attributeCount * ratio);
	if (tmpMin < 1)
		tmpMin = 1;
	int tmpMax = (int)(map->attributeCount * (ratio + radius));
	if (tmpMax < 1)
		tmpMax = 1;
	int tmp2;
	genrand_integer(&tmp2, dist, tmpMin, tmpMax, 0, stream);
	// Wrap around if the number is larger than the max.
	tmp2 = tmp2 % map->attributeCount + 1;
	ds_key_t tmp_key = tmp2;
	mapKeyPermutation(&tmp_key, attributePermutation);
	// Roll over to the next attribute if the corresponding attribute has 0 keys.
	while (map->attributeKeyCount[tmp_key - 1] == 0) {
		tmp_key = (tmp_key + 1) % map->attributeCount;
	}
	*key = genrandKeyWithAttribute(map, DIST_UNIFORM, (int)tmp_key, stream);
}


/*
* Generate a pair of keys with exponential distribution.
*/
void genrandExpJointDistribution(struct ATTRIBUTE_KEY_MAP * map1, struct ATTRIBUTE_KEY_MAP * map2,
	int * attributePermutation1, int * attributePermutation2,
	int distJoint, int distBucket,
	int stream,
	ds_key_t * key1, ds_key_t * key2)
{
	int n = map1->attributeCount * map2->attributeCount;
	int bucket;
	int bucketCount;
	makeBucket(&bucket, &bucketCount, JOINT_DISTRIBUTION_BUCKET_COUNT, n);

	int temp;
	genrand_integer(&temp, distJoint, 1, bucketCount, 0, stream);
	// Map the bucket to the range.
	int rangeMin;
	int rangeMax;
	makeRangeFromBucket(&rangeMin, &rangeMax, bucket, temp, 1, n);
	// Get the original number in the range.
	genrand_integer(&temp, distBucket, rangeMin, rangeMax, 0, stream);

	// Get the attribute IDs.
	int tmp1 = (temp - 1) / map2->attributeCount + 1;
	int tmp2 = (temp - 1) % map2->attributeCount + 1;

	mapPermutation(&tmp1, attributePermutation1);
	// Ideally, we want to use a permutation in the 2D grid. But the number
	// of entries can be too large.
	// As an approximation, we get the coordinates of the 2D and use a permutation
	// for each coordinate. To make the permutation more random, for each attribute in map1,
	// we use a different permutation in map2.
	// As an approximation, we simply shift the permutation in map2 by a different
	// number for each attribute value in map1.
	tmp2 = (tmp2 + tmp1) % map2->attributeCount + 1;
	mapPermutation(&tmp2, attributePermutation2);

	// Roll over to the next attribute if the corresponding attribute has 0 keys.
	while (map1->attributeKeyCount[tmp1 - 1] == 0) {
		tmp1 = (tmp1 + 1) % map1->attributeCount + 1;
	}
	while (map2->attributeKeyCount[tmp2 - 1] == 0) {
		tmp2 = (tmp2 + 1) % map2->attributeCount + 1;
	}

	*key1 = genrandKeyWithAttribute(map1, DIST_UNIFORM, tmp1, stream);
	*key2 = genrandKeyWithAttribute(map2, DIST_UNIFORM, tmp2, stream);
}

/*
* Return a random key from the attribute.
* Both the key and the attribute use 1-based indexing scheme.
*/
ds_key_t genrandKeyWithAttribute(struct ATTRIBUTE_KEY_MAP * map, int dist, int attribute_id, int stream)
{
	int index;
	genrand_integer(&index, dist, 1, map->attributeKeyCount[attribute_id - 1], 0, stream);
	return map->key[map->firstKeyIndex[attribute_id - 1] + index - 1];
}

/*
* Store the information of attribute and the corresponding keys with the attribute.
*/
struct ATTRIBUTE_KEY_MAP * deserializeAttributeKeyMap(char * metafile)
{
	char path[512];
	sprintf(path, "%s%c%s.meta",
		get_str("DIR"),
		PATH_SEP, metafile);

	FILE * f = fopen(path, "r");
	// Load the number of keys.

	int attributeCount, keyCount;
	fscanf(f, "%d %d ", &attributeCount, &keyCount);
	struct ATTRIBUTE_KEY_MAP * map = initializeAttributeKeyMap(attributeCount, keyCount);

	int count = 0;
	for (int i = 0; i < map->attributeCount; ++i)
	{
		map->firstKeyIndex[i] = count;
		fscanf(f, "%d ", &map->attributeKeyCount[i]);
		for (int j = 0; j < map->attributeKeyCount[i]; ++j) {
			fscanf(f, "%lld ", &map->key[count]);
			map->attribute[map->key[count] - 1] = i + 1;
			++count;
		}
	}

	fclose(f);

	return map;
}

/*
* Deserialize the attributes and the corresponding keys for each attribute.
*/
void serializeAttributeKeyRecord(char * metafile, struct ATTRIBUTE_KEY_RECORD * record)
{
	char path[512];
	sprintf(path, "%s%c%s.meta",
		get_str("DIR"),
		PATH_SEP, metafile);

	FILE * f = fopen(path, "w");

	fprintf(f, "%d %d\n", record->attributeCount, record->keyCount);
	for (int i = 0; i < record->attributeCount; ++i) {
		fprintf(f, "%d", record->attributeKeyCount[i]);
		ds_key_t next = record->firstKey[i];
		int count = 0;
		while (next != -1) {
			fprintf(f, " %lld", next + 1); // Convert from 0-based index scheme to 1-based index scheme.
			next = record->nextKey[next];
			++count;
			if (count > record->attributeKeyCount[i]) {
				printf("[ERROR] count is larger than attributeKeyCount for key ID %d, count %d, attributeKeyCount %d\n", i, count, record->attributeKeyCount[i]);
			}
		}
		fprintf(f, "\n");
	}
	fclose(f);
}

/*
* Deserialize the attributes and the corresponding number of keys.
*/
void serializeAttributeKeyRecordCountOnly(char * metafile, struct ATTRIBUTE_KEY_RECORD * record)
{
	char path[512];
	sprintf(path, "%s%c%s.meta",
		get_str("DIR"),
		PATH_SEP, metafile);

	FILE * f = fopen(path, "w");

	fprintf(f, "%d", record->attributeCount);
	for (int i = 0; i < record->attributeCount; ++i) {
		fprintf(f, " %d", record->attributeKeyCount[i]);
	}
	fprintf(f, "\n");
	fclose(f);
}
