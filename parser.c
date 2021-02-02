/********************************************************************************************
* Parser.h: contem o prototipo das funcoes				    *
* Grupo 07: Caroline Mafra, Thais Caliman e Cristian Castro                                 *
*                                                                                           *
*********************************************************************************************/


#include<parser.h>
#include<string.h>
#include<constants.h>
#include<keywords.h>

/* Funcao que deriva as expressoes
 E -> ['+''-'] T { (1a) (+) T (1) } */
double E(void) {
	int signal = 0;
	double E_val, T_val;
	
	if (lookahead == '+' || lookahead == '-') {
		signal = lookahead;
		match(lookahead);
	}

	T_val = T();
	
	if (signal == '-')
		T_val = -T_val;

	E_val = T_val;
	
	while (lookahead == '+' || lookahead == '-') { 
		/*(1a)*/ int oplus = lookahead; /**/
	 	match (lookahead);
		T_val = T();
	 	if (oplus == '+')
	 		E_val += T_val;
		else
			E_val -= T_val;
	}
	return E_val;
}

/* Funcao que deriva as termos
 T -> F { (2a) (*) F (2) } */
double T(void) { 
	double T_val, F_val;
	
	F_val = F();
	T_val = F_val;
	
	while (lookahead == '*' || lookahead == '/') {
		/*(2a)*/ int otimes = lookahead; /**/
		match (lookahead);
		F_val = F();
		if (otimes == '*')
			T_val *= F_val;
		else
			T_val /= F_val;
	}
	return T_val;
}

double memory[MAXSTBENTRIES];

/*
  Struct que guarda nome e posicao do simbolo
*/
typedef struct _symtab_ {
	char name[MAXIDLEN + 1];
	int pos;
} SYMTAB;

//tabela de simbolos
SYMTAB symtab[MAXSTBENTRIES];


//posicao inicial do simbolo
int symtab_nextentry = 0;

/*
 Verifica, compara e retorna se o simbolo passado na variavel name estah presente na tabela de simbolos
*/
double recall(const char *name) {
	int i;
	
	for (i = 0; i < symtab_nextentry; i++) {
		if (strcmp(name, symtab[i].name) == 0)
			return memory[i];
	}
	strcpy(symtab[i].name, name);
	symtab_nextentry++;
	return 0;
}

/*
  Salva o conteudo da variavel na tabela de simbolos
*/
void store(const char *name, double val) {
	int i;
	
	for (i = 0; i < symtab_nextentry; i++) {
		if (strcmp(name, symtab[i].name) == 0)
			break;
	}
	
	if (i == symtab_nextentry) {
		strcpy(symtab[i].name, name);
		symtab_nextentry++;
	}
	memory[i] = val;
}

/*
  Conversao de HEXA e OCTA para float
*/
double convert(const char * str_convert, int tipo_dado) {
	if (tipo_dado == 0) // HEXADECIMAL
		return (double) strtol(str_convert, NULL, 0);
	else // OCTAL
		return (double) strtol(str_convert, NULL, 8);
}

/*
  Funcao responsavel pelas derivacoes dos fatores
*/
double F(void) {
	double F_val;
	char name[MAXIDLEN + 1];
	
	switch (lookahead) {
		case '(':
			match('(');
			F_val = E();
			match(')');
			break;
		case UINT:
			F_val = atof(lexeme);
			match(lookahead);
			break;
		case FLOAT:
			F_val = atof(lexeme);
			match(lookahead);
			break;
		case HEX:
			F_val = convert(lexeme, 0);
			match(lookahead);
			break;
		case OCT:
			F_val = convert(lexeme, 1);
			match(lookahead);
			break;
		default:
            strcpy(name, lexeme);
			match(ID);
			if (lookahead == '=') {
				match('=');
				F_val = E();
                store(name, F_val);
			} else {
                F_val = recall(name);
			}
	}
	return F_val;
}

/*
  Verificador de tipos e expressões
*/
void cmd(void) {
	double E_val;
	
	switch(lookahead) {
		case '\n':
		case ';':
		case EOF:
			break;
		case QUIT:
			exit(0);
			break;
		case EXIT:
			exit(0);
			break;
		case HEX:
			E_val = E();
            printf("0x%x\n", (int) E_val);
			break;
		case OCT:
			E_val = E();
            printf("0x%o\n", (int) E_val);
            break;
		default:
			E_val = E();
            printf("%lg\n", E_val);
	}
}


/*
  Verifica se o a lookahead eh fim de arquivo (EOF) ou se lookahead eh os comandos EXIT ou QUIT
*/
void end(void) {
	switch(lookahead) {
		case EOF:
			match(EOF);
			break;
		case EXIT:
			match(EXIT);
			break;
		default:
			match(QUIT);
			break;
	}
}

/*
  Chamada principal do programa
*/
void mybc(void) {
	cmd();
	
	while (lookahead == '\n' || lookahead == ';') {
		if (lookahead == '\n') {
    		int l = ftell(stdin);
    		if (l <= 0) 
				printf("mybc > ");
		}
		match(lookahead);
		cmd();
	}
	end();
}

/*
  Verifica se lookahead eh igual a variavel passada pela funcao, caso nao seja, retorna uma mensagem de erro. 
*/
void match(int expected) {
	if (lookahead == expected) {
		lookahead = gettoken(source);
	} else {
		fprintf(stderr, "token mismatch: expected %d whereas found %d\n", expected, lookahead);
	}
}

