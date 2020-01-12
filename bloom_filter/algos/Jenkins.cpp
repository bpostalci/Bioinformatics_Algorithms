#include "Jenkins.h"

u64 jenkins_hash(const void *key, u64 len)
{
    u64 result = 0;

    const char *data = (const char *)key;

    for (u64 i = 0; i < len; i++)
    {
        result += data[i];
        result += (result << 10);
        result ^= (result >> 6);
    }
    result += (result << 3);
    result ^= (result >> 11);
    result += (result << 15);

    return result;
}