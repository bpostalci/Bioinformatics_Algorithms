/**
 * @description   Sequence to profile alignment program
 * @author        Berat Postalcioglu - 21401769 
 **/

#include <stdio.h>
#include <getopt.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

struct prg_options
{
    char *fasta = NULL;
    char *aln = NULL;
    char *out = NULL;
    int gap = -1;
    int match = 2;
    int mismatch = -1;
};

static const char *help =
    "usage: alignSeqToProfile [option] ... [arg]\n\
Options and arguments:\n\
--fasta    or -f  [<filename>.fasta]  : sequence fasta file to be aligned to the given profile (REQUIRED)\n\
--aln      or -a  [<filename>.aln]    : profile file that contains alignments (REQUIRED)\n\
--out      or -o  [<filename>.aln]    : profile to sequence alignment output file (default: sequence.aln)\n\
--gap      or -g  [number]            : gap penalty score\n\
--match    or -m  [number]            : match score\n\
--mismatch or -i  [number]            : mismatch penalty score\n";

int main(int argc, char **argv)
{
    prg_options prg_options;

    const char *optstring = "f:a:o:g:m:i:";
    static struct option long_options[] = {
        {"fasta", required_argument, NULL, 'f'},
        {"aln", required_argument, NULL, 'a'},
        {"out", required_argument, NULL, 'o'},
        {"gap", required_argument, NULL, 'g'},
        {"match", required_argument, NULL, 'm'},
        {"mismatch", required_argument, NULL, 'i'}};

    int c, option_index = 0;
    while ((c = getopt_long(argc, argv, optstring, long_options, &option_index)) != -1)
    {
        switch (c)
        {
        case 'f':
            prg_options.fasta = optarg;
            break;
        case 'a':
            prg_options.aln = optarg;
            break;
        case 'o':
            prg_options.out = optarg;
            break;
        case 'g':
            prg_options.gap = atoi(optarg);
            break;
        case 'm':
            prg_options.match = atoi(optarg);
            break;
        case 'i':
            prg_options.mismatch = atoi(optarg);
            break;
        default:
            printf("%s", help);
            exit(1);
        }
    }

    if (prg_options.fasta == NULL || prg_options.aln == NULL)
    {
        printf("%s", help);
        exit(1);
    }
    else
    {
        bool is_default_out = false;
        if (prg_options.out == NULL)
        {
            const char *tmp = "sequence.aln";
            size_t tmp_len = strlen(tmp);
            size_t tmp_size = sizeof(char) * (tmp_len + 1);
            prg_options.out = (char *)malloc(tmp_size);
            strncpy(prg_options.out, tmp, tmp_len);
            is_default_out = true;
        }
        printf("out: %s\n", prg_options.out);


        // free memory
        if (is_default_out)
            free(prg_options.out);
    }

    return 0;
}
