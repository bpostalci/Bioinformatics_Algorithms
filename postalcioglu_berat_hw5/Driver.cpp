/**
 * @description   I/O helper
 * @author        Berat Postalcioglu - 21401769 
 **/

#include "Typedefs.h"
#include "IOHelper.h"
#include "Seq.h"
#include <iostream>
#include <vector>
#include <getopt.h>

using namespace std;

struct prg_options
{
  char *fasta = NULL;
  char *out = NULL;
  int gapopen = -1;
  int gapext = -1;
  int match = 2;
  int mismatch = -1;
};

static const char *help =
    "usage: buildUPGMA [option] ... [arg]\n\
Options and arguments:\n\
--fasta    or -f  [<filename>.fasta]  : sequences fasta file (REQUIRED)\n\
--out      or -o  [<filename>.tree]   : UPGMA output file path (default: sequences.tree)\n\
--match    or -m  [number]            : match score\n\
--gapopen  or -g  [number]            : gap opening penalty score\n\
--gapext   or -e  [number]            : gap extension penalty score\n\
--mismatch or -i  [number]            : mismatch penalty score\n";

int main(int argc, char **argv)
{

  prg_options prg_options;

  const char *optstring = "f:o:g:e:m:i:";
  static struct option long_options[] = {
      {"fasta", required_argument, NULL, 'f'},
      {"out", required_argument, NULL, 'o'},
      {"gapopen", required_argument, NULL, 'g'},
      {"gapext", required_argument, NULL, 'e'},
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
    case 'o':
      prg_options.out = optarg;
      break;
    case 'g':
      prg_options.gapopen = atoi(optarg);
      break;
    case 'e':
      prg_options.gapext = atoi(optarg);
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

  if (prg_options.fasta == NULL)
  {
    printf("%s", help);
    exit(1);
  }
  else
  {
    string outfile(prg_options.out != NULL ? prg_options.out : "sequences.tree");

    printf("fasta file                   => %s\n", prg_options.fasta);
    printf("output file                  => %s\n", outfile.c_str());
    printf("gap opening penalty score    => %d\n", prg_options.gapopen);
    printf("gap extension penalty score  => %d\n", prg_options.gapext);
    printf("match score                  => %d\n", prg_options.match);
    printf("mismatch penalty score       => %d\n", prg_options.mismatch);

    // vector<seq> seqs;
    // fill_sequences_buff(seqs, "sequences.fasta");

    // for(auto it : seqs)
    // {
    //   cout << it.seq << "\n";
    //   cout << it.title << "\n";
    //   cout << it.score << "\n";
    // }
  }

  return 0;
}
