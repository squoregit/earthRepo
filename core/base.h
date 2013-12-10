#ifndef _BASE_H_
#define _BASE_H_

#define MIN(a,b) (a<b ? a : b)
#ifdef DEBUG
#define PDEBUG(bool,val) if (bool) printf("%d",val) 
#else
#define PDEBUG(bool,val)
#endif


#include "master.h"

extern void end_game(int* curr , int* typ);
extern void prompt(char* s);
extern void format_output(char* s, int code);
extern void skipline(int nb);
extern void set_dummy();
extern void make_code(guess* ges);
extern int  find_digit(char col_name[7]);

#endif
