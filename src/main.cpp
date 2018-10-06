// Game of 8
// Copyright (C) 2018 Yurii Khomiak 
// Yurii Khomiak licenses this file to you under the MIT license. 
// See the LICENSE file in the project root for more information.

#include "game_field.h"

#include <iostream>
#include <list>
#include <array>


const std::array< std::array< char, 3 >, 3 > initial_field = { {
    {'1', '8', '2'},
    {'7', ' ', '3'},
    {'6', '5', '4'}
} };
const std::array< std::array< char, 3 >, 3 > resulting_field = { {
    {'1', '2', '3'},
    {'4', '5', '6'},
    {'7', '8', ' '}
} };

const Direction directions[4] = { Direction::DOWN, Direction::LEFT, Direction::UP, Direction::RIGHT };


void breadth_search();


int main()
{
    breadth_search();

    system("pause");

    return 0;
}

void breadth_search()
{
    std::list< GameField > conditions{ initial_field };
    int level = 0;

    GameField field{ initial_field };

    std::cout << field;
    for (int i = 0; i < 4; i++)
    {
        field = field.move(directions[i]);
        std::cout << field;
    }
}
