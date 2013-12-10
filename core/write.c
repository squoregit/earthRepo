
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
    char inst;
    char lang;
    int ok = 0;
    
    format_output("Would you like instructions, y/n [default is n]-> ",0);
    inst = waiting_loop();
    if (inst != 'y' && inst != 'Y')
    {
      ok = 1;
      return(ok);
    }
    format_output("In which language,e(nglish)/f(rench)/i(talian)/g(erman)/b(elgian)/r(ussian) [default is e(nglish)]-> ",0);
    lang = waiting_loop();
    switch (lang)
      {
      case 'r':
      case 'R':
	format_output("Are you sure? y/n [default is n]-> ",0);
	inst = waiting_loop();
	if (inst == 'n' || inst == 'N')
	  return(0);
	else
	  {
	    format_output("You really thought you could get russian  \n",0);
	    ok = 1;
	    return(ok);
	  }	
      case 'i':
      case 'I':
	format_output("Are you sure? y/n [default is n]-> ",0);
	inst = waiting_loop();
	if (inst == 'n' || inst == 'N')
	  return(0);
	else
	  {
	    format_output("  I was joking   \n",0);
	    ok = 1;
	    return(ok);
	  }
      case 'g':
      case 'G':
	format_output("Are you sure? y/n [default is n]-> ",0);
	inst = waiting_loop();
	if (inst == 'n' || inst == 'N')
	  return(0);
	else
	  {
	    format_output("  I don't understand  \n",0);
	    ok = 1;
	    return(ok);
	  }
      case 'b':
      case 'B':
	format_output("Are you sure? y/n [default is n]-> ",0);
	inst = waiting_loop();
	if (inst == 'n' || inst == 'N')
	  return(0);
	else
	  {
	    format_output(" Are you (w)alloon ou (f)lemish ?   \n",0);
	    inst = waiting_loop();
	    if (inst == 'f' || inst == 'F')
	      {
		format_output("Sorry, i never learnt flemish\n",0);
		ok = 1;
		return(ok);
	      }
	    else
	      {
		print_instructions_fr();
		ok = 1;
		return(ok);
	      }
	    print_instructions_fr();
	    ok = 1;
	    return(ok);
	  }
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
