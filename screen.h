#ifndef FT_SCREEN_H
#define FT_SCREEN_H

#include "types.h"

void		 DrawInitial(void);
void		 DrawLevel(GameData*);
void		 DrawPause(void);
void		 DrawGameOver(GameData*);

void		 DrawRanking(GameData*);
void		 DrawAbout(GameData*);
void		 DrawAboutPage_1(void);
void		 DrawAboutPage_2(void);

void		 DrawScreen(GameData*);

#endif /* FT_SCREEN_H */
