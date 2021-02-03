/********************************************************************************************
* Parser.h                                                                                  *
* Grupo 07: Caroline Mafra, Thais Caliman e Cristian Castro                                 *
*                                                                                           *
*********************************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<tokens.h>
#include<constants.h>

extern char lexeme[MAXIDLEN + 1];

double E(void);
double T(void);
double F(void);

void match(int expected);

int gettoken(FILE *);

extern int lookahead;
extern FILE *source;
