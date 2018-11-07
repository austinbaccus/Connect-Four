// Austin Baccus
// Washington State University, CPTS_121, Prof. Andrew O'Fallon
// 11/06/2018
// Bonus Assignment - Connect Four

#define _CRT_SECURE_NO_WARNINGS


#include <stdio.h>
#include <stdbool.h>
#include <Windows.h>
#include "game_constants.h"

bool play_again(void);
void print_game_over_message(int game_result);
void print_welcome_message(void);
void print_goodbye_message(void);
void erase_board(char board[][_BOARD_WIDTH]);

int main(void)
{
	srand((unsigned int)time(NULL));
	print_welcome_message(); // print the welcome message once at the start of the program.

	char board[_BOARD_HEIGHT][_BOARD_WIDTH]; // creating the game board.

	do // play the game...
	{
		erase_board(board); // erasing the board to clear all board cell values from the previous game.
		int game_result = play(board); // start the game.
		print_game_over_message(game_result); // print the results of the game to the screen.
	} while (play_again()); // ...and play again, if the user wants to.

	print_goodbye_message(); // Say goodbye to the player, and exit the program.
	return 0;
}
bool play_again(void)
{
	printf("\n\tWould you like to play again? Enter 'y' if yes, 'n' if no.\n\t");
	char user_input;
	scanf(" %c", &user_input);
	if (user_input == 'y')
	{
		return true;
	}
	return false;
}
void print_game_over_message(int game_result)
{
	switch (game_result)
	{
	case (-2):
		printf("\n\n\tTie game!");
		break;
	case (-1):
		printf("\n\n\tYou lost! :(");
		break;
	case (1):
		printf("\n\n\tYou won! :)");
		break;
	default:
		break;
	}
}
void print_welcome_message(void)
{
	printf("\n\tWelcome to Connect 4!\n");
	printf("\n\tYou will be playing against the computer in this game.");
	printf("\n\tYour pieces are marked by X, and your opponent's tokens are marked by O.");
	printf("\n\n\tPress 'enter' to continue ");
	getchar();
}
void print_goodbye_message(void)
{
	printf("\n\tGoodbye!\n");
	Sleep(2000);
}
void erase_board(char board[][_BOARD_WIDTH])
{
	for (int i = 0; i < _BOARD_HEIGHT; i++)
	{
		for (int j = 0; j < _BOARD_WIDTH; j++)
		{
			board[i][j] = _EMPTY_BOARD_CELL_SYMBOL;
		}
	}
}