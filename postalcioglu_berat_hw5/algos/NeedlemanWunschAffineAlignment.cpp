#include "NeedlemanWunschAffineAlignment.h"
#include "../data_structures/Typedefs.h"
#include <string.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

struct score_item
{
    int score;
    char pos;
};

#define MAX(a, b) (a > b ? a : b)
#define GET_POS(score, match_mismatch, insertion, deletion) ((score == match_mismatch) ? 'd' : (score == insertion) ? 'u' : (score == deletion) ? 'l' : '\0')

int max(int a, int b, int c)
{
    int m = MAX(a, b);
    return m > c ? m : c;
}

char local_get_pos(int score, int match_mismatch, int insertion, int deletion)
{
    char ch = GET_POS(score, match_mismatch, insertion, deletion);
    return ch == '\0' ? 'd' : ch;
}

double calculate_edit_distance(score_item **m, u32 i, u32 j);

/**
 *    
 * @return Edit distance between s1 and s2
 **/
double needleman_wunsch_affine_align(const char *s1, const char *s2, int match, int mismatch, int gapopen, int gapext)
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
            bool is_match = true;
            int match_mismatch;
            if (s1[i - 1] == s2[j - 1])
            {
                match_mismatch = matrix_s[i - 1][j - 1].score + match;
            }
            else
            {
                match_mismatch = matrix_s[i - 1][j - 1].score + mismatch;
                is_match = false;
            }
            matrix_s[i][j].score = max(match_mismatch, matrix_e[i][j], matrix_f[i][j]);
            char pos = local_get_pos(matrix_s[i][j].score, match_mismatch, matrix_f[i][j], matrix_e[i][j]);
            matrix_s[i][j].pos = pos == 'd' ? (!is_match ? 'i' : 'm') : pos;
        }
    }

    // output_result(matrix_s, s1_len, s2_len, (char *)s1, (char *)s2, "global-alignment.aln");
    // for (i = 1; i < s1_len + 1; i++)
    // {
    //     for (u32 j = 1; j < s2_len + 1; j++)
    //     {
    //         cout << matrix_s[i][j].pos << " ";
    //     }
    //     cout << "\n";
    // }

    double result = calculate_edit_distance(matrix_s, s1_len, s2_len);

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

    return result;
}

double calculate_edit_distance(score_item **m, u32 i, u32 j) // i = row, j = col
{
    int distance = 0;

    while (i > 0 || j > 0)
    {
        if (m[i][j].pos == '-') // we reached the edge
        {
            while (j > 0)
            {
                ++distance;
                --j;
            }
            while (i > 0)
            {
                ++distance;
                --i;
            }
            break;
        }

        switch (m[i][j].pos)
        {
        case 'm':
            --i;
            --j;
            break;
        case 'i':
            ++distance;
            --i;
            --j;
            break;
        case 'u':
            ++distance;
            --i;
            break;
        case 'l':
            ++distance;
            --j;
            break;
        }
    }

    return (double)distance;
}
