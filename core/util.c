
#include <stdio.h>

#include "util.h"
#include "base.h"
#include "master.h"


void refresh()
{
  int x, y;
  
  if (!player && check)
    {
      format_output("Your correct sequence:  ",1);
      for (y = 0; y < 4; y++)
	printf("%-8s",col[dig[code.pegs[y].color]]);
      skipline(2);
    }
  
  for (x = 0; x < cur; x++)
    {
      printf("%2d.  ",x + 1);
      for (y = 0; y < 4; y++)
	printf("%-8s",col[dig[guesses[x].pegs[y].color]]);
      for (y = 0; y < guesses[x].blacks; y++)
	format_output("b",0);
      for (y = 0; y < guesses[x].whites; y++)
	format_output("w",0);
      skipline(1);
    }
  skipline(1);
}


void consistent()
{
  int x, y, z;
  
  for (z = 0; z < cur; z++)
    {
      dummy[z].blacks = dummy[z].whites = 0;
      
      for (x = 0; x < 4; x++)
	guesses[cur].pegs[x].used = dummy[z].pegs[x].used = NONE;
      
      for (x = 0; x < 4; x++)
	if (guesses[cur].pegs[x].color == dummy[z].pegs[x].color)
	  {
	    dummy[z].pegs[x].used = guesses[cur].pegs[x].used = BLACK;
	    dummy[z].blacks++;
	  }
      if (dummy[z].blacks != 4)
	{
	  for (x = 0; x < 4; x++)
	    for (y = 0; y < 4; y++)
	      if (guesses[cur].pegs[x].color == dummy[z].pegs[y].color &&
		  !dummy[z].pegs[y].used && !guesses[cur].pegs[x].used)
		{
		  dummy[z].pegs[y].used = guesses[cur].pegs[x].used = 
		    WHITE;
		  dummy[z].whites++;
		}
	}
    }
  
  cons = TRUE;
  
  for (z = 0; z < cur; z++)
    {
      if (dummy[z].blacks != guesses[z].blacks ||
	  dummy[z].whites != guesses[z].whites)
	{
	  if (cons)
	    {
	      cons = FALSE;
	      if (player)
		format_output("Inconsistent guess.  If this were correct:\n",1);
	    }
	  if (player)
	    {
	      printf("    guess #%d would have gotten ",z + 1);
	      printf("%d black and %d white.\n",dummy[z].blacks,dummy[z].whites);
	    }
	}
    }
  if (cons && player)
    format_output("This guess is consistent with all previous clues.\n",1);
}


