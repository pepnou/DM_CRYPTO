
#include "Options.h"

const char *argp_program_version =
  "TestPrimalité v1.0";
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
static char args_doc[] = "NUMBER\nFILE INDEX";

/* The options we understand. */
static struct argp_option options[] = {
  {"verbose",  'v', 0,       0, "Produce verbose output" },
  {"base",  'b', 0,       0, "Base dans laquelle est lu le nombre" },
  {"position",  'p', "INDEX",       0,
   "Selection de l'indice de l'entier dans le fichier" },
  {"input",   'i', "FILE",  0,
   "Input from FILE instead of standard output" },
  { 0 }
};

/* Used by main to communicate with parse_opt. */
struct arguments
{
  int verbose;   /* ‘-v’ */
  char* input_file;            /* file from ‘--input’ */
  int index;
  int base;
  char* number;
  size_t argz_len;
  char* argz;
};

/* Parse a single option. */
static error_t
parse_opt (int key, char *arg, struct argp_state *state)
{
  /* Get the input argument from argp_parse, which we
     know is a pointer to our arguments structure. */
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
	    if(count == 0)
	    {
			argument->input_file = arg;
			argument->number = arg;
		} else if(count == 1)
	    {
			argument->index = atoi(arg);
			argument->number = NULL;
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
	    if (count > 2)
	    argp_failure (state, 1, 0, "too many arguments");
	    else if (count < 1)
	    argp_failure (state, 1, 0, "too few arguments");
	    else if (count == 1)
	    argument->input_file = NULL;
      }
	break;
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
  

  /* Parse our arguments; every option seen by parse_opt will be
     reflected in arguments. */
  argp_parse (&argp, argc, argv, 0, 0, &arguments);
  
  printf("xd\n");
  
  if(arguments.input_file)
	printf("%s %d\n",arguments.input_file,arguments.index);
  else
	printf("%s\n",arguments.number);
}
