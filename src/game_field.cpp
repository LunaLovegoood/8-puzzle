// Game of 8
// Copyright (C) 2018 Yurii Khomiak 
// Yurii Khomiak licenses this file to you under the MIT license. 
// See the LICENSE file in the project root for more information.

#include "game_field.h"

#include <iostream>
#include <array>

GameField::GameField(std::array< std::array< char, 3 >, 3 > field)
{
    for (int i = 0; i < size_; i++)
    {
        for (int j = 0; j < size_; j++)
        {
            field_[i][j] = field.at(i).at(j);
        }
    }
}

std::ostream& operator<<(std::ostream &stream, const GameField &field)
{
    for (int i = 0; i < field.size_; i++)
    {
        stream << "+-+-+-+\n";
        for (int j = 0; j < field.size_; j++)
        {
            stream << '|' << field.field_[i][j];
        }
        stream << "|\n";
    }
    stream << "+-+-+-+\n";

    stream << std::endl;
    return stream;
}
