#include <curses.h>

#include "draw.h"
#include "fcurses.h"
#include "score.h"
#include "screen.h"
#include "types.h"
#include "update.h"

/*
 * Desenha a tela inicial do jogo ou seja, o menu principal
 */
void DrawInitial(void) {

	short int j;

	for( j = 20; j < 24; j++)
		PrintColumn(1, j, COLOR_CYAN, 9); // coluna de L

	for( j = 9; j < 11; j++)
		PrintLine(j, 20, COLOR_CYAN, 10); // risco baixo L

	for( j = 32; j < 35; j++)
		PrintColumn(5, j, COLOR_CYAN, 6); //  coluna de E

	PrintLine(10, 35, COLOR_CYAN, 4); // risco em baixo de E

	for( j = 5; j <7; j++)
		PrintLine(j, 35, COLOR_CYAN, 4); // risco em cima de E

	PrintLine(8, 35, COLOR_CYAN, 3); // risco no meio de E

	for( j = 47; j < 51; j++)
		PrintColumn(1, j, COLOR_CYAN, 10); // coluna de F

 	for( j = 1; j < 3; j++)
 		PrintLine(j, 47, COLOR_CYAN, 10); // risco cima de F

 	for( j = 5; j < 7; j++)
 		PrintLine(j, 47, COLOR_CYAN, 7); // risco meio de F

 	for( j = 57; j < 60; j++)
 		PrintColumn(5, j, COLOR_CYAN, 6); // coluna maior de R

 	for( j = 5; j <7; j++)
 		PrintLine(j, 60, COLOR_CYAN, 4); // risco de cima de R

 	for( j = 62; j < 65; j++)
 		PrintColumn(5, j, COLOR_CYAN, 3); // coluna menor de R

	PrintLine(8, 60, COLOR_CYAN, 5); // baixo - R

	PrintLine(9, 61, COLOR_CYAN, 2);
 	PrintLine(10, 63, COLOR_CYAN, 2);
 	PrintLine(11, 65, COLOR_CYAN, 2);

 	for( j = 69; j < 72; j++)
 		PrintColumn(5, j, COLOR_CYAN, 6); // esquerda - A1

 	for( j = 5; j <7; j++)
 		PrintLine(j, 70, COLOR_CYAN, 4); // cima - A1

 	for( j = 74; j < 77; j++)
		PrintColumn(5, j, COLOR_CYAN, 6); // direita - A1

 	PrintLine(8, 70, COLOR_CYAN, 5); // baixo - A1

 	for( j = 82; j < 85; j++)
 		PrintColumn(5, j, COLOR_CYAN, 6); // T

 	for( j = 5; j <7 ; j++)
 		PrintLine(j, 79, COLOR_CYAN, 10); // cima - T

 	for( j = 91; j < 94; j++)
 		PrintColumn(5, j, COLOR_CYAN, 6); // esquerda - A1

 	for( j = 5; j <7; j++)
 		PrintLine(j, 92, COLOR_CYAN, 4); // cima - A1

 	for( j = 96; j < 99; j++)
 		PrintColumn(5, j, COLOR_CYAN, 6); // direita - A1

 	PrintLine(8, 92, COLOR_CYAN, 5); // baixo - A1

	/* Desenha o Frata */
	DrawFrata(14, 85);


	/* Desenha os buracos da tela inicial */
	PrintHole( 9, 5, COLOR_RED, 8);
    	PrintHole( 15, 8, COLOR_RED, 2);
	PrintHole( 16, 13, COLOR_RED, 4);
   	PrintHole( 18, 20, COLOR_RED, 8);

	SetColor(COLOR_WHITE, COLOR_BLACK , A_BOLD);


	mvaddch(15,45,ACS_DIAMOND);
	mvaddch(17,45,ACS_DIAMOND);
	mvaddch(19,45, ACS_DIAMOND);
	mvaddch(21,45, ACS_DIAMOND);
	mvaddch(15,61,ACS_DIAMOND);
	mvaddch(17,61,ACS_DIAMOND);
	mvaddch(19,61, ACS_DIAMOND);
	mvaddch(21,61, ACS_DIAMOND);


	/* Imprime o menu */
	SetColor(COLOR_WHITE, COLOR_BLACK, A_BOLD);

	move(15, 50);
	printw("(S)TART");

	move(17, 50);
	printw("(Q)UIT");

	move(19, 50);
	printw("(A)BOUT");

	move(21, 49);
	printw("(R)ANKING");

}

