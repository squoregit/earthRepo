#ifndef _MASTERP_H_
#define _MASTERP_H_

#define FALSE 0
#define TRUE 1
#define NONE 0
#define WHITE 1
#define BLACK 2
#define BAD_COLOR -1
#define MAX_TRY 9
#define MAX_TRY_MAC 5

typedef struct _peg { 
    int color;
    int used;
} peg;

typedef struct _guess { 
    struct _peg pegs[4];
    int blacks;
    int whites;  
} guess;

extern int cur;
extern int game_won;
extern int player;
extern int cons;
extern int check;
extern int JACKPOT;
extern int dig[];

extern guess code;
extern guess guesses[];
extern guess dummy[];

extern char *col[];

extern void rest();
extern void machine_plays();
extern void setcolors();

#endif
