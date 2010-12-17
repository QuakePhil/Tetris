void think(int depth)
	{
	int piece_id, piece_memory_place;

	piece_id = memory[memory_place];
	piece_memory_place = memory_place;
	memory[memory_place++] = rand() % 7;
	if (memory_place >= MEMORY_SIZE)
		memory_place = 0; // Is modulus/bitand faster? At this point, do I care?

	generate_moves(piece_id, piece_memory_place, depth);
//	qsort(moves[depth], move_counter[depth], sizeof(MOVE), move_sort);

//	print_moves(depth);

/*	save_field();
	draw_piece(moves[depth][0].piece, moves[depth][0].i % COLS);
	display();
	hmm();
	restore_field();
*/

	lines_cleared += draw_piece(moves[depth][0].piece, moves[depth][0].i);
	++pieces_dropped;
	}
