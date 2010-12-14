/* display the field on the screen */
void display()
	{
	int i = 0;
	int m = memory_place;
	int c, r;
	for (r = 0; r < ROWS; ++r)
		{
		printf ("%02d |", r);
		for (c = 0; c < COLS; ++c)
			{
			printf("%c", chars[field[i++]]);
			}
		printf ("|");
		if (r < 4)
			{
			printf(" ");
			do
				{
				for (c = 0; c < 4; ++c)
					{
					if (r * 4 + c < 15 && pieces[memory[m]*ROTATIONS_PER_PIECE*PIECE_BITS + r * 4 + c])
						printf("%c", chars[memory[m]+1]);
					else
						printf(" ");
					}
				m = (m + 1) % MEMORY_SIZE;
				}
			while (m != memory_place);
			}
		printf ("\n");
		}
	printf("Pieces dropped: %d\n", pieces_dropped);
	printf("Lines cleared:  %d\n", lines_cleared);
	printf("Evaluation: %d\n", evaluate());
	}

/* just to be able to undo moves */
int saved_field[COLSROWS];
inline void save_field()
	{
	int i;
	for (i = 0; i < COLSROWS; ++i)
		saved_field[i] = field[i];
	}
inline void restore_field()
	{
	int i;
	for (i = 0; i < COLSROWS; ++i)
		field[i] = saved_field[i];
	}

/* other helpers */
void hmm()
	{
	printf("Pause...");
	getc(stdin);
	printf("\n");
	}

void new_game()
	{
	int i;
	pieces_dropped =
	lines_cleared = 0;
	for (i = 0; i < MEMORY_SIZE; ++i)
		memory[i] = rand() % 7;
	for (i = 0; i < COLSROWS; ++i)
		field[i] = 0;
	}

