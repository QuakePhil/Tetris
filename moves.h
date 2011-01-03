int generate_moves(int piece_id, int piece_memory_place, int depth)
	{
//printf("generate_moves(piece_memory_place = %d, depth = %d\n", piece_memory_place, depth);
//hmm();
	int* piece = &pieces[piece_id * ROTATIONS_PER_PIECE * PIECE_BITS];

	int rotation;

	int i;
	int col;

	int best_value_here;

	move_counter[depth] = 0;

	for (rotation = 0;
		rotation < ROTATIONS_PER_PIECE * PIECE_BITS;
		rotation += PIECE_BITS)
		{
		for (col = 0; col < COLS + 1 - *(piece + 15 + rotation); ++col)
			{
			for (i = col; i < COLSROWS; i += COLS)
				{
/*
save_field();
printf("dropping a piece....\n");
printf("dropping a piece....\n");
draw_piece(piece + rotation, i);
display();
hmm();
restore_field();*/
				if (collide_piece(piece + rotation, i))
					break;
				}

			save_field(depth);
			draw_piece(piece + rotation, i - COLS);

			moves[depth][move_counter[depth]].piece = piece + rotation;
			moves[depth][move_counter[depth]].i = i - COLS;
			if (depth == MEMORY_SIZE || 1)
				moves[depth][move_counter[depth]].value = evaluate();
			else
				moves[depth][move_counter[depth]].value = generate_moves(
					memory[(piece_memory_place+depth+1)%3]
					, piece_memory_place
					, depth + 1);
			move_counter[depth]++;
			restore_field(depth);
			}
		}

	qsort(moves[depth], move_counter[depth], sizeof(MOVE), move_sort);
	return moves[depth][0].value;
	}
