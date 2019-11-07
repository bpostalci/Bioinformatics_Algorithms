#include "FileHelper.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sstream>
#include <iostream>

#define IS_LINEBREAK(ch) (ch == '\n' || ch == '\r')

void write_buffer_2d(char **buffer, uint_t buffer_len, const char *file_path, const char *extension, const char *mode)
{
	std::stringstream sstream;
	sstream << file_path << extension;
	std::cout << extension << " index file => " << sstream.str() << std::endl;

	FILE *outfp = NULL;
	outfp = fopen(sstream.str().c_str(), mode);
	if (outfp == NULL)
	{
		printf("file cannot be opened...\n");
		exit(1);
	}
	for (uint_t i = 0; i < buffer_len; i++)
	{
		for (uint_t j = 0; j < strlen(buffer[i]); j++)
		{
			fprintf(outfp, "%c", buffer[i][j]);
		}
	}
	fclose(outfp);
}

void write_buffer_1d(char *buffer, const char *file_path, const char *extension, const char *mode)
{
	std::stringstream sstream;
	sstream << file_path << extension;
	std::cout << extension << " index file => " << sstream.str() << std::endl;

	FILE *outfp = NULL;
	outfp = fopen(sstream.str().c_str(), mode);
	if (outfp == NULL)
	{
		printf("file cannot be opened...\n");
		exit(1);
	}
	for (uint_t i = 0; i < strlen(buffer); i++)
	{
		fprintf(outfp, "%c", buffer[i]);
	}
	fclose(outfp);
}

void fill_buffer(char **buffer, const char *file_path)
{
	FILE *fp = NULL;

	fp = fopen(file_path, "r");

	if (fp == NULL)
	{
		printf("file cannot be opened...\n");
		exit(1);
	}

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
	*buffer = (char *)malloc(sizeof(char) * num_of_chs + 1);

	rewind(fp);

	// fill buffer
	int i = 0;
	while (!feof(fp))
	{
		ch = fgetc(fp);
		if (!(IS_LINEBREAK(ch) || ch == EOF))
		{
			*(*buffer + i++) = ch;
		}
	}
	*(*buffer + i) = '\0';

	fclose(fp);
}
