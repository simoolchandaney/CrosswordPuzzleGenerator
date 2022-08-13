# Crossword Puzzle Generator
Crossword Anagram

Program:
The program, given a list of words, will create a crossword anagram puzzle, with both the board and the anagram clues, that can be played on paper and pencil. The program also provides a solution to the crossword puzzle.

The resulting crossword will be a board where most of the cells are filled in. The blank spaces on the board indicate places where the player must fill in a complete word. Where the spaces intersect, the words must share a common letter. A clue for each word is given by giving an anagram, which is simply the word with all of its letters shuffled. You may assume that the user will only enter single words. The output's format should follow the format shown in the example outputs provided below.

Algorithm behind the crossword:
1. The program starts by reading a list of up to 20 words of up to 15 letters each. It stop when a period "." is read instead of a word, or if 20 words have been provided, whichever comes first. In normal interactive mode, the above is done by entering the words from the keyboard; if the words are in a text file, that file's name can be passed at the command line.
2. A 15-by-15 board is created and is initially empty. The longest word inputted is placed it horizontally centered in the middle of the board.
3. For each of the remaining words in descending order of length, they are placed on the board in a way that intersects with exactly one identical letter already on the board. All letters of a word must be separated from other words by at least one blank space, except of course where it intersects with another word.
4. If it is not possible to place a given word according to the above rules, it is skipped (with an appropriate message) and all the placeable words are placed. In the end there will be a list of words that were not placed. 
5. Display the solution to the puzzle, with all the words that have been placed.
6. Display the unsolved puzzle and generate the anagram clues.

The program also handles the following conditions:
- Words may only contain the letters A-Z, and must consist of at least two letters. Any word that contains a non-letter is ignored, with a proper brief message. Same for single-letter words.
- Both upper and lower cases are accepted as input, but everything is converted to upper case when displayed in the generated puzzle.
- Any problem discovered (incorrect file name, too many arguments, etc) is handled by producing an appropriate error message.

Usage: The program is set up to handle 3 modes:
   1) interactive for the words' entries, with standard input and output
   2) command line input from a file containing the words, with standard output
   3) command line input from a file, and command line output to another file.
The mode will be determined by the existence, and number, of command line arguments after the executable.

In other words, the above modes are reflected in the following usage examples:
          1)  crossword
          2)  crossword mywords.txt
          3)  crossword mywords.txt myoutput.txt
If the user enters too many arguments, the program displays an appropriate error message and exit.

Output content: in summary, the output provides the following three components:
   i) a solution, where the placeable words are placed, and all remaining cells show a "." (period)
   ii) the puzzle, with spaces for where the words will go, and a "#" (hashtag) in all remaining cells
   iii) the clues, which consists of 3 columns: the coordinates for a word's start; the direction (Across or Down); and the clue, which is a scrambled anagram of the word

