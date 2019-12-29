#include "helpers/IOHelper.h"
#include "data_structures/Typedefs.h"
#include "data_structures/Bloomfilter.h"
#include "algos/Murmur2.h"
#include "algos/Jenkins.h"
#include "algos/FNV.h"
#include <iostream>
#include <vector>
#include <functional>
#include <getopt.h>
#include <limits>

using namespace std;

struct prg_options
{
  char *ref = NULL;
  char *query = NULL;
  u32 kmer_len = 1;
  u32 bloom_size = 50;
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

  if (prg_options.ref == NULL || prg_options.query == NULL)
  {
    printf("%s", help);
    exit(1);
  }
  else
  {
    printf("reference FASTA file   => %s\n", prg_options.ref);
    printf("query FASTA file       => %s\n", prg_options.query);
    printf("kmer length            => %d\n", prg_options.kmer_len);
    printf("bloomsize              => %d\n", prg_options.bloom_size);

    vector<string> ref_seqs, query_seqs;

    fill_sequences_buff(ref_seqs, prg_options.ref, prg_options.kmer_len);
    fill_sequences_buff(query_seqs, prg_options.query, prg_options.kmer_len);

    // cout << "reference sequences\n";
    // for (auto it : ref_seqs)
    // {
    //   cout << it << "\n";
    // }

    // cout << "query sequences\n";
    // for (auto it : query_seqs)
    // {
    //   cout << it << "\n";
    // }

    bloomfilter bf(prg_options.kmer_len, (u64)(prg_options.bloom_size * 8));
    bf.add_hash_func(murmur_hash);
    bf.add_hash_func(jenkins_hash);
    bf.add_hash_func(fnv_hash);
    bf.generate(ref_seqs);
    u32 result = bf.query(query_seqs);

    // print result to stdout
    cout << "\n=== RESULT ===\n";
    cout << "Number of k-mers indexed in reference: " << bf.indexed_kmers() << "\n";
    cout << "Number of k-mers scanned in query: " << bf.scanned_kmers() << "\n";
    cout << "Number of k-mers from query found in the reference: " << result << "\n";

    // cout << "size: " << bf.bitvector().size() << "\n";
    // for(auto it : bf.bitvector())
    // {
    //   cout << it << " ";
    // }
    // cout << "\n";

  }

  return 0;
}
