#include <stdio.h>
#include <stdlib.h>
#include <termio.h>
#include <unistd.h>
#include "pilha_ref.h"

#define T_PRETO 		printf("\33[30m");
#define T_VERMELHO 	printf("\33[31m");
#define T_VERDE 		printf("\33[32m");
#define T_LARANJA 	printf("\33[33m");
#define T_AZUL 		printf("\33[34m");
#define T_ROXO 		printf("\33[35m");
#define T_BRANCO 		printf("\33[37m");

#define peca01 	2
#define peca02 	4
#define peca03 	6
#define peca04 	8

void printTorres(int *t1, int *t2, int *t3, int cur, int sel);
void setColor(int c);
int getch(void);

int main() {

	int cursor = 0;
	int fim = 0;
	int sel = -1; 	
	int n_mov = 0;
	char op;

	int *torre1 = malloc(4 * sizeof(int));
	int *torre2 = malloc(4 * sizeof(int));
	int *torre3 = malloc(4 * sizeof(int));

	// Inicia Torres
	init(torre1, 1);  
	init(torre2, 0);  
	init(torre3, 0);

	while(fim == 0) {
		system("clear");

		T_LARANJA
		printf("\n**********************************");
		printf("\n********* TORRE DE HANOI *********");
		printf("\n**********************************");
		// Imprime Torres
		printTorres(torre1, torre2, torre3, cursor, sel);
		T_LARANJA
		printf("\n**********************************");
		printf("\n****** Numero de movimentos: %i", n_mov);
		printf("\n**********************************\n");

		// TECLA PRESSIONADA
		T_BRANCO
		__fpurge(stdin);
		op = getch();

		// TECLA ESPECIAL
		if(op == 27) {
			op = getch(); 
			if(op == 91) {      
				op = getch();
				// Direita
				if(op == 67) {
					if(cursor == 2) { cursor = 0; }
					else { cursor++; }
				}		
	  			// Esquerda
				else if(op == 68) {
		    			if(cursor == 0) { cursor = 2; }
					else { cursor--; }
				}
			}
		}
		// ENTER
		else if(op == 10 || op == 13) {
			// Primeira Selecao
			if(sel == -1) {		
				sel = cursor;
			}
			// Segunda Selecao
			else {
				// Mesma torre
				if(sel == cursor) {
					sel = -1;
				}

				sel = -1;
			}
		}
	}

	T_BRANCO
	printf("\n");
	return 0;	
}

void printTorres(int *t1, int *t2, int *t3, int cur, int sel) {

	int a, lin, col, peca, n_esp=0;

	printf("\n");
	// Selecionado
	if(sel != -1) {
		n_esp = 12*sel + 3;
		for(a=0; a<n_esp; a++) { printf(" "); }
		printf("**");	
	}
	// Torres
	printf("\n");
	for(lin=3; lin>=0; lin--) {
		for(col=0; col<3; col ++) {
			// Seleciona a torre
			if(col == 0) { peca = getDado(t1, lin); }
			else if(col == 1) { peca = getDado(t2, lin); }
			else { peca = getDado(t3, lin); }
			// printf("Peça: %i", peca);
			//__fpurge(stdin);
			//getchar();

			// Configura Cor
			setColor(peca);
			// Desenha peça e espaços
			n_esp = (8 - peca)/2;
			for(a=0; a<n_esp; a++) { printf(" "); }
			for(a=0; a<peca; a++) { printf("="); }
			n_esp = n_esp + 4;
			for(a=0; a<n_esp; a++) { printf(" "); }
		}
		printf("\n");
	}
		
	// Cursor
	n_esp = 12*cur;
	for(a=0; a<n_esp; a++) { printf(" "); }
	T_LARANJA
	for(a=0; a<8; a++) { printf("-"); }		

	// Configura Cor Padrão - Branco
	T_BRANCO
}

void setColor(int c) {
	if(c == peca01) { T_VERMELHO }
	else if(c == peca02) { T_VERDE }
	else if(c == peca03) { T_ROXO }
	else if(c == peca04) { T_AZUL }
	else { T_BRANCO }
}

int getch(void) {

	struct termios oldattr, newattr;
	int ch;

	tcgetattr( STDIN_FILENO, &oldattr);
	newattr = oldattr;
	newattr.c_lflag &= ~( ICANON | ECHO);
	tcsetattr( STDIN_FILENO, TCSANOW, &newattr);
	ch = getchar();
	tcsetattr( STDIN_FILENO, TCSANOW, &oldattr);

	return ch;
}
