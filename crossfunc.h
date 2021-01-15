// SIMRAN MOOLCHANDANEY
// SECTION 01
// OCTOBER 14
// crossfunc.h
// function prototypes
#define SIZE 15
typedef struct {
	char name[15];
	int x;
	int y;
	char position[7]; // across or down
	char shuffle[15];
} Clues;

void create_board(char [][SIZE], int);
void upper_words(char [][100], int, int);
void print_board(char [][SIZE], int);
void sortStrings(char [][100], int);
void print_words(char [][100], int);
void place_word1(char [][SIZE], char [][100], Clues [],  int);
void fill_dots(char [][SIZE], int);
void create_crossword(char [][SIZE], int);
void swap(char *, char *);
void shuffle_words(char [][100], Clues [], int, int);
void print_clues(Clues [], int);
void print_board_file(char [][SIZE], int, FILE *);
void print_clues_file(Clues [], int, FILE *);
void place_words(int, char [][SIZE], char [][100], Clues [], int);
void place_down(int, int, int, char [][SIZE], char [][100], Clues []);
void place_across(char [][SIZE], Clues [], char [][100], int);
int checkD(char [][SIZE], char [][100], int, Clues []);
int checkA(char [][SIZE], char [][100], int, Clues []);
int check_bounds(int, int);
int check_spaceD(char [][SIZE], char [][100], int, int, int, int, Clues []);
int check_spaceA(char [][SIZE], char [][100], int, int, int, int, Clues []);
void print_unplaced(Clues [], int);
void print_unplaced_file(Clues [], int, FILE *);
