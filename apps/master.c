
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
  while (getchar() != '\n') 
    format_output("\n-- More --   ",0); 
} 

void setcolors() 
     /****************************************/ 
     /* Function: Initializes the code      */ 
     /****************************************/ 
{ 
  int x, val, y; 
  int digit_found, place_found; 
  time_t t;
  
  time(&t);
  srand((unsigned int) t);

  for (x = 0; x < 6; x++) 
    dig[x] = BAD_COLOR; 
  
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
  /* if a parameter is present, the machine code is displayed */ 
  if (argc > 1) 
    JACKPOT = 1; 
  
  while (!instruction()); /* to display game rules*/ 
  player = TRUE; 
  game_won = FALSE; 
  
  format_output("Do you want to guess, or make up the code,",0); 
  format_output(" g/m [default is g] -> ",0); 
  
  /* >RELAX<NOASGCOND>: clearing out the buffer by assigning inst to the next char  */
  if ((inst = getchar()) != '\n') 
    while (getchar() != '\n');   /* %RELAX<COMPOUND>: keeping some conciseness by avoiding using compound {} */

  /*result used for FullMCDC test */
  result =(inst == 'm' || inst == 'M');
  if (result) 
    player = FALSE; 
  
  setcolors(); /* initializes the colors */ 
  if (player) 
    player_plays(); 
  else 
    machine_plays(); 
  
  exit(0); 
} 
