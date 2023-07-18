#ifndef FT_SCORE_H
#define FT_SCORE_H

#include "types.h"

#define		SCOREFILE				"scores.txt"

short int	 CountEntries(FILE*);
void		 FillEntries(GameData*);

void		 SaveScorePlayer(FILE*, ScEntry);

void		 CreateIfDoesntExist(GameData*);
void		 OpenFile(GameData*);

#endif /* FT_SCORE_H */

