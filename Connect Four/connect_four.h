#pragma once

#include "game_constants.h"
#include <stdbool.h>
#include <stdlib.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_RESET   "\x1b[0m"

int play(char board[][_BOARD_WIDTH]);
void start_new_turn(char board[][_BOARD_WIDTH], int turn_number);
void place_token_on_board(char board[][_BOARD_WIDTH], int turn_number, int x_coordinate);
char get_token_symbol(int turn_number);
int get_token_drop_x_coordinate(char board[][_BOARD_WIDTH], int turn_number);
bool is_x_coordinate_legal(char board[][_BOARD_WIDTH], int x);
int is_game_won(char board[][_BOARD_WIDTH], int turn_number);
void print_board(char board[][_BOARD_WIDTH]);