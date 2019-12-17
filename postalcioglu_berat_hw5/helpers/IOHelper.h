#pragma once

#include "../data_structures/Typedefs.h"
#include "../data_structures/Seq.h"
#include <string>
#include <vector>

using namespace std;

void fill_sequences_buff(vector<seq> &seqs, const string &filename);
void write_tree(const string &tree, const string &output_file);
