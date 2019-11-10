/**
 * @description   Smith-Waterman algorithm with affine gap scoring (Local Affine Alignment)
 * @author        Berat Postalcioglu - 21401769 
 **/

#include "SmithWatermanAffineAlignment.h"
#include "Typedefs.h"
#include "ScoreMatrix.h"
#include "LocalAlignmentCommon.h"
#include "AlignmentCommon.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void smith_waterman_affine_alignment(char *s1, char *s2, char *title1, char *title2, int gapopen, int gapext)
{
    u32 s1_len = strlen(s1);
    u32 s2_len = strlen(s2);
    u32 i;

    // allocate dynamic memories - matrix V
    score_item **matrix_s = (score_item **)calloc((s1_len + 1), sizeof(score_item *));
    for (i = 0; i < (s1_len + 1); i++)
    {
        matrix_s[i] = (score_item *)calloc((s2_len + 1), sizeof(score_item));
    }

    // matrix - E
    int **matrix_e = (int **)calloc((s1_len + 1), sizeof(int *));
    for (i = 0; i < (s1_len + 1); i++)
    {
        matrix_e[i] = (int *)calloc((s2_len + 1), sizeof(int));
    }

    // matrix - F
    int **matrix_f = (int **)calloc((s1_len + 1), sizeof(int *));
    for (i = 0; i < (s1_len + 1); i++)
    {
        matrix_f[i] = (int *)calloc((s2_len + 1), sizeof(int));
    }

    // initialize all matrixes
    matrix_e[0][0] = -1000000;
    matrix_f[0][0] = -1000000;
    matrix_s[0][0].score = 0;
    matrix_s[0][0].pos = '-';
    for (i = 1; i < s1_len + 1; i++)
    {
        matrix_s[i][0].score = gapopen + i * gapext;
        matrix_s[i][0].pos = '-';
        matrix_e[i][0] = matrix_s[i][0].score;
        matrix_f[i][0] = 0;
    }
    for (i = 1; i < s2_len + 1; i++)
    {
        matrix_s[0][i].score = gapopen + i * gapext;
        matrix_s[0][i].pos = '-';
        matrix_f[0][i] = matrix_s[0][i].score;
        matrix_e[0][i] = 0;
    }
    // iterate
    for (i = 1; i < s1_len + 1; i++)
    {
        for (u32 j = 1; j < s2_len + 1; j++)
        {
            matrix_e[i][j] = MAX((matrix_e[i][j - 1] + gapext), (matrix_s[i][j - 1].score + gapopen + gapext));
            matrix_f[i][j] = MAX((matrix_f[i - 1][j] + gapext), (matrix_s[i - 1][j].score + gapopen + gapext));
            int match_mismatch = matrix_s[i - 1][j - 1].score + score_matrix[GET_NUM(s1[i - 1])][GET_NUM(s2[j - 1])];
            matrix_s[i][j].score = four_max(0, match_mismatch, matrix_e[i][j], matrix_f[i][j]);
            matrix_s[i][j].pos = local_get_pos(matrix_s[i][j].score, match_mismatch, matrix_f[i][j], matrix_e[i][j]);
        }
    }

    output_local_result(matrix_s, s1_len, s2_len, s1, s2, title1, title2, "local-affineGap.aln");

    // free memory
    for (i = 0; i < (s1_len + 1); i++)
    {
        free(matrix_s[i]);
    }
    free(matrix_s);

    // matrix - E
    for (i = 0; i < (s1_len + 1); i++)
    {
        free(matrix_e[i]);
    }
    free(matrix_e);

    // matrix - F
    for (i = 0; i < (s1_len + 1); i++)
    {
        free(matrix_f[i]);
    }
    free(matrix_f);
}