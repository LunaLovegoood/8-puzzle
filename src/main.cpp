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

#include "eight_puzzle_solver.h"

constexpr auto initial_board = std::array< std::array< char, 3 >, 3 >{ {
    {'1', '8', '2'},
    {'7', ' ', '3'},
    {'6', '5', '4'}
} };
constexpr auto target_board = std::array< std::array< char, 3 >, 3 >{ {
    {'1', '2', '3'},
    {'8', ' ', '4'},
    {'7', '6', '5'}
} };


int main()
{
    std::cout << "Breadth first search path:";
    breadth_first_search(GameBoard<3>(initial_board), GameBoard<3>(target_board)).show_path();

    std::cout << "Depth first search path:";
    depth_first_search(GameBoard<3>(initial_board), GameBoard<3>(target_board)).show_path();

    std::cout << "A* search path (Manhattan):\n";
    A_star(GameBoard<3>(initial_board), GameBoard<3>(target_board), DistanceType::Manhattan).show_path();

    std::cout << "A* search path (Euclidean):\n";
    A_star(GameBoard<3>(initial_board), GameBoard<3>(target_board), DistanceType::Euclidean).show_path();

    std::cout << "A* search path (Chebyshev):\n";
    A_star(GameBoard<3>(initial_board), GameBoard<3>(target_board), DistanceType::Chebyshev).show_path();

    system("pause");

    return 0;
}