/*
 * Desenha o nível atual do jogo
 */
void DrawLevel(GameData* Game) {

	/* Aumenta o Game->Refresh e verifica se está na hora de aumentar o nível */
	UpdateLevel(Game);

	/* Move os buracos para a esquerda se Game->Refresh >= 100 */
	MoveHoles(Game);

	/* Calcula se houve alguma colisão */
	CalculateColision(Game);

	/* Desenha o LeFrata */
	if (Game->Damage % 2 == 0)
		DrawFrata(Game->Frata.y, Game->Frata.x);

	/* Desenha as vias */
	DrawStreetLane();

	/* Desenha os buracos */
	DrawHoles(Game);

	/* Desenha o indicador dos pontos de vida */
	DrawLifePoints(Game);

	/* Desenha o indicador de nível */
	DrawLevelIndicator(Game);

	/* Gera um novo buraco na tela */
	GenerateNewHole(Game);

}

/*
 * Desenha a tela de Pause
 */
void DrawPause(void) {

	short int x;

	PrintLine(4, 17, COLOR_YELLOW, 5);
	PrintLine(6, 17, COLOR_YELLOW, 5);

	for(x = 17; x < 19; x++)
		PrintColumn(4, x, COLOR_YELLOW, 5);
	for(x = 22; x < 24; x++)
		PrintColumn(4, x, COLOR_YELLOW, 3);

	//a
	PrintLine(4, 26, COLOR_YELLOW, 5);
	PrintLine(6, 26, COLOR_YELLOW, 5);

	for(x = 26; x < 28; x++)
		PrintColumn(4, x, COLOR_YELLOW, 5);
	for(x = 31; x < 33; x++)
		PrintColumn(4, x, COLOR_YELLOW, 5);

	//u
	for(x = 35; x < 37; x++)
		PrintColumn(4, x, COLOR_YELLOW, 5);
	for(x = 40; x < 42; x++)
		PrintColumn(4, x, COLOR_YELLOW, 5);

	PrintLine(8, 35, COLOR_YELLOW, 5);

	//s
	PrintLine(4, 44, COLOR_YELLOW, 6);
	PrintLine(6, 44, COLOR_YELLOW, 6);
	PrintLine(8, 44, COLOR_YELLOW, 6);

	for(x = 44; x < 46; x++)
		PrintColumn(4, x, COLOR_YELLOW, 3);
	for(x = 48; x < 50; x++)
		PrintColumn(6, x, COLOR_YELLOW, 3);

	//e
	for(x = 52; x < 54; x++)
		PrintColumn(4, x, COLOR_YELLOW, 5);

	PrintLine(4, 52, COLOR_YELLOW, 6);
	PrintLine(6, 52, COLOR_YELLOW, 6);
	PrintLine(8, 52, COLOR_YELLOW, 6);

	//botao de pause
	for(x = 29; x < 31; x++)
		PrintColumn(10, x, COLOR_YELLOW, 9);
	for(x = 44; x < 46; x++)
		PrintColumn(10, x, COLOR_YELLOW, 9);

	PrintLine(10, 30, COLOR_YELLOW, 14);
	PrintLine(18, 30, COLOR_YELLOW, 14);

	//setinha no meio
	for(x = 35; x < 37; x++)
		PrintColumn(12, x, COLOR_YELLOW, 5);
	for(x = 37; x < 39; x++)
		PrintColumn(13, x, COLOR_YELLOW, 3);
	for(x = 39; x < 41; x++)
		PrintColumn(14, x, COLOR_YELLOW, 1);

}

/*
 * Desenha a tela de GameOver
 */
