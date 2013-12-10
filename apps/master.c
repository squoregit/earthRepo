
#include <stdlib.h> 
#include <stdio.h> 
#include <time.h>

#include "base.h" 
#include "master.h" 
#include "write.h" 
#include "player.h" 
#include "machine.h" 
 
int JACKPOT;  
 
char  *col[6] = { "white", 
                  "black", 
                  "red", 
                  "green", 
                  "yellow", 
                  "blue"}; 
 
int    dig[6]; 
int    cur; 
guess  guesses[MAX_TRY]; 
guess  dummy[MAX_TRY]; 
guess  code; 
int    game_won, player, check, cons; 
 
void rest() 
{ 
   format_output("\n-- More --   ",0); 
} 


void setcolors() 
{
  int x, val, y; 
  int digit_found, place_found; 
  time_t t; 
  time(&t);
  srand((unsigned int) t);

   dig[0] = BAD_COLOR;
   dig[1] = BAD_COLOR;
   dig[2] = BAD_COLOR;
   dig[3] = BAD_COLOR;
   dig[4] = BAD_COLOR;
   dig[5] = BAD_COLOR; 
  
  for (x = 6; x > 1; x--) 
    { 
      /* if you want a random value: val = rand() % x;*/ 
      val = x - 1;     
      val = rand() %x;
      place_found = FALSE;
      while (!place_found) 
	{ 
	  digit_found = FALSE; 
	  for (y = 0; y < (6 - x); y++) 
	    if (val == dig[y]) 
	      digit_found = TRUE; 
	  if (!digit_found) 
	    { 
	      dig[y] = val; 
	      place_found = TRUE; 
	    } 
	  else 
	    val = (val + 5) % 6; 
	} 
    } 
  
  dig[5] = 15 - dig[4] - dig[3] - dig[2] - dig[1] - dig[0]; 
} 

void main(int argc, char* argv[]) 
{ 
  char inst; 
  int result; 
  
  /* to display game rules*/ 
  player = TRUE; 
  game_won = FALSE; 
  
  format_output("Do you want to guess, or make up the code,",0); 
  format_output(" g/m [default is g] -> ",0); 
  
  /*result used for FullMCDC test */
  result =(inst == 'm' || inst == 'M');
  if (result) 
    player = FALSE; 

  /* initializes the colors */
  setcolors();  

   /* initializes the role */
  if (player) 
    player_plays(); 
  else 
    machine_plays(); 
  
  exit(0); 
} 