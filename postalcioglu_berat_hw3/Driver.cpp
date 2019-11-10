/**
 * @description   Sequence alignment program
 * @author        Berat Postalcioglu - 21401769 
 **/

#include "NeedlemanWunschAlignment.h"
#include "NeedlemanWunschAffineAlignment.h"
#include "SmithWatermanAlignment.h"
#include "SmithWatermanAffineAlignment.h"
#include "IOHelper.h"
#include <stdio.h>
#include <getopt.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

struct prg_options
{
  char *mode = NULL;
  char *input = NULL;
  int gapopen = -1;
  int gapext = -2;
};

static const char *help =
    "usage: allalign [option] ... [arg]\n\
Options and arguments:\n\
--mode    or -m [global | local | aglobal | alocal]    : specifies which alignment mode should be used (REQUIRED)\n\
--input   or -i [<filename>.fasta]                     : input FASTA file for sequences (REQUIRED)\n\
--gapopen or -o [number]                               : gap opening penalty for affine gap model, or unit gap cost for naive model (should be numeric)\n\
--gapext  or -e [number]                               : gap extension penalty for affine gap model\n";

int main(int argc, char **argv)
{
  prg_options prg_options;

  const char *optstring = "m:i:o:e:"; // --mode, --input, --gapopen, --gapext
  static struct option long_options[] = {
      {"mode", required_argument, NULL, 'm'},
      {"input", required_argument, NULL, 'i'},
      {"gapopen", required_argument, NULL, 'o'},
      {"gapext", required_argument, NULL, 'e'},
      {0, 0, 0, 0}};

  int c, option_index = 0;
  while ((c = getopt_long(argc, argv, optstring, long_options, &option_index)) != -1)
  {
    switch (c)
    {
    case 'm':
      prg_options.mode = optarg;
      break;
    case 'i':
      prg_options.input = optarg;
      break;
    case 'o':
      prg_options.gapopen = atoi(optarg);
      break;
    case 'e':
      prg_options.gapext = atoi(optarg);
      break;
    case '?':
      if (!isprint(optopt))
        fprintf(stderr, "Unknown option character `\\x%x'.\n", optopt);
      exit(1);
    default:
      abort();
    }
  }

  if (prg_options.mode == NULL || prg_options.input == NULL)
  {
    printf("%s", help);
    exit(1);
  }
  else
  {
    char *s1 = NULL;
    char *s2 = NULL;
    char *title1 = NULL;
    char *title2 = NULL;
    fill_buffers((char **)&s1, (char **)&s2, (char **)&title1, (char **)&title2, prg_options.input);

    printf("input file            => %s\n", prg_options.input);
    printf("mode                  => %s\n", prg_options.mode);
    printf("gap open penalty      => %d\n", prg_options.gapopen);
    printf("gap extension penalty => %d\n", prg_options.gapext);
    printf("aligning...\n\n");

    if (strcmp(prg_options.mode, "global") == 0)
    {
      needleman_wunsch_align(s1, s2, title1, title2, prg_options.gapopen);
    }
    else if (strcmp(prg_options.mode, "aglobal") == 0)
    {
      needleman_wunsch_affine_align(s1, s2, title1, title2, prg_options.gapopen, prg_options.gapext);
    }
    else if (strcmp(prg_options.mode, "local") == 0)
    {
      smith_waterman_alignment(s1, s2, title1, title2, prg_options.gapopen);
    }
    else if (strcmp(prg_options.mode, "alocal") == 0)
    {
      smith_waterman_affine_alignment(s1, s2, title1, title2, prg_options.gapopen, prg_options.gapext);
    }
    else
    {
      printf("%s", "--mode or -m options must be one of the following arguments [global | local | aglocal | alocal]\n");
    }

    free(s1);
    free(s2);
    free(title1);
    free(title2);
  }

  for (int index = optind; index < argc; index++)
  {
    printf("Non-option argument %s\n", argv[index]);
  }

  return 0;
}