void DrawGameOver(GameData* Game) {

	short int y, x;

	/*QUADRADOS ESQUERDA*/

	for (x=3; x < 9; x++)
		PrintColumn(4, x, COLOR_RED, 3);

	for (x=3; x < 9; x++)
		PrintColumn(8, x, COLOR_RED, 3);

	for (x=3; x < 9; x++)
		PrintColumn(12, x, COLOR_RED, 3);

	for (x=3; x < 9; x++)
		PrintColumn(16, x, COLOR_RED, 3);

	for (x=3; x < 9; x++)
		PrintColumn(20, x, COLOR_RED, 1);

	/*G*/

	for (y=4; y < 5; y++)
		PrintLine(y, 16, COLOR_RED, 5);

	for (x=15; x < 17; x++)
		PrintColumn(5, x, COLOR_RED, 5);

	for (y=10; y < 11; y++)
		PrintLine(y, 16, COLOR_RED, 4);

	for (x=19; x < 21; x++)
		PrintColumn(8, x, COLOR_RED, 2);

	for (y=7; y < 8; y++)
		PrintLine(y, 18, COLOR_RED, 3);

	for (x=17; x < 18; x++)
		PrintColumn(11, x, COLOR_RED, 3);

	for (x=18; x < 19; x++)
		PrintColumn(11, x, COLOR_RED, 1);

	/*A*/

	for (x=22; x < 24; x++)
		PrintColumn(4, x, COLOR_RED, 7);

	for (y=4; y < 5; y++)
		PrintLine(y, 24, COLOR_RED, 2);

	for (y=7; y < 8; y++)
		PrintLine(y, 24, COLOR_RED, 2);

	for (x=26; x < 28; x++)
		PrintColumn(4, x, COLOR_RED, 7);

	for (x=23; x < 24; x++)
		PrintColumn(11, x, COLOR_RED, 2);

	for (x=26; x < 27; x++)
		PrintColumn(11, x, COLOR_RED, 3);

	/*M*/

	for (x=29; x < 31; x++)
		PrintColumn(4, x, COLOR_RED, 7);

	for (y=4; y < 5; y++)
		PrintLine(y, 31, COLOR_RED, 1);

	for (x=32; x < 33; x++)
		PrintColumn(5, x, COLOR_RED, 2);

	for (y=4; y < 5; y++)
		PrintLine(y, 33, COLOR_RED, 1);

	for (x=34; x < 36; x++)
		PrintColumn(4, x, COLOR_RED, 7);

	for (x=29; x < 30; x++)
		PrintColumn(11, x, COLOR_RED, 3);

	for (x=34; x < 35; x++)
		PrintColumn(11, x, COLOR_RED, 1);

	/*E*/

	for (x=37; x < 39; x++)
		PrintColumn(4, x, COLOR_RED, 7);

	for (y=4; y < 5; y++)
		PrintLine(y, 39, COLOR_RED, 4);

	for (y=7; y < 8; y++)
		PrintLine(y, 39, COLOR_RED, 2);

	for (y=10; y < 11; y++)
		PrintLine(y, 39, COLOR_RED, 4);

	for (x=40; x < 41; x++)
		PrintColumn(11, x, COLOR_RED, 3);


	for (x=38; x < 39; x++)
		PrintColumn(11, x, COLOR_RED, 2);

	for (x=41; x < 42; x++)
		PrintColumn(11, x, COLOR_RED, 1);

	/*O*/

	for (x= 49; x < 51; x++)
		PrintColumn(5, x, COLOR_RED, 5);

	for (y=4; y < 5; y++)
		PrintLine(y, 50, COLOR_RED, 4);

	for (y=10; y < 11; y++)
		PrintLine(y, 50, COLOR_RED, 4);

	for (x= 53; x < 55; x++)
		PrintColumn(5, x, COLOR_RED, 5);

	for (x=51; x < 52; x++)
		PrintColumn(11, x, COLOR_RED, 2);

	for (x=52; x < 53; x++)
		PrintColumn(11, x, COLOR_RED, 1);

	/*V*/

	for (x= 56; x < 58; x++)
		PrintColumn(4, x, COLOR_RED, 5);

	for (x=58; x < 59; x++)
		PrintColumn(9, x, COLOR_RED, 2);

	for (x=60; x < 61; x++)
		PrintColumn(9, x, COLOR_RED, 2);

	for (x= 61; x < 63; x++)
		PrintColumn(4, x, COLOR_RED, 5);

	for (x=59; x < 60; x++)
		PrintColumn(11, x, COLOR_RED, 2);

	/*E*/

	for (x= 64; x < 66; x++)
		PrintColumn(4, x, COLOR_RED, 7);

	for (y=4; y < 5; y++)
		PrintLine(y, 66, COLOR_RED, 4);

	for (y=7; y < 8; y++)
		PrintLine(y, 66, COLOR_RED, 2);

	for (y=10; y < 11; y++)
		PrintLine(y, 66, COLOR_RED, 4);

	for (x=65; x < 66; x++)
		PrintColumn(11, x, COLOR_RED, 1);

	for (x=66; x < 67; x++)
		PrintColumn(11, x, COLOR_RED, 2);

	for (x=69; x < 70; x++)
		PrintColumn(11, x, COLOR_RED, 3);

	/*R*/

	for (x= 71; x < 73; x++)
		PrintColumn(4, x, COLOR_RED, 7);

	for (y=4; y < 5; y++)
		PrintLine(y, 73, COLOR_RED, 4);

	for (x= 75; x < 77; x++)
		PrintColumn(4, x, COLOR_RED, 3);

	for (y=7; y < 8; y++)
		PrintLine(y, 73, COLOR_RED, 4);

	for (y=8; y < 9; y++)
		PrintLine(y, 73, COLOR_RED, 1);

	for (y=9; y < 10; y++)
		PrintLine(y, 74, COLOR_RED, 1);

	for (x=75; x < 76; x++)
		PrintColumn(10, x, COLOR_RED, 3);

	/*QUADRADOS DIREITA*/

	for (x= 84; x < 90; x++)
		PrintColumn(4, x, COLOR_RED, 3);

	for (x= 84; x < 90; x++)
		PrintColumn(8, x, COLOR_RED, 3);

	for (x= 84; x < 90; x++)
		PrintColumn(12, x, COLOR_RED, 3);

	for (x= 84; x < 90; x++)
		PrintColumn(16, x, COLOR_RED, 3);

	for (x= 84; x < 90; x++)
		PrintColumn(20, x, COLOR_RED, 1);


	/*ENTRADAS MARGEM*/


	for (y = 16; y < 17; y++)
		PrintLine(y, 15, COLOR_WHITE, 62);

	for (x = 15; x < 16; x++)
		PrintColumn(16, x, COLOR_WHITE, 4);

	for (y = 20; y < 21; y++)
		PrintLine(y, 15, COLOR_WHITE, 62);

	for (x = 76; x < 77; x++)
		PrintColumn(16, x, COLOR_WHITE, 4);


	/* Imprime o Score na tela GameOver*/

	SetColor(COLOR_BLACK, COLOR_WHITE, A_BOLD);
	mvprintw(18, 22, "SCORE %d", Game->Player.Score);

	SetColor(COLOR_WHITE, COLOR_RED, A_BOLD);

	/*ENTRADAS*/

	mvprintw(18, 35, ("(T)RY AGAIN")); // antes era 28

	mvprintw(18, 48, ("(S)AVE SCORE"));	// 41

	mvprintw(18, 62, ("(Q)UIT"));	// 55

}

