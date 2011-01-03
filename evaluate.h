/*

big value = better field

*/

int evaluate()
	{
	int i, j;

	/*
	hole factor shows you the highest hole.
	the bigger this number the better.
	if there are no holes, this value is 0
	*/
	int hole_factor = 0;

	/*
	highest point is just the first encountered block.
	the bigger this number the better
	*/
	int highest_point = 0;

	/*
	biggest difference is a measure of the biggest
	"jagged" edge.  initialized to 2 because I don't care
	about 2 vs 1 difference
	*/
	int biggest_difference = 2;

	/*
	total height for evaluation works sort of like average
	height but we don't really need to average it
	*/
	int total_height = 0;

	int pieces_can_fit =
		can_fit_piece(1, 1)
		+ can_fit_piece(2, 1)
		+ can_fit_piece(5, 1)
		+ can_fit_piece(6, 1);

	for (i = 0; i < COLSROWS; ++i)
		{
		if (i < COLS)
			column_height[i] = ROWS;

		if (field[i] > 0)
			{
			// look for highest point (wait... shouldn't it be negative?)
			if (column_height[i % COLS] == ROWS)
				column_height[i % COLS] = i/COLS;

			if (highest_point == 0)
				{
				if (i < COLSROWS/2)
					highest_point = 0;
				else
					highest_point = i/COLS;
				}

			// first hole we find will be highest, look no further
			if (hole_factor == 0 && i + COLS < COLSROWS && field[i + COLS] == 0)
				hole_factor = i - COLSROWS;
			}
		}

	for (i = 0; i < COLS; ++i)
		{
		total_height += column_height[i];
		if (column_height[i] < highest_point) highest_point = column_height[i];

		if (i == 0) continue; // there is no difference for the first column
		j = column_height[i] - column_height[i-1]; // this difference
		if (j < 0) j = -j; // absolute value
		if (j > biggest_difference) biggest_difference = j; // maximum difference
		}

	total_height = total_height / COLS;
//	printf("Highest point: %d\nBiggest difference: %d\n", highest_point, biggest_difference);

//printf("Hole factor: %d\nHighest point: %d\n", hole_factor, highest_point);
//	return hole_factor + hole_factor + highest_point;
	return pieces_can_fit + highest_point - biggest_difference + hole_factor; //+ hole_factor;

//	return highest_point;// hole_factor + hole_factor + highest_point;
	}

