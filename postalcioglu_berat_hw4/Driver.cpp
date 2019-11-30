/**
 * @description   Sequence to profile alignment program
 * @author        Berat Postalcioglu - 21401769 
 **/

#include <stdio.h>
#include <getopt.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "SequenceToProfileAlignment.h"
#include "IOHelper.h"
#include <vector>
#include <string>
#include <iostream>

using namespace std;

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
        string outfile(prg_options.out != NULL ? prg_options.out : "new_profile.aln");

        printf("fasta file              => %s\n", prg_options.fasta);
        printf("profile file            => %s\n", prg_options.aln);
        printf("output file             => %s\n", outfile.c_str());
        printf("match score             => %d\n", prg_options.match);
        printf("mismatch penalty score  => %d\n", prg_options.mismatch);
        printf("gap penalty score       => %d\n", prg_options.gap);

        string seq;
        string seq_title;
        fill_sequence_buff(seq, seq_title, prg_options.fasta);

        vector<string> seqs;
        vector<string> seqs_titles;
        fill_profile_buff(seqs, seqs_titles, prg_options.aln);

        scoring scores = {prg_options.match, prg_options.mismatch, prg_options.gap};
        align_seq_to_profile(seq, seqs, seqs_titles, scores, seq_title, outfile);
    }

    return 0;
}
