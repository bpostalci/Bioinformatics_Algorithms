#pragma once

#include <vector>
#include <string>

using namespace std;

struct scoring
{
    int match, mistmatch, gap;
};

void align_seq_to_profile(string seq, vector<string> profile, scoring scores, string out_path);
