/**
 * @description   Common functions of local alignment algorithms
 * @author        Berat Postalcioglu - 21401769 
 **/

#pragma once

#include "ScoreMatrix.h"
#include "Typedefs.h"

char local_get_pos(int score, int match_mismatch, int insertion, int deletion);
int four_max(int a, int b, int c, int d);

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
void output_local_result(score_item **matrix, u32 row, u32 col, char *s1, char *s2, char *title1, char *title2, const char *filename);