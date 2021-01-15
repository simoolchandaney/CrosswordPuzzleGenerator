// SIMRAN MOOLCHANDANEY
// SECTION 01
// OCTOBER 14
// crossword.c
// main program
// given a list of words, the program will create a crossword anagram puzzle

#include <stdio.h>
#include <string.h>
#include "crossfunc.h"

const char space = ' ';
const char hash = '#';
const char dot = '.';
const int middle = 7;

int main(int argc, char *argv[]) {

	char board[SIZE][SIZE];
	create_board(board, SIZE);
	Clues clues[20];
	char words[20][100];
	char words2[20][100];

	if (argc == 1) { // interactive mode, stops reading in words if we reach . or if we reach 20 words -- use while loop
		int i = 0;
		printf("Anagram Crossword Puzzle Generator\n");
		printf("----------------------------------\n");
		int d = 0;
		char temp[100];

		printf("Enter a list of words\n");
		printf("\n");

		while ((i <= 20) && (d != 1)) {
			scanf("%s", &temp);
			getchar();
			int valid = 1;
				if (strlen(temp) > 15) {
					printf("word entered is too long. enter another word: \n");
					valid = 0;
				}
				int j;
				if ((strlen(temp) == 1) && (temp[0] != dot)) {
					printf("word entered is too short, enter another word: \n");
					valid = 0;
				}
				for (j = 0; j < strlen(temp); j++) {
					if ((!isalpha(temp[j])) && (temp[0] != dot)) {
						printf("word inputted contains an invalid character, enter another word: \n");
						valid = 0;
						break;
					}
				}
				if (temp[0] == dot) {
					d = 1;
				}
				else if (valid) {
					strcpy(words[i], temp);
					i++;
				}
		}
		int total = i;
		sortStrings(words, total); // sorts from longest to shortest word
		upper_words(words, total, SIZE); // all words become upper case
		create_words2(words, words2, total, SIZE); // copies all words from words to words2
		print_words(words2, total); // prints all the words in uppercase
		printf("Solution:\n");
		int track = 1;
		while (track <= total) {
			switch (track) {
				case 1:
					place_word1(board, words, clues, SIZE);
					break;
				default:
					place_words((track-1), board, words, clues, SIZE);
			}
			track++;
		} 

		fill_dots(board, SIZE);
		print_board(board, SIZE);
		printf("\n");
	
		printf("Crossword puzzle:\n");
		create_crossword(board, SIZE);
		print_board(board, SIZE);
		printf("\n");

		shuffle_words(words2, clues, total, SIZE);
		printf("Clues:\n");
		printf("\n"); 
		print_clues(clues, total);
		print_unplaced(clues, total);
	}


	else if (argc == 2) { // non-interactive mode -- read in file
		int i = 0;
		printf("Anagram Crossword Puzzle Generator\n");
		printf("----------------------------------\n");
		int d = 0;
		char temp[100];

		FILE *fp = fopen(argv[1], "r"); // opens text file if it exists
		if (!fp) {
			printf("file %s not found\n", argv[1]);
			return 1;
		}

		while((i <= 20) && (d != 1)) {
			fscanf(fp, "%s", temp);
			int valid = 1;
			if (strlen(temp) > 15) {
				printf("%s was too long to place\n", temp);
				valid = 0;
			}
			int j;
			if ((strlen(temp) == 1) && (temp[0] != dot)) {
				printf("%s was too short to place\n", temp);
				valid = 0;
			}
			for (j = 0; j < strlen(temp); j++) {
				if ((!isalpha(temp[j])) && (temp[0] != dot)) {
					printf("%s had an invalid character and could not be placed\n", temp);
					valid = 0;
					break;
				}
			}
			if (temp[0] == dot) {
				d = 1;
			}
			else if (valid) {
				strcpy(words[i], temp);
				i++;
			}
			if (feof(fp)) break;
		}
		// fscanf in words -- reading in

		int total1 = i;

		sortStrings(words, total1);
		upper_words(words, total1, SIZE);
		create_words2(words, words2, total1, SIZE);

		printf("Solution:\n");
		int track1 = 1;
		while (track1 <= total1) {
			switch (track1) {
				case 1:
					place_word1(board, words, clues, SIZE);
					break;
				default:
					place_words((track1-1), board, words, clues, SIZE);
			}
			track1++;
		}
		fill_dots(board, SIZE);
		print_board(board, SIZE);
		printf("\n");
	
		printf("Crossword puzzle:\n");
		create_crossword(board, SIZE);
		print_board(board, SIZE);
		printf("\n");

		shuffle_words(words2, clues, total1, SIZE);
		printf("Clues:\n");
		printf("\n"); 
		print_clues(clues, total1);
		print_unplaced(clues, total1);
	}

	else if (argc == 3) {
		int i = 0;
		int d = 0;
		char temp[100];
		FILE *ifp = fopen(argv[1], "r"); // opens text file if it exists
		if (!ifp) {
			printf("file %s not found\n", argv[1]);
			return 1;
		}
		FILE *ofp;
		ofp = fopen(argv[2], "w");
		fprintf(ofp, "Anagram Crossword Puzzle Generator\n");
		fprintf(ofp, "----------------------------------\n");
		while((i <= 20) && (d != 1)) {
			fscanf(ifp, "%s", temp);
			int valid = 1;
			if (strlen(temp) > 15) {
				fprintf(ofp, "%s was too long to place\n", temp);
				valid = 0;
			}
			int j;
			if ((strlen(temp) == 1) && (temp[0] != dot)) {
				fprintf(ofp, "%s was too short to place\n", temp);
				valid = 0;
			}
			for (j = 0; j < strlen(temp); j++) {
				if ((!isalpha(temp[j])) && (temp[0] != dot)) {
					fprintf(ofp, "%s had an invalid character and could not be placed\n", temp);
					valid = 0;
					break;
				}
			}
			if (temp[0] == dot) {
				d = 1;
			}
			else if (valid) {
				strcpy(words[i], temp);
				i++;
			}
			if (feof(ifp)) break;
		}
		int total2 = i;

		sortStrings(words, total2);
		upper_words(words, total2, SIZE);
		create_words2(words, words2, total2, SIZE);

		fprintf(ofp, "Solution:\n");
		int track2 = 1;
		while (track2 <= total2) {
			switch (track2) {
				case 1:
					place_word1(board, words, clues, SIZE);
					break;
				default:
					place_words((track2-1), board, words, clues, SIZE);
			}
			track2++;
		}
		fill_dots(board, SIZE);
		print_board_file(board, SIZE, ofp);
		fprintf(ofp, "\n");

		fprintf(ofp, "Crossword puzzle:\n");
		create_crossword(board, SIZE);
		print_board_file(board, SIZE, ofp);
		fprintf(ofp, "\n");

		shuffle_words(words2, clues, total2, SIZE);
		fprintf(ofp, "Clues:\n");
		fprintf(ofp, "\n");
		print_clues_file(clues, total2, ofp);
		print_unplaced_file(clues, total2, ofp);
	
		// fprintf crosswords into new text file 
	}
	
	else {
		printf("you entered too many arguments\n");
	}
	return 0;
}

