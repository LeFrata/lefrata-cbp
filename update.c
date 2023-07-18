#include <stdlib.h>
#include <stdbool.h>
#include <curses.h>

#include "draw.h"
#include "fcurses.h"
#include "screen.h"
#include "types.h"
#include "update.h"

void Quit(GameData* Game) {

	curs_set(1);
	endwin();

	FreeData(Game);

	exit(EXIT_SUCCESS);

}

void HandleInput(GameData* Game) {

	int Input = getch();

	if (Input != -1)
		Game->Input = Input;

	switch(Game->Input) {

		case 'q':
		case 'Q':
			Quit(Game);
			break;

		/*
		 * CTRL + R e T reinicia o game
		 */
		case 18:
		case 't':
		case 'T':
			InitData(Game);
			break;

		case KEY_RESIZE:
			endwin();
			InitScreen();

			clear();
			refresh();

			break;

		/*
		 * Tela inicial
		 */
		case 'i':
		case 'I':
			if (Game->Screen == GAMEOVER)
				InitData(Game);
			ChangeScreen(Game, INITIAL);
			break;

		/*
		 * Tela de ranking
		 */
		case 'r':
		case 'R':
			if (Game->Screen == RANKING)
				ChangeScreen(Game, Game->PrevScreen);
			else if (Game->Screen == INITIAL || Game->Screen == GAMEOVER)
				ChangeScreen(Game, RANKING);
			break;

		/*
		 * Pausa o jogo
		 */
		case 'p':
		case 'P':
			if (Game->Screen == PAUSE)
				ChangeScreen(Game, Game->PrevScreen);
			else if (Game->Screen == LEVEL)
				ChangeScreen(Game, PAUSE);
			break;

		/*
		 * Tela Sobre
		 */
		case 'a':
		case 'A':
			if (Game->Screen == ABOUT)
				ChangeScreen(Game, Game->PrevScreen);

			else if(Game->Screen == LEVEL){
				ChangeScreen(Game, ABOUT);
                		Game->About = PAGE_2;
               		 }

            		else {
            			ChangeScreen(Game, ABOUT);
				Game->About = PAGE_1;
			}
			break;

		/*
		 * Página do about
		 */
		case '1':
			if (Game->Screen == ABOUT)
				Game->About = PAGE_1;
			break;

		case '2':
			if (Game->Screen == ABOUT)
				Game->About = PAGE_2;
			break;

		/* Isso será removido, está aqui somente para testes */
		case 'l':
			Game->Level = 5;
			break;

		case 's':
		case 'S':
			if (Game->Screen == INITIAL) {
				ChangeScreen(Game, LEVEL);
				break;
			}
			if (Game->Screen == GAMEOVER) {
				ChangeScreen(Game, SAVESCORE);
				break;
			}

			/* FALLTHROUGH */

		case 'w':
		case 'W':
			/* FALLTHROUGH */

		case KEY_UP:
		case KEY_DOWN:
			UpdatePosition(Game, Game->Input);
			break;

	}

}

/*
 * Reduz a quantidade de vidas e verifica se é Game Over
 */
void IsGameOver(GameData* Game, short int i) {

	Game->Life--;

	if (Game->Life == 0)
		ChangeScreen(Game, GAMEOVER);

	/* Faz o Frata piscar por 50 ms */
	Game->Damage = 50;

	/* Evita a recolisão do buraco com o Le Frata */
	Game->Holes[i].x = 0;

}

/*
 * Atualiza o Game->Refresh e aumenta de nível caso necessário
 */
void UpdateLevel(GameData* Game) {

	/* Evitar overflows, Refresh agora fica entre os intervalos [0, 100] somente */
	if (Game->Level > 5)
		Game->Refresh = 100;
	else
		Game->Refresh += 20 * Game->Level;

	/* no nv 1
	 * refresh = 0
	 * depois de 10 ms = 20
	 * depois de 10 ms = 40
	 * depois de 10 ms = 60
	 * depois de 10 ms = 80
	 * depois de 10 ms = 100
	 * move os buracos para a esquerda
	 *
	 * no nv 2
	 * refresh = 0
	 * depois de 10 ms = 40
	 * depois de 10 ms = 80
	 * depois de 10 ms = 120
	 * move os buracos para a esquerda
	 * ...
	 */

	/* Quando forem gerados 25 buracos naquele nível, vá para o próximo nível */
	if (Game->nb == 25) {

		Game->nb = 0;
		Game->Level++;

	}

	if (Game->Damage > 0)
		Game->Damage--;

}

/*
 * Move os buracos para a esquerda (x--)
 */
void MoveHoles(GameData* Game) {

	short int i;

	/* Quando refresh for >= 100, movemos os buracos */
	if (Game->Refresh >= 100) {

		for (i = 0; i < Game->nb; i++)

			/* Só move caso o x for acima de 0 */
			if (Game->Holes[i].x > 0)
				Game->Holes[i].x--;

		Game->Refresh = 0;

	}

}

/*
 * Verifica se houve colisão
 */
void CalculateColision(GameData* Game) {

	short int i;

	for (i = 0; i < Game->nb; i++) {

		/* Verifica se os x e y do Frata e do Buraco[i] são iguais */
		if (Game->Holes[i].x == FRATA_X)
			if (Game->Holes[i].y == Game->Frata.y)
				IsGameOver(Game, i);

	}


}

/*
 * Gera novos buracos (obstáculos) no jogo para o Frata desviar
 */
void GenerateNewHole(GameData* Game) {

	bool existe = false;
	short int i;

	for (i = 0; i < Game->nb; i++) {

		/* Caso exista algum buraco com coordenada x maior que 75 */
		if (Game->Holes[i].x > 75)
			existe = true;

	}

	/* Só gera outro buraco caso não existirem buracos com x > 75 */
	if (existe != true) {

		Game->nb++;

		if (rand() % 2 == 0)
			Game->Holes[Game->nb % 25].y = 2;	/* Cria na primeira via */
		else
			Game->Holes[Game->nb % 25].y = 14;	/* Cria na segunda via */

		Game->Holes[Game->nb % 25].x = 95;

		/* Calcula o novo score com o buraco gerado */
		Game->Player.Score = Game->Level * 100 + Game->nb * 4;

	}

}

/*
 * Muda os enum de tela atual e tela anterior
 */
void ChangeScreen(GameData* Game, enum Scr NextScreen) {

	Game->PrevScreen = Game->Screen;
	Game->Screen = NextScreen;

}

/*
 * Atualizar a posição do Input em x ou y de acordo com as KEY_(direção)
 * Os y possíveis são 2 na primeira via e 14 na segunda via
 */
void UpdatePosition(GameData* Game, int Input) {

	switch (Input) {

		case 'w':
		case 'W':
		case KEY_UP:
			if (Game->Frata.y > FRATA_Y_INITIAL)
				Game->Frata.y = FRATA_Y_INITIAL;
			break;

		case 's':
		case 'S':
		case KEY_DOWN:
			if (Game->Frata.y < 14)
				Game->Frata.y = 14;
			break;

	}

}

