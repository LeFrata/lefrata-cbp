#include <curses.h>

#include "fcurses.h"
#include "draw.h"
#include "types.h"

/*
 * Desenha uma linha de algo
 * n é a quantidade de espaços
 */
void PrintLine(unsigned char y, unsigned char x, short int cor, short int n) {

	move(y, x);
	SetColor(COLOR_WHITE, cor, A_BOLD);

	for (; n > 0; n--)
		printw(" ");

}

/*
 * Desenha uma coluna de algo
 * n é a quantidade de espaços
 */
void PrintColumn(unsigned char y, unsigned char x, short int cor, short int n){

	SetColor(COLOR_WHITE, cor, A_BOLD);

	for( ; n > 0; n--){

		move(y++, x);
		printw(" ");

	}

}

/*
 * Desenha um buraco na tela inicial de tamanho n
 */
void PrintHole(unsigned char y, unsigned char x, short int cor, short int n){

	short int w = (n / 2);

	for (; w > 0; y++, w--)
		PrintLine(y, x, cor, n);


}

/* Imprime uma quantidade i de Diamantes */
void PrintDiamond(short int i) {

	for (; i > 0; i--)
		mvaddch(21, 76 + 2 * i, ACS_DIAMOND);

}


/*
 * Desenha as faixas da rua
 */
void DrawStreetLane(void) {

	/* Faixa contínua de cima */
	PrintLine(1, 2, COLOR_WHITE, 100);

	/* Faixa do meio */
	PrintLine(12, 8, COLOR_YELLOW, 10);
	PrintLine(12, 28, COLOR_YELLOW, 10);
	PrintLine(12, 48, COLOR_YELLOW, 10);
	PrintLine(12, 68, COLOR_YELLOW, 10);
	PrintLine(12, 88, COLOR_YELLOW, 10);

	/* Faixa contínua de baixo */
	PrintLine(23, 2, COLOR_WHITE, 100);

}

/*
 * Desenha os pontos de vida restantes
 */
void DrawLifePoints(GameData* Game) {

	SetColor(COLOR_WHITE, COLOR_BLACK, A_BOLD);

	mvprintw(21, 70, "VIDAS = ");

	SetColor(COLOR_RED, COLOR_BLACK, A_BOLD);

	PrintDiamond(Game->Life);

}

/*
 * Imprime o nível atual
 */
void DrawLevelIndicator(GameData* Game) {

	SetColor(COLOR_WHITE, COLOR_BLACK, A_BOLD);

	mvprintw(21, 87, "LEVEL = ");

	SetColor(COLOR_CYAN, COLOR_BLACK, A_BOLD);

	printw(" %d", Game->Level);

}

/*
 * Desenha o Frata na tela, na posição y e x
 */
void DrawFrata(unsigned char y, unsigned char x) {

	PrintLine(y + 2, x, COLOR_MAGENTA, 9);

	/* Vidros */
	PrintLine(y + 2, x + 9, COLOR_CYAN, 2);

	PrintLine(y + 3, x, COLOR_MAGENTA, 13);
	PrintLine(y + 3, x + 12, COLOR_YELLOW, 1);
	PrintLine(y + 4, x, COLOR_BLUE, 13);
	PrintLine(y + 5, x, COLOR_MAGENTA, 13);

	/* Rodas */
	PrintLine(y + 6, x + 1, COLOR_WHITE, 2);
	PrintLine(y + 6, x + 9, COLOR_WHITE, 2);

}

/*
 * Desenha os buracos
 */
void DrawHoles(GameData* Game) {

	short int i;

	for (i = 0; i < Game->nb; i++) {

		/*
		 * Os buracos devem possuir x > frente do Frata para serem desenhados
		 */
		if (Game->Holes[i].x > FRATA_X) {

			PrintLine(Game->Holes[i].y + 3, Game->Holes[i].x, COLOR_RED, 6);
			PrintLine(Game->Holes[i].y + 4, Game->Holes[i].x, COLOR_RED, 6);
			PrintLine(Game->Holes[i].y + 5, Game->Holes[i].x, COLOR_RED, 6);

		}

	}

}

