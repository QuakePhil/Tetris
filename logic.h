/*
logic to:
* clear lines
* collide and draw pieces against the field
*/

int clear_lines()
	{
	int i = COLSROWS;

	int this_row_blocks = 0;
	int shift_field = 0;
	int lines_cleared = 0;

	while (--i > -1)
		{
		if (i % COLS == COLS - 1)
			{
			if (this_row_blocks == COLS) // found a clear row, shift field down some more
				{
//				printf("shift_field = %d + %d\n", shift_field, COLS);
//				printf("i = %d + %d\n", i, COLS);
				shift_field += COLS;
				i += COLS;
				++lines_cleared;
				}
//			printf(" (%d)\n", this_row_blocks);
			this_row_blocks = 0;
			}
		//printf("%c", chars[field[i]]);
//		printf("%3d=%3d ", i, i - shift_field);
		if (i - shift_field < 0)
			field[i] = 0;
		else
			field[i] = field[i - shift_field];

		if (field[i])
			++this_row_blocks;
		}
//	printf("\n");
	return lines_cleared;
	}

int collide_piece(int *piece, int row)
	{
	int i;
	int subrow = 0;
	for (i = 0; i < PIECE_BITS - 1; ++i)
		{
		if (*(piece + i) && (i + row + subrow > COLSROWS-1 || field[i + row + subrow]))
			return 1;
		if (i % 4 == 3) subrow += (COLS - 4);
		}
	return 0;
	}

void draw_piece(int *piece, int row)
	{
	int i;
	int subrow = 0;
	for (i = 0; i < PIECE_BITS - 1; ++i)
		{
		if (*(piece + i))
			field[i + row + subrow] = *(piece+i); // fixme: no bounds checking
		if (i % 4 == 3) subrow += (COLS - 4);
		}

	clear_lines();
	}

