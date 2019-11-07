/**
 * @name   sequence alignment program
 * @author Berat Postalcioglu - 21401769 
 **/

#include <stdio.h>
#include <getopt.h>
#include <string>

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
--mode    or -m [global | local | aglobal | alocal] : specifies which alignment mode should be used (REQUIRED)\n\
--input   or -i [<filename>.fasta]                  : input FASTA file for sequences (REQUIRED)\n\
--gapopen or -o [num]                               : gap opening penalty for affine gap model, or unit gap cost for naive model (should be numeric)\n\
--gapext  or -e [num]                               : gap extension penalty for affine gap model\n";

int score_matrix[4][4] =
  //  a   c   g   t
    {{2, -3, -3, -3},  // a
     {-3, 2, -3, -3},  // c
     {-3, -3, 2, -3},  // g
     {-3, -3, -3, 2}}; // t

int main(int argc, char **argv)
{
  struct prg_options prg_options;

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
      return 1;
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
    std::string mode_str = std::string(prg_options.mode);
    if (mode_str != "global" && mode_str != "aglobal" && mode_str != "local" && mode_str != "alocal")
    {
      printf("%s", "--mode or -m options must be one of the following arguments [global | local | aglocal | alocal]\n");
      exit(1);
    }
  }

  printf("prg_options.mode = %s\n", prg_options.mode);
  printf("prg_options.input = %s\n", prg_options.input);
  printf("prg_options.gapopen = %d\n", prg_options.gapopen);
  printf("prg_options.gapext = %d\n", prg_options.gapext);

  for (int index = optind; index < argc; index++)
  {
    printf("Non-option argument %s\n", argv[index]);
  }

  return 0;
}