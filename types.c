#include <stdlib.h>
#include <time.h>

#include "draw.h"
#include "types.h"

void GetCurrentDate(struct tm* Date) {

	time_t CurrentTime;

	/* Lê a data do sistema e salva em CurrentTime */
	time(&CurrentTime);

	struct tm* tmp;

	/* Converte o conteúdo de time_t para struct tm */
	tmp = localtime(&CurrentTime);

	Date->tm_mday = tmp->tm_mday;

	/* tm_mon conta quantos meses se passaram desde Janeiro */
	Date->tm_mon = tmp->tm_mon + 1;

	/* tm_year conta os anos passados desde 1900 */
	Date->tm_year = tmp->tm_year + 1900;

}

/*
 * Compara duas structs tm Date. Retorna 1 se forem iguais e 0 se forem diferentes
 */
char CompareStruct_Date(struct tm* Date_1, struct tm* Date_2) {

	if (Date_1->tm_mday == Date_2->tm_mday)
		if (Date_1->tm_mon == Date_2->tm_mon)
			if (Date_1->tm_year == Date_2->tm_year)
				return 1;

	return 0;


}

/*
 * Copia duas structs ScEntry (Score Entry)
 */
void CopyStruct_ScEntry(ScEntry* Dst, ScEntry* Src) {

	Dst->Score = Src->Score;
	Dst->Date.tm_mday = Src->Date.tm_mday;
	Dst->Date.tm_mon = Src->Date.tm_mon;
	Dst->Date.tm_year = Src->Date.tm_year;

}


void InitData(GameData *Game) {

	GetCurrentDate(&(Game->Player.Date));

	/* Inicializa o score atual como 100 = Lv 1 e 0 buracos gerados */
	Game->Player.Score = 100;

	/* Inicializa o maior score atingido hoje */
	Game->Scores.Sc_today = Game->Player.Score;

	/* Inicializa o maior score já atingido como o jogador atual */
	CopyStruct_ScEntry(&(Game->Scores.Sc_highest), &(Game->Player));

	/* Screen padrão é a inicial */
	Game->Screen = INITIAL;
	Game->PrevScreen = INITIAL;
	Game->About = 0;

	/* Coordenadas iniciais do Frata */
	Game->Frata.y = FRATA_Y_INITIAL;
	Game->Frata.x = 4;

	/* Não há buracos no começo do jogo */
	Game->nb = 0;

	/* Contador começa em zero */
	Game->Refresh = 0;
	Game->Damage = 0;

	/* O jogador começa com 3 vidas */
	Game->Life = 3;

	/* Começa no nível 1 */
	Game->Level = 1;

	Game->Input = -1;

	/* Seed para o rand() */
	srand((unsigned) time(NULL));

}

void FreeData(GameData* Game) {

	if (Game->Scores.Players != NULL)
		free(Game->Scores.Players);

	if (Game->Scores.File != NULL)
		fclose(Game->Scores.File);

}

