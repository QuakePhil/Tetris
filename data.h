// #define DRAW_PIECE_DROPPING

// #define PIECE_OVERRIDE 5

#define INTERACTIVE_PAUSES

#define COLS 15
#define ROWS 20
#define COLSROWS 300

// Scoring

int pieces_dropped;
int lines_cleared;
int column_height[COLS];

// Future piece memory

#define MEMORY_SIZE 2 // segfaults with 3 so something is broken :(
// (although valgrind doesn't find anything...?)
int memory[MEMORY_SIZE] = {0, 0};
int memory_place = 0;

// Moves

typedef struct
	{
	int* piece;
	int i;
	int value;
	}
MOVE;
MOVE moves[8][64];
int move_counter[8];

// Piece bits
// T L J I O S Z

int field[COLSROWS];

int chars[8] = {'.', 'T', 'L', 'J', 'I', 'O', 'S', 'Z'};

#define ROTATIONS_PER_PIECE 4
#define PIECE_BITS 16
#define PIECES 7*ROTATIONS_PER_PIECE*PIECE_BITS

// on second thought, there is probably no good reason
// not to do this as a multi-dimensional array, but oh
// well, too late now :p
int pieces[PIECES] = {
// T
	1,1,1,0,
	0,1,0,0,
	0,0,0,0,
	0,0,0,3,

	1,0,0,0,
	1,1,0,0,
	1,0,0,0,
	0,0,0,2,

	0,1,0,0,
	1,1,1,0,
	0,0,0,0,
	0,0,0,3,

	0,1,0,0,
	1,1,0,0,
	0,1,0,0,
	0,0,0,2,
// L
	2,0,0,0,
	2,0,0,0,
	2,2,0,0,
	0,0,0,2,

	0,0,2,0,
	2,2,2,0,
	0,0,0,0,
	0,0,0,3,

	2,2,0,0,
	0,2,0,0,
	0,2,0,0,
	0,0,0,2,

	2,2,2,0,
	2,0,0,0,
	0,0,0,0,
	0,0,0,3,
// J
	0,3,0,0,
	0,3,0,0,
	3,3,0,0,
	0,0,0,2,

	3,0,0,0,
	3,3,3,0,
	0,0,0,0,
	0,0,0,3,

	3,3,0,0,
	3,0,0,0,
	3,0,0,0,
	0,0,0,2,

	3,3,3,0,
	0,0,3,0,
	0,0,0,0,
	0,0,0,3,

// I
	4,0,0,0,
	4,0,0,0,
	4,0,0,0,
	4,0,0,1,

	4,4,4,4,
	0,0,0,0,
	0,0,0,0,
	0,0,0,4,

	4,0,0,0,	4,0,0,0,	4,0,0,0,	4,0,0,1,

	4,4,4,4,	0,0,0,0,	0,0,0,0,	0,0,0,4,
// O
	5,5,0,0,
	5,5,0,0,
	0,0,0,0,
	0,0,0,2,

	5,5,0,0,	5,5,0,0,	0,0,0,0,	0,0,0,2,

	5,5,0,0,	5,5,0,0,	0,0,0,0,	0,0,0,2,

	5,5,0,0,	5,5,0,0,	0,0,0,0,	0,0,0,2,


// S
	0,6,6,0,
	6,6,0,0,
	0,0,0,0,
	0,0,0,3,

	6,0,0,0,
	6,6,0,0,
	0,6,0,0,
	0,0,0,2,

	0,6,6,0,	6,6,0,0,	0,0,0,0,	0,0,0,3,

	6,0,0,0,	6,6,0,0,	0,6,0,0,	0,0,0,2,

// Z
	7,7,0,0,
	0,7,7,0,
	0,0,0,0,
	0,0,0,3,

	0,7,0,0,
	7,7,0,0,
	7,0,0,0,
	0,0,0,2,

	7,7,0,0,	0,7,7,0,	0,0,0,0,	0,0,0,3,

	0,7,0,0,	7,7,0,0,	7,0,0,0,	0,0,0,2,

};
