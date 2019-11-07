#include <math.h>
#include <string.h>
#include "RabinKarpSearch.h"
#include "Typedefs.h"
#include "Alphabet.h"
#include <stdio.h>

// a big prime number
const uint64_t q = 5915587277L;

std::vector<int> rabin_karp_search(char* text, char* pattern, int* num_of_char_comparisons)
{
	std::vector<int> occurences;
	uint_t pattern_len = strlen(pattern);
	uint_t text_len = strlen(text);
	uint_t c = 1;
	uint_t i;

	// calculate c (10^pattern_len-1 mod q)
	for (i = 0; i < pattern_len - 1; i++)
	{
		c = (c * alphabet_len) % q;
	}

	// preprocessing pattern and text[0..pattern_len - 1]
	uint_t fp = 0;
	uint_t ft = 0;
	for (i = 0; i < pattern_len; i++)
	{
		fp = (alphabet_len * fp + GET_DIGIT(pattern[i])) % q;
		ft = (alphabet_len * ft + GET_DIGIT(text[i])) % q;
	}

	// searching
	for (i = 0; i <= text_len - pattern_len; i++)
	{
		// hash values are equal
		if (fp == ft)
		{
			// control if the strings are equal
			bool matched = true;
			for (uint_t j = 0; j < pattern_len; j++)
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
		// calculate next hash
		ft = ((ft - GET_DIGIT(text[i]) * c) * alphabet_len + GET_DIGIT(text[i + pattern_len])) % q;
	}

	return occurences;
}

