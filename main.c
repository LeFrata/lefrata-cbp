/* 
 * Desenvolvedores:
 *  Alexandre Boutrik (@alexandreboutrik)
 *  Maria Fernanda de Bastiani (@MariaFernandadb)
 *  Giulia Rheinheimer (@Tchiulia)
 *  Larissa Machado (@Iarissamachado)
 */

#include <curses.h>

#include "fcurses.h"
#include "score.h"
#include "screen.h"
#include "types.h"
#include "update.h"

/*
 * Van Le Frata, o grande esquivador de buracos
 */
int main(int argc, const char* argv[]) {

	GameData Game;

	InitScreen();

	InitData(&Game);
	OpenFile(&Game);

	while (1) {

		/* Recebe o input do usuário */
		HandleInput(&Game);

		/* Desenha alguma tela */
		DrawScreen(&Game);

		/* Atualiza a cada 5 ms */
		napms(5);

	}

	endwin();

	Quit(&Game);

	return 0;

}

