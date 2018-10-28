// 8-puzzle
// Copyright (C) 2018 Yurii Khomiak 
// Yurii Khomiak licenses this file to you under the MIT license. 
// See the LICENSE file in the project root for more information.

#ifndef EIGHT_PUZZLE_SOLVER_
#define EIGHT_PUZZLE_SOLVER_

#include "game_board.h"

GameBoard breadth_first_search(const GameBoard &initial, const GameBoard &target);
GameBoard depth_first_search(const GameBoard &initial, const GameBoard &target);

#endif // EIGHT_PUZZLE_SOLVER_
