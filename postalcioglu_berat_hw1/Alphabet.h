#pragma once

#include "Typedefs.h"

#define GET_DIGIT(ch) (ch == 'A' ? 1 : ch == 'C' ? 2 : ch == 'G' ? 3 : 4)
const uint_t alphabet_len = 4;