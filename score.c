#include <stdlib.h>

#include "score.h"
#include "types.h"

/*
 * Conta via leitura formatada quantas entradas existem no arquivo
 */
short int CountEntries(FILE* File) {

	short int count = 0;
	ScEntry Entry;

	while ((fscanf(File, "%d %d %d %d", &(Entry.Score),
			&(Entry.Date.tm_mday), &(Entry.Date.tm_mon),
			&(Entry.Date.tm_year))) != EOF)
		count++;

	rewind(File);

	return count;

}

/*
 * Salva as entradas salvas do arquivo na struct Players
 * Também calcula os scores (Sc_highest, Sc_today e Sc_last)
 */
void FillEntries(GameData* Game) {

	short int i;
	for (i = 0; i < Game->Scores.np; i++) {

		fscanf(Game->Scores.File, "%d %d %d %d", &(Game->Scores.Players[i].Score),
				&(Game->Scores.Players[i].Date.tm_mday),
				&(Game->Scores.Players[i].Date.tm_mon),
				&(Game->Scores.Players[i].Date.tm_year));

		/* Se for maior que o maior score de hoje e as datas forem as mesmas */
		if (Game->Scores.Players[i].Score > Game->Scores.Sc_today)
			if (CompareStruct_Date(&(Game->Scores.Players[i].Date), &(Game->Player.Date)))
					Game->Scores.Sc_today = Game->Scores.Players[i].Score;

		/* Se for maior que o maior score já atingido */
		if (Game->Scores.Players[i].Score > Game->Scores.Sc_highest.Score)
			CopyStruct_ScEntry(&(Game->Scores.Sc_highest), &(Game->Scores.Players[i]));

	}

	/* Salva o score da última entrada em Sc_last */
	CopyStruct_ScEntry(&(Game->Scores.Sc_last), &(Game->Scores.Players[i-1]));

}

/*
 * Salva o score do player no arquivo
 */
void SaveScorePlayer(FILE* File, ScEntry Player) {

	/* Move o ponteiro para o final do arquivo */
	fseek(File, 0, SEEK_END);

	fprintf(File, "\n%d %d %d %d", Player.Score,
			Player.Date.tm_mday, Player.Date.tm_mon,
			Player.Date.tm_year);

}

/*
 * Verifica se existe o arquivo e cria ele caso não exista
 * Tentamos garantir que ele tenha sempre pelo menos uma entrada
 */
void CreateIfDoesntExist(GameData* Game) {

	if ((Game->Scores.File = fopen(SCOREFILE, "r")) == NULL) {

		if ((Game->Scores.File = fopen(SCOREFILE, "w")) == NULL) {

			fprintf(stderr, "erro no fopen");
			exit(1);

		}

		SaveScorePlayer(Game->Scores.File, Game->Player);

	}

	fclose(Game->Scores.File);

}

/*
 * Abre o ponteiro arquivo e salva as entradas com FillEntries
 */
void OpenFile(GameData* Game) {

	short int n;

	CreateIfDoesntExist(Game);

	/* Abre o arquivo para leitura e escrita */
	if ((Game->Scores.File = fopen(SCOREFILE, "r+")) == NULL) {

		fprintf(stderr, "Erro em fopen");
		exit(1);

	}

	/* Quantidade de entradas no arquivo */
	n = CountEntries(Game->Scores.File);

	/* Salva a quantidade em Scores.np */
	Game->Scores.np = n;

	/* alocação dinâmica da lista de jogadores */
	if ((Game->Scores.Players = (ScEntry *) malloc(n * sizeof(ScEntry))) == NULL) {

		fprintf(stderr, "erro no malloc");
		exit(1);

	}

	/* Lê o arquivo e salva cada jogador e seu score na struct Players */
	FillEntries(Game);

}

