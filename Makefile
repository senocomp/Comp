#********************************************************************************************
# Makefile: conjunto de comandos e argumentos para compilar e excuir arquivos               *
# Grupo 07: Caroline Mafra, Thais Caliman e Cristian Castro                                 *
#                                                                                           *
#********************************************************************************************

# CFLAGS é a variavel que adiciona argumentos ao compilador
# argumentos:
	# -g : Gera mais informações da tabela de símbolos para o debugger.
	# -I./include : Adiciona os arquivos da pasta include ao processo de linkedição
CFLAGS=-g -I./include

mybc: mybc.o lexer.o parser.o keywords.o
	$(CC) -o $@ $^ -lm	# a flag -lm possibilita o uso de math.h

# comando para excluir todos os arquivos .o gerados na compilação
clean:
	$(RM) *.o


mostlyclean: clean
	$(RM) *~
