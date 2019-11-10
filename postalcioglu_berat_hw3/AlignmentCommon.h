#pragma once

#include "ScoreMatrix.h"
#include "Typedefs.h"

#define MAX(a, b) (a > b ? a : b)
#define GET_POS(score, match_mismatch, insertion, deletion) ((score == match_mismatch) ? 'd' : (score == insertion) ? 'u' : (score == deletion) ? 'l' : '\0')

int max(int a, int b, int c);
void output_result(score_item **matrix, u32 row, u32 col, char *s1, char *s2, char *title1, char *title2, const char *filename);