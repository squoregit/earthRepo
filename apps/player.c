
#include <stdio.h>

#include "master.h"
#include "player.h"
#include "base.h"
#include "util.h"
#include "write.h"
#include "score.h"

void score_player()
     /**************************************/
     /* Function: defines score for        */
     /*           current guess            */
     /**************************************/ 
{
  int x, y;
    /* checks black pegs*/
  for (x = 0; x < 4; x++)
    guesses[cur].pegs[x].used = code.pegs[x].used = NONE;
  
  for (x = 0; x < 4; x++)
    if (guesses[cur].pegs[x].color == code.pegs[x].color)
      {
	/* guess color = code color */
	code.pegs[x].used = guesses[cur].pegs[x].used = BLACK;
	guesses[cur].blacks++;
        PDEBUG(0,guesses[cur].blacks);
	printf("b");
      }
  
  if (guesses[cur].blacks != 4)
    /* if not game_won, checks white pegs*/
    {
      for (x = 0; x < 4; x++)
	for (y = 0; y < 4; y++)
	  if (guesses[cur].pegs[x].color == code.pegs[y].color &&
	      !code.pegs[y].used && !guesses[cur].pegs[x].used)
	    {
	      code.pegs[y].used = guesses[cur].pegs[x].used = WHITE;
	      guesses[cur].whites++;
	      printf("w");
	    }
    }
  else
    game_won = TRUE;
  
  if (guesses[cur].blacks != 0 || guesses[cur].whites != 0)
    skipline(2);
  else
    /*bad guess,no score */
    format_output("No score.\n\n",1);
}


void get_code_player(guess* kode)
     /**************************************/
     /* Function: accepts player guess     */
     /*                                    */
     /* Parameters:                        */
     /*      kode: IN OUT guess structure  */
     /**************************************/
{
  char c[4][7];
  int bad_in, code_valid;
  int x;

  code_valid = bad_in = FALSE;
  kode->blacks = kode->whites = 0;
  while (!code_valid)
    {
      code_valid = TRUE;
      if (bad_in)
	format_output("Previous code contains invalid color.\n",1);
      
      format_output("Please enter guess",1);
      printf(" #%d -> ",cur + 1);
      
      scanf("%s %s %s %s",c[0],c[1],c[2],c[3]);
      while (getchar() != '\n');

      /* loop to get 4 colors*/
      for (x = 0; x < 4; x++)
	{
	  kode->pegs[x].used = NONE;
	  kode->pegs[x].color = find_digit(c[x]); 
	  if (kode->pegs[x].color == BAD_COLOR)
	    {
	      /*invalid code color*/
	      code_valid = FALSE;
	      bad_in = TRUE;
	    }
	}
    }
}


void help(int* tt)
     /*******************************/
     /* Function: helps player      */
     /*                             */
     /* Parameters:                 */
     /*      tt: IN a guess         */
     /*******************************/
{
    int z, w ;
    
    skipline(1);

    z = 0;
    
    /* Enter the guess you need the hint for */
    while (z < 1 || z > cur)
      {
	z = 0;
	format_output("Enter the guess you need the hint for -> ",1);
	while((*tt = getchar()) != '\n')
	  z = z * 10 + *tt - '0';
      }
    
    w = 0;
    /*choose the peg you need the hint for */
    while (w < 1 || w > 4)
      {
	w = 0;
	format_output("Which peg of guess",1);
	printf(" #%d -> ",z);
	while((*tt = getchar()) != '\n')
	  w = w * 10 + *tt - '0';
      }
    
    format_output("In guess",1);
    printf(" #%d,",z);
    printf("peg #%d received ",w);
    
    if (guesses[z - 1].pegs[w - 1].used == BLACK)
      format_output("a black peg.\n",0);
    
    if (guesses[z - 1].pegs[w - 1].used == WHITE)
      format_output("a white peg.\n",0);
    
    if (guesses[z - 1].pegs[w - 1].used == NONE)
	format_output("no peg.\n",0);
    
    skipline(1);
}

void play(guess choice[], int* curr, int guide)
     /**********************************************/
     /* Function: gets a player guess,             */
     /*           checks it                        */
     /*           and returns score                */
     /* Parameters:                                */
     /*      choice: IN current guess              */
     /*      curr: IN OUT current guess number     */
     /*      guide: IN for checking guess validity */ 
     /**********************************************/
{
  get_code_player(&choice[*curr]);
  set_dummy();
  if (guide && *curr)
    /*verify the validity of the guess*/
    consistent();
  score_player();
  (*curr)++;
}

void player_plays()
     /**************************************/
     /* Function: player looking for      */
     /*           computer's code          */
     /**************************************/
{
  
  int good_try;
  char inst, action;
  int coach, quit;
  int t;

  coach = quit = FALSE;
  format_output("Do you want coaching, y/n [default is n] -> ",1);
  if ((inst = getchar()) != '\n')
    while (getchar() != '\n');
  if (inst == 'y' || inst == 'Y')
    coach = TRUE;
  skipline(1);
  format_output("Choosing a code for you to guess.\n",1);
  t = rand() % 3 + 2;
  sleep(t);
  make_code(&code);
  
  if (JACKPOT == 1)
    {
      /* ... mark  ...                                          */
      /*  Mark in order to succeed with the first guess.         */
      
      printf("  You must guess:   %-8s %-8s %-8s %-8s\n", 
	     col[dig[code.pegs[0].color]],                         
	     col[dig[code.pegs[1].color]],                         
	     col[dig[code.pegs[2].color]],                         
	     col[dig[code.pegs[3].color]]);                        
      /* ... end mark ...                                       */
    }
  for (cur = 0; cur < MAX_TRY && !game_won;)
    {
      if (cur)
	{
	  good_try = cur + 1;
	  format_output("guess, refresh, print, or quit [default is guess] -> ",1);
	  if ((action = getchar()) != '\n')
	    while (getchar() != '\n');
	}
      else
	action = 'g';

      switch (action)
	{
	case 'r':
	case 'R':
	  /* you want to see your guesses*/
	  if (cur != 0)
	    {
	      refresh();
	      break;
	    }
	case 'q':
	case 'Q':
	  /* you want to quit*/
	  end_game(&cur,&quit);
	  break;
	case 'h':
	case 'H':
	  /* you need a hint to find the code*/
	  help(&t);
	  break;
	case 'p':
	case 'P':
	  /* you want to have  help*/
	  /*about this menu*/
	  print_help();
	  break; 
	default:
	  /* you want to guess*/
	  play(guesses,&cur,coach);
	  break;
	}
      
    }
     
    if (game_won)
    {
	if (cur != 1)
	  {
	    format_output("         You broke the code in",0);
	    printf(" %d tries.\n",good_try);
	    skipline(1);
	    format_output("         FREE GAME - PLAY AGAIN\n",0);
	  }
	else
	  {
	    system("/usr/5bin/banner \" JACKPOT\"");
	  }
	print_score_player(good_try);
      }
    else if (!quit)
    {
      skipline(1);
      format_output("Sorry.  You've run out of guesses.\n",1);
      /* display the correct code*/
      format_output("    The correct code was:",1);
      printf("   %-8s %-8s %-8s %-8s\n",
	     col[dig[code.pegs[0].color]],
	     col[dig[code.pegs[1].color]],
	     col[dig[code.pegs[2].color]],
	     col[dig[code.pegs[3].color]]);
    }
    else
      format_output("Was that too tough for you?  I'll be nicer next time.\n",1);
}
