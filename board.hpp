//
//  board.hpp
//  sudoku
//
//  Created by Istiaque Shanjib on 10/24/15.
//  Copyright © 2015 Istiaque Shanjib. All rights reserved.
//

#ifndef board_hpp
#define board_hpp

// Declarations and functions for the Sudoku project

#include <iostream>
#include <vector>
#include <limits.h>
#include "d_matrix.h"
#include "d_except.h"
#include <list>
#include <fstream>

using namespace std;

typedef int ValueType; // The type of the value in a cell
const int Blank = -1;  // Indicates that a cell is blank

const int SquareSize = 3;  //  The number of cells in a small square
//  (usually 3).  The board has
//  SquareSize^2 rows and SquareSize^2
//  columns.

const int BoardSize = SquareSize * SquareSize;

const int MinValue = 1;
const int MaxValue = 9;

//int numSolutions = 0;

class board
// Stores the entire Sudoku board
{
public:
    board(int);          //function written for project 4A
    void clear();        //function written for project 4A
    void initialize(ifstream &fin);
    
    void solve(int &n);      //function written for project 4B
    bool isSolved();        //function written for project 4A
    
    void print();
    void printCon();        //function written for project 4A
    
    bool isBlank(int, int);
    int squareNumber(int, int);
    bool checkCon(int i, int j, ValueType val);        //function written for project 4A
    
    ValueType getCell(int, int);
    void setCell(int i,int j, ValueType val);
    void clearCell(int i, int j, ValueType val);        //function written for project 4A
private:
    
    // The following matrices go from 1 to BoardSize in each
    // dimension.  I.e. they are each (BoardSize+1) X (BoardSize+1)
    
    matrix<ValueType> value;
    matrix<ValueType> cons;
    vector< vector<bool> > rows;
    vector< vector<bool> > cols;
    vector< vector<bool> > squa;
};

#endif /* board_hpp */
