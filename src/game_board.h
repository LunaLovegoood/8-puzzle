// 8-puzzle
// Copyright (C) 2018 Yurii Khomiak 
// Yurii Khomiak licenses this file to you under the MIT license. 
// See the LICENSE file in the project root for more information.

#ifndef GAME_BOARD_H_
#define GAME_BOARD_H_

#include <iostream>
#include <cstdlib>
#include <array>
#include <memory>
#include <list>


enum class Direction {DOWN, LEFT, UP, RIGHT};

template <std::size_t Size>
class GameBoard
{
public:
    GameBoard() = default;
    explicit GameBoard(std::array< std::array< char, Size >, Size > board);

    GameBoard move(Direction direction) const noexcept;

    void show_path() const noexcept;

    bool is_init() const noexcept
    {
        return is_init_;
    }

    template <std::size_t Size>
    friend bool operator==(const GameBoard<Size> &lhs, const GameBoard<Size> &rhs);

    template <std::size_t Size>
    friend std::ostream& operator<<(std::ostream &stream, const GameBoard<Size> &board);

private:
    char board_[Size][Size]{};
    int row_blank_{ -1 };
    int col_blank_{ -1 };

    std::shared_ptr< GameBoard > parent{ nullptr };

    bool is_init_{ false };

    void move_down(GameBoard &board) const noexcept;
    void move_left(GameBoard &board) const noexcept;
    void move_up(GameBoard &board) const noexcept;
    void move_right(GameBoard &board) const noexcept;
};

// Avoiding zero size arrays
template<>
class GameBoard<0> {};


template <std::size_t Size>
GameBoard<Size>::GameBoard(std::array< std::array< char, Size >, Size > board)
{
    for (int i = 0; i < Size; i++)
    {
        for (int j = 0; j < Size; j++)
        {
            board_[i][j] = board.at(i).at(j);

            if (board_[i][j] == ' ')
            {
                row_blank_ = i;
                col_blank_ = j;
            }
        }
    }

    is_init_ = true;
}

template <std::size_t Size>
GameBoard<Size> GameBoard<Size>::move(Direction direction) const noexcept
{
    GameBoard<Size> result;

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

template <std::size_t Size>
void GameBoard<Size>::move_down(GameBoard<Size> &board) const noexcept
{
    if (row_blank_ == (Size - 1))
    {
        return;
    }

    board = *this;

    // Swap blank cell with lower cell
    board.board_[row_blank_][col_blank_] = board_[row_blank_ + 1][col_blank_];
    board.board_[row_blank_ + 1][col_blank_] = ' ';

    board.parent = std::make_shared<GameBoard<Size>>(*this);

    ++board.row_blank_;
}

template <std::size_t Size>
void GameBoard<Size>::move_left(GameBoard<Size> &board) const noexcept
{
    if (col_blank_ == 0)
    {
        return;
    }

    board = *this;

    // Swap blank cell with left cell
    board.board_[row_blank_][col_blank_] = board_[row_blank_][col_blank_ - 1];
    board.board_[row_blank_][col_blank_ - 1] = ' ';

    board.parent = std::make_shared<GameBoard<Size>>(*this);

    --board.col_blank_;
}

template <std::size_t Size>
void GameBoard<Size>::move_up(GameBoard<Size> &board) const noexcept
{
    if (row_blank_ == 0)
    {
        return;
    }

    board = *this;

    // Swap blank cell with upper cell
    board.board_[row_blank_][col_blank_] = board_[row_blank_ - 1][col_blank_];
    board.board_[row_blank_ - 1][col_blank_] = ' ';

    board.parent = std::make_shared<GameBoard<Size>>(*this);

    --board.row_blank_;
}

template <std::size_t Size>
void GameBoard<Size>::move_right(GameBoard<Size> &board) const noexcept
{
    if (col_blank_ == (Size - 1))
    {
        return;
    }

    board = *this;

    // Swap blank cell with right cell
    board.board_[row_blank_][col_blank_] = board_[row_blank_][col_blank_ + 1];
    board.board_[row_blank_][col_blank_ + 1] = ' ';

    board.parent = std::make_shared<GameBoard<Size>>(*this);

    ++board.col_blank_;
}

template <std::size_t Size>
void GameBoard<Size>::show_path() const noexcept
{
    auto path = std::list<GameBoard<Size>>{};
    auto trace = std::make_shared<GameBoard<Size>>(*this);

    while (trace != nullptr)
    {
        path.push_back(*trace);
        trace = trace->parent;
    }

    auto iter = path.crbegin();
    while (iter != path.rend())
    {
        std::cout << *(iter++);
    }
}

template <std::size_t Size>
bool operator==(const GameBoard<Size> &lhs, const GameBoard<Size> &rhs)
{
    for (int i = 0; i < Size; i++)
    {
        for (int j = 0; j < Size; j++)
        {
            if (lhs.board_[i][j] != rhs.board_[i][j])
            {
                return false;
            }
        }
    }

    return true;
}

template <std::size_t Size>
std::ostream& operator<<(std::ostream &stream, const GameBoard<Size> &board)
{
    stream << std::endl;

    for (int i = 0; i < Size; i++)
    {
        stream << "+---+---+---+\n";
        for (int j = 0; j < Size; j++)
        {
            stream << "| " << board.board_[i][j] << ' ';
        }
        stream << "|\n";
    }
    stream << "+---+---+---+\n";

    stream << std::endl;
    return stream;
}

#endif // GAME_BOARD_H_
