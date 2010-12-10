typedef struct
	{
	int* piece;
	int i;
	int value;
	}
MOVE;
MOVE moves[8][64];
int move_counter[8];

void generate_moves(int piece_id, int depth)
	{
	int * piece = &pieces[piece_id * ROTATIONS_PER_PIECE * PIECE_BITS];

	int rotation;

	int i;
	int col;

	move_counter[depth] = 0;

	for (rotation = 0;
		rotation < ROTATIONS_PER_PIECE * PIECE_BITS;
		rotation += PIECE_BITS)
		{
		for (col = 0; col < COLS + 1 - *(piece + 15 + rotation); ++col)
			{
			for (i = col; i < COLSROWS; i += COLS)
				{
/*save_field();
printf("dropping a piece....\n");
printf("dropping a piece....\n");
draw_piece(piece + rotation, i);
display();
hmm();
restore_field();*/
				if (collide_piece(piece + rotation, i))
					break;
				}

			save_field();
			draw_piece(piece + rotation, i - COLS);

			moves[depth][move_counter[depth]].piece = piece + rotation;
			moves[depth][move_counter[depth]].i = i - COLS;
			moves[depth][move_counter[depth]].value = evaluate();
			move_counter[depth]++;

			restore_field();
			}
		}
	}

int move_sort(const void * a, const void * b)
	{
	return ((MOVE*)a)->value < ((MOVE*)b)->value;
	}

int last_piece = 0;
