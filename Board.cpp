#include <cstring>
#include <iostream>
#include "Board.hpp"
#include <map>
#include "Direction.hpp"
#include <vector>
#include <string.h>

using namespace std;

namespace ariel
{
    void Board::lowerBound(unsigned int rows, unsigned int columns)
    {
        if (rows <= row_starter())
        {
            row_starter() = rows;
            if (row_starter() >= ROW_BOUND)
            {
                row_starter() = rows - ROW_BOUND;
            }
        }
        if (columns <= column_starter())
        {
            column_starter() = columns;
            if (column_starter() >= COLU_BOUND)
            {
                column_starter() = column_starter() - COLU_BOUND;
            }
        }
    }
    void Board::higherBound(unsigned int rows, unsigned int columns)
    {

        if (Board::row() <= rows)
        {
            row() = rows + ROW_BOUND;
        }
        if (column() <= columns)
        {
            column() = columns + COLU_BOUND;
        }
    }
    void Board::post(unsigned int rows, unsigned int columns, Direction direct, const string &str)
    {
        lowerBound(rows, columns);
        unsigned int str_index = 0;
        map<unsigned int, map<unsigned int, char>>::iterator itr;
        map<unsigned int, char>::iterator ptr;
        if (direct == Direction::Horizontal)
        {
            higherBound(rows, columns + str.length());
            while (str_index < str.length())
            {
                itr = this->_board.find(rows);
                if (itr != this->_board.end())
                {
                    ptr = itr->second.find(columns);
                    if (ptr != itr->second.end())
                    {
                        ptr->second = str[str_index++];
                        columns++;
                    }
                    else
                    {
                        this->_board[rows].insert(make_pair(columns, str[str_index++]));
                        columns++;
                    }
                }
                else
                {
                    this->_board.insert(make_pair(rows, map<unsigned int, char>()));
                    this->_board[rows].insert(make_pair(columns++, str[str_index++]));
                }
            }
        }
        else
        {
            higherBound(rows + str.length(), columns);
            while (str_index < str.length())
            {
                itr = this->_board.find(rows);
                if (itr != this->_board.end())
                {
                    ptr = itr->second.find(columns);
                    if (ptr != itr->second.end())
                    {
                        ptr->second = str[str_index++];
                        rows++;
                    }
                    else
                    {
                        this->_board[rows].insert(make_pair(columns, str[str_index++]));
                        rows++;
                    }
                }
                else
                {
                    this->_board.insert(make_pair(rows, map<unsigned int, char>()));
                    this->_board[rows++].insert(make_pair(columns, str[str_index++]));
                }
            }
        }
    }
    string Board::read(unsigned int rows, unsigned int columns, Direction direct, unsigned int string_length)
    {
        string ans;
        uint index = 0;
        map<unsigned int, map<unsigned int, char>>::iterator itr;
        map<unsigned int, char>::iterator ptr;
        if (direct == Direction::Horizontal)
        {
            while (index < string_length)
            {
                itr = this->_board.find(rows);
                if (itr != this->_board.end())
                {
                    ptr = itr->second.find(columns + index);
                    if (ptr != itr->second.end())
                    {
                        ans += ptr->second;
                        index++;
                    }
                    else
                    {
                        ans += DEFAULT_KEY;
                        index++;
                    }
                }
                else
                {
                    ans += DEFAULT_KEY;
                    index++;
                }
            }
        }

        else
        {
            while (index < string_length)
            {
                itr = this->_board.find(rows + index);
                if (itr != this->_board.end())
                {
                    ptr = itr->second.find(columns);
                    if (ptr != itr->second.end())
                    {
                        ans += ptr->second;
                        index++;
                    }
                    else
                    {
                        ans += DEFAULT_KEY;
                        index++;
                    }
                }
                else
                {
                    ans += DEFAULT_KEY;
                    index++;
                }
            }
        }
        return ans;
    }
    void Board::show()
    {
        if (this->_board.empty())
        {
            cout << EMPTY_BOARD_MESSAGE
                 << endl;
            return;
        }
        const unsigned int row_size = row() - row_starter();
        const unsigned int col_size = column() - column_starter();
        vector<vector<char>> mat(row_size, vector<char>(col_size, '_'));
        map<unsigned int, map<unsigned int, char>>::iterator itr = this->_board.begin();
        map<unsigned int, char>::iterator ptr = itr->second.begin();
        for (itr = this->_board.begin(); itr != this->_board.end(); itr++)
        {

            for (ptr = itr->second.begin(); ptr != itr->second.end(); ptr++)
            {
                mat[itr->first - row_starter()][ptr->first - column_starter()] = ptr->second;
            }
        }

        // for (unsigned int i = 0; i < row_size; i++)
        // {
        //     for (unsigned int j = 0; j < col_size; j++)
        //     {
        //         itr = this->_board.find(i + row_starter());
        //         if (itr != this->_board.end())
        //         {
        //             ptr = itr->second.find(j + column_starter());
        //             if (ptr != itr->second.end())
        //             {
        //                 mat[i][j] = ptr->second;
        //             }
        //         }
        //     }
        // }
        for (unsigned int i = 0; i < row_size; i++)
        {
            cout << i + row_starter() << ": ";
            for (unsigned int j = 0; j < col_size; j++)
            {

                cout << mat[i][j];
            }
            cout << endl;
        }
    }

    Board::~Board(){};
}