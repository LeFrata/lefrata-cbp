#ifndef FT_TYPES_H
#define FT_TYPES_H

#include <stdio.h>
#include <time.h>

enum Scr {
	INITIAL = 0,
	LEVEL,
	PAUSE,
	GAMEOVER,
	SAVESCORE,
	RANKING,
	ABOUT
};

enum Abt {
	PAGE_1 = 0,
	PAGE_2
};

typedef struct ScEntry {		/* ScEntry = Score Entry */

	int				 Score;
	struct tm		 Date;

} ScEntry;

typedef struct Score {

	FILE			*File;

	ScEntry			*Players;	/* lista de jogadores */
	short int		 np;		/* quantidade de entradas, de jogadores */

	ScEntry			 Sc_highest;/* maior score já atingido, vai ter data */
	ScEntry			 Sc_last;	/* último score salvo no arquivo */
	int				 Sc_today;	/* maior score atingido hoje */

} Score;

typedef struct Hole {

	unsigned char	 y;			/* a posição em y */
	unsigned char	 x;			/* a posição em x */

} Hole;

typedef struct Van {

	unsigned char 	 y;			/* a posição em y */
	unsigned char	 x;			/* a posição em x */

} Van;

typedef struct GameData {

	ScEntry			 Player;	/* jogador atual */
	Score			 Scores;	/* ranking de scores, contém lista dos jogadores */

	enum Scr		 Screen;	/* tela atual, define quais das telas deve desenhar */
	enum Scr		 PrevScreen;/* tela anterior */
	enum Abt		 About;		/* define o número da página da tela About */

	Van				 Frata;		/* Le Frata */

	Hole			 Holes[25];	/* vetor de buracos */
	short int		 nb;		/* quantidade de buracos existentes */

	unsigned char	 Refresh;	/* contador de atualização de tela */
	unsigned char	 Damage;	/* variável auxiliar para o piscar quando leva dano */

	unsigned char	 Life;		/* quantidade de vidas */
	int				 Level;		/* nível atual */

	int				 Input;		/* última tecla pressionada */

} GameData;

void		 GetCurrentDate(struct tm*);
char		 CompareStruct_Date(struct tm*, struct tm*);

void		 CopyStruct_ScEntry(ScEntry*, ScEntry*);

void		 InitData(GameData*);
void		 FreeData(GameData*);

#endif /* FT_TYPES_H */

