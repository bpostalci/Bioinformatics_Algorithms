#pragma once

#include "../data_structures/Seq.h"
#include "../data_structures/Typedefs.h"
#include <string>
#include <sstream>
#include <vector>

using namespace std;

void build_UPGMA(double** dm, u32 size, const vector<seq>& seqs, const string& outfile);