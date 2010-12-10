/*

need to actually clear lines

is evaluation correct?

*/

#include <stdlib.h>
#include <stdio.h>
#include "data.h"
#include "misc.h"
#include "logic.h"
#include "evaluate.h"
#include "moves.h"
#include "think.h"

int main()
	{
	new_game();

//int i;for (i = 0; i < PIECES; ++i){printf("%c", chars[pieces[i]]);if (i % 80 == 79)printf("\n");}
//printf("\n");return 0;

	while (1)
		{
		think(0);
		display();
		hmm();
		}

	return 0;
	}
