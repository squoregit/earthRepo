
#include <stdio.h>
#include <stdlib.h> 
#include <ctype.h>

#include "master.h" 
#include "score.h" 
#include "base.h" 
#include "util.h"


/*---------------------------------------*/ 
void machine_read_file() 
/*---------------------------------------*/
 
{ 
  char car; 
  int max_string; 
  char * name; 
  char * firstname; 
  char * number; 
  int i; 

  last_hi_score = 0; 
 
  hi_scores_file = fopen ("hi_score.lst", "r"); 
  
  if (hi_scores_file == NULL) 
   { 
     /* no high score file*/ 
     skipline(2); 
     format_output("*************************\n",0); 
     format_output("   NO HIGH SCORE TABLE   \n",0); 
     format_output("*************************\n\n",0); 
   } 

  else 

    { 
      
      
      /* reads the high score file to fill the hi_scores_tab table */ 
      
      car = getc (hi_scores_file); 
      
     
      while (((car != EOF) && (last_hi_score < MAX_TAB))) /* reading the file */ 

	{ 
          
	  max_string = MAX_STRING; 
	  name = (char *) malloc (sizeof (char) * MAX_STRING); 
	  firstname = (char *) malloc (sizeof (char) * MAX_STRING); 
	  number = (char *) malloc (sizeof (char) * MAX_STRING); 
	  i = 0; 
	  
	  while ((car != '\n') && (car != EOF)) 
	  /* reading a name*/ 
	    { 

	      if (i >= max_string - 1) 
	      /*if size of name is too long: reallocation */ 
  		{	 
		  max_string += MAX_STRING; 
		  name = (char *) realloc (name, sizeof (char) * max_string); 
		} 
 
 	      if (islower(car)) 
	      /*if lowercase then uppercase*/ 
		car = toupper(car); 
	      name [i] = car; 
	      car = getc (hi_scores_file); 
	      i++; 
	    } 
	  
	  name [i] = '\0'; 
	  (hi_scores_tab [last_hi_score]).name = name; 
	  
           
	  car = getc (hi_scores_file); 
	  max_string = MAX_STRING; 
	  i = 0; 

	  while ((car != '\n') && (car != EOF)) 
	  /* reading a firstname*/ 
	    { 
              /*if size of firstname is too long: reallocation */ 
	      if (i >= max_string - 1) 
		{	 
		  max_string += MAX_STRING; 
		  firstname = (char *) realloc (firstname, sizeof (char) * max_string); 
		} 

	      if (islower(car)) 
	      /*if lowercase then uppercase*/ 
		car = toupper(car); 
	      firstname [i] = car; 
	      car = getc (hi_scores_file); 
	      i++; 
	    }  
	  
	  firstname [i] = '\0'; 
	  (hi_scores_tab [last_hi_score]).firstname = firstname; 
	  
          
	  car = getc (hi_scores_file); 
	  max_string = MAX_STRING; 
	  i = 0; 
	  
	  while ((car != '\n') && (car != EOF)) 
	  /* reading a score */ 
	    
	    { 
	      if (i >= max_string - 1) 
		{ 
		/*if size of score is too long: reallocation*/ 
		  max_string += MAX_STRING; 
		  number = (char *) realloc (number, sizeof (char) * max_string); 
		} 
	      number [i] = car; 
	      car = getc (hi_scores_file); 
	      i++; 
	    } 
	  
	  number [i] = '\0'; 
	  (hi_scores_tab [last_hi_score]).score = atoi (number); 
	  free (number); 
	  
         car = getc (hi_scores_file); 
         last_hi_score++; 
	} 
      
      /* close hi_scores_file file */ 
      fclose (hi_scores_file); 
    } 
} 

 
/*---------------------------------------*/ 
void machine_update_scores (int score) 
/*---------------------------------------*/ 

