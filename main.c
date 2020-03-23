/*
 * Tic Tac Toe
 * 
 * Copyright 2020 Reuben Scheck <rzach@outlook.com>
 * Github: <https://github.com/reutiteuti>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of version 3 the GNU General Public License as
 * published by the Free Software Foundation;
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */
 
#include <stdio.h>

typedef int Board[3][3]; /* A 3x3 board */

typedef enum {			/* The actual integer values of each player. */
	PLAYER_ONE = -1,	/* This makes it easier to calculate a win	 */
	PLAYER_TWO = 1		/* than just checking if a space is X or O.	 */
} Player;

/* You don't really need Row or Col; it just looks nice */

typedef enum { ROW_ONE, ROW_TWO, ROW_THREE } Row;

typedef enum { COL_ONE, COL_TWO, COL_THREE } Col;

void printBoard(Board board) {
	printf("  0 1 2\n");	/* Print the column labels */
	
	for (int i = 0; i < 3; i++) {
		printf("%d ", i);		/* Print the row labels */
		for (int j = 0; j < 3; j++) {
			if (board[i][j] == -1) {
				printf("X");		/* X is Player One */
			} else if (board[i][j] == 1) {
				printf("O"); 		/* O is Player Two */
			} else {
				printf("-");		/* Spaces that haven't been played in yet */
			}
			if (j < 2) printf(" ");
		}
		printf("\n");
	}
}

void move(Board board, Player player) {
	Row row;
	Col col;
	printf("Enter Row and Column: ");	/* Get row and column from stdin */
	scanf("%d", &row);
	scanf("%d", &col);
	if ((row < 0) || (row > 2) || (col < 0) || (col > 2)) {
		printf("Please enter numbers between 0 and 2, inclusive.\n");
		move(board, player);
	}
	if (board[row][col] != 0) {
		printf("This spot has already been taken!\n");
		move(board, player);
	} else {
		board[row][col] = player;
	}
}

/* The "avg___" functions take the average of the respective row,
   column, or diagonal. If it's not -1 or 1, set it to 0. */
	
int avgRow(Board board, Row row) {
	float w = ((float)board[row][0] + (float)board[row][1] + (float)board[row][2])/3;
	if ((w != -1) && (w != 1)) w = 0;
	return (int)w;
}

int avgCol(Board board, Col col) {
	float w = ((float)board[0][col] + (float)board[1][col] + (float)board[2][col])/3;
	if ((w != -1) && (w != 1)) w = 0;
	return (int)w;
}

int avgDiagTL(Board board) {	/* Top left diagonal */
	float w = ((float)board[0][0] + (float)board[1][1] + (float)board[2][2])/3;
	if ((w != -1) && (w != 1)) w = 0;
	return (int)w;
}

int avgDiagBL(Board board) {	/* Bottom left diagonal */
	float w = ((float)board[2][0] + (float)board[1][1] + (float)board[0][2])/3;
	if ((w != -1) && (w != 1)) w = 0;
	return (int)w;
}

int checkWin(Board board) {
	/* Check the average of each row, column, and diagonal */
	for (int i = 0; i < 3; i++) {
		if (avgRow(board, i) != 0) return avgRow(board, i);
		if (avgCol(board, i) != 0) return avgCol(board, i);
	}
	if (avgDiagTL(board) != 0) return avgDiagTL(board);
	if (avgDiagBL(board) != 0) return avgDiagBL(board);
	return 0;
}

int gameLoop(Board board, char name1[], char name2[]) {
	for (int player = -1; player < 10; player *= -1) {
		printBoard(board);
		if (player == -1) {
			printf("%s's turn!\n", name1);
		} else {
			printf("%s's turn!\n", name2);
		}
		move(board, player);
		int win = checkWin(board);
		if (win == -1) {
			printf("%s won!\n", name1);
			return 0;
		} else if (win == 1) {
			printf("%s won!\n", name2);
			return 0;
		} else {
			continue;
		}
	}
	printf("It's a draw!\n");
	return 0;
}

int main(int argc, char* argv[]) {
	if (argc != 3) {
		printf("Usage: ./ttt x_name o_name\n");
		return 1;
	} else {
		Board board = {0};
		gameLoop(board, argv[1], argv[2]);
		printBoard(board);
		return 0;
	}
}
