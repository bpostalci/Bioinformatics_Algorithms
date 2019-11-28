#include "SequenceToProfileAlignment.h"

#include <iostream>
#include "Typedefs.h"

#define REP(i, a, b) for (u32 i = a; i < b; i++)

struct score_item
{
    int score;
    char pos;
};

void align_seq_to_profile(string seq, vector<string> profile, scoring scores, string out_path)
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
    matrix_v[0][0].pos = '-';

    REP(i, 1, seq_len + 1)
    {
        matrix_v[i][0].score = matrix_v[i - 1][0].score + scores.gap;
        matrix_v[i][0].pos = '-';
    }

    REP(i, 1, profile_seq_len + 1)
    {
    }

    // free memory
    REP(i, 0, seq_len + 1)
    {
        delete matrix_v[i];
    }

    delete[] matrix_v;
}