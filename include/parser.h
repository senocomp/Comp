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

<<<<<<< HEAD
=======
extern char lexeme[MAXIDLEN + 1];

>>>>>>> 48d07ccbc9cc981ea452f1ccd10ea8e3179ab90e
double E(void);
double T(void);
double F(void);
void match(int expected);
int gettoken(FILE *);

extern char lexeme[];
extern int lookahead;
extern FILE *source;

/*
  Struct que guarda nome e posicao do simbolo
*/
typedef struct _symtab_ {
	char name[MAXIDLEN + 1];
	int pos;
} SYMTAB;

//declaração de variaveis
SYMTAB symtab[MAXSTBENTRIES];
double memory[MAXSTBENTRIES];

//posicao inicial do simbolo
int symtab_nextentry = 0;