/*
 * Desenha a tela com os rankings
 */
void DrawRanking(GameData* Game) {

	char x;

        //tabela
        for (x = 17; x < 78; x++)
		PrintColumn(4, x, COLOR_CYAN, 7);

	for (x = 17; x < 19; x++)
		PrintColumn(11, x, COLOR_CYAN, 12);

	for (x = 76; x < 78; x++)
		PrintColumn(11, x, COLOR_CYAN, 12);

	for (x = 37; x < 39; x++)
		PrintColumn(11, x, COLOR_CYAN, 12);

	for (x = 56; x < 58; x++)
		PrintColumn(11, x, COLOR_CYAN, 12);


	PrintLine(22, 19, COLOR_CYAN, 57);
	PrintLine(14, 19, COLOR_CYAN, 57);
	PrintLine(18, 19, COLOR_CYAN, 57);

        //f
	PrintLine(5, 19, COLOR_WHITE, 4);
	PrintLine(7, 19, COLOR_WHITE, 3);
	PrintColumn(5, 19, COLOR_WHITE, 5);

	//r

	PrintColumn(5, 24, COLOR_WHITE, 5);
	PrintColumn(5, 27, COLOR_WHITE, 2);
	PrintLine(5, 24, COLOR_WHITE, 3);
	PrintLine(7, 24, COLOR_WHITE, 3);
	PrintColumn(8, 27, COLOR_WHITE, 2);

	//a

	PrintColumn(5, 29, COLOR_WHITE, 5);
	PrintColumn(5, 32, COLOR_WHITE, 5);
	PrintLine(5, 29, COLOR_WHITE, 3);
	PrintLine(7, 29, COLOR_WHITE, 3);

	//t

	PrintColumn(5, 36, COLOR_WHITE, 5);
	PrintLine(5, 34, COLOR_WHITE, 5);

	//a

	PrintColumn(5, 40, COLOR_WHITE, 5);
	PrintColumn(5, 43, COLOR_WHITE, 5);
	PrintLine(5, 40, COLOR_WHITE, 3);
	PrintLine(7, 40, COLOR_WHITE, 3);

	//s

	PrintLine(5, 49, COLOR_WHITE, 5);
	PrintLine(7, 49, COLOR_WHITE, 5);
	PrintLine(9, 49, COLOR_WHITE, 5);
	PrintColumn(5, 49, COLOR_WHITE, 2);
	PrintColumn(7, 53, COLOR_WHITE, 2);

	//c

	PrintColumn(5, 55, COLOR_WHITE, 5);
	PrintLine(5, 55, COLOR_WHITE, 5);
	PrintLine(9, 55, COLOR_WHITE, 5);

	//o

	PrintLine(5, 61, COLOR_WHITE, 5);
	PrintLine(9, 61, COLOR_WHITE, 5);
	PrintColumn(5, 61, COLOR_WHITE, 5);
	PrintColumn(5, 65, COLOR_WHITE, 5);

	//r
	PrintColumn(5, 67, COLOR_WHITE, 5);
	PrintColumn(5, 70, COLOR_WHITE, 2);
	PrintLine(5, 67, COLOR_WHITE, 3);
	PrintLine(7, 67, COLOR_WHITE, 3);
	PrintColumn(8, 70, COLOR_WHITE, 2);

	//e
	PrintColumn(5, 72, COLOR_WHITE, 5);
	PrintLine(5, 72, COLOR_WHITE, 4);
	PrintLine(7, 72, COLOR_WHITE, 4);
	PrintLine(9, 72, COLOR_WHITE, 4);


	SetColor(COLOR_WHITE, COLOR_BLACK, A_BOLD);
	mvprintw(12, 22, "HIGHEST EVER"); //pontuacao mais alta

	mvprintw(16, 23, "BEST TODAY"); //melhor pontuacao no dia

	mvprintw(20, 23, "LAST SCORE"); //pontuacao atual

	mvprintw(12, 45, "%d", Game->Scores.Sc_highest.Score); //puxa a pontuacao mais alta

	mvprintw(16, 45, "%d", Game->Scores.Sc_today); // puxa a melhor do dia

	mvprintw(20, 45, "%d", Game->Scores.Sc_last.Score); // puxa a última

	//imprime a data da pontuacao
	mvprintw(12, 63, "%d/%d/%d ", Game->Scores.Sc_highest.Date.tm_mday, Game->Scores.Sc_highest.Date.tm_mon, Game->Scores.Sc_highest.Date.tm_year);
	mvprintw(16, 63, "%d/%d/%d ", Game->Player.Date.tm_mday, Game->Player.Date.tm_mon, Game->Player.Date.tm_year);
	mvprintw(20, 63, "%d/%d/%d ", Game->Scores.Sc_last.Date.tm_mday, Game->Scores.Sc_last.Date.tm_mon, Game->Scores.Sc_last.Date.tm_year);

}

