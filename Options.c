#include <stdlib.h>
#include <error.h>
#include <argp.h>
#include <argz.h>

const char *argp_program_version =
  "TestPrimalité v2.0";
const char *argp_program_bug_address =
  "<thibaut.pepin@ens.uvsq.fr>, <kamilia.loualia@ens.uvsq.fr>";

/* Program documentation. */
static char doc[] =
  "TestPrimalité -- a program that test the primality of a big number. \
  \n\nThe file given must contain number seperated by white space.\
\vIf the base is specified, it must be between 2 and 62. For bases up \
to 36, case is ignored; upper-case and lower-case letters have the same \
value. For bases 37 to 62, upper-case letter represent the usual 10..35 \
while lower-case letter represent 36..61.";

/* A description of the arguments we accept. */
static char args_doc[] = "NUMBER\nFILE INDEX";

/* The options we understand. */
static struct argp_option options[] = {
  {"verbose",  'v', 0,       0, "Produce verbose output" },
  {"base",  'b', "BASE",       0, "Base of the input number, default is 10" },
  {"repetitions",  'r', "REP",       0, "Number of repetitions of the algorithm, default is 15" },
  { 0 }
};

/* Used by main to communicate with parse_opt. */
struct arguments
{
  int verbose;
  char* input_file;
  int index;
  int base;
  int repetitions;
  char* number;
  size_t argz_len;
  char* argz;
};

/* Parse a single option. */
static error_t
parse_opt (int key, char *arg, struct argp_state *state)
{
  struct arguments* argument = state->input;

  switch (key)
    {
    case 'v':
      argument->verbose = 1;
      break;
    case 'b':
      argument->base = atoi(arg);
      break;
    case 'r':
      argument->repetitions = atoi(arg);
      break;
    case ARGP_KEY_ARG:
	  {
	    size_t count = argz_count (argument->argz, argument->argz_len);
	    
	    switch(count)
	    {
			case 0:
				argument->input_file = arg;
				argument->number = arg;
				break;
			case 1:
				argument->index = atoi(arg);
				break;
		}
		
	    argz_add (&argument->argz, &argument->argz_len, arg);
	  }
	  break;
	case ARGP_KEY_INIT:
	  argument->argz = 0;
	  argument->argz_len = 0;
	  argument->verbose = 0;
	  argument->base = 10;
	  argument->repetitions = 15;
	  argument->input_file = NULL;
	  argument->number = NULL;
	  break;
	case ARGP_KEY_END:
	  {
	    size_t count = argz_count (argument->argz, argument->argz_len);
	    if (count > 2)
	    argp_failure (state, 1, 0, "too many arguments, run with --help");
	    else if (count < 1)
	    argp_failure (state, 1, 0, "too few arguments, run with --help");
	    else if (count == 1)
	    argument->input_file = NULL;
      }
	break;
    }
  return 0;
}

/* Our argp parser. */
static struct argp argp = { options, parse_opt, args_doc, doc };
