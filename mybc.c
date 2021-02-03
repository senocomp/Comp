/********************************************************************************************
* MyBc.c: Chamada principal do programa que recebe as informações passadas pelo usuário e as*
* processa, retornando o resultado de acordo com o processamento nas demais funções.        *
* Grupo 07: Caroline Mafra, Thais Caliman e Cristian Castro                                 *
*********************************************************************************************/

#include<parser.h>
#include<stdio.h>
#include<stdlib.h>
#include<tokens.h>

// Declarações
void mybc(void);

int gettoken(FILE *);

// Função principal
int main(int argc, char const *argv[]) {
	source = fopen (argv[1], "r");

	switch (argc) {
		case 1:
			source = stdin;
			break;
		default:
			if (source == NULL) {
				fprintf (stderr, 
					"argv[1]: cannot open... exiting with error status\n");
				exit (-1);
			}
	}
	while (1) { // loop infinito para controlar prompt customizado
		fputs("mybc > ", stdout);
		
		lookahead = gettoken(source);
		mybc();
		
		exit(0);
	}
}