/*
 * Desenha a tela que diz "Score salvo"
 */
void DrawSaveScore(GameData* Game) {

	char x;

        //s
	PrintLine(7, 22, COLOR_BLUE, 5);
	PrintLine(9, 22, COLOR_BLUE, 5);
	PrintLine(11, 22, COLOR_BLUE, 5);
	PrintColumn(7, 22, COLOR_BLUE, 2);
	PrintColumn(9, 26, COLOR_BLUE, 2);

	//c
	PrintColumn(7, 28, COLOR_BLUE, 5);
	PrintLine(7, 28, COLOR_BLUE, 5);
	PrintLine(11, 28, COLOR_BLUE, 5);

	//o
	PrintLine(7, 34, COLOR_BLUE, 5);
	PrintLine(11, 34, COLOR_BLUE, 5);
	PrintColumn(7, 34, COLOR_BLUE, 5);
	PrintColumn(7, 38, COLOR_BLUE, 5);

	//r
	PrintColumn(7, 40, COLOR_BLUE, 5);
	PrintColumn(7, 43, COLOR_BLUE, 2);
	PrintLine(7, 40, COLOR_BLUE, 3);
	PrintLine(9, 40, COLOR_BLUE, 3);
	PrintColumn(10, 43, COLOR_BLUE, 2);

	//e
	PrintColumn(7, 45, COLOR_BLUE, 5);
	PrintLine(7, 45, COLOR_BLUE, 4);
	PrintLine(9, 45, COLOR_BLUE, 4);
	PrintLine(11, 45, COLOR_BLUE, 4);

	//s
	PrintLine(7, 51, COLOR_BLUE, 5);
	PrintLine(9, 51, COLOR_BLUE, 5);
	PrintLine(11, 51, COLOR_BLUE, 5);
	PrintColumn(7, 51, COLOR_BLUE, 2);
	PrintColumn(9, 55, COLOR_BLUE, 2);

	//a
	PrintLine(7, 57, COLOR_BLUE, 5);
	PrintLine(9, 58, COLOR_BLUE, 3);
	PrintColumn(7, 57, COLOR_BLUE, 5);
	PrintColumn(7, 61, COLOR_BLUE, 5);

	//faz o l
	PrintColumn(7, 63, COLOR_BLUE, 5);
	PrintLine(11, 64, COLOR_BLUE, 4);

	//v
	PrintColumn(7, 69, COLOR_BLUE, 3);
	PrintColumn(7, 73, COLOR_BLUE, 3);
	PrintColumn(10, 70, COLOR_BLUE, 1);
	PrintColumn(11, 71, COLOR_BLUE, 1);
	PrintColumn(10, 72, COLOR_BLUE, 1);

	//o
	PrintLine(7, 76, COLOR_BLUE, 4);
	PrintLine(11, 76, COLOR_BLUE, 4);
	PrintColumn(7, 75, COLOR_BLUE, 5);
	PrintColumn(7, 79, COLOR_BLUE, 5);

	// !
	PrintColumn(7, 85, COLOR_BLUE, 3);
	PrintLine(11, 85, COLOR_BLUE, 1);

        SetColor(COLOR_WHITE, COLOR_BLACK, 0);
	mvprintw(14, 44, " Clique para sair:");
	mvaddch(15, 49, ACS_ULCORNER);
	mvaddch(17, 49, ACS_LLCORNER);
	mvaddch(15, 56, ACS_URCORNER);
	mvaddch(17, 56, ACS_LRCORNER);

	for(x = 50; x < 56; x++) {
	mvaddch(17, x, ACS_HLINE);
	mvaddch(17, x, ACS_HLINE);
	mvaddch(15, x, ACS_HLINE);
	mvaddch(15, x, ACS_HLINE); }

	mvaddch(16, 49, ACS_VLINE);
	mvaddch(16, 56, ACS_VLINE);

        SetColor(COLOR_BLUE, COLOR_BLACK, 0);
	mvprintw(16, 51, "(O)K");

	SaveScorePlayer(Game->Scores.File, Game->Player);

	while (1) {

		switch (Game->Input) {

			case 'o':
			case 'O':
			case 'q':
			case 'Q':
				Quit(Game);
				break;

			default:
				Game->Input = getch();

		}

	}

}


