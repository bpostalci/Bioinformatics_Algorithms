/**
 *   Fowler-Noll-Vo Hash 64-bit implementation
 **/

#pragma once

#include "../data_structures/Typedefs.h"

u64 fnv_hash(const void *key, u64 len);
