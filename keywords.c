/********************************************************************************************
* Keywords.c: Verifica se a entrada contém palavras chaves				    *
* Grupo 07: Caroline Mafra, Thais Caliman e Cristian Castro                                 *
*                                                                                           *
*********************************************************************************************/
#include<string.h>
#include<keywords.h>

// Declaração das palavras chaves no vetor.
char *keyword[] = {"quit", "exit"};

// Função de verificação
int iskeyword(const char *name) {
    int i;
    
    // Laço de verificação
    for (i = QUIT; i < EXIT + 1; i++) {
        if (strcmp(keyword[i - QUIT], name) == 0)
			return i;
    }
    return 0;
}