/*
 * Desenha a primeira página do About
 */
void DrawAboutPage_1(void){

	char i;

	/* Desenha ABOUT na tela */

	// Desenha A
	for( i = 29; i < 31; i++ )
		PrintColumn(1, i, COLOR_BLUE, 5);

	PrintLine(1, 31, COLOR_BLUE, 3);
	PrintLine(3, 31, COLOR_BLUE, 3);

	for( i = 34 ; i < 36; i++ )
		PrintColumn(1, i, COLOR_BLUE, 5);


	// Desenha B
	for( i = 38; i < 40; i++ )
		PrintColumn(1, i, COLOR_BLUE, 4);

	PrintLine(1, 39, COLOR_BLUE, 4);
	PrintLine(3, 39, COLOR_BLUE, 4);

	for( i = 42 ; i < 44; i++ )
		PrintColumn(1, i, COLOR_BLUE, 2);

	for( i = 43; i < 45; i++ )
		PrintColumn(3, i, COLOR_BLUE, 2);

	PrintLine(5, 38, COLOR_BLUE, 7);


	// Desenha O
	for( i = 47; i< 49; i++ )
		PrintColumn(1, i, COLOR_BLUE, 5);

	PrintLine(1, 49, COLOR_BLUE, 3);
	PrintLine(5, 49, COLOR_BLUE, 3);

	for( i = 52 ; i < 54; i++ )
		PrintColumn(1, i, COLOR_BLUE, 5);


	// Desenha U
	for( i = 56; i < 58; i++ )
		PrintColumn(1, i, COLOR_BLUE, 5);

	PrintLine(5, 58, COLOR_BLUE, 3);

	for( i = 61 ; i < 63; i++ )
		PrintColumn(1, i, COLOR_BLUE, 5);


	// Desenha T
	for( i = 67; i< 69; i++ )
		PrintColumn(1, i, COLOR_BLUE, 5);

	PrintLine(1, 65 , COLOR_BLUE, 6);


	/* Imprime o cabeçalho*/
	SetColor(COLOR_WHITE, COLOR_BLACK, A_BOLD);
	mvprintw(1, 2,"P%cGINA 1/2", 181);
	mvprintw(1, 85, "Press (2) for ");
	mvaddch(1, 99, ACS_RARROW);
	SetColor(COLOR_YELLOW, COLOR_CYAN, A_BOLD);
	mvprintw(1, 9,"1");


	/* Imprime o texto de conteztualização */
	SetColor(COLOR_WHITE, COLOR_BLACK, A_BOLD);
	move(8, 2);
	printw("      Uma bela sexta-feira ensolarada! Diferentemente do dia anterior, h%c poucas, mas brancas", 160);
	move(9, 2);
	printw("nuvens no c%cu de uma fresca manh%c. Com %cxito, a afamada van Frata cumprir%c mais uma vez o seu mais", 130, 198, 136, 160);
	move(10, 14);
	printw("nobre objetivo: levar os estudantes e chegar ao seu destino %c tempo...", 133);
	move(12, 2);
	printw("    Ah n%co! Sua rota di%cria parece ter sido obtru%cda por %crvores e pedras advindas da tempestade ", 198, 160, 161, 160);
	move(13, 2);
	printw("noite de quinta-feira. Sua %cnica alternativa, ent%co: fazer um desvio por uma estrada seriamente ", 163, 198);
	move(14, 15);
	printw("esburacada. Frata est%c atrasado dessa vez e, agora, precisar%c se apressar.", 160, 160);

	SetColor(COLOR_CYAN, COLOR_BLACK, A_BOLD);
	move(17, 14);
	printw("GUIE O FRATA AO LONGO DE SUA ROTA DESVIANDO DO M%cXIMO DE BURACOS QUE PUDER", 181);
	move(20, 65);
	SetColor(COLOR_WHITE, COLOR_BLACK, A_BOLD);
	printw("(Instru%c%ces e informa%c%ces p%cgina 2)", 135, 228, 135, 228,160);


	/* Imprime os diamantes */
	SetColor(COLOR_CYAN, COLOR_BLACK, A_BOLD);
	mvaddch(17, 10, ACS_DIAMOND);
        mvaddch(17, 91, ACS_DIAMOND);


	/* Imprime os quadrados vermelhos (buracos) na tela*/
	PrintHole(20, 2, COLOR_RED, 4);
	PrintHole(18, 5, COLOR_RED, 2);
	PrintHole(16, 2, COLOR_RED, 2);
	PrintHole(19, 9, COLOR_RED, 4);
	PrintHole(21, 15, COLOR_RED, 2);

}

