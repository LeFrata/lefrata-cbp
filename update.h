#ifndef FT_UPDATE_H
#define FT_UPDATE_H

#include "types.h"

void		 Quit(GameData*);

void		 HandleInput(GameData*);

void		 IsGameOver(GameData*, short int);
void		 UpdateLevel(GameData*);

void		 MoveHoles(GameData*);
void		 CalculateColision(GameData*);
void		 GenerateNewHole(GameData*);

void		 ChangeScreen(GameData*, enum Scr);
void		 UpdatePosition(GameData*, int);

#endif /* FT_UPDATE_H */

