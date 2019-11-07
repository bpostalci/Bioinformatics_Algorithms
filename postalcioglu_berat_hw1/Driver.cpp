#pragma warning(disable : 4996)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <iostream>
#include <functional>
#include <algorithm>
#include "Typedefs.h"
#include "BruteForceSearch.h"
#include "KnuthMorrisPrattSearch.h"
#include "BoyerMooreSearch.h"
#include "RabinKarpSearch.h"

#define IS_LINEBREAK(ch) (ch == '\n' || ch == '\r')

bool equals(double x, double y);
void display_header(const std::string header);
void fill_buffer(char **buffer, const char *filename);
void display_occurences(std::vector<int> &v);

// since all operations are same for all algorithms (measuring performance...) instead of defining several functions I used lambda expressions to set 'algorithm' parameter
double search(char *dna, char *pattern, const std::string header, std::function<std::vector<int>()> algorithm);

int main(int argc, char **argv)
{
	char *dna = NULL;
	fill_buffer((char **)&dna, "db/text.fa");

	char *pattern = NULL;
	fill_buffer((char **)&pattern, "db/pattern.fa");

	int brute_force_score = 0;
	double brute_force_time = search(dna, pattern, "Brute Force Search", [&]() {
		return brute_force_search(dna, pattern, &brute_force_score);
	});
	printf("number of character comparisons = %d\n", brute_force_score);

	int kmp_score = 0;
	double kmp_time = search(dna, pattern, "Knuth Morris Pratt Search", [&]() {
		return knuth_morris_pratt_search(dna, pattern, &kmp_score);
	});
	printf("number of character comparisons = %d\n", kmp_score);

	int rabin_karp_score = 0;
	double rabin_karp_time = search(dna, pattern, "Rabin Karp Search", [&]() {
		return rabin_karp_search(dna, pattern, &rabin_karp_score);
	});
	printf("number of character comparisons = %d\n", rabin_karp_score);

	int boyer_moore_score = 0;
	double boyer_moore_time = search(dna, pattern, "Boyer Moore Search", [&]() {
		return boyer_moore_search(dna, pattern, &boyer_moore_score);
	});
	printf("number of character comparisons = %d\n", boyer_moore_score);

	double best_time = std::min({brute_force_time, kmp_time, rabin_karp_time, boyer_moore_time});
	int best_score = std::min({brute_force_score, kmp_score, rabin_karp_score, boyer_moore_score});

	display_header("Results");
	printf("Fastest running algorithm = ");
	if (equals(brute_force_time, best_time))
	{
		printf("-Brute Force-");
	}
	else if (equals(kmp_time, best_time))
	{
		printf("-Knuth Morris Pratt-");
	}
	else if (equals(boyer_moore_time, best_time))
	{
		printf("-Boyer Moore-");
	}
	else if (equals(rabin_karp_time, best_time))
	{
		printf("-Rabin Karp-");
	}
	printf(" with %.5f microseconds\n", best_time);

	printf("Algorithm with minimum character comparisons = ");
	if (brute_force_score == best_score)
	{
		printf("-Brute Force-");
	}
	else if (kmp_score == best_score)
	{
		printf("-Knuth Morris Pratt-");
	}
	else if (boyer_moore_score == best_score)
	{
		printf("-Boyer Moore-");
	}
	else if (rabin_karp_score == best_score)
	{
		printf("-Rabin Karp-");
	}
	printf(" with %d character comparisons\n\n", best_score);

	printf("NOTE: With large input files Boyer Moore algorithm is much more faster than other algorithms...\n\n");

	free(pattern);
	free(dna);

	return 0;
}

bool equals(double x, double y)
{
	return std::abs(x - y) < std::numeric_limits<double>::epsilon();
}

void display_header(const std::string header)
{
	std::string decoration = "~~~~~";
	std::cout << "\n"
			  << decoration << header << decoration << std::endl;
}

void fill_buffer(char **buffer, const char *filename)
{
	FILE *fp = NULL;

	fp = fopen(filename, "r");

	if (fp == NULL)
	{
		printf("file cannot be opened...\n");
		exit(1);
	}

	while (fgetc(fp) != '\n'){}

	// get number of characters
	uint_t num_of_chs = 0;
	char ch;
	while (!feof(fp))
	{
		ch = fgetc(fp);
		if (!(IS_LINEBREAK(ch) || ch == EOF))
		{
			num_of_chs++;
		}
	}
	*buffer = (char *)malloc(sizeof(char) * (num_of_chs + 1));

	rewind(fp);

	while (fgetc(fp) != '\n'){}

	// fill buffer
	uint_t i = 0;
	while (!feof(fp))
	{
		ch = fgetc(fp);
		if (!(IS_LINEBREAK(ch) || ch == EOF))
		{
			*(*buffer + i) = ch;
		}
		++i;
	}
	*(*buffer + i - 1) = '\0'; // i - 1 to undo last increment

	fclose(fp);
}

void display_occurences(std::vector<int> &v)
{
	if (v.empty())
	{
		printf("there is no occurences...\n");
		return;
	}
	printf("indexes of occurences: ");
	std::vector<int>::iterator it = v.begin();
	while (it != v.end())
	{
		// *it + 1 since 1-based coordinate
		printf("%d", *it + 1);
		if ((++it) != v.end())
		{
			printf(", ");
		}
	}
	printf("\n");
}

double search(char *dna, char *pattern, const std::string header, std::function<std::vector<int>()> algorithm)
{
	display_header(header);
	std::vector<int> occurences;

	clock_t start, end;
	start = clock();
	occurences = algorithm();
	end = clock();

	double ellapsed_time = (double)(end - start) * 1000.0;
	printf("ellapsed time = %.5f microseconds\n", ellapsed_time);

	display_occurences(occurences);

	return ellapsed_time;
}
