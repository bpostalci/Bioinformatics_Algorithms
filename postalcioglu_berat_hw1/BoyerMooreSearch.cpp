#include "BoyerMooreSearch.h"
#include "Typedefs.h"
#include "Alphabet.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define MAX(x, y) (x > y ? x : y)

int* preprocess_bad_char_rule(char* pattern);
void preprocess_good_suffix_rule1(char* pattern, int* shift, int* window); // strong
void preprocess_good_suffix_rule2(char* pattern, int* shift, int* window); // weak

std::vector<int> boyer_moore_search(char* text, char* pattern, int* num_of_char_comparisons)
{
	std::vector<int> occurences;
	int pattern_len = strlen(pattern);
	int text_len = strlen(text);
	int* bad_char = preprocess_bad_char_rule(pattern);
	int* good_suffix = (int*)calloc((pattern_len + 1), sizeof(int));
	int* window = (int*)calloc((pattern_len + 1), sizeof(int));
	preprocess_good_suffix_rule1(pattern, good_suffix, window);
	preprocess_good_suffix_rule2(pattern, good_suffix, window);
	int i = 0, j;

	while (text_len - pattern_len >= i)
	{
		j = pattern_len - 1;

		++(*num_of_char_comparisons);
		while (text[i + j] == pattern[j] && j >= 0)
		{
			--j;
		}

		int bad_char_shift = i;
		if (j < 0)
		{
			occurences.push_back(i);

			if (pattern_len + i < text_len)
			{
				bad_char_shift += pattern_len - bad_char[GET_DIGIT(text[i + pattern_len])];
			}
			else {
				++bad_char_shift;
			}
			i = MAX(bad_char_shift, i + good_suffix[0]);
		}
		else {
			bad_char_shift += MAX(1, j - bad_char[GET_DIGIT(text[i + j])]);
			i = MAX(bad_char_shift, i + good_suffix[j + 1]);
		}
	}

	free(bad_char);
	free(good_suffix);
	free(window);

	return occurences;
}

int* preprocess_bad_char_rule(char* pattern)
{
	uint_t pattern_len = strlen(pattern);
	int* bad_char = (int*)malloc(sizeof(int) * pattern_len);
	uint_t i;

	for (i = 0; i < alphabet_len; i++)
	{
		bad_char[i] = -1;
	}

	for (i = 0; i < pattern_len; i++)
	{
		bad_char[GET_DIGIT(pattern[i])] = i;
	}

	return bad_char;
}

void preprocess_good_suffix_rule1(char* pattern, int* good_suffix, int* window)
{
	int pattern_len = strlen(pattern);
	int i = pattern_len;
	int j = i + 1;
	window[i] = j;

	while (i > 0)
	{
		while (j <= pattern_len && pattern[i - 1] != pattern[j - 1])
		{
			if (good_suffix[j] == 0)
			{
				good_suffix[j] = j - i;
			}
			j = window[j];
		}
		--i;
		window[i] = --j;
	}

}

void preprocess_good_suffix_rule2(char* pattern, int* good_suffix, int* window)
{
	int pattern_len = strlen(pattern);
	int i, j;
	j = window[0];
	for (i = 0; i <= pattern_len; i++)
	{
		good_suffix[i] = (good_suffix[i] == 0) ? j : good_suffix[i];
		j = (i == j) ? window[j] : j;
	}
}


