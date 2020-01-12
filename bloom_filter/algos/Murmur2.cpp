#include "Murmur2.h"

#define CUC const unsigned char *

static const u64 SEED = 1;

u64 murmur_hash(const void *key, u64 len)
{
  const u64 m = 0xc6a4a7935bd1e995LLU;
  u64 h = SEED ^ (len * m);
  u32 r = 47;
  const u64 *data = (const u64 *)key;
  const u64 *end = data + (len / 8);

  while (data != end)
  {
    u64 k = *data++;
    k *= m;
    k ^= k >> r;
    k *= m;
    h ^= k;
    h *= m;
  }

  CUC new_data = (CUC)data;

  u64 val = len & 7;
  if (val == 1)
  {
    h ^= u64(new_data[0]);
    h *= m;
  }
  else if (val == 2)
  {
    h ^= u64(new_data[1]) << 8;
  }
  else if (val == 3)
  {
    h ^= u64(new_data[2]) << 16;
  }
  else if (val == 4)
  {
    h ^= u64(new_data[3]) << 24;
  }
  else if (val == 5)
  {
    h ^= u64(new_data[4]) << 32;
  }
  else if (val == 6)
  {
    h ^= u64(new_data[5]) << 40;
  }
  else if (val == 7)
  {
    h ^= u64(new_data[6]) << 48;
  }
  h ^= h >> r;
  h *= m;
  h ^= h >> r;

  return h;
}
