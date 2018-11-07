// 8-puzzle
// Copyright (C) 2018 Yurii Khomiak 
// Yurii Khomiak licenses this file to you under the MIT license. 
// See the LICENSE file in the project root for more information.

#ifndef EIGHT_PUZZLE_SOLVER_
#define EIGHT_PUZZLE_SOLVER_

#include "game_board.h"

#include <list>
#include <algorithm>


namespace
{
    const Direction directions[4] = { Direction::DOWN, Direction::LEFT, Direction::UP, Direction::RIGHT };

    template <std::size_t Size>
    class DepthFirstSearcher
    {
    public:
        void set_target(GameBoard<Size> target)
        {
            target_ = target;
        }

        GameBoard<Size> depth_search_find(const GameBoard<Size> &current)
        {
            if (!current.is_init()) // Check if move is possible
            {
                return {};
            }
            else if (current == target_) // Check if the goal is reached
            {
                return current;
            }

            // Add board if it is unique
            if (conditions_.end() == std::find(conditions_.begin(), conditions_.end(), current))
            {
                conditions_.push_back(current);
            }
            else
            {
                return {};
            }

            GameBoard<Size> temp{};

            for (Direction direction : directions)
            {
                temp = depth_search_find(current.move(direction));

                // Check if the goal is reached
                if (temp.is_init())
                {
                    return temp;
                }
            }

            return {};
        }

    private:
        std::list<GameBoard<Size>> conditions_{}; // storage of all boards
        GameBoard<Size> target_{}; // target board
    };

}

template <std::size_t Size>
GameBoard<Size> breadth_first_search(const GameBoard<Size> &initial, const GameBoard<Size> &target)
{
    auto conditions = std::list< GameBoard<Size> >{ initial }; // storage of all boards
    auto previous_level_board = 1; // number of boards added on previous level
    auto current_level_board = 0; // number of boards on current level

    auto level_begin = std::next(conditions.end(), -previous_level_board); // iterator to the beginning of the current level

    auto temp = GameBoard<Size>{};

    for (int level = 1; ; level++, current_level_board = 0, level_begin = std::next(conditions.end(), -previous_level_board))
    {
        // Get childs from every board on the previous level
        for (int i = 0; i < previous_level_board; ++i, ++level_begin)
        {
            // Move in every possible direction
            for (Direction direction : directions)
            {
                temp = level_begin->move(direction);

                // Check if moving in the given direction is possible
                if (!temp.is_init())
                {
                    continue;
                }
                // Check for duplicates
                else if (conditions.end() == std::find(conditions.begin(), conditions.end(), temp))
                {
                    // Check if the result is reached
                    if (temp == target)
                    {
                        return temp;
                    }

                    conditions.push_back(temp);
                    ++current_level_board;
                }
            }
        }

        previous_level_board = current_level_board;
    }
}

template <std::size_t Size>
GameBoard<Size> depth_first_search(const GameBoard<Size> &initial, const GameBoard<Size> &target)
{
    DepthFirstSearcher<Size> depth_first_searcher;

    // Find solution
    depth_first_searcher.set_target(target);
    auto result = depth_first_searcher.depth_search_find(initial);

    return result;
}

template <std::size_t Size>
GameBoard<Size> A_star(const GameBoard<Size> &initial, const GameBoard<Size> &target)
{
    // TODO: Implement A* algorithm

    return {};
}

#endif // EIGHT_PUZZLE_SOLVER_
