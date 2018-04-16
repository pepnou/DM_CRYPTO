
#include "Options.h"

const char *argp_program_version =
  "TestPrimalité 1.0";
const char *argp_program_bug_address =
  "<thibaut.pepin@ens.uvsq.fr>";

/* Program documentation. */
static char doc[] =
  "Argp example #4 -- a program with somewhat more complicated \
options\
\vThis part of the documentation comes *after* the options;\
 note that the text is automatically filled, but it's possible\
 to force a line-break, e.g.\n<-- here.";

/* A description of the arguments we accept. */
static char args_doc[] = "ARG1 [STRING...]";

/* The options we understand. */
static struct argp_option options[] = {
  {"verbose",  'v', 0,       0, "Produce verbose output" },
  {"index",  'p', 0,       0, "Selection de l'indice de l'entier dans le fichier" },
  {"input",   'i', "FILE",  0,
   "Input from FILE instead of standard output" },
  { 0 }
};

/* Used by main to communicate with parse_opt. */
struct arguments
{
  int verbose;   /* ‘-s’, ‘-v’, ‘--abort’ */
  char *input_file;            /* file from ‘--input’ */
};

/* Parse a single option. */
static error_t
parse_opt (int key, char *arg, struct argp_state *state)
{
  /* Get the input argument from argp_parse, which we
     know is a pointer to our arguments structure. */
  struct arguments *arguments = state->input;

  switch (key)
    {
    case 'v':
      arguments->verbose = 1;
      break;
    case 'i':
      arguments->input_file = arg;
      break;
    default:
      return ARGP_ERR_UNKNOWN;
    }
  return 0;
}

/* Our argp parser. */
static struct argp argp = { options, parse_opt, args_doc, doc };





void Option(int argc, char** argv)
{
	//int i, j;
  struct arguments arguments;

  /* Default values. */
  arguments.verbose = 0;
  arguments.input_file = "-";

  /* Parse our arguments; every option seen by parse_opt will be
     reflected in arguments. */
  argp_parse (&argp, argc, argv, 0, 0, &arguments);

  /*for (i = 0; i < arguments.repeat_count; i++)
    {
      printf ("ARG1 = %s\n", arguments.arg1);
      printf ("STRINGS = ");
      for (j = 0; arguments.strings[j]; j++)
        printf (j == 0 ? "%s" : ", %s", arguments.strings[j]);
      printf ("\n");
      printf ("OUTPUT_FILE = %s\nVERBOSE = %s\nSILENT = %s\n",
              arguments.output_file,
              arguments.verbose ? "yes" : "no",
              arguments.silent ? "yes" : "no");
    }*/
}
