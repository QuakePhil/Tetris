void think(int depth)
	{
	int piece_id, piece_memory_place;

	piece_id = memory[memory_place];
	piece_memory_place = memory_place;
#ifdef PIECE_OVERRIDE
	memory[memory_place++] = PIECE_OVERRIDE;
#else
	memory[memory_place++] = rand() % 7;
#endif
	if (memory_place >= MEMORY_SIZE)
		memory_place = 0; // Is modulus/bitand faster? At this point, do I care?

	generate_moves(piece_id, piece_memory_place, depth);
//	qsort(moves[depth], move_counter[depth], sizeof(MOVE), move_sort);

//	print_moves(depth);

	int i = 0;
#ifdef DRAW_PIECE_DROPPING
	for (i = 0; i < COLSROWS; i+=COLS)
#endif
		{
#ifdef DRAW_PIECE_DROPPING
		if (collide_piece(moves[depth][0].piece, moves[depth][0].i % COLS + i))
			break;
#endif
		save_field(depth);
		draw_piece(moves[depth][0].piece, moves[depth][0].i % COLS + i);
		display();
		hmm();
		restore_field(depth);
		}

	lines_cleared += draw_piece(moves[depth][0].piece, moves[depth][0].i);
	++pieces_dropped;
	}
