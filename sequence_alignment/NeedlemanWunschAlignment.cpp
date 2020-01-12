/**
 * @description   Needleman-Wunsch algorithm with naive gap scoring (Global alignment)
 * @author        Berat Postalcioglu - 21401769 
 **/

#include "NeedlemanWunschAlignment.h"
#include "Typedefs.h"
#include "ScoreMatrix.h"
#include "AlignmentCommon.h"
#include <string.h>
#include <stdlib.h>

void needleman_wunsch_align(char *s1, char *s2, char *title1, char *title2, int gap_penalty)
{
    u32 s1_len = strlen(s1);
    u32 s2_len = strlen(s2);
    u32 i;

    // allocate dynamic memory
    score_item **matrix_s = (score_item **)calloc((s1_len + 1), sizeof(score_item *));
    for (i = 0; i < (s1_len + 1); i++)
    {
        matrix_s[i] = (score_item *)calloc((s2_len + 1), sizeof(score_item));
    }

    // initialize matrix
    matrix_s[0][0].score = 0;
    matrix_s[0][0].pos = '-';
    for (i = 1; i < s1_len + 1; i++)
    {
        matrix_s[i][0].score = matrix_s[i - 1][0].score + gap_penalty;
        matrix_s[i][0].pos = '-';
    }
    for (i = 1; i < s2_len + 1; i++)
    {
        matrix_s[0][i].score = matrix_s[0][i - 1].score + gap_penalty;
        matrix_s[0][i].pos = '-';
    }

    // iterate
    for (i = 1; i < s1_len + 1; i++)
    {
        for (u32 j = 1; j < s2_len + 1; j++)
        {
            int match_mistmatch = matrix_s[i - 1][j - 1].score + score_matrix[GET_NUM(s1[i - 1])][GET_NUM(s2[j - 1])];
            int insertion = matrix_s[i - 1][j].score + gap_penalty;
            int deletion = matrix_s[i][j - 1].score + gap_penalty;
            matrix_s[i][j].score = max(match_mistmatch, insertion, deletion);
            matrix_s[i][j].pos = GET_POS(matrix_s[i][j].score, match_mistmatch, insertion, deletion);
        }
    }

    output_result(matrix_s, s1_len, s2_len, s1, s2, title1, title2, "global-naiveGap.aln");

    // free memory
    for (i = 0; i < (s1_len + 1); i++)
    {
        free(matrix_s[i]);
    }
    free(matrix_s);
    
}