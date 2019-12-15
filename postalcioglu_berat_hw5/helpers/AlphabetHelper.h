#include "../data_structures/Typedefs.h"

#define GET_DIGIT(ch) (ch == 'A' ? 1 : ch == 'C' ? 2 : ch == 'G' ? 3 : ch == 'T' ? 4 : 5)
#define GET_CHAR(i) (i == 1 ? 'A' : i == 2 ? 'C' : i == 3 ? 'G' : i == 4 ? 'T' : '-')
const u32 alphabet_len = 5;
