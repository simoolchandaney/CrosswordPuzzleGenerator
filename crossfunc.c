// SIMRAN MOOLCHANDANEY
// SECTION 01
// OCTOBER 14
// crossfunc.c
// function definitions

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "crossfunc.h"

extern const char space;
extern const char hash;
extern const char dot;
extern const int middle;

void create_board(char board[][SIZE], int size) {
	int i, j;
	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			board[i][j] = dot;
		}
	}
} // intializes the board to all hashtags

void print_board(char board[][SIZE], int size) {
	int i, j, k;
	for (i = 0; i < (size+2); i++) {
		printf("-");
	}
	printf("\n");
	for (j = 0; j < size; j++) {
		printf("|");
		for (k = 0; k < size; k++) {
			printf("%c", board[j][k]);
		}
		printf("|");
		printf("\n");
	}
	for (i = 0; i < (size+2); i++) {
		printf("-");
	}
	printf("\n");
}

void sortStrings(char words[][100], int n) { // sorts from longest to shortest word
	char temp[100];
	int i, j;
	for (j = 0; j < n-1; j++) {
		for (i = j+1; i < n; i++) {
			if (strlen(words[j]) < strlen(words[i])) {
				strcpy(temp, words[j]);
				strcpy(words[j], words[i]);
				strcpy(words[i], temp);
				}
		}
	}
}

void upper_words(char words[][100], int n, int size) {
	// n is the number of words (i.e. the number of rows)
	int i, j; 
	for (j = 0; j < n; j++) {
		for (i = 0; i < size; i++) {
			words[j][i] = toupper(words[j][i]);
		}
	}
} // transform all words to upper case

void create_words2(char words[][100], char words2[][100],  int n, int size) {
	int i, j;
	for (j = 0; j < n; j++) {
		for (i = 0; i < size; i++) {
			words2[j][i] = words[j][i];
		}
	}
}

void print_words(char words[][100], int total) {
	int i;
	for (i = 0; i < total; i++) {
		printf("%s\n", words[i]);
	}
}

void place_word1(char board[][SIZE], char words[][100], Clues clues[20], int size) {
	int maxL = strlen(words[0]);
	strcpy(clues[0].position, "across");
	strcpy(clues[0].name, words[0]);
	clues[0].y = middle;
	if ((maxL % 2) != 0) { // word has odd length
		int i = middle;
		int j;
		for (j = ((maxL-1)/2); j >= 0; j--) {
			board[middle][i] = words[0][j];
			i--;
		}
		clues[0].x = (i+1);
		int k = middle + 1;
		for (j = (((maxL-1)/2)+1); j < maxL; j++) {
			board[middle][k] = words[0][j];
			k++;
		}
	}
	else { // word has even length 
		int i = middle - 1;
		int j;
		for (j = ((maxL/2)-1); j >= 0; j--) { 
			board[middle][i] = words[0][j];
			i--;  // places longest word in the middle, now need to center it 
		}
		clues[0].x = (i+1);
		int k = middle;
		for (j = (maxL/2); j < maxL; j++) {
			board[middle][k] = words[0][j];
			k++;
		}
	}
}

void fill_dots (char board[][SIZE], int size) {	 
	int m, n;
	for (m = 0; m < size; m++) {
		for (n = 0; n < size; n++) {
			if (isalpha(board[n][m]) == 0) {
			board[n][m] = dot;
			}
		}
	}
}

void create_crossword(char board[][SIZE], int size) {
	int m, n;
	for (m = 0; m < size; m++) {
		for (n = 0; n < size; n++) {
			if (isalpha(board[n][m])) {
				board[n][m] = space;
			}
			else {
				board[n][m] = hash;
			}
		}
	}
}

void swap(char *a, char *b) {
	char temp = *a;
	*a = *b;
	*b = temp;
}

