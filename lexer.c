/********************************************************************************************
* Lexer.c: Analisador Léxico								    *
* Grupo 07: Caroline Mafra, Thais Caliman e Cristian Castro                                 *
*                                                                                           *
*********************************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<math.h>
#include<parser.h>
#include<tokens.h>
#include<keywords.h>
#include<constants.h>
#include<lexer.h>

<<<<<<< HEAD
=======
// Declaração variáveis
int decimal = 0;

>>>>>>> 48d07ccbc9cc981ea452f1ccd10ea8e3179ab90e
// Função que verifica se é um identificador
int isID(FILE *tape) {
	int i = 0;

	if (isalpha(lexeme[i] = getc(tape))) {
		i++;
		
		while (isalnum(lexeme[i] = getc(tape)))
			i++;
		
		ungetc (lexeme[i], tape);
		lexeme[i] = 0;
		
		int token = iskeyword(lexeme);
		
		if (token)
			return token;
		
		return ID;
	}
	ungetc (lexeme[i], tape);
	return 0;
}

// Função que verifica os inteiros
int isUINT(FILE *tape) {
	int i = 0;
	
	if (isdigit(lexeme[i] = getc(tape))) {
		if (lexeme[i] == '0') {
			i++;
			lexeme[i] = 0;
		} else {
			i++;
			while (isdigit(lexeme[i] = getc(tape)))
				i++;
				
			ungetc (lexeme[i], tape);
			lexeme[i] = 0;
		}
		decimal = i;
		return UINT;
	}
	ungetc(lexeme[i], tape);
	decimal = i;
	lexeme[i] = 0;
	return 0;
}

// Função que verifica os númericos
int isNUM(FILE *tape) {
	int token = 0, i = 0;
	int head;

	if ((token = isUINT(tape))) {
		i = decimal;
		
		if ((lexeme[i++] = getc(tape)) == '.' ) {
			token = FLOAT;
			while (isdigit(lexeme[i++] = getc(tape)));
			ungetc (lexeme[--i], tape);
			lexeme[i] = 0;
		} else {
			ungetc(lexeme[--i], tape);
			lexeme[i] = 0;
		}
	} else if ((lexeme[i++] = getc(tape)) == '.' ) {
		/** decimal point has been already read **/
		if (isdigit(lexeme[i++] = getc(tape))) {
			token = FLOAT;
			while (isdigit(lexeme[i++] = getc(tape)));
			ungetc(lexeme[--i], tape);
			lexeme[i] = 0;
		} else {
			/** after decimal point another char, non-digit has been read **/
			ungetc(lexeme[--i], tape);
			lexeme[i] = 0;
			ungetc(lexeme[--i], tape);
			lexeme[i] = 0;
		}
	} else {
			ungetc(lexeme[--i], tape);
			lexeme[i] = 0;
	}
	
	int eE, j = 0;
	char elevado[MAXIDLEN + 1];
	double coeficiente, multiplicador, resultado;
	
	if (token > 0) {
		if (toupper(eE = getc(tape)) == 'E') {
			int plusminus;
			if ((plusminus = getc(tape)) == '+' || plusminus == '-') {
				;
			} else {
				ungetc(plusminus, tape);
				plusminus = 0;
			}
			if (isdigit(head = getc(tape))) {
				token = FLOAT;
				
				elevado[j++] = head;
				
				while (isdigit(head = getc(tape)))
					elevado[j++] = head;
				
				elevado[j] = lexeme[i] = '\0';
				
				coeficiente = atof(lexeme);
				multiplicador = pow(10.0, atof(elevado));
				resultado = coeficiente * multiplicador;
				
				ungetc (head, tape);
			} else {
				ungetc (head, tape);
				if (plusminus) {
					ungetc(plusminus, tape);
				}
				ungetc(eE, tape);
			}
		} else {
			ungetc(eE, tape);
		}
	}
	return token;
}

// Função que verifica os OCTAS
int isOCT(FILE *tape) {
	int i = 0;
	
	if ((lexeme[i++] = getc(tape)) == '0') {
		if (isdigit(lexeme[i++] = getc(tape)) && lexeme[i - 1] <= '7') {
			while (isdigit(lexeme[i++] = getc(tape)) && lexeme[i - 1] <= '7');
			ungetc(lexeme[--i], tape);
			lexeme[i] = 0;
			return OCT;
		} else {
			ungetc(lexeme[--i], tape);
			lexeme[i] = 0;
			ungetc('0', tape);
			lexeme[--i] = 0;
			return 0;
		}
	}
	ungetc(lexeme[--i], tape);
	lexeme[i] = 0;
	return 0;
}

// Função que verifica os HEXAS
int isHEX(FILE *tape) {
	int x;
	int i = 0;
	
	if ((lexeme[i++] = getc(tape)) == '0') {
		if ((x = lexeme[i++] = getc(tape)) == 'X' || x == 'x') {
			if (isxdigit(lexeme[i++] = getc(tape))) {
				while (isxdigit(lexeme[i++] = getc(tape)));
				ungetc (lexeme[--i], tape);
				lexeme[i] = 0;
				return HEX;
			} else {
				ungetc (lexeme[--i], tape);
				lexeme[i] = 0;
				ungetc (x, tape);
				lexeme[--i] = 0;
				ungetc ('0', tape);
				lexeme[--i] = 0;
				return 0;
			}
		}
		ungetc (x, tape);
		lexeme[--i] = 0;
		ungetc ('0', tape);
		lexeme[--i] = 0;
		return 0;
	}
	ungetc (lexeme[--i], tape);
	lexeme[i] = 0;
	return 0;
}

// Verifica e pula os espaços
void skipspaces(FILE *tape) {
    int head;
    
    while (isspace(head = getc(tape)))
        if (head == '\n')
			break;
			
    ungetc(head, tape);
}

// Função responsável por pegar o token e chamar as demais funções
int gettoken(FILE *source) {
	int token;
	
	skipspaces(source);

	if((token = isID(source)))
		return token;
		
	if((token = isOCT(source)))
		return token;
		
	if((token = isHEX(source)))
		return token;
		
	if((token = isNUM(source)))
		return token;

	token = getc(source);

	return token;
}
