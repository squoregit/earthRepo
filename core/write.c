
#include <stdio.h>

#include "write.h"
#include "base.h"
#include "master.h"

int waiting_loop()
{
  char inst;
  if ((inst = getchar()) != '\n') ;
  return(inst);
}

void print_help()
{
  format_output ("        GUESS: Make another guess, same as before, using the\n",0);
  format_output ("               score from previous guesses to make deductions.\n",0);
  printf ("               You have %d chances to find the right code.\n\n",MAX_TRY);
  format_output ("        REFRESH: Shows all your previous guesses and scores.\n\n",0);
  format_output ("        QUIT: You don't want to play anymore.  Remember, the code\n",0);
  format_output ("              will not be revealed if you quit.\n\n",0);
  format_output ("        PRINT: Display a local help.\n\n",0);
}

void print_instructions_gb()
{
  skipline(2);
  format_output ("                    Instructions for Master Mind\n\n",0);
  format_output ("To Be Completed",0);
  print_help();
  skipline(2);
}

void print_instructions_fr()
{
  skipline(2);
  format_output("                   Regles du jeu de Master Mind\n\n",0);
  format_output("A completer",0);
   print_help();
   skipline(2);
}

int instruction()
{
    char lang;
    int ok = 0;

    format_output("In which language,e(nglish)/f(rench)/i(talian)/g(erman)/b(elgian)/r(ussian) [default is e(nglish)]-> ",0);
    lang = waiting_loop();
    switch (lang)
   {
      case 'r':
      case 'R':
		format_output("Instructions in Russian ... to be completed",0);
		break;
      case 'i':
      case 'I':
		format_output("Instructions in Italian ... to be completed",0);
		break;
      case 'g':
      case 'G':
		format_output("Instructions in German ... to be completed",0);
		break;
      case 'b':
      case 'B':
		format_output("Instructions in Flamish ... to be completed",0);
		break;
      case 'f':
      case 'F':
		print_instructions_fr();
		break;
      case 'e':
      case 'E':
		print_instructions_gb();
		break;
      default:
		print_instructions_gb();
		break;
	}
    ok = 1;
    return(ok);
}
