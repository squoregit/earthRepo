

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "base.h"
#include "score.h"


void hi_scores_disp(int i)

     /**********************************************/
     /* Function: Displays high score table        */
     /*                                            */
     /* Parameters:                                */
     /*      i: IN current index of the high score */
     /*             table                          */
     /**********************************************/

{
  
  
    /* print a score*/
    printf ("         | %10.10s ", hi_scores_tab [i].name);
    printf ("| %10.10s ", hi_scores_tab [i].firstname);
    printf ("|   %.2d  |\n", hi_scores_tab [i].score);
 
  
}


int hi_scores_write ()
     /* update the score file*/
{
	int i,status;
  
	hi_scores_file = fopen ("hi_score.lst", "w");
  
    i = 0;
	/* write all hight score  */
    while (i != last_hi_score)
    {
      fprintf (hi_scores_file, "%s\n", hi_scores_tab [i].name);
      fprintf (hi_scores_file, "%s\n", hi_scores_tab [i].firstname);
      fprintf (hi_scores_file, "%d\n", hi_scores_tab [i].score);
      i++;
    }
    /* close the high score file*/		
    fclose (hi_scores_file);
    status = 0;
    return(status);
}


void player_score (int score)
{
  char car;
  int max_string;
  char * name;
  char * firstname;
  char * number;
  int i,j;

  last_hi_score = 0;


  /* Processing to be completed */

     
}

void print_score_player (int try)
{
  int i = 0;

  player_score (try);
  
  hi_scores_disp (i);
 
}
