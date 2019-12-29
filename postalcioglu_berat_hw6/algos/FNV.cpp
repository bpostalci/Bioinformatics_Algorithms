/**
 *   Fowler-Noll-Vo Hash 64-bit implementation
 **/

#include "FNV.h"

// recommended values
const u64 PRIME = 0x01000193;
const u64 SEED = 0x811C9DC5;

#define CUC const unsigned char *

u64 fnv_hash(const void *key, u64 len)
{
    u64 result = SEED;

    CUC data = (CUC)key;
    while (len--)
    {
        result = (*data++ ^ result) * PRIME;
    }
    return result;
}
