#include "BruteForceSearch.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

std::vector<int> brute_force_search(char* text, char* pattern, int* num_of_char_comparisons)
{
	int pattern_len = strlen(pattern);
	int text_len = strlen(text);
	std::vector<int> occurences;

	for (int i = 0; i <= text_len - pattern_len; i++)
	{
		bool matched = true;
		for (int j = 0; j < pattern_len; j++)
		{
			++(*num_of_char_comparisons);
			if (text[i + j] != pattern[j])
			{
				matched = false;
				break;
			}
		}
		if (matched)
		{
			occurences.push_back(i);
		}
	}

	return occurences;
}