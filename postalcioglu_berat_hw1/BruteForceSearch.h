#pragma once

#include <vector>

using namespace std;

/*
	returns indexes of occurences of pattern in text if exists
	returns NULL otherwise
*/
std::vector<int> brute_force_search(char* text, char* pattern, int* num_of_char_comparisons);