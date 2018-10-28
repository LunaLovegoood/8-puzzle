// 8-puzzle
// Copyright (C) 2018 Yurii Khomiak 
// Yurii Khomiak licenses this file to you under the MIT license. 
// See the LICENSE file in the project root for more information.

#include "eight_puzzle_solver.h"

const auto initial_board = std::array< std::array< char, 3 >, 3 >{ {
    {'1', '8', '2'},
    {'7', ' ', '3'},
    {'6', '5', '4'}
} };
const auto target_board = std::array< std::array< char, 3 >, 3 >{ {
    {'1', '2', '3'},
    {'8', ' ', '4'},
    {'7', '6', '5'}
} };

int main()
{
    breadth_first_search(initial_board, target_board).show_path();

    depth_first_search(initial_board, target_board).show_path();

    system("pause");

    return 0;
}
