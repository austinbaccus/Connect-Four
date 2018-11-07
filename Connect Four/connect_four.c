#include "connect_four.h"

int play(char board[][_BOARD_WIDTH])
{
	int game_state = 0; // -1 if the computer won, 0 if the game hasn't been won, and +1 if the player won
	int turn_number = 0;

	do
	{
		system("cls");
		print_board(board);
		turn_number++;
		start_new_turn(board, turn_number);
		game_state = is_game_won(board, turn_number);
	} while (game_state == 0);

	system("cls");
	print_board(board);

	return game_state;
}

void start_new_turn(char board[][_BOARD_WIDTH], int turn_number)
{
	int x; // the x-coordinate of where the token will be dropped on the board.
	x = get_token_drop_x_coordinate(board, turn_number);
	place_token_on_board(board, turn_number, x);
}

void place_token_on_board(char board[][_BOARD_WIDTH], int turn_number, int x_coordinate)
{
	for (int y_coordinate = _BOARD_HEIGHT - 1; y_coordinate >= 0; y_coordinate--)
	{
		if (board[y_coordinate][x_coordinate] == _EMPTY_BOARD_CELL_SYMBOL) // if this board location is not filled by a cell...
		{
			// ...then this board location must be the first unfilled index of this column, and
			// therefore this is the spot that the token we just dropped will occupy.
			board[y_coordinate][x_coordinate] = get_token_symbol(turn_number);
			return;
		}
	}
}

char get_token_symbol(int turn_number)
{
	return (turn_number % 2 == 1) ? _PLAYER_SYMBOL : _OPPONENT_SYMBOL;
}

/// Returns the x-coordinate of the token drop location by asking for user input (if it's their turn) or
/// by randomly generating a coordinate from a list of unfilled columns if it's the computer's turn.
int get_token_drop_x_coordinate(char board[][_BOARD_WIDTH], int turn_number)
{
	char c; 
	int x = 0;// the x-coordinate of where the token will be dropped on the board.
	if (turn_number % 2 == 1) // if the turn number is odd, it's the player's turn, and we need to ask for player input on where they want to put their token.
	{
		do
		{
			scanf(" %c", &c);
			x = (c - '0') - 1;
			is_x_coordinate_legal(board, x);
		} while (!is_x_coordinate_legal);
		return x;
	}
	else // else it's the computer's turn, and a random x-coordinate should be generated.
	{
		int num_of_unfilled_columns = 0; // the total number of columns in the board that are not full of tokens.
		int unfilled_column_indexes[_BOARD_WIDTH]; // an array of the indexes of those unfilled columns.
		for (int i = 0; i < _BOARD_WIDTH; i++)
		{
			if (board[0][i] == _EMPTY_BOARD_CELL_SYMBOL) // if the top of this column is empty...
			{
				unfilled_column_indexes[num_of_unfilled_columns] = i; // ...mark this column as unfilled
				num_of_unfilled_columns++;
			}
		}
		// The x-coordinate will be chosen at random from an array of unfilled column indexes on the game board. 
		// This way, the x-coordinate will never target a column that is already completey filled with tokens.
		x = unfilled_column_indexes[rand() % num_of_unfilled_columns]; 
	}
}

/// Returns true if the spot where the token is being dropped is a legal column to place the token in. 
/// Returns false if the column is already full, or the x-coordinate is not inside the board.
bool is_x_coordinate_legal(char board[][_BOARD_WIDTH], int x)
{
	if (0 > x || x > _BOARD_WIDTH) // if the x-coordinate is outside the bounds of the board (such as 'x = -3', or 'x = 12' on a board with only 10 columnds), return false.
	{
		return false;
	}
	return (board[0][x] != _EMPTY_BOARD_CELL_SYMBOL); // If the column of the token drop is already full of tokens, return false. Else, return true.
}

/// Returns -1 if the computer beat the player, 0 if the game hasn't been won yet, +1 if the player beat the computer, 
/// and -2 if it's a tie.
int is_game_won(char board[][_BOARD_WIDTH], int turn_number)
{
	if (turn_number == _BOARD_HEIGHT * _BOARD_WIDTH) // if the entire board has been filled up and there are no more unfilled spots to place tokens in...
	{
		return -2; // return a game state value of "tie" between the player and the computer
	}
	
	// check for diagonal 4-in-a-row
	for (int y = 0; y < _BOARD_HEIGHT - 3; y++)
	{
		for (int x = 0; x < _BOARD_WIDTH - 3; x++)
		{
			// check diagonal, top-left to bottom-right
			if (board[y][x] != _EMPTY_BOARD_CELL_SYMBOL &&
				board[y][x] == board[y + 1][x + 1] &&
				board[y][x] == board[y + 2][x + 2] &&
				board[y][x] == board[y + 3][x + 3])
			{
				return (board[y][x] == _PLAYER_SYMBOL) ? 1 : -1;
			}
			// check diagonal, bottom-left to top-right
			if (board[y + 3][x] != _EMPTY_BOARD_CELL_SYMBOL &&
				board[y + 3][x] == board[y + 2][x + 1] &&
				board[y + 3][x] == board[y + 1][x + 2] &&
				board[y + 3][x] == board[y + 0][x + 3])
			{
				return (board[y + 3][x] == _PLAYER_SYMBOL) ? 1 : -1;
			}
		}
	}

	// check for horizontal 4-in-a-row
	for (int y = 0; y < _BOARD_HEIGHT; y++)
	{
		for (int x = 0; x - _BOARD_WIDTH - 3; x++)
		{
			if (board[y][x] != _EMPTY_BOARD_CELL_SYMBOL &&
				board[y][x] == board[y][x + 1] &&
				board[y][x] == board[y][x + 2] &&
				board[y][x] == board[y][x + 3])
			{
				return (board[y][x] == _PLAYER_SYMBOL) ? 1 : -1;
			}
		}
	}

	// check for vertical 4-in-a-row
	for (int y = 0; y < _BOARD_HEIGHT - 3; y++)
	{
		for (int x = 0; x < _BOARD_WIDTH; x++)
		{
			if (board[y][x] != _EMPTY_BOARD_CELL_SYMBOL &&
				board[y][x] == board[y + 1][x] &&
				board[y][x] == board[y + 2][x] &&
				board[y][x] == board[y + 3][x])
			{
				return (board[y][x] == _PLAYER_SYMBOL) ? 1 : -1;
			}
		}
	}

	return 0; // the game has not been won by anyone yet, and there are still spaces to place more tokens in.
}

void print_board(char board[][_BOARD_WIDTH])
{
	for (int i = 0; i < _BOARD_HEIGHT; i++)
	{
		printf("\n\t|");
		for (int j = 0; j < _BOARD_WIDTH; j++)
		{
			if (board[i][j] == _EMPTY_BOARD_CELL_SYMBOL) printf(" |");
			else (board[i][j] == _PLAYER_SYMBOL) ? printf(ANSI_COLOR_RED "%c" ANSI_COLOR_RESET "|", _PLAYER_SYMBOL) : printf("%c|", _OPPONENT_SYMBOL);
		}
	}
	printf("\n\t");
	for (int i = 1; i <= _BOARD_WIDTH; i++)
	{
		printf("%2d", i);
	}
	printf("\n\n\t");
}