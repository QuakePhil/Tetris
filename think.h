void think(int depth)
	{
	int piece_id;

	do
		{
		piece_id = rand() % 7;
		}
	while (piece_id == last_piece);
	last_piece = piece_id;

	printf("Dropping piece: %d\n", piece_id);
	generate_moves(piece_id, depth);
	qsort(moves[depth], move_counter[depth], sizeof(MOVE), move_sort);

/*	save_field();
	draw_piece(moves[depth][0].piece, moves[depth][0].i % COLS);
	display();
	hmm();
	restore_field();
*/

	draw_piece(moves[depth][0].piece, moves[depth][0].i);
	}