// function to shuffle letters in words and store in shuffled array
void shuffle_words(char words2[][100], Clues clues[], int n, int size) {
	int i, j;
	for (i = 0; i < n; i++) {
		for (j = strlen(words2[i])-1; j > 0; j--) {
			int k = rand() % strlen(words2[i]);
			swap(&words2[i][j], &words2[i][k]);
		}
		strcpy(clues[i].shuffle, words2[i]);
	}
}

void print_clues(Clues clues[], int n) {
	int i;
	for (i = 0; i < n; i++) {
		if (strcmp(clues[i].position, "NULL") != 0) {
			printf("  %s\n", clues[i].shuffle);
			printf("    %d, %d\n", clues[i].x, clues[i].y);
			printf("    %s\n", clues[i].position);
			printf("\n");
		}
	}
}

void print_board_file(char board[][SIZE], int size, FILE *ofp) {
	int i, j, k;
	for (i = 0; i < (size+2); i++) {
		fprintf(ofp, "-");
	}
	fprintf(ofp, "\n");
	for (j = 0; j < size; j++) {
		fprintf(ofp, "|");
		for (k = 0; k < size; k++) {
			fprintf(ofp, "%c", board[j][k]);
		}
		fprintf(ofp, "|");
		fprintf(ofp, "\n");
	}
	for (i = 0; i < (size+2); i++) {
		fprintf(ofp, "-");
	}
	fprintf(ofp, "\n");
}


void print_clues_file(Clues clues[], int n, FILE *ofp) {
	int i;
	for (i = 0; i < n; i++) {
		if (strcmp(clues[i].position, "NULL") != 0) {
			fprintf(ofp, "  %s\n", clues[i].shuffle);
			fprintf(ofp, "    %d, %d\n", clues[i].x, clues[i].y);
			fprintf(ofp, "    %s\n", clues[i].position);
			fprintf(ofp, "\n");
		}
	}
}

void place_down(int x, int j, int n, char board[][SIZE], char words[][100], Clues clues[]) {
	clues[0].y = middle;
	int i;
	int m = clues[j].y - x;
	for (i = 0; i < strlen(words[n]); i++) {
		board[m][clues[n].x] = words[n][i];
		m++;
	}
	clues[n].y = clues[j].y - x;
	strcpy(clues[n].position, "down");
}

void place_across(char board[][SIZE], Clues clues[], char words[][100], int n) {
	int i;
	int m = strlen(words[n]);
	for (i = 0; i < m; i++) {
		board[clues[n].y][(clues[n].x)+i] = words[n][i];
	}
}

// check if enough space to place
int checkD (char board[][SIZE], char words[][100], int n, Clues clues[]) {
	int len = strlen(words[n]);
	int i;
	for (i = 0; i < len; i++) {
		if (((board[(clues[n].y)+i][clues[n].x]) != dot) && ((board[(clues[n].y) + i][(clues[n].x)] != words[n][i]))){
			return 0;
		}
	}
	return 1;
}

int checkA (char board[][SIZE], char words[][100], int n, Clues clues[]) {
	int len = strlen(words[n]);
	int i;
	for (i = 0; i < len; i++) {
		if (((board[clues[n].y][(clues[n].x)+i]) != dot) && ((board[clues[n].y][(clues[n].x) + i]) != words[n][i])) {
			return 0;
		}
	}
	return 1;
}

int check_spaceD (char board[][SIZE], char words[][100], int n, int j, int x, int k, Clues clues[]) {
	int i;
	int len = strlen(words[n]);
		if (board[(clues[n].y) - 1][clues[n].x] != dot) { // checks spot before first char of the word I am placing
			return 0;
		}
		if (board[(clues[n].y) + len][clues[n].x] != dot) { // checks spot after last char of the word I m placing
			return 0;
		}
		for (i = 0; i < len; i++) { 
			if (board[(clues[n].y) + i][clues[n].x] != board[clues[j].y][(clues[j].x) + k]) { // not intersection
				if ((board[(clues[n].y) + i][(clues[n].x) - 1] != dot) || (board[(clues[n].y) + i][(clues[n].x) + 1] != dot)) { 
					return 0;
				}
			}
		}
		return 1;
}