{ 

  char car; 
  int max_string; 
  char * name; 
  char * firstname; 
  int i,j,result;

  /* result used for FullMCDC test */
  result= ((score <= hi_scores_tab [last_hi_score - 1].score) || 
	   (last_hi_score < MAX_TAB));
    if (result)
      { 
	j = last_hi_score;  
	while ((j > 0) && (score <= hi_scores_tab [j - 1].score)) 
	  { 
	    if (j == MAX_TAB) 
	      { 
		/*if insertion in last position: free */ 
		free (hi_scores_tab [j - 1].name); 
		free (hi_scores_tab [j - 1].firstname); 
	      } 
	    
	    else 
	    /*include in the table*/ 
	      { 
		/* move the end of the table down */ 
		hi_scores_tab [j].name = hi_scores_tab [j - 1].name; 
		hi_scores_tab [j].firstname = hi_scores_tab [j - 1].firstname; 
		hi_scores_tab [j].score = hi_scores_tab [j - 1].score; 
	      } 
	    j--; 
	  } 
	
	skipline(2); 
	format_output("Please, enter your lastname\n",1); 
	car = getchar (); 
	
	/* read a name */ 
	max_string = MAX_STRING; 
	name = (char *) malloc (sizeof (char) * MAX_STRING); 
	i = 0; 
	while ((car != '\n') && (car != EOF)) 
	/*reading a name on the screen*/ 
	  { 
	    if (i >= max_string - 1)
	     /*if size of name is too long: reallocation */ 
	      {	 
		max_string += MAX_STRING; 
		name = (char *) realloc (name, sizeof (char) * max_string); 
	      } 
	    if (islower(car)) 
	    /*if lowercase then uppercase*/ 
	      car = toupper(car); 
	    name [i] = car; 
	    car = getchar (); 
	    i++; 
	  }  
	
	name [i] = '\0'; 
	
	format_output("Please, enter your firstname\n",1); 
	car = getchar (); 
	
	/* reading a firstname */ 
	max_string = MAX_STRING; 
	firstname = (char *) malloc (sizeof (char) * MAX_STRING); 
	i = 0; 
	while ((car != '\n') && (car != EOF)) 
	  { 
	    if (i >= max_string - 1) 
	    /*if size of firstname is too long: 
	       reallocation */ 
	      {	 
		max_string += MAX_STRING; 
		firstname = (char *) realloc (firstname, sizeof (char) * max_string); 
	      } 
	    if (islower(car)) 
	    /*if lowercase then uppercase*/ 
	      car = toupper(car); 
	    firstname [i] = car; 
	    car = getchar (); 
	    i++; 
	  }  
	
	firstname [i] = '\0'; 
	 
	hi_scores_tab [j].name = (char *) malloc (sizeof (char) * strlen (name)); 
	strcpy (hi_scores_tab [j].name, name); 
	hi_scores_tab [j].firstname = (char *) malloc (sizeof (char) * strlen (firstname)); 
	strcpy (hi_scores_tab [j].firstname, firstname); 
	hi_scores_tab [j].score = score; 
	if (last_hi_score < MAX_TAB) 
	  { 
	    last_hi_score++; 
	  } 
      } 
    else 
      { 
	format_output("Sorry !!!!You are not in the top ",1); 
        printf(" %d\n",MAX_TAB); 
      } 
  skipline(2); 
  format_output("\n\n         ----- SEE YOU LATER -----\n",1);        
} 


void machine_print_score (int try) 

{ 

  int i = 0; 
  machine_read_file(); 
  machine_update_scores(try); 

  if (hi_scores_write() == 1) 
    format_output("opening error, file: hi_score.lst\n",1); 
  skipline(2); 

} 


