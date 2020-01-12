/**
 * @description   Common functions of alignment algorithms
 * @author        Berat Postalcioglu - 21401769 
 **/

#pragma once

#include "ScoreMatrix.h"
#include "Typedefs.h"

#define MAX(a, b) (a > b ? a : b)
#define GET_POS(score, match_mismatch, insertion, deletion) ((score == match_mismatch) ? 'd' : (score == insertion) ? 'u' : (score == deletion) ? 'l' : '\0')
int max(int a, int b, int c);

/**
 *    @param matrix          - contains score and position information
 *    @param row             - row position to traverse matrix 
 *    @param col             - column position to traverse matrix 
 *    @param s1              - first sequence 
 *    @param s2              - second sequence 
 *    @param title1          - title of the first sequence  (>my_first_sequence) 
 *    @param title2          - title of the second sequence (>another_sequence) 
 *    @param filename        - file name of the output file 
 **/
void output_result(score_item **matrix, u32 row, u32 col, char *s1, char *s2, char *title1, char *title2, const char *filename);