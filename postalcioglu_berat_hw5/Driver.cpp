/**
 * @description   I/O helper
 * @author        Berat Postalcioglu - 21401769 
 **/

#include "algos/NeedlemanWunschAffineAlignment.h"
#include "data_structures/Typedefs.h"
#include "data_structures/Seq.h"
#include "helpers/IOHelper.h"
#include <iostream>
#include <vector>
#include <getopt.h>

using namespace std;

#define REP(i, a, b) for (u32 i = a; i < b; i++)

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

void construct_distance_matrix(const vector<seq> &seqs, double **dm, const prg_options& prg_options);
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

    vector<seq> seqs;
    fill_sequences_buff(seqs, prg_options.fasta);
    u32 seqs_size = seqs.size();

    // allocate distance matrix
    double **dm = new double *[seqs_size]; // distance matrix
    REP(i, 0, seqs_size)
    {
      dm[i] = new double[seqs_size]{0};
    }
    construct_distance_matrix(seqs, dm, prg_options);

    // display distance matrix
    cout << "--- distance matrix ---" << "\n";
    for (u32 i = 0; i < seqs_size; i++)
    {
      for (u32 j = 0; j < seqs_size; j++)
      {
        cout << dm[i][j] << " ";
      }
      cout << "\n";
    }

    // for (auto it : seqs)
    // {
    //   cout << it.seq << "\n";
    // }

    // free memory
    REP(i, 0, seqs_size)
    {
      delete[] dm[i];
    }
    delete[] dm;
  }

  return 0;
}

void construct_distance_matrix(const vector<seq> &seqs, double **dm, const prg_options& prg_options)
{
  u32 seqs_size = seqs.size();

  // construct distance matrix
  for (u32 i = 0; i < seqs_size - 1; i++)
  {
    for (u32 j = i + 1; j < seqs_size; j++)
    {
      dm[i][j] = needleman_wunsch_affine_align(seqs[i].seq.c_str(), seqs[j].seq.c_str(), prg_options.match, prg_options.mismatch, prg_options.gapopen, prg_options.gapext);
      dm[j][i] = dm[i][j];
    }
  }
}
