/* just to be able to undo moves */
int saved_field[MEMORY_SIZE][COLSROWS];
inline void save_field(int depth)
	{
	int i;
	for (i = 0; i < COLSROWS; ++i)
		saved_field[depth][i] = field[i];
	}
inline void restore_field(int depth)
	{
	int i;
	for (i = 0; i < COLSROWS; ++i)
		field[i] = saved_field[depth][i];
	}

/* helper function mostly for can_fit_piece() */
int count_holes()
	{
	int i;

	/*
	this doesn't actually count holes but holes per column
	but should be good enough for comparative purposes
	*/
	int holes = 0;

	for (i = 0; i < COLSROWS; ++i)
		{
		if (i < COLS)
			column_height[i] = ROWS;

		if (field[i] > 0)
			if (i + COLS < COLSROWS && field[i + COLS] == 0)
				++holes;
		}
	return holes;
	}

/* helper function for evaluation */
int can_fit_piece(int piece_id, int depth)
	{
	int* piece = &pieces[piece_id * ROTATIONS_PER_PIECE * PIECE_BITS];

	int rotation;

	int i;
	int col;

	int hole_count = count_holes();

	int number_of_times_can_fit = 0;

	for (rotation = 0;
		rotation < ROTATIONS_PER_PIECE * PIECE_BITS;
		rotation += PIECE_BITS)
		{
		for (col = 0; col < COLS + 1 - *(piece + 15 + rotation); ++col)
			{
			for (i = col; i < COLSROWS; i += COLS)
				{
				if (collide_piece(piece + rotation, i))
					break;
				}

			save_field(depth);
			draw_piece(piece + rotation, i - COLS);

			if (count_holes() == hole_count)
				++number_of_times_can_fit;
			//moves[depth][move_counter[depth]].value = evaluate();
			// count holes here, compare to before

			restore_field(depth);
			}
		}
	return number_of_times_can_fit;
	}

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
//	printf("Holes: %d\n", count_holes());
//	for (i = 0; i < 7; ++i)
//		printf("can_fit_piece(%d,1) - %c: %d\n", i, chars[i+1], can_fit_piece(i, 1));

/*	int row_count[ROWS];
	for (i = 0; i < ROWS; ++i)
		row_count[i] = 0;

	c = 0;
	for (i = 0; i < COLS; ++i)
		{
		printf("%2d ", column_height[i]);
		c = c + i;
		}
	printf("\nTotal = ");
*/
	}

/* other helpers */
void hmm()
	{
#ifdef INTERACTIVE_PAUSES
	printf("Pause...");
	getc(stdin);
	printf("\n");
#else
	system("sleep 0.05");
	return;
#endif
	}

void new_game()
	{
//	srand(time());
	int i;
	pieces_dropped =
	lines_cleared = 0;
	for (i = 0; i < MEMORY_SIZE; ++i)
#ifdef PIECE_OVERRIDE
		memory[i] = PIECE_OVERRIDE;
#else
		memory[i] = rand() % 7;
#endif
	for (i = 0; i < COLSROWS; ++i)
		field[i] = 0;
	}

void print_moves(int depth)
	{
	int i;
	for (i = 0; i < move_counter[depth]; ++i)
		{
		printf("move #%d at depth %d from col %d value %d\n", i, depth
			, moves[depth][i].i
			, moves[depth][i].value);
		}
	}

int move_sort(const void * a, const void * b)
	{
	return ((MOVE*)a)->value < ((MOVE*)b)->value;
	}
