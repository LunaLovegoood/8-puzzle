/* n-puzzle
*  Copyright (C) 2018 Yurii Khomiak
*
*  Permission is hereby granted, free of charge, to any person obtaining a copy of this software
*  and associated documentation files (the "Software"), to deal in the Software without restriction,
*  including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
*  and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so,
*  subject to the following conditions:
*
*  The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
*
*  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
*  INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
*  IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
*  WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
*  OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef EIGHT_PUZZLE_SOLVER_
#define EIGHT_PUZZLE_SOLVER_

#include "game_board.h"

#include <list>
#include <vector>
#include <array>
#include <algorithm>


enum class DistanceType
{
    Manhattan,
    Euclidean,
    Chebyshev
};


namespace
{
    template <std::size_t Size>
    using DistanceFunction = float(*)(const GameBoard<Size>&, const GameBoard<Size>&);

    const std::array<Direction, 4> directions = { Direction::DOWN, Direction::LEFT, Direction::UP, Direction::RIGHT };

    template <std::size_t Size>
    class DepthFirstSearcher
    {
    public:
        DepthFirstSearcher() = delete;

        DepthFirstSearcher(GameBoard<Size> target)
            :target_(target)
        {}

        GameBoard<Size> find(const GameBoard<Size> &current)
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
                temp = find(current.move(direction));

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

    template <std::size_t Size>
    DistanceFunction<Size> get_distance_function(DistanceType distance_type)
    {
        switch (distance_type)
        {
        case DistanceType::Manhattan:
            return GameBoard<Size>::manhattan_distance;

        case DistanceType::Euclidean:
            return GameBoard<Size>::euclidean_distance;

        case DistanceType::Chebyshev:
            return GameBoard<Size>::chebyshev_distance;

        default:
            return GameBoard<Size>::manhattan_distance;
        }
    }

    template <std::size_t Size>
    class AStarSearcher
    {
    public:
        AStarSearcher() = delete;

        AStarSearcher(GameBoard<Size> target, DistanceType distance_type)
            : target_{ target }, distance_function_{ get_distance_function<Size>(distance_type) }
        {}

        GameBoard<Size> find(const GameBoard<Size> &current)
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

            std::vector<GameBoard<Size>> possible_boards{}; // possible boards from current board
            std::vector<float> board_distances{}; // distances of possible boards
            GameBoard<Size> temp{};

            // Getting all possible boards
            // and their distances
            for (Direction direction : directions)
            {
                temp = current.move(direction);

                if (temp.is_init())
                {
                    possible_boards.push_back(temp);
                    board_distances.push_back(distance_function_(temp, target_));
                }
            }

            int size = possible_boards.size();

            // Go down through all possible boards with respect
            // to the value of distance function
            for (int i = 0; i < size; i++)
            {
                // Get index of the element with the min distance
                int index = std::min_element(board_distances.begin(), board_distances.end()) - board_distances.begin();

                temp = find(possible_boards[index]);

                // Check if the solution is found
                if (temp.is_init())
                {
                    return temp;
                }

                // Erase checked elements
                possible_boards.erase(std::remove(possible_boards.begin(), possible_boards.end(), possible_boards[index]),
                    possible_boards.end());
                board_distances.erase(std::remove(board_distances.begin(), board_distances.end(), board_distances[index]),
                    board_distances.end());
            }

            return {};
        }

    private:
        std::list<GameBoard<Size>> conditions_{}; // storage of all boards
        GameBoard<Size> target_{}; // target board

        DistanceFunction<Size> distance_function_{ nullptr };
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
    DepthFirstSearcher<Size> depth_first_searcher(target);

    // Find solution
    auto result = depth_first_searcher.find(initial);

    return result;
}

template <std::size_t Size>
GameBoard<Size> A_star(const GameBoard<Size> &initial, const GameBoard<Size> &target, DistanceType distance_type)
{
    AStarSearcher<Size> A_star_searcher(target, distance_type);

    // Find solution
    auto result = A_star_searcher.find(initial);

    return result;
}

#endif // EIGHT_PUZZLE_SOLVER_
