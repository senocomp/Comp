#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<tokens.h>
#include<constants.h>

extern char lexeme[];

double E(void);
double T(void);
double F(void);

void match(int expected);

int gettoken(FILE *);

extern int lookahead;
extern FILE *source;
