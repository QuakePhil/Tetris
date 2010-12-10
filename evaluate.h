/*

big value = better field

*/

int evaluate()
	{
	int i;

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

	for (i = 0; i < COLSROWS; ++i)
		{
		if (field[i] > 0)
			{
			// look for highest point (wait... shouldn't it be negative?)
			if (highest_point == 0)
				{
				if (i < COLSROWS/2)
					highest_point = 0;
				else
					highest_point = i;
				}

			// first hole we find will be highest, look no further
			if (hole_factor == 0 && i + COLS < COLSROWS && field[i + COLS] == 0)
				hole_factor = i - COLSROWS;
			}
		}

//printf("Hole factor: %d\nHighest point: %d\n", hole_factor, highest_point);
	return hole_factor + hole_factor + highest_point;

//	return highest_point;// hole_factor + hole_factor + highest_point;
	}

