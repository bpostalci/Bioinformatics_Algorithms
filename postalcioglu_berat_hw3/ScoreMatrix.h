/**
 * @description   score matrix utilities
 * @author        Berat Postalcioglu - 21401769 
 **/

#pragma once

#define GET_NUM(ch) (ch == 'A' ? 0 : ch == 'C' ? 1 : ch == 'G' ? 2 : ch == 'T' ? 3 : 0)

struct score_item
{
  int score;
  char pos;
};

const int score_matrix[4][4] =
    //  a   c   g   t
    {{2, -3, -3, -3},  // a
     {-3, 2, -3, -3},  // c
     {-3, -3, 2, -3},  // g
     {-3, -3, -3, 2}}; // t