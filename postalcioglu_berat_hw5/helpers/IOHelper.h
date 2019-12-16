#pragma once

#include "../data_structures/Typedefs.h"
#include "../data_structures/Seq.h"
#include <string>
#include <vector>

using namespace std;

void fill_sequences_buff(vector<seq> &seqs, const string &filename);
void fill_sequence_buff(string &seq, string &title, const string &filename);
void fill_profile_buff(vector<string> &seqs, vector<string> &seqs_titles, const string &filename);
void write_alignment(const string &aln, const string &output_file);
