#ifndef JOINT_DISTRIBUTION
#define JOINT_DISTRIBUTION

#include "porting.h"

/*
* Data structure to store the attribute key map after deserializing from the file.
*/
struct ATTRIBUTE_KEY_MAP {
	int keyCount; // Total number of keys.
	int attributeCount; // Total number of attributes.
	int * attributeKeyCount; // Number of keys for each attribute.
	ds_key_t * firstKeyIndex; // The starting index for attribute 0, attribute 1, ...
	ds_key_t * key; // The keys are ordered as [keys for attribute 0, keys for attribute 1, ... ]. The keys use 1-based indexing scheme.
	int * attribute; // Map keys to attributes, the attribute ID starts from 1.
};

/*
* Data structure to keep track of attribute key map when serializing the information to a file.
*/
struct ATTRIBUTE_KEY_RECORD {
	int keyCount; // Total number of keys.
	int attributeCount; // Total number of attributes.
	int maxAttributeCount; // Maximal number of possible attribute values. This is used for string attribute values, i.e., states.
	char ** attributeValue; // Used to store and map attribute values to IDs.
	ds_key_t curKeyCount; // The number of keys recorded so far.
	int * attributeKeyCount; // The number of keys for each attribute.
	ds_key_t * firstKey; // The first key for each attribute.
	ds_key_t * curKey; // The most recent recorded key for each attribute.
	ds_key_t * nextKey; // The linked list of keys.
};

struct ATTRIBUTE_KEY_RECORD * initializeAttributeKeyRecord(int attributeCount, int keyCount);
struct ATTRIBUTE_KEY_RECORD * initializeCharAttributeKeyRecord(int maxAttributeCount, int keyCount);

struct ATTRIBUTE_KEY_RECORD * initializeAttributeKeyRecordCountOnly(int attributeCount);

int searchAttributeId(struct ATTRIBUTE_KEY_RECORD * record, char * attribute_value);

void updateAttributeKeyRecord(struct ATTRIBUTE_KEY_RECORD * record, int attribute_id);
void updateCharAttributeKeyRecord(struct ATTRIBUTE_KEY_RECORD * record, char * attribute_value);

void updateAttributeKeyRecordCountOnly(struct ATTRIBUTE_KEY_RECORD * record, int attribute_id);

struct ATTRIBUTE_KEY_MAP * initializeAttributeKeyMap(int attributeCount, int keyCount);

void serializeAttributeKeyRecord(char * metafile, struct ATTRIBUTE_KEY_RECORD * record);

struct ATTRIBUTE_KEY_MAP * deserializeAttributeKeyMap(char * metafile);

ds_key_t genrandKeyWithAttribute(struct ATTRIBUTE_KEY_MAP * map, int dist, int attribute_id, int stream);

void genrandCorrelatedJointDistribution(struct ATTRIBUTE_KEY_MAP * map1, struct ATTRIBUTE_KEY_MAP * map2,
	int * attributePermutation1, int * attributePermutation2,
	int distAttribute1, // Distribution of the first attribute.
	int distAttribute2, // Conditional distribution of the second attribute.
	double radius, // Mapped range from the first attribute to the second attribute.
	int stream,
	ds_key_t * key1, ds_key_t * key2);

void
genrandSingleTableOneSidedCorrelatedJointDistribution(int driveAttributeCount, int driveAttributeId,
	struct ATTRIBUTE_KEY_MAP * map,
	int * attributePermutation,
	int dist, double radius,
	int stream,
	ds_key_t * key);

void genrandExpJointDistribution(struct ATTRIBUTE_KEY_MAP * map1, struct ATTRIBUTE_KEY_MAP * map2,
	int * attributePermutation1, int * attributePermutation2,
	int distJoint, // Distribution of the 2D grid.
	int distBucket, // Distribution within a bucket.
	int stream,
	ds_key_t * key1, ds_key_t * key2);

void genrandCorrelatedKeyDistribution(int driveAttributeCount, ds_key_t driveAttributeId,
	int attributeCount,
	ds_key_t * attributePermutation,
	int dist, double radius,
	int stream,
	ds_key_t * attributeId);

#endif