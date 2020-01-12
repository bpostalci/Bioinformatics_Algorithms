#include "FileHelper.h"
#include "Typedefs.h"
#include "BurrowsWheelerTransform.h"
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <string>

#define DISPLAY_AND_RETURN(code) ({display_parameters(); return code; })

void display_parameters()
{
    std::string out;
    out += "usage: bwtfm [option]\n";
    out += "Options:\n";
    out += "--help                                      :  display help\n";
    out += "--index  [text].fa                          :  outputs [text].fa.bwt and [text].fa.fm index files\n";
    out += "--search [text].fa --pattern [query].fa     :  file to be searched by a specified pattern file (both text and pattern files must be supplied)\n";
    std::cout << out;
}

void generate_indexes(const char *index_file)
{
    char *text = NULL;
    fill_buffer((char **)&text, index_file);
    transform(text, index_file);
   
}

void search(const char *text_file, const char *pattern_file)
{
    char *text = NULL;
    fill_buffer((char **)&text, text_file);

    char ch = 'a';
    uint_t i = 0;
    while (ch != '\0')
    {
        ch = text[i++];
        printf("%c", ch);
    }

    char *pattern = NULL;
    fill_buffer((char **)&pattern, pattern_file);

    printf("\n\n\n\n\n");
    i = 0;
    ch = 'a';
    while (ch != '\0')
    {
        ch = pattern[i++];
        printf("%c", ch);
    }
}

int main(int argc, char **argv)
{
    // interpret parameters
    if (argc <= 1 || strcmp(argv[1], "--help") == 0)
    {
        DISPLAY_AND_RETURN(0);
    }
    else if (strcmp(argv[1], "--index") == 0)
    {
        if (!argv[2])
        {
            DISPLAY_AND_RETURN(0);
        }
        generate_indexes(argv[2]);
    }
    else if (strcmp(argv[1], "--search") == 0)
    {
        if (!argv[2] || !argv[3] || !argv[4])
        {
            DISPLAY_AND_RETURN(0);
        }
        else if (strcmp(argv[3], "--pattern") != 0)
        {
            DISPLAY_AND_RETURN(0);
        }
        search(argv[2], argv[4]);
    }
    else if (strcmp(argv[1], "--pattern") == 0)
    {
        if (!argv[2] || !argv[3] || !argv[4])
        {
            DISPLAY_AND_RETURN(0);
        }
        else if (strcmp(argv[3], "--search") != 0)
        {
            DISPLAY_AND_RETURN(0);
        }
        search(argv[4], argv[2]);
    }

    return 0;
}