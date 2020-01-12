#pragma once

#include "../data_structures/Typedefs.h"
#include <vector>
#include <string>

void fill_sequences_buff(std::vector<std::string> &seqs, const std::string &filename, u32 kmer_length);
