#define BUMPER 2

typedef struct {
    int key;
    int index;
} IndexCacheEntry;

typedef struct {
    int                 entrySize;
    IndexCacheEntry*    entries;
} IndexCache;

void InitializeIndexCache(IndexCache* indexCache, int entrySize) {
    size_t sizeOfEntries    = sizeof(IndexCacheEntry) * entrySize;

    indexCache->entrySize   = entrySize;
    indexCache->entries     = (IndexCacheEntry*) malloc(sizeOfEntries);

    memset(indexCache->entries, -1, sizeOfEntries);
}

void DestroyIndexCache(IndexCache* indexCache) {
    free(indexCache->entries);
}

inline unsigned int GetHash(int key, int entrySize) {
    return ((unsigned int)key << BUMPER) % entrySize;
}

int GetIndexCache(IndexCache* indexCache, int key) {
    unsigned int hash = GetHash(key, indexCache->entrySize);
    
    while (indexCache->entries[hash].index != -1) {
        if (indexCache->entries[hash].key == key) {
            return indexCache->entries[hash].index;
        }

        hash = (hash + 1) % indexCache->entrySize;
    }

    return -1;
}

void PutIndexCache(IndexCache* indexCache, int key, int index) {
    unsigned int hash = GetHash(key, indexCache->entrySize);
    
    while (indexCache->entries[hash].index != -1) {
        if (indexCache->entries[hash].key == key) {
            indexCache->entries[hash].index = index;
            return;
        }

        hash = (hash + 1) % indexCache->entrySize;
    }

    indexCache->entries[hash].key   = key;
    indexCache->entries[hash].index = index;
}

int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
    IndexCache indexCache;
    int*        result     = (int*) malloc(sizeof(int) * 2);
    
    InitializeIndexCache(&indexCache, numsSize << BUMPER);

    for (int i = 0; i < numsSize; i++) {
        int correct = target - nums[i];
        int foundIndex = GetIndexCache(&indexCache, correct);

        if (foundIndex != -1) {
            result[0] = i;
            result[1] = foundIndex;
            *returnSize = 2;

            DestroyIndexCache(&indexCache);
            return result;
        }

        PutIndexCache(&indexCache, nums[i], i);
    }

    *returnSize = 0;

    DestroyIndexCache(&indexCache);
    return result;
}