/* display the field on the screen */
void display()
	{
	int i = 0;
	int c, r;
	for (r = 0; r < ROWS; ++r)
		{
		printf ("%02d |", r);
		for (c = 0; c < COLS; ++c)
			{
			printf("%c", chars[field[i++]]);
			}
		printf ("|\n");
		}
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
	for (i = 0; i < COLSROWS; ++i)
		field[i] = 0;
	}

