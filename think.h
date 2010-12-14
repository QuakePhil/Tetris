void think(int depth)
	{
	int piece_id;

	piece_id = memory[memory_place];
	memory[memory_place++] = rand() % 7;
	if (memory_place >= MEMORY_SIZE)
		memory_place = 0; // Is modulus/bitand faster? At this point, do I care?

/*	do
		{
		piece_id = rand() % 7;
		}
	while (piece_id == last_piece);
	last_piece = piece_id;
*/

	generate_moves(piece_id, depth);
	qsort(moves[depth], move_counter[depth], sizeof(MOVE), move_sort);

/*	save_field();
	draw_piece(moves[depth][0].piece, moves[depth][0].i % COLS);
	display();
	hmm();
	restore_field();
*/

	lines_cleared += draw_piece(moves[depth][0].piece, moves[depth][0].i);
	++pieces_dropped;
	}
