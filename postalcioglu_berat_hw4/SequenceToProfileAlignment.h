#pragma once

#include <vector>
#include <string>

using namespace std;

struct scoring
{
    int match, mistmatch, gap;
};

void align_seq_to_profile(string &seq, vector<string> &profile, const scoring &scores, const string &title, const string &out_path);
