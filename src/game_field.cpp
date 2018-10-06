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

            if (field_[i][j] == ' ')
            {
                row_blank = i;
                col_blank = j;
            }
        }
    }
}

GameField GameField::move(Direction direction)
{
    GameField result;

    switch (direction)
    {
    case Direction::DOWN:
        move_down(result);
        break;

    case Direction::LEFT:
        move_left(result);
        break;

    case Direction::UP:
        move_up(result);
        break;

    case Direction::RIGHT:
        move_right(result);
        break;
    }

    return result;
}

void GameField::move_down(GameField &field)
{
    if (row_blank == (size_ - 1))
    {
        return;
    }

    field = *this;

    field.field_[row_blank][col_blank] = field_[row_blank + 1][col_blank];
    field.field_[row_blank + 1][col_blank] = ' ';

    field.row_blank++;
}

void GameField::move_left(GameField &field)
{
    if (col_blank == 0)
    {
        return;
    }

    field = *this;

    field.field_[row_blank][col_blank] = field_[row_blank][col_blank - 1];
    field.field_[row_blank][col_blank - 1] = ' ';

    field.col_blank--;
}

void GameField::move_up(GameField &field)
{
    if (row_blank == 0)
    {
        return;
    }

    field = *this;

    field.field_[row_blank][col_blank] = field_[row_blank - 1][col_blank];
    field.field_[row_blank - 1][col_blank] = ' ';

    field.row_blank--;
}

void GameField::move_right(GameField &field)
{
    if (col_blank == (size_ - 1))
    {
        return;
    }

    field = *this;

    field.field_[row_blank][col_blank] = field_[row_blank][col_blank + 1];
    field.field_[row_blank][col_blank + 1] = ' ';

    field.col_blank++;
}

bool GameField::operator==(const GameField& field) const
{
    for (int i = 0; i < size_; i++)
    {
        for (int j = 0; j < size_; j++)
        {
            if (field_[i][j] != field.field_[i][j])
            {
                return false;
            }
        }
    }

    return true;
}

std::ostream& operator<<(std::ostream &stream, const GameField &field)
{
    stream << std::endl;

    for (int i = 0; i < field.size_; i++)
    {
        stream << "+---+---+---+\n";
        for (int j = 0; j < field.size_; j++)
        {
            stream << "| " << field.field_[i][j] << ' ';
        }
        stream << "|\n";
    }
    stream << "+---+---+---+\n";

    stream << std::endl;
    return stream;
}
