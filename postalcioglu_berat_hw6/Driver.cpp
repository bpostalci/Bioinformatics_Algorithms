#include <iostream>
#include <getopt.h>

using namespace std;

#define REP(i, a, b) for (u32 i = a; i < b; i++)

struct prg_options
{
  char *ref = NULL;
  char *query = NULL;
  int kmer_len = 1;
  int bloom_size = 1;
};

static const char *help =
    "usage: buildUPGMA [option] ... [arg]\n\
Options and arguments:\n\
--ref        or -f  [<filename>.fasta]  : FASTA-formatted file that contains the sequences to index.\n\
--query      or -o  [<filename>.fasta]  : FASTA-formatted file that contains the sequences to search in reference.\n\
--kmer       or -m  [number]            : kmer length.\n\
--bloomsize  or -g  [number]            : Size of the Bloom filter bit vector in bytes\n";

int main(int argc, char **argv)
{
  prg_options prg_options;

  const char *optstring = "r:q:k:b:";
  static struct option long_options[] = {
      {"ref", required_argument, NULL, 'r'},
      {"query", required_argument, NULL, 'q'},
      {"kmer", required_argument, NULL, 'k'},
      {"bloomsize", required_argument, NULL, 'b'}};

  int c, option_index = 0;
  while ((c = getopt_long(argc, argv, optstring, long_options, &option_index)) != -1)
  {
    switch (c)
    {
    case 'r':
      prg_options.ref = optarg;
      break;
    case 'q':
      prg_options.query = optarg;
      break;
    case 'k':
      prg_options.kmer_len = atoi(optarg);
      break;
    case 'b':
      prg_options.bloom_size = atoi(optarg);
      break;
    default:
      printf("%s", help);
      exit(1);
    }
  }

  printf("reference FASTA file   => %s\n", prg_options.ref);
  printf("query FASTA file       => %s\n", prg_options.query);
  printf("kmer length            => %d\n", prg_options.kmer_len);
  printf("bloomsize              => %d\n", prg_options.bloom_size);

  return 0;
}

