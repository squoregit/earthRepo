#include <stdlib.h> 
#include <stdio.h> 
#include <string.h> 

#include "base.h" 

/* a very simple function with no control structure */
int cf_1_asimplesequence()
{
   int ok = 0;
   format_output("Would you like instructions, y/n [default is n]-> ",0);
}

/* a simple function with just an if structure */
int cf_2_anif()
{
	char inst;
    format_output("Would you like help, y/n [default is n]-> ",0);
    inst = waiting_loop();
    if (inst != 'y' && inst != 'Y')
    {
		print_help();
    }
}

/* a simple function with just an if-else structure */
int cf_3_anifelse()
{
	char inst;
    format_output("Would you like instructions in french, y/n [default is n]-> ",0);
    inst = waiting_loop();
    if (inst != 'y' && inst != 'Y')
    {
		print_instructions_fr();
    }
	else
	{
		print_instructions_gb();
	}	
}

/* a simple function with a for structure */
int cf_4_afor()
{
  int x; 
  
  dummy[cur].blacks = dummy[cur].whites = 0; 
  for (x = 0; x < 4; x++) 
    { 
      dummy[cur].pegs[x].used = NONE; 
      dummy[cur].pegs[x].color = guesses[cur].pegs[x].color; 
    } 
} 

/* a simple function with a while structure */
int cf_5_awhile()
{
  int i = 0; 
  while (i < nb)
  { 
    printf("\n"); 
    i++; 
  } 
} 

/* a simple function with a do...while structure */
int cf_6_adowhile(nb)
{
  int i = 0; 
  do 
  { 
    printf("\n"); 
    i++; 
  } 
  while (i < nb);
} 

/* a simple function with return statement */
int cf_7_return()
{
	char inst;
	int ok = 0;
    format_output("Would you like instructions in french, y/n [default is n]-> ",0);
    inst = waiting_loop();
    if (inst != 'y' && inst != 'Y')
    {
		print_instructions_fr();
		return(ok);
    }
	print_instructions_gb();	
}

/* a simple function with a switch structure */
int cf_8_alargeswitch()
{
    char inst;
    char year;
    int ok = 1;
    
    format_output("Please type the last digit of your birth year -> ",0);
    year = waiting_loop();
    switch (year)
    {
    case '0':
			format_output("You'll be the 'A' player !  \n",0);
			break;	
    case '1':
			format_output("You'll be the 'B' player !  \n",0);
			break;	
	case '2':
			format_output("You'll be the 'C' player !  \n",0);
			break;	
    case '3':
			format_output("You'll be the 'D' player !  \n",0);
			break;				
    case '4':
			format_output("You'll be the 'E' player !  \n",0);
			break;	
    case '5':
			format_output("You'll be the 'F' player !  \n",0);
			break;	
    case '6':
			format_output("You'll be the 'G' player !  \n",0);
			break;	
	case '7':
			format_output("You'll be the 'H' player !  \n",0);
			break;	
    case '8':
			format_output("You'll be the 'I' player !  \n",0);
			break;				
    case '9':
			format_output("You'll be the 'J' player !  \n",0);
			break;		
	default:
			format_output("Sorry, you type a wrong number ! You're out ! \n",0);
			ok = 0;
			break;
      }
    return(ok);
}

/* an if-else if structure */
int cf_9_anifelsif()
{
    char inst;
    char year;
    int ok = 1;
    
    format_output("Please type the last digit of your birth year -> ",0);
    year = waiting_loop();
   
    if (year == '0')
    {
		format_output("You'll be the 'A' player !  \n",0);
    }
	else  if (year == '1')
    {
		format_output("You'll be the 'B' player !  \n",0);
    }
	else  if (year == '2')
    {
		format_output("You'll be the 'C' player !  \n",0);
    }
	else  if (year == '3')
    {
		format_output("You'll be the 'D' player !  \n",0);
    }
	else  if (year == '4')
    {
		format_output("You'll be the 'E' player !  \n",0);
    }
	else  if (year == '5')
    {
		format_output("You'll be the 'F' player !  \n",0);
    }
	else  if (year == '6')
    {
		format_output("You'll be the 'G' player !  \n",0);
    }
	else  if (year == '7')
    {
		format_output("You'll be the 'H' player !  \n",0);
    }
	else  if (year == '8')
    {
		format_output("You'll be the 'I' player !  \n",0);
    }
	else  if (year == '9')
    {
		format_output("You'll be the 'J' player !  \n",0);
    }
	else
    {
		format_output("Sorry, you type a wrong number ! You're out ! \n",0);
		ok = 0;
    }
}

/* a sequence of if structure */
int cf_10_asequenceofif()
{
    char inst;
    char year;
    int ok = 1;
    
    format_output("Please type the last digit of your birth year -> ",0);
    year = waiting_loop();
   
    if (year == '0')
    {
		format_output("You'll be the 'A' player !  \n",0);
    }
	if (year == '1')
    {
		format_output("You'll be the 'B' player !  \n",0);
    }
	if (year == '2')
    {
		format_output("You'll be the 'C' player !  \n",0);
    }
	if (year == '3')
    {
		format_output("You'll be the 'D' player !  \n",0);
    }
	if (year == '4')
    {
		format_output("You'll be the 'E' player !  \n",0);
    }
	if (year == '5')
    {
		format_output("You'll be the 'F' player !  \n",0);
    }
	if (year == '6')
    {
		format_output("You'll be the 'G' player !  \n",0);
    }
	if (year == '7')
    {
		format_output("You'll be the 'H' player !  \n",0);
    }
	if (year == '8')
    {
		format_output("You'll be the 'I' player !  \n",0);
    }
	if (year == '9')
    {
		format_output("You'll be the 'J' player !  \n",0);
    }
	else
    {
		format_output("Sorry, you type a wrong number ! You're out ! \n",0);
		ok = 0;
    }
}