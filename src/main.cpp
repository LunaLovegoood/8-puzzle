// Game of 8
// Copyright (C) 2018 Yurii Khomiak 
// Yurii Khomiak licenses this file to you under the MIT license. 
// See the LICENSE file in the project root for more information.

#include "game_board.h"

#include <iostream>
#include <list>
#include <array>
#include <algorithm>

const Direction directions[4] = { Direction::DOWN, Direction::LEFT, Direction::UP, Direction::RIGHT };


GameBoard breadth_first_search(const GameBoard &initial, const GameBoard &target);


int main()
{
    const std::array< std::array< char, 3 >, 3 > initial_field = { {
        {'1', '8', '2'},
        {'7', ' ', '3'},
        {'6', '5', '4'}
    } };
    const std::array< std::array< char, 3 >, 3 > target = { {
        {'1', '2', '3'},
        {'8', ' ', '4'},
        {'7', '6', '5'}
    } };

    breadth_first_search(initial_field, target).show_path();

    return 0;
}

GameBoard breadth_first_search(const GameBoard &initial, const GameBoard &target)
{
    std::list< GameBoard > conditions{ initial }; // storage of all added boards
    int previous_level_board = 1; // number of boards added on previous level
    int current_level_board = 0; // number of boards on current level

    GameBoard temp;
    char choice = 'y';

    for (int level = 1; ; level++, current_level_board = 0)
    {
        std::cout << "Level: " << level << "\n";

        auto level_begin = std::next(conditions.end(), -previous_level_board);

        for (int i = 0; i < previous_level_board; ++i, ++level_begin)
        {
            for (int j = 0; j < 4; ++j)
            {
                if (choice == 'y') {
                    std::cout << "Step-by-step/Automatic enter (y/n): ";
                    std::cin >> choice;
                }

                temp = (*level_begin).move(directions[j]);

                if (!temp.is_init()) // Check if moving in the given direction is possible
                {
                    continue;
                }
                else if (conditions.end() == std::find(conditions.begin(), conditions.end(), temp)) // Check for duplicates
                {
                    if (temp == target) // Check if result is reached
                    {
                        return temp;
                    }

                    if (choice == 'y')
                    {
                        std::cout << temp;
                    }
                    conditions.push_back(temp);
                    ++current_level_board;
                }
            }
        }

        std::cout << "Number of boards: " << current_level_board << "\n";
        previous_level_board = current_level_board;
    }
}
