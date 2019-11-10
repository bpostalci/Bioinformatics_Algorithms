/**
 * @description   Common functions of local alignment algorithms
 * @author        Berat Postalcioglu - 21401769 
 **/

#include "LocalAlignmentCommon.h"
#include "AlignmentCommon.h"
#include "IOHelper.h"
#include <string>
#include <sstream>
#include <algorithm>

char local_get_pos(int score, int match_mismatch, int insertion, int deletion)
{
    char ch = GET_POS(score, match_mismatch, insertion, deletion);
    return ch == '\0' ? 'd' : ch;
}

int four_max(int a, int b, int c, int d)
{
    int m = max(a, b, c);
    return d > m ? d : m;
}

void output_local_result(score_item **matrix, u32 row, u32 col, char *s1, char *s2, char *title1, char *title2, const char *filename)
{
    using namespace std;

    // find maximum element
    u32 max_i = 0, max_j = 0;
    int max = matrix[0][0].score;
    for (u32 i = 0; i < row + 1; i++)
    {
        for (u32 j = 0; j < col + 1; j++)
        {
            if (matrix[i][j].score > max)
            {
                max = matrix[i][j].score;
                max_i = i;
                max_j = j;
            }
        }
    }

    string str;
    str.reserve(row + col); // eliminate heap allocation overhead
    stringstream s1_stream(str);
    stringstream s2_stream(str);
    u32 i = max_i;
    u32 j = max_j;

    while (i > 0 || j > 0)
    {
        if (matrix[i][j].pos == '-') // we reached the edge
        {
            break;
        }

        switch (matrix[i][j].pos)
        {
        case 'd':
            if (s1[i - 1] == s2[j - 1])
            {
                s1_stream << s1[i - 1];
                s2_stream << s2[j - 1];
            }
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

    write_alignment((char *)s1_str.c_str(), (char *)s2_str.c_str(), (char *)title1_str.c_str(), (char *)title2_str.c_str(), matrix[max_i][max_j].score, filename);
}