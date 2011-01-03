#define TEST

int test()
	{
	int i;

	for (i = 132; i < 142; ++i)
		{
		field[i] = 1;
		}
	field[44] = 2;

	memory[0] = 0;
	memory[1] = 0;

	display();

	return 1;
	}