void score_mac()
{
  /**************************************/
  /* Function: defines score for        */
  /*           current guess            */
  /**************************************/ 
  
  int x, y;
  
  for (x = 0; x < 4; x++)
    guesses[cur].pegs[x].used = code.pegs[x].used = NONE;
  
  for (x = 0; x < 4; x++) 
  /* searching black pegs */
    if (guesses[cur].pegs[x].color == code.pegs[x].color)
      {
	/* guess color = code color */
	code.pegs[x].used = guesses[cur].pegs[x].used = BLACK;
	guesses[cur].blacks++;
      }
  
  if (guesses[cur].blacks != 4) 
  /* computer guess is partially correct */
    {
      for (x = 0; x < 4; x++)
	for (y = 0; y < 4; y++) 
	  /*searching white pegs */
	  if (guesses[cur].pegs[x].color == code.pegs[y].color &&
	      !code.pegs[y].used && !guesses[cur].pegs[x].used)
	    {
	      code.pegs[y].used = guesses[cur].pegs[x].used = WHITE;
	      guesses[cur].whites++;
	    }
    }
  else 
  /* computer guess is correct */
    game_won = TRUE;
}



void get_code_mac(guess* kode)
  /**************************************/
  /* Function: accepts player's code    */
  /*                                    */
  /* Parameters:                        */
  /*      kode: IN OUT guess structure  */
  /**************************************/
{
  extern int cur;
  char c[4][7];
  int bad_in, code_valid;
  int x;
  
  code_valid = bad_in = FALSE;
  kode->blacks = kode->whites = 0;
  while (!code_valid) /* get a player code */
    {
      code_valid = TRUE;
      if (bad_in) /* Invalid player code */
	format_output("Previous code contains invalid color.\n",1);
      format_output("Please enter the correct code -> ",1);
      scanf("%s %s %s %s",c[0],c[1],c[2],c[3]);
      while (getchar() != '\n');
      skipline(1);  /* Bug Report #625: Wrong formatting */ 
      for (x = 0; x < 4; x++) /* checks player's code */
	{
	  kode->pegs[x].used = NONE;
	  kode->pegs[x].color = find_digit(c[x]); 
	  if (kode->pegs[x].color == BAD_COLOR)
	    {
	      code_valid = FALSE;
	      bad_in = TRUE;
	    }
	}
    }
}




void machine_plays()

{
  /**************************************/
  /* Function: computer looking for     */
  /*           player's code            */
  /**************************************/


  int t, u, v;
  int w, x, y, z;
  int randomizing = TRUE;
  int quit = FALSE;
  int refreshed;
  char car;
  
  check = TRUE;
  format_output("Do you want me to double check you, y/n [default is y] -> ",1);
  

  if (check) 
  /* get the player code before the search */
    get_code_mac(&code);
  cur = 0;

  make_code(&guesses[cur]);

  set_dummy();
  /* check guess consistency */
  check_consultancy();
  
  
  for (++cur; cur < MAX_TRY_MAC && !game_won && randomizing && !quit;)
    {
      x = 0;
      cons = FALSE;
      while (!cons && x < 1200)
	{
	  x++;
	  make_code(&guesses[cur]);
	  consistent();
	}
      if (cons) 
      /* check guess consistency */
	{
	  set_dummy();
	  check_consultancy();
	  cur++;
	}
      else
	randomizing = FALSE;
    }

  if (!game_won)
    for (cur; cur < MAX_TRY_MAC && !game_won && !quit; cur++)
      {

	if (cons) 
	/* check guess consistency */
	  {
	    set_dummy();
	    check_consultancy();
	  }
	else 
	/* inconsistent guess, we quit the game */
	  {
	    format_output("No guess is consistent.  You must have cheated!\n",1);
				format_output("Can't recover from this.  Goodbye!\n",1);
				quit = TRUE;
	  }
      }

  if (game_won)
    {
    /* the computer  broke the code*/
      format_output("I broke your code in",1);
      printf(" %d ",cur);
      if (cur != 1)
	format_output("guesses.\n",0);
      else 
      /*the computer break the code in one guess */
	format_output("guess.  Machines can get lucky, too!\n",0);
    }

  else 
     /* the computer didn't break the code*/
     if (!quit) 
         format_output("I didn't break your code.  You win this time!\n",1);

  machine_print_score(cur);

}






















