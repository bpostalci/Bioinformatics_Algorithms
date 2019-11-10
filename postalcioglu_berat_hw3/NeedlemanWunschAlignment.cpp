/**
 * @description   Needleman-Wunsch algorithm with naive gap scoring (Global alignment)
 * @author        Berat Postalcioglu - 21401769 
 **/

#include "NeedlemanWunschAlignment.h"
#include "Typedefs.h"
#include "ScoreMatrix.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sstream>
#include <iostream>

#define MAX(a, b) (a > b ? a : b)
#define GET_POS(score, match_mismatch, insertion, deletion) ((score == match_mistmatch) ? 'd' : (score == insertion) ? 'u' : (score == deletion) ? 'l' : '\0')
struct score_item
{
    int score;
    char pos;
};

inline int max(int a, int b, int c)
{
    int f = MAX(a, b);
    return f > c ? f : c;
}

void display_matrix(score_item **matrix, u32 row, u32 col)
{
    for (u32 i = 0; i < row + 1; i++)
    {
        for (u32 j = 0; j < col + 1; j++)
        {
            printf("%d (%c)\t", matrix[i][j].score, matrix[i][j].pos);
        }
        printf("\n");
    }
}

void display_solution(score_item **matrix, u32 row, u32 col, char *s1, char *s2)
{
    std::string str;
    str.reserve(row + col);
    std::stringstream s1_stream(str);
    std::stringstream s2_stream(str);
    u32 i = row;
    u32 j = col;

    printf("Score = %d\n", matrix[i][j].score);

    while (i > 0 || j > 0)
    {
        if (matrix[i][j].pos == '-') // we reached edge
        {
            while (j > 0)
            {
                s1_stream << '-';
                s2_stream << s1[j--];
            }
            while (i > 0)
            {
                s2_stream << '-';
                s1_stream << s1[i--];
            }
            break;
        }

        switch (matrix[i][j].pos)
        {
        case 'd':
            s1_stream << s1[i - 1];
            s2_stream << s2[j - 1];
            --i;
            --j;
            break;
        case 'u':
            s1_stream << s1[i - 1];
            s2_stream << '-';
            --i;
            break;
        case 'l':
            s1_stream << '-';
            s2_stream << s2[j - 1];
            --j;
            break;
        }
    }

    std::cout << s1_stream.str() << std::endl;
    std::cout << s2_stream.str() << std::endl;
}

void needleman_wunsch_align(char *s1, char *s2, int gap_penalty)
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
        matrix_s[0][i].score = matrix_s[i - 1][0].score + gap_penalty;
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

   // display_matrix(matrix_s, s1_len, s2_len);
    display_solution(matrix_s, s1_len, s2_len, s1, s2);
}