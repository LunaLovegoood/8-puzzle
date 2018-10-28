// 8-puzzle
// Copyright (C) 2018 Yurii Khomiak 
// Yurii Khomiak licenses this file to you under the MIT license. 
// See the LICENSE file in the project root for more information.

#include "eight_puzzle_solver.h"

#include <list>
#include <algorithm>

namespace
{
    const Direction directions[4] = { Direction::DOWN, Direction::LEFT, Direction::UP, Direction::RIGHT };

    auto conditions = std::list<GameBoard>{}; // storage of all boards
    auto target = GameBoard{}; // target board

    GameBoard find_depth(const GameBoard &current)
    {
        if (!current.is_init()) // Check if move is possible
        {
            return {};
        }
        else if (current == target) // Check if the goal is reached
        {
            return current;
        }

        // Add board if it is unique
        if (conditions.end() == std::find(conditions.begin(), conditions.end(), current))
        {
            conditions.push_back(current);
        }
        else
        {
            return {};
        }

        GameBoard temp{};

        for (Direction direction : directions)
        {
            temp = find_depth(current.move(direction));

            // Check if the goal is reached
            if (temp.is_init())
            {
                return temp;
            }
        }

        return {};
    }
}

GameBoard breadth_first_search(const GameBoard &initial, const GameBoard &target)
{
    auto conditions = std::list< GameBoard >{ initial }; // storage of all boards
    auto previous_level_board = int{ 1 }; // number of boards added on previous level
    auto current_level_board = int{ 0 }; // number of boards on current level

    auto temp = GameBoard{};
    auto choice = char{ 'y' };

    for (int level = 1; ; level++, current_level_board = 0)
    {
        auto level_begin = std::next(conditions.end(), -previous_level_board);

        for (int i = 0; i < previous_level_board; ++i, ++level_begin)
        {
            for (Direction direction : directions)
            {
                if (choice == 'y') {
                    std::cout << "Step-by-step/Automatic enter (y/n): ";
                    std::cin >> choice;
                }

                temp = level_begin->move(direction);

                if (!temp.is_init()) // Check if moving in the given direction is possible
                {
                    continue;
                }
                else if (conditions.end() == std::find(conditions.begin(), conditions.end(), temp)) // Check for duplicates
                {
                    if (temp == target) // Check if the result is reached
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

        previous_level_board = current_level_board;
    }
}

GameBoard depth_first_search(const GameBoard &initial, const GameBoard &target)
{
    // Find solution
    ::target = target;
    auto result = find_depth(initial);

    // Restore conditions and target
    conditions.clear();
    ::target = {};

    return result;
}