/*
 * Desenha a segunda página do About
 */
void DrawAboutPage_2(void){

	/* Imprime os cabeçalho */
	SetColor(COLOR_WHITE, COLOR_BLACK, A_BOLD);
	mvprintw(1,2,"P%cGINA 1/2", 181);
	mvprintw(1, 92, "Press (1)");
	mvaddch(1, 89, ACS_LARROW);
	SetColor(COLOR_YELLOW, COLOR_CYAN, A_BOLD);
	mvprintw(1,11,"2");

	/* Imprime os títulos das seções */
	SetColor(COLOR_WHITE, COLOR_BLUE, A_BOLD);
	move(3,18);
	printw("INSTRU%c%cES", 128, 229);
	move(14, 54);
	printw("CR%cDITOS", 144);


	/* Imprime as linhas de divisão da tela */
	SetColor(COLOR_BLUE, COLOR_BLACK, A_BOLD);
	char i;
	for( i = 3; i < 23; i++)
        	mvaddch( i , 50, ACS_VLINE);
    	SetColor(COLOR_BLUE, COLOR_BLACK, A_BOLD);
    	for( i = 63; i < 101; i++)
        	mvaddch( 14, i, ACS_HLINE);


    	/* Imrpime as instruções de movimentação */
    	SetColor(COLOR_WHITE, COLOR_BLACK, A_BOLD);
    	mvaddch(6, 10,',');
    	mvprintw(6, 15, "PARA MOVER-SE NO JOGO.");
    	SetColor(COLOR_RED, COLOR_BLACK, A_BOLD);
    	mvaddch( 6, 8, ACS_UARROW);
    	mvaddch( 7, 8, ACS_DARROW);
    	SetColor(COLOR_YELLOW, COLOR_BLACK, A_BOLD);
    	mvaddch( 6, 12, 'W');
    	mvaddch( 7, 12, 'S');


    	/* Imprime as demais intruções */
    	SetColor(COLOR_WHITE, COLOR_BLACK, A_BOLD);
    	mvprintw(9, 2,"ABOUT:  pressione A a qualque momento.");
    	mvprintw(11, 2,"PAUSE:  pressione P durante o jogo.");
    	mvprintw(13, 2,"QUIT:  pressione Q a qualquer momento.");
    	mvprintw(15, 2,"REINICIAR O JOGO:            ou    .");
    	mvprintw(17, 2,"TELA INICIAL:  pressione I a qualquer momento");
    	mvprintw(19, 2,"RANKING:  pressione R antes ou ao final do jogo.");
    	mvprintw(21, 2,"SAVESCORE:  pressione S ao final do jogo.");


    	/* Imprime os caracteres de destaque das intruções */
    	SetColor(COLOR_BLUE, COLOR_BLACK, A_BOLD);
    	mvaddch(9, 20, 'A');
    	mvaddch(11, 20, 'P');
    	mvaddch(13, 19, 'Q');
    	mvprintw(15, 21,"CTRL + R");
    	mvaddch(15, 35, 'T');
    	mvaddch(17, 27,'I');
    	mvaddch(19, 22, 'R');
    	mvaddch(21, 24, 'S');


    	/* Imprime os nomes em destaque de cada intruções */
    	SetColor(COLOR_CYAN, COLOR_BLACK, A_BOLD);
    	mvprintw(6,2,"USE: ");
    	mvprintw(9,2,"ABOUT:");
    	mvprintw(11,2,"PAUSE:");
    	mvprintw(13,2,"QUIT:");
    	mvprintw(15,2,"REINICIAR O JOGO:");
    	mvprintw(17,2,"TELA INICIAL:");
    	mvprintw(19,2,"RANKING:");
    	mvprintw(21,2,"SAVESCORE:");


    	/* Imprime as informações do lado esquerdo */
    	SetColor(COLOR_WHITE, COLOR_BLACK, A_BOLD);
    	move(3, 53);
    	printw("O GAMEOVER acontece ap%cs 3 colis%ces com buracos.", 162, 228);
    	move(5, 53);
    	printw("A velocidade m%cxima %c atingida ao alcan%car LEVEL 5.", 160, 130, 135);
    	move(7, 53);
    	printw("Caso seja desejado, pode-se acessar o hist%crico de", 162);
    	move(8, 53);
    	printw("scores: pesquise pelo arquivo 'score.txt' em sua");
    	move(9, 53);
    	printw("m%cquina.", 160);
    	SetColor(COLOR_RED, COLOR_BLACK, A_BOLD);
    	move(11, 53);
    	printw("ATEN%c%cO: as dimens%ces m%cnimas da tela do terminal", 128, 199, 228, 161);
    	mvprintw(12,53,"devem ser 103 X 23.");


    	/* Imprime os créditos */
    	SetColor(COLOR_WHITE, COLOR_BLACK, A_BOLD);
    	move(16, 53);
    	printw("Criadores:");
    	mvprintw(16, 68,"Alexandre Boutrik");
    	mvprintw(17, 68,"Giulia Maria Rheinheimer");
    	mvprintw(18, 68,"Larissa Machado");
    	mvprintw(19, 68,"Maria Fernanda De Bastiani");
    	move(21, 68);
    	printw("2023 LeFrata%c", 169);

    	/* Imprime os quadrados vermelhos (buracos) na tela*/
    	PrintHole(21, 100, COLOR_RED, 4);
    	PrintHole(18, 97, COLOR_RED, 4);
    	PrintHole(16, 100, COLOR_RED, 2);
    	PrintHole(21, 95, COLOR_RED, 2);
    	PrintHole(22, 91, COLOR_RED, 2);

}

void DrawAbout(GameData* Game) {

    switch (Game->About){

        case PAGE_1:
            DrawAboutPage_1();
            break;

        case PAGE_2:
            DrawAboutPage_2();
             break;
     }

}


/*
 * Desenha a tela especificada em Game->Screen
 */
void DrawScreen(GameData* Game) {

	clear();

	switch (Game->Screen) {

		case LEVEL:
			DrawLevel(Game);
			break;

		case PAUSE:
			DrawPause();
			break;

		case GAMEOVER:
			DrawGameOver(Game);
			break;

		case RANKING:
			DrawRanking(Game);
			break;

		case SAVESCORE:
			DrawSaveScore(Game);
			break;

		case ABOUT:
			DrawAbout(Game);
			break;

		default:
			DrawInitial();

	}

	/* Voltamos o Input para seu valor inicial */
	Game->Input = -1;

	refresh();

}


