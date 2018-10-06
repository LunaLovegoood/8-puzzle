// Game of 8
// Copyright (C) 2018 Yurii Khomiak 
// Yurii Khomiak licenses this file to you under the MIT license. 
// See the LICENSE file in the project root for more information.

#ifndef GAME_FIELD_H_
#define GAME_FIELD_H_

#include <iostream>
#include <array>

enum class Direction {DOWN, LEFT, UP, RIGHT};

class GameField
{
public:
    GameField() {}
    GameField(std::array< std::array< char, 3 >, 3 > field);

    GameField move(Direction direction);

    bool operator==(const GameField& field) const;

    friend std::ostream& operator<<(std::ostream &stream, const GameField &field);

private:
    static const int size_ = 3;

    char field_[3][3]{ ' ' };
    int row_blank{ -1 };
    int col_blank{ -1 };

    void move_down(GameField &field);
    void move_left(GameField &field);
    void move_up(GameField &field);
    void move_right(GameField &field);
};

#endif // GAME_FIELD_H_
