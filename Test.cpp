//
// Created by JosefMamo on 3/4/2021.
//
#include <string>
#include "doctest.h"
#include <iostream>
#include "Board.hpp"
#include "Direction.hpp"

using namespace ariel;
using namespace std;

unsigned int columns;
unsigned int rows;
const unsigned int length = 10;

const string empty_string = "";
const string str = "TEST";
const unsigned int strLen = str.length();
unsigned int excpected, actual;

TEST_CASE("============Good Cases============== \n")
{
  SUBCASE("       Empty String")
  {
    Board board;

    for (unsigned i = 0; i < length; i++)
    {
      rows = rand() % 500 ;
      columns = rand() % 500;
      board.post(rows,columns,Direction::Horizontal,empty_string);
      CHECK_EQ(board.read(rows,columns,Direction::Horizontal,length),"__________");
    }
  }

  SUBCASE("               Check if string  is override when we take place of an exisitng place\n")
  {
    Board board;
    rows = 22, columns = 15;
    board.post(rows, columns, Direction::Horizontal, "OVERRIDE");
    rows = 21, columns = 16;
    board.post(rows, columns, Direction::Vertical, "ABC");
    
    rows = 22, columns = 15;
    CHECK_EQ(board.read(rows, columns, Direction::Horizontal, 8), "OBERRIDE");

    rows = 1, columns = 1;
    board.post(rows, columns, Direction::Vertical, "OVERRIDE");
    rows = 3, columns = 0;
    board.post(rows, columns, Direction::Horizontal, "ABC");
    rows = 1, columns = 1;
    CHECK_EQ(board.read(rows, columns, Direction::Vertical, 8), "OVBRRIDE");
  }
  SUBCASE("Vertical cases")
  {
    Board board;
    /*
    Backspacd case
    */
    board.post(0, 0, Direction::Vertical, " ");
    CHECK_EQ(board.read(0, 0, Direction::Vertical, 2), " _");

    /*
Posting from the first values.
*/
    CHECK_NOTHROW(board.post(0, 0, Direction::Vertical, str));
    /*
after posting we trying to read what we have posted
*/
    CHECK_EQ(board.read(0, 0, Direction::Vertical, strLen), str);

    /*
check Posting 10 times in random raws and random columns in range 1 - 100 
 then checking for each if the string that we posted get back 
*/
    for (int i = 0; i < length; i++)
    {
      columns = rand() % 100 + 1;
      rows = rand() % 100 + 1;
      CHECK_NOTHROW(board.post(rows, columns, Direction::Vertical, str));
      CHECK_EQ(board.read(rows, columns, Direction::Vertical, strLen), str);
    }
  }
  SUBCASE("Horizntal cases")
  {
    Board board;
    /*
Posting from the first values.
*/
    CHECK_NOTHROW(board.post(0, 0, ariel::Direction::Horizontal, str));
    /*
after posting we trying to read what we have posted
*/
    CHECK_EQ(board.read(0, 0, ariel::Direction::Horizontal, strLen), str);

    /*
check Posting 10 times in random raws and random columns and then checking for each if the string that we posted get back from read function
*/

    for (int i = 0; i < length; i++)
    {
      columns = rand() % 100 + 1;
      rows = rand() % 100 + 1;
      CHECK_NOTHROW(board.post(rows, columns, ariel::Direction::Horizontal, str));
      CHECK_EQ(board.read(rows, columns, ariel::Direction::Horizontal, strLen), str);
    }
  }
}