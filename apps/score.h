
#ifndef _SCORE_H_
#define _SCORE_H_

/* define string lenght */
#define MAX_STRING 10

/* define max number of hight score table element */
#define MAX_TAB 10

/* "hight score" file descriptor */
FILE * hi_scores_file;

/* element type of table: hi_scores_tab*/
typedef struct type_hi_score_struct
{
   char * name;
   char * firstname;
   int score;
} type_hi_score;

/* hight scores table */
type_hi_score hi_scores_tab [MAX_TAB];

/* number of the badless hight score */
int last_hi_score;

extern void hi_scores_disp(int i);
extern int hi_scores_write();
extern void player_score(int score);
extern void print_score_player(int try);

#endif
