
#include <stdlib.h> 
#include <stdio.h> 
#include <string.h> 

#include "base.h" 
#include "master.h" 
 
void end_game(int* curr , int* typ) 
     /******************************************/ 
     /* function: redefines current number of  */ 
     /*           guesses to quit playing      */ 
     /*                                        */ 
     /* Parameters:                            */ 
     /*      curr: IN OUT current guess number */ 
     /*      typ: IN OUT var to quit the game  */ 
     /******************************************/  
{ 
  *curr = MAX_TRY; 
  *typ = TRUE; 
} 

void prompt(char* s) 
{ 
    if (player) 
      printf("PLAYER--> %s",s); 
    else 
      printf("MACHINE--> %s",s); 
} 

void format_output(char* s, int code) 
     /******************************************/ 
     /* function: formats screen messages      */ 
     /*                                        */ 
     /* Parameters:                            */ 
     /*      s: IN OUT message                 */ 
     /*      code: IN to prefix or not prefix  */ 
     /*               messages                 */ 
     /******************************************/ 
{ 
  if (code == 0) /* not prefixed message */ 
    printf("%s",s); 
  else  /* prefixed message */ 
    prompt(s); 
} 

void skipline(int nb) 
     /******************************************/ 
     /* function: skips lines                  */ 
     /*                                        */ 
     /* Parameters:                            */ 
     /*      nb: IN number of lines to skip    */ 
     /******************************************/ 
{ 
  int i = 0; 
  while (MIN(i,i) < nb)  /*%RELAX<Complexity_11_NoCommaAndTernary> Ternary Operator in macro MIN */
    { 
      printf("\n"); 
      i++; 
    } 
} 


void set_dummy() 
     /********************************************/ 
     /* function: defines a dummy guess structure*/ 
     /*                                          */ 
     /* Parameters:                              */ 
     /*                                          */ 
     /********************************************/ 
{ 
  int x; 
  
  dummy[cur].blacks = dummy[cur].whites = 0; 
  
  for (x = 0; x < 4; x++) 
    { 
      dummy[cur].pegs[x].used = NONE; 
      dummy[cur].pegs[x].color = guesses[cur].pegs[x].color; 
    } 
} 

void make_code(guess* ges) 
     /******************************************/ 
     /* function: defines a random code        */ 
     /*                                        */ 
     /* Parameters:                            */ 
     /*      ges: IN OUT guess structure       */ 
     /******************************************/ 
{ 
  int x; 
  int random_value; 
  
  for (x = 0; x < 4; x++) /* creates random code */ 
    {                       
      /* if you want a random value: random_value = rand();*/ 
      random_value = x; 
      ges->pegs[x].color = random_value % 6; 
      ges->blacks = 0; 
      ges->whites = 0; 
    }                       
} 
 
int find_digit(char col_name[7]) 
     /******************************************/ 
     /* function: checks wether the color is   */ 
     /*            authorized                  */ 
     /*                                        */ 
     /* Parameters:                            */ 
     /*      col_name: IN color name           */ 
     /*                                        */ 
     /* Return:                                */ 
     /*       s: color number                  */ 
     /******************************************/ 
{ 
  int result;
  int s; 
  int max; 
  max = 6; 
  for (s = 0; s < max; s++) 
    { 
      
      /* result used for FullMCDC test*/
      result=(strlen(col_name) == strlen(col[dig[s]]) 
	      &&  
	      !(strncmp(col[dig[s]],col_name,strlen(col_name))));
      
      if (result)
	return(s); 
    }
  return(BAD_COLOR); /*  not a valid color */ 
}


