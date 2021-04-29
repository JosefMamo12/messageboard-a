#include <cstring>
#include <iostream>
#include "Direction.hpp"
#include <iterator>
#include <map>
#include <string.h>

using namespace std;

const int COLU_BOUND = 1;
const int ROW_BOUND = 1;
const string DEFAULT_KEY = "_";
const string EMPTY_BOARD_MESSAGE = "THE BOARD IS EMPTY, THEREFORE NOTHING TO SHOW!!!";

namespace ariel
{

    class Board
    {
        map<unsigned int, map<unsigned int, char>> _board;
        unsigned int _row;
        unsigned int _col;
        unsigned int _starting_column;
        unsigned int _starting_row;

    public:
        Board(unsigned int rows = 0, unsigned int columns = 0, unsigned int starting_row = UINT32_MAX, unsigned int starting_column = UINT32_MAX) : _col(columns),
                                                                                                                                                    _row(rows),
                                                                                                                                                    _starting_row(starting_row),
                                                                                                                                                    _starting_column(starting_column)
        {
        }
        void post(unsigned int rows, unsigned int columns, Direction direct, const string &str);
        string read(unsigned int rows, unsigned int columns, Direction direct, unsigned int string_length);
        unsigned int &column() { return _col; }                     // getter and setters
        unsigned int &row() { return _row; }                        // getter and setter
        unsigned int &column_starter() { return _starting_column; } // getter and setters
        unsigned int &row_starter() { return _starting_row; }       // getter and setter
        void show();
        void higherBound(unsigned int, unsigned int);
        void lowerBound(unsigned int, unsigned int);
        ~Board();
    };

}