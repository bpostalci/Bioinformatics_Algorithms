/**
 * @description   I/O helper
 * @author        Berat Postalcioglu - 21401769 
 **/

#include "IOHelper.h"
#include "Typedefs.h"
#include <stdio.h>
#include <stdlib.h>

#define IS_LINEBREAK(ch) (ch == '\n' || ch == '\r')

void alloc_title_buffer(FILE *fp, char **title)
{
	u32 title_ch_len = 0;
	while (fgetc(fp) != '\n')
	{
		++title_ch_len;
	}
	*title = (char *)malloc(sizeof(char) * (title_ch_len + 1)); // first line such as >pattern in FASTA file
}

void fill_title(FILE *fp, char **title)
{
	char ch;
	u32 i = 0;
	while (ch != '\n')
	{
		ch = fgetc(fp);
		*(*title + i++) = ch;
	}
	*(*title + i - 1) = '\0'; // override \n character
}

void fill_buffers(char **s1, char **s2, char **title1, char **title2, const char *filename)
{
	FILE *fp = NULL;

	fp = fopen(filename, "r");

	if (fp == NULL)
	{
		printf("file cannot be opened...\n");
		exit(1);
	}

	alloc_title_buffer(fp, (char **)&(*title1));

	// get number of characters for s1
	u32 num_of_chs = 0;
	char ch;
	while (ch != '>')
	{
		ch = fgetc(fp);
		if (!IS_LINEBREAK(ch))
			++num_of_chs;
	}
	*s1 = (char *)malloc(sizeof(char) * (num_of_chs + 1));

	rewind(fp);

	fill_title(fp, (char **)&(*title1));

	// fill s1
	ch = '\0';
	u32 i = 0;
	while (ch != '>')
	{
		ch = fgetc(fp);
		*(*s1 + i) = ch;
		if (!IS_LINEBREAK(ch))
		{
			++i;
		}
	}
	*(*s1 + i - 1) = '\0'; // override '>' character

	fseek(fp, -1, SEEK_CUR);

	alloc_title_buffer(fp, (char **)&(*title2));

	num_of_chs = 0;
	while (!feof(fp))
	{
		ch = fgetc(fp);
		if (!(IS_LINEBREAK(ch) || ch == EOF))
		{
			num_of_chs++;
		}
	}
	*s2 = (char *)malloc(sizeof(char) * num_of_chs + 1);

	rewind(fp);

	// get back to second '>' character
	while(fgetc(fp) != '>')
	{}
	while(fgetc(fp) != '>')
	{}
	fseek(fp, -1, SEEK_CUR); // back to '>' ch

	fill_title(fp, (char**)&(*title2));

	// fill s2
	i = 0;
	while (!feof(fp))
	{
		ch = fgetc(fp);
		if (!(IS_LINEBREAK(ch) || ch == EOF))
		{
			*(*s2 + i++) = ch;
		}
	}
	*(*s2 + i) = '\0';

	fclose(fp);
}
