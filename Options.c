#define debug printf("line : %d in function : %s\n",__LINE__,__func__);

#include <stdlib.h>
#include <error.h>
#include <argp.h>
#include <argz.h>

const char *argp_program_version =
  "TestPrimalité v1.0";
const char *argp_program_bug_address =
  "<thibaut.pepin@ens.uvsq.fr>, <kamilia.loualia@ens.uvsq.fr>";

/* Program documentation. */
static char doc[] =
  "TestPrimalité -- a program that test the primality of a big number \
\vThis part of the documentation comes *after* the options;\
 note that the text is automatically filled, but it's possible\
 to force a line-break, e.g.\n<-- here.";

/* A description of the arguments we accept. */
static char args_doc[] = "NUMBER REPETITIONS\nFILE INDEX REPETITIONS";

/* The options we understand. */
static struct argp_option options[] = {
  {"verbose",  'v', 0,       0, "Produce verbose output" },
  {"base",  'b', "BASE",       0, "Base of the input number, default is 10" },
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
			argument->repetitions = atoi(arg);
				break;
			case 2:
				argument->repetitions = atoi(arg);
			argument->number = NULL;
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
	  argument->input_file = NULL;
	  argument->number = NULL;
	  break;
	case ARGP_KEY_END:
	  {
	    size_t count = argz_count (argument->argz, argument->argz_len);
	    if (count > 3)
	    argp_failure (state, 1, 0, "too many arguments, run with --help");
	    else if (count < 2)
	    argp_failure (state, 1, 0, "too few arguments, run with --help");
	    else if (count == 2)
	    argument->input_file = NULL;
      }
	break;
    }
  return 0;
}

/* Our argp parser. */
static struct argp argp = { options, parse_opt, args_doc, doc };