int check_spaceA (char board[][SIZE], char words[][100], int n, int j, int x, int k, Clues clues[]) {
	int i;
	int len = strlen(words[n]);
		if (board[clues[n].y][(clues[n].x) - 1] != dot) { // checks spot before first char of the word I am placing
			return 0;
		}
		if (board[clues[n].y][(clues[n].x) + len] != dot) { // checks spot after last char of the word I am placing
			return 0;
		}
		for (i = 0; i < len; i++) { 
			if (board[clues[n].y][(clues[n].x) + i] != board[(clues[j].y) + k][clues[j].x]) { // not intersection
			if ((board[(clues[n].y) - 1][(clues[n].x) + i] != dot) || (board[(clues[n].y) + 1][(clues[n].x) + i] != dot)) { 
					return 0;
				}
			}
		}
		return 1;
}

int check_bounds(int x, int y) {
	if ((x >= 0) && (x < SIZE) && (y >= 0) && (y < SIZE)) {
		return 1;
	}
}

void place_words(int n, char board [][SIZE], char words[][100], Clues clues[], int size) {
	// n: word i am placing (i.e. n = 1 is the second word i am placing)
	// j: word n matched wit (i.e j = 0, means that n matched with the first/longest word)
	// k: index within j that n matched with (i.e if k = 2, n matched with j's third character)
	// x: index within n that matched with j (i.e if x = 1, the intersection occured at n's second character)
	int j, k, x;
	clues[0].y = middle;
	strcpy(clues[n].name, words[n]);
	for (j = 0; j < n; j++) { 
		for (k = 0; k < strlen(words[j]); k++) { 
			for (x = 0; x < strlen(words[n]); x++) { 
				if (words[j][k] == words[n][x]) {  
					if (((strcmp(clues[j].position, "across")) == 0)) { 
						clues[n].x = clues[j].x + k;
						clues[n].y = clues[j].y - x;
						if ((checkD(board, words, n, clues) == 1) && (check_bounds(clues[n].x, clues[n].y) == 1) && (check_bounds(clues[n].x, (clues[n].y)+strlen(words[n])) == 1)  && (check_spaceD(board, words, n, j, x, k, clues) == 1)) {
							place_down(x, j, n, board, words, clues);
							strcpy(clues[n].position, "down");
							return;
						}
						else {
							strcpy(clues[n].position, "NULL");
						}
					}
					else if (((strcmp(clues[j].position, "down")) == 0)) { 
						if (x == 0) {
							clues[n].x = clues[j].x;
						}
						if (x != 0) {
							clues[n].x = clues[j].x - x;
						}
						clues[n].y = clues[j].y + k;
						if((checkA(board, words, n, clues) == 1) && (check_bounds(clues[n].x, clues[n].y) == 1)  && (check_bounds(((clues[n].x)+strlen(words[n])), clues[n].y) == 1) && (check_spaceA(board, words, n, j, x, k, clues) == 1)) { 
							place_across(board, clues, words, n);
							strcpy(clues[n].position, "across");
							return;
						}
						else {
							strcpy(clues[n].position, "NULL");
						}
					}
				}
			}
		}
	}
	strcpy(clues[n].position, "NULL");
}

void print_unplaced (Clues clues[], int n) {
	int i;
	for (i = 0; i < n; i++) {
		if (strcmp(clues[i].position, "NULL") == 0) {
			printf("word %s could not be placed after first iteration\n", clues[i].name);
		}
	}
}

void print_unplaced_file(Clues clues[], int n, FILE *ofp) {
	int i;
	for (i = 0; i < n; i++) {
		if (strcmp(clues[i].position, "NULL") == 0) {
			fprintf(ofp, "word %s could not be placed after first iteration\n", clues[i].name);
		}
	}
}

