#include "SequenceToProfileAlignment.h"
#include "Typedefs.h"
#include "AlphabetHelper.h"
#include <iostream>
#include <sstream>
#include <algorithm>

#define REP(i, a, b) for (u32 i = a; i < b; i++)

bool double_equals(double a, double b, double epsilon = 0.0001)
{
    return abs(a - b) < epsilon;
}

#define GET_POS(score, match_mismatch, insertion, deletion) (double_equals(score, match_mismatch) ? 'd' : double_equals(score, insertion) ? 'u' : double_equals(score, deletion) ? 'l' : '\0')

int max(double a, double b, double c)
{
    double m = (a > b ? a : b);
    return m > c ? m : c;
}

struct score_item
{
    double score;
    char pos;
};

double probability(char x, string col)
{
    u32 found = 0;
    for (char ch : col)
    {
        if (x == ch)
            ++found;
    }

    return ((double)found / col.length());
}

double score(char x, u32 col_index, const vector<string> &profile, const scoring &scores)
{
    double score = 0;

    REP(y, 1, alphabet_len + 1)
    {
        char cur_ch = GET_CHAR(y);
        double p = probability(cur_ch, profile[col_index]);
        if (x == cur_ch)
        {
            score += p * scores.match;
        }
        else if (x != cur_ch)
        {
            score += p * scores.mistmatch;
        }
        else
        {
            score += p * scores.gap;
        }
    }

    return score;
}
// char getMaxOccuringChar(const string &str)
// {
//     int count[4] = {0};
//     int max = 0;
//     char result;

//     REP(i, 0, str.length())
//     {
//         count[GET_DIGIT(str[i]) - 1]++;
//         if (max < count[GET_DIGIT(str[i]) - 1])
//         {
//             max = count[str[i]];
//             result = str[i];
//         }
//     }

//     return result;
// }

// void output_result(vector<string> &transponse_profile, score_item **matrix_v, string &seq, u32 row, u32 col, const string &title, const string &out_path)
// {
//     string str;
//     str.reserve(col); // eliminate heap allocation overhead
//     stringstream res_stream(str);
//     u32 i = row;
//     u32 j = col;

//     while (i > 0 || j > 0)
//     {
//         if (matrix_v[i][j].pos == '-') // we reached the edge
//         {
//             while (j > 0)
//             {
//                 cout << transponse_profile[j] << "\n";
//                 char ch = getMaxOccuringChar(transponse_profile[j]);
//                 cout << ch << "\n";
//                 res_stream << ch;
//                 --j;
//             }
//             while (i > 0)
//             {
//                 res_stream << seq[i--];
//             }
//             break;
//         }

//         switch (matrix_v[i][j].pos)
//         {
//         case 'd':
//             res_stream << seq[i - 1];
//             --i;
//             --j;
//             break;
//         case 'u':
//             res_stream << seq[--i];
//             break;
//         case 'l':
//             cout << transponse_profile[j] << "\n";
//             char ch = getMaxOccuringChar(transponse_profile[j]);
//             cout << ch << "\n";
//             res_stream << ch;
//             --j;
//             break;
//         }
//     }

//     cout << res_stream.str() << "\n";
// }

void align_seq_to_profile(string &seq, vector<string> &profile, const scoring &scores, const string &title, const string &out_path)
{
    u32 seq_len = seq.length();
    u32 profile_seq_len = profile[0].length();

    score_item **matrix_v = new score_item *[seq_len + 1];
    REP(i, 0, seq_len + 1)
    {
        matrix_v[i] = new score_item[profile_seq_len + 1];
    }

    // init matrix
    matrix_v[0][0].score = 0;
    matrix_v[0][0].pos = 'd';

    REP(i, 1, seq_len + 1)
    {
        matrix_v[i][0].score = matrix_v[i - 1][0].score + scores.gap;
        matrix_v[i][0].pos = 'u';
    }

    REP(j, 1, profile_seq_len + 1)
    {
        matrix_v[0][j].score = matrix_v[0][j - 1].score + scores.gap;
        matrix_v[0][j].pos = 'l';
    }

    // get transpose of profile to not calculate column over and over again
    vector<string> transponse_profile;
    REP(j, 0, profile[0].length())
    {
        stringstream ss;
        REP(i, 0, profile.size())
        {
            ss << profile[i][j];
        }
        transponse_profile.push_back(ss.str());
    }
    REP(i, 1, seq_len + 1)
    {
        REP(j, 1, profile_seq_len + 1)
        {
            double match_mismatch = matrix_v[i - 1][j - 1].score + score(seq[i - 1], j - 1, transponse_profile, scores);
            double insertion = matrix_v[i - 1][j].score + scores.gap;
            double deletion = matrix_v[i][j - 1].score + score('-', j - 1, transponse_profile, scores);
            matrix_v[i][j].score = max({match_mismatch, insertion, deletion});
            matrix_v[i][j].pos = GET_POS(matrix_v[i][j].score, match_mismatch, insertion, deletion);
        }
    }

    REP(i, 0, seq_len + 1)
    {
        REP(j, 0, profile_seq_len + 1)
        {
            cout << matrix_v[i][j].score << " " << (matrix_v[i][j].pos == 'd' ? '<' : matrix_v[i][j].pos) << "\t";
        }
        cout << "\n";
    }

    // output_result(transponse_profile, matrix_v, seq, seq_len, profile_seq_len, title, out_path);

    // free memory
    REP(i, 0, seq_len + 1)
    {
        delete matrix_v[i];
    }

    delete[] matrix_v;
}
