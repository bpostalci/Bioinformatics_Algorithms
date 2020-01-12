/**
 * @description   Common functions of alignment algorithms
 * @author        Berat Postalcioglu - 21401769 
 **/

#include "AlignmentCommon.h"
#include "IOHelper.h"
#include "ScoreMatrix.h"
#include <stdio.h>
#include <string>
#include <sstream>
#include <algorithm>

int max(int a, int b, int c)
{
    int m = MAX(a, b);
    return m > c ? m : c;
}

void output_result(score_item **matrix, u32 row, u32 col, char *s1, char *s2, char *title1, char *title2, const char *filename)
{
    using namespace std;

    string str;
    str.reserve(row + col); // eliminate heap allocation overhead
    stringstream s1_stream(str);
    stringstream s2_stream(str);
    u32 i = row;
    u32 j = col;

    while (i > 0 || j > 0)
    {
        if (matrix[i][j].pos == '-') // we reached the edge
        {
            while (j > 0)
            {
                s1_stream << '-';
                s2_stream << s2[j--];
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
            s1_stream << s1[--i];
            s2_stream << '-';
            break;
        case 'l':
            s1_stream << '-';
            s2_stream << s2[--j];
            break;
        }
    }

    string title1_str = string(title1).erase(0, 1);
    string title2_str = string(title2).erase(0, 1);

    string s1_str = s1_stream.str();
    reverse(s1_str.begin(), s1_str.end());
    string s2_str = s2_stream.str();
    reverse(s2_str.begin(), s2_str.end());

    write_alignment((char *)s1_str.c_str(), (char *)s2_str.c_str(), (char *)title1_str.c_str(), (char *)title2_str.c_str(), matrix[row][col].score, filename);
}