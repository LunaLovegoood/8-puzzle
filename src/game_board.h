// 8-puzzle
// Copyright (C) 2018 Yurii Khomiak 
// Yurii Khomiak licenses this file to you under the MIT license. 
// See the LICENSE file in the project root for more information.

#ifndef GAME_BOARD_H_
#define GAME_BOARD_H_

#include <iostream>
#include <array>
#include <memory>


enum class Direction {DOWN, LEFT, UP, RIGHT};

class GameBoard
{
public:
    GameBoard() {}
    GameBoard(std::array< std::array< char, 3 >, 3 > board);

    GameBoard move(Direction direction) const noexcept;

    void show_path() const noexcept;

    bool is_init() const noexcept
    {
        return is_init_;
    }

    friend bool operator==(const GameBoard& lhs, const GameBoard& rhs);
    friend bool operator!=(const GameBoard& lhs, const GameBoard& rhs);

    friend std::ostream& operator<<(std::ostream &stream, const GameBoard &board);

private:
    static const int size_ = 3;

    char board_[3][3]{};
    int row_blank_{ -1 };
    int col_blank_{ -1 };

    std::shared_ptr< GameBoard > parent{ nullptr };

    bool is_init_{ false };

    void move_down(GameBoard &board) const noexcept;
    void move_left(GameBoard &board) const noexcept;
    void move_up(GameBoard &board) const noexcept;
    void move_right(GameBoard &board) const noexcept;
};

#endif // GAME_BOARD_H_
