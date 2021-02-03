/********************************************************************************************
* Parser.h: Contém declaração variaveis, prototipos de funçoes, o tipo SYMTAB e a indicação *
* de variaveis externas.                                                                    *
* Grupo 07: Caroline Mafra, Thais Caliman e Cristian Castro                                 *
*                                                                                           *
*********************************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<tokens.h>
#include<constants.h>

//Prototipo das funções
double E(void);
double T(void);
double F(void);
void match(int expected);
int gettoken(FILE *);

// Variaveis externas
extern char lexeme[MAXIDLEN + 1];
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

//posicao inicial do simbolo:
int symtab_nextentry = 0;
