#include "KnuthMorrisPrattSearch.h"
#include "Typedefs.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int* preprocess_pattern(char* pattern);

std::vector<int> knuth_morris_pratt_search(char* text, char* pattern, int* num_of_char_comparisons)
{
	std::vector<int> occurences;
	uint_t text_len = strlen(text);
	uint_t pattern_len = strlen(pattern);
	int* f = preprocess_pattern(pattern);
	uint_t i = 0;
	uint_t j = 0;

	while (i < text_len)
	{
		++(*num_of_char_comparisons);
		if (text[i] == pattern[j])
		{
			if (j == pattern_len - 1)
			{
				occurences.push_back((i++) - (j++));
			}
			else {
				++i;
				++j;
			}
		}
		else {
			if (j > 0) {
				j = f[j - 1];
			}
			else {
				++i;
			}
		}
	}


	free(f);
	return occurences;
}

// failure function
int* preprocess_pattern(char* pattern)
{
	uint_t pattern_len = strlen(pattern);
	int* f = (int*)calloc(pattern_len, sizeof(int));
	uint_t i = 1;
	uint_t j = 0;

	while (i < pattern_len)
	{
		if (pattern[i] == pattern[j])
		{
			// we have matched j + 1 characters
			f[i] = j + 1;
			++i;
			++j;
		}
		else if (j > 0)
		{
			j = f[j - 1];
		}
		else {
			++i;
		}
	}

	return f;
}