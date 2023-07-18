#ifndef FT_DRAW_H
#define FT_DRAW_H

#include "types.h"

#define		FRATA_Y_INITIAL		2
#define		FRATA_X				16

void		 PrintLine(unsigned char, unsigned char, short int, short int);
void		 PrintColumn(unsigned char, unsigned char, short int, short int);
void		 PrintHole(unsigned char, unsigned char, short int, short int);
void		 PrintDiamond(short int);

void		 DrawStreetLane(void);
void		 DrawLifePoints(GameData*);
void		 DrawLevelIndicator(GameData*);

void		 DrawFrata(unsigned char, unsigned char);
void		 DrawHoles(GameData*);

#endif /* FT_DRAW_H */
