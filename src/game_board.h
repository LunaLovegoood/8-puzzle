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

#ifndef GAME_BOARD_H_
#define GAME_BOARD_H_

#include <iostream>
#include <cstdlib>
#include <cstdint>
#include <cmath>
#include <array>
#include <memory>
#include <list>

/**
* \brief Direction enum class
* 
* \details Contains member for moving in four directions:
* down, left, up, right
*/
enum class Direction {
    DOWN, ///< down direction
    LEFT, ///< left direction
    UP, ///< up direction
    RIGHT ///< right direction
};

/**
* \brief Game board for n-puzzle
*
* \details Represents n*n game board for n-puzzle
*
* @tparam Size stands for the size of the board 
*/
template <std::size_t Size>
class GameBoard
{
public:
    GameBoard() = default;
    explicit GameBoard(std::array< std::array< char, Size >, Size > board);

    GameBoard move(Direction direction) const noexcept;

    void show_path() const noexcept;

    /**
    * \brief Checks whether board is initialized or not
    *
    * \details if_init() will return false if the board was default initialized
    * or move in some direction wasn't possible
    *
    * @return True if the board is initialized, false otherwise
    */
    bool is_init() const noexcept
    {
        return is_init_;
    }

    static float manhattan_distance(const GameBoard<Size> &begin, const GameBoard<Size> &end) noexcept;
    static float euclidean_distance(const GameBoard<Size> &begin, const GameBoard<Size> &end) noexcept;
    static float chebyshev_distance(const GameBoard<Size> &begin, const GameBoard<Size> &end) noexcept;

    template <std::size_t Size>
    friend bool operator==(const GameBoard<Size> &lhs, const GameBoard<Size> &rhs);

    template <std::size_t Size>
    friend std::ostream& operator<<(std::ostream &stream, const GameBoard<Size> &board);

private:
    static constexpr uint16_t size_ = static_cast<uint16_t>(Size);

    char board_[Size][Size]{}; ///< actual game board with blank tile
    int row_blank_{ -1 }; ///< row position of the blank tile
    int col_blank_{ -1 }; ///< column position of the blank tile

    std::shared_ptr< GameBoard > parent{ nullptr }; ///< parent of the board in the search tree

    bool is_init_{ false }; ///< true if the board is initialized, false otherwise

    struct TilePosition
    {
        uint16_t row;
        uint16_t col;
    };

    TilePosition find_tile(char searched_value) const noexcept;

    void move_down(GameBoard &board) const noexcept;
    void move_left(GameBoard &board) const noexcept;
    void move_up(GameBoard &board) const noexcept;
    void move_right(GameBoard &board) const noexcept;
};

/**
* \brief Handle for 0*0 board
*/
template<>
class GameBoard<0> {};


template <std::size_t Size>
GameBoard<Size>::GameBoard(std::array< std::array< char, Size >, Size > board)
{
    for (int i = 0; i < size_; i++)
    {
        for (int j = 0; j < size_; j++)
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
    if (row_blank_ == (size_ - 1))
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
    if (col_blank_ == (size_ - 1))
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

/**
* \brief Computes manhattan distance
*
* \details Computes manhattan distance from current board to the target board
*
* @tparam Size stands for the size of the board
*
* @param target board to which distance will be computed
*
* @return Manhattan distance from current board to the target board
*/
template <std::size_t Size>
float GameBoard<Size>::manhattan_distance(const GameBoard<Size> &begin, const GameBoard<Size> &end) noexcept
{
    uint16_t distance{};

    for (uint16_t i = 0; i < size_; i++)
    {
        for (uint16_t j = 0; j < size_; j++)
        {
            auto[row, col] = end.find_tile(begin.board_[i][j]);

            distance += abs(row - i) + abs(col - j);
        }
    }

    return distance;
}

/**
* \brief Computes euclidean distance
*
* \details Computes euclidean distance from current board to the target board
*
* @tparam Size stands for the size of the board
*
* @param target board to which distance will be computed
*
* @return Euclidean distance from current board to the target board
*/
template <std::size_t Size>
float GameBoard<Size>::euclidean_distance(const GameBoard<Size> &begin, const GameBoard<Size> &end) noexcept
{
    float distance{};

    for (uint16_t i = 0; i < size_; i++)
    {
        for (uint16_t j = 0; j < size_; j++)
        {
            auto[row, col] = end.find_tile(begin.board_[i][j]);

            distance += static_cast<float>(pow( (pow(row - i, 2) + pow(col - j, 2)) , 0.5));
        }
    }

    return distance;
}

/**
* \brief Computes Chebyshev distance
*
* \details Computes Chebyshev distance from current board to the target board
*
* @tparam Size stands for the size of the board
*
* @param target board to which distance will be computed
*
* @return Chebyshev distance from current board to the target board
*/
template <std::size_t Size>
float GameBoard<Size>::chebyshev_distance(const GameBoard<Size> &begin, const GameBoard<Size> &end) noexcept
{
    uint16_t distance{};

    for (uint16_t i = 0; i < size_; i++)
    {
        for (uint16_t j = 0; j < size_; j++)
        {
            auto[row, col] = end.find_tile(begin.board_[i][j]);

            distance += ( (abs(row - i) > abs(col - j)) ? abs(row - i) : abs(col - j) );
        }
    }

    return distance;
}

/**
* \brief Find tile by given tile value
*
* \details Find tile by given tile value and return it's coordinates as TilePosition struct
*
* @tparam Size stands for the size of the board
*
* @param value which is to be found in the board
*
* @return Returns searched tile coordinates as TilePosition struct
*/
template <std::size_t Size>
typename GameBoard<Size>::TilePosition GameBoard<Size>::find_tile(char searched_value) const noexcept
{
    for (uint16_t i = 0; i < size_; i++)
    {
        for (uint16_t j = 0; j < size_; j++)
        {
            if (board_[i][j] == searched_value)
            {
                return {i, j};
            }
        }
    }

    return {};
}

/**
* \brief Compares two strings for equality
*
* \details Compares two strings for equality,
* no matter which board is their parent
*
* @tparam Size stands for the size of the board
*
* @param lhs left-hand side of the comparison
* @param rhs right-hand side of the comparison
*
* @return True if the board are equal, false otherwise
*/
template <std::size_t Size>
bool operator==(const GameBoard<Size> &lhs, const GameBoard<Size> &rhs)
{
    for (int i = 0; i < lhs.size_; i++)
    {
        for (int j = 0; j < lhs.size_; j++)
        {
            if (lhs.board_[i][j] != rhs.board_[i][j])
            {
                return false;
            }
        }
    }

    return true;
}

/**
* \brief Outputs board
*
* \details Outputs game board to the output stream
*
* @tparam Size stands for the size of the board
*
* @param stream output stream
* @param board board which will be printed
*
* @return Reference to the output stream
*/
template <std::size_t Size>
std::ostream& operator<<(std::ostream &stream, const GameBoard<Size> &board)
{
    stream << std::endl;

    for (int i = 0; i < board.size_; i++)
    {
        stream << "+---+---+---+\n";
        for (int j = 0; j < board.size_; j++)
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
