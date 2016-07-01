//
//  board.cpp
//  sudoku
//
//  Created by Istiaque Shanjib on 10/24/15.
//  Copyright © 2015 Istiaque Shanjib. All rights reserved.
//

#include "board.hpp"

void board::solve(int &n)
{
    n++;
    int i=0, j=0, k=0;
    int ui=1, uj=1;
    bool check = false;
    if (isSolved() == true)                 //if solved
    {
        print();
    }
    else
    {
        for (i = 1; i <= BoardSize; i++)
        {
            for (j = 1; j <= BoardSize; j++)
            {
                for (k = 1; k <= BoardSize; k++)
                {
                    if (checkCon(i,j,k) == false && isBlank(i, j) == true)
                        cons[i][j]++;           //find number of possibilities for each cell
                }
            }
        }
        
        for (i = 1; i <= BoardSize; i++)
        {
            for (j = 1; j <= BoardSize; j++)
            {
                check = isBlank(i,j);
                if (check)
                {
                    ui = i;                     //set usage cell to first blank
                    uj = j;                     //aka initialize usage cell
                    break;
                }
            }
            if (check)
                break;
        }
        
        
        for (i = 1; i <= BoardSize; i++)
        {
            for (j = 1; j <= BoardSize; j++)
            {
                if (cons[ui][uj] > cons [i][j]  && isBlank(i, j) == true)
                {
                    ui = i;                     //set usage cell to cell with lowest number of possibilities
                    uj = j;
                }
            }
        }
        
        for (k = 1; k <= BoardSize; k++)
        {
            if (checkCon(ui, uj, k) == false)
            {
                setCell(ui, uj, k);             //set cell to a legal possibility
                print();
                cout<<n<<endl;
                solve(n);                       //recurse
                if (isSolved() == false)
                    clearCell(ui,uj,k);         //if it hasn't been solved, clear on recursing back
            }
        }
    }
}



board::board(int sqSize)
: value(BoardSize+1,BoardSize+1) , cons(BoardSize+1,BoardSize+1)
// Board constructor                        written for project 4A
{
    rows.resize(9);                         //resize all conflict vectors
    cols.resize(9);
    squa.resize(9);
    for (int a = 1; a <= BoardSize; a++)
    {
        rows[a-1].resize(9);
        cols[a-1].resize(9);
        squa[a-1].resize(9);
    }
    clear();                                //clear the whole board
}



void board::clear()
// Clear the entire board.                      written for project 4A
{
    for (int i = 1; i <= BoardSize; i++)        //loop through whole board
    {
        for (int j = 1; j <= BoardSize; j++)
        {
            value[i][j] = Blank;                //set matrix indices to blank
            cons[i][j] = 0;
            rows[i-1][j-1] = false;             //set conflict vectors to false
            cols[i-1][j-1] = false;
            squa[i-1][j-1] = false;
        }
    }
}




void  board::setCell(int i,int j, ValueType val)
// set cell i,j to val and update conflicts         written for project 4A
{
    value[i][j] = val;                              //set matrix index to value
    
    int s = squareNumber(i,j);                      //get square number
    rows[i-1][val-1] = true;                        //set conflict vectors to true
    cols[j-1][val-1] = true;
    squa[s-1][val-1] = true;
}


void board::clearCell(int i, int j, ValueType val)
//  clear cell i,j and update conflicts             written for project 4A
{
    value[i][j] = Blank;                            //set matrix index to blank
    
    int s = squareNumber(i,j);                      //get square number
    rows[i-1][val-1] = false;                       //set conflict vectors to false
    cols[j-1][val-1] = false;
    squa[s-1][val-1] = false;
}




void board::initialize(ifstream &fin)
// Read a Sudoku board from the input file.
{
    char ch;
    
    clear();
    for (int i = 1; i <= BoardSize; i++)
        for (int j = 1; j <= BoardSize; j++)
        {
            fin >> ch;
            
            // If the read char is not Blank
            if (ch != '.')
            {
                setCell(i,j,ch-'0');   // Convert char to int
            }
        }
}




int board::squareNumber(int i, int j)
// Return the square number of cell i,j (counting from left to right,
// top to bottom.  Note that i and j each go from 1 to BoardSize
{
    // Note that (int) i/SquareSize and (int) j/SquareSize are the x-y
    // coordinates of the square that i,j is in.
    
    return SquareSize * ((i-1)/SquareSize) + (j-1)/SquareSize + 1;
}




ostream &operator<<(ostream &ostr, vector<int> &v)
// Overloaded output operator for vector class.
{
    for (int i = 0; i < v.size(); i++)
        ostr << v[i] << " ";
    ostr << endl;
    return ostr;
}




ValueType board::getCell(int i, int j)
// Returns the value stored in a cell.  Throws an exception
// if bad values are passed.
{
    if (i >= 1 && i <= BoardSize && j >= 1 && j <= BoardSize)
        return value[i][j];
    else
        throw rangeError("bad value in getCell");
}




bool board::isBlank(int i, int j)
// Returns true if cell i,j is blank, and false otherwise.
{
    if (i < 1 || i > BoardSize || j < 1 || j > BoardSize)
        throw rangeError("bad value in setCell");
    if (value[i][j] < 1 || value [i][j] > 9)
        return true;
    else
        return false;
}





void board::print()
// Prints the current board.
{
    for (int i = 1; i <= BoardSize; i++)
    {
        if ((i-1) % SquareSize == 0)
        {
            cout << " -";
            for (int j = 1; j <= BoardSize; j++)
                cout << "---";
            cout << "-";
            cout << endl;
        }
        for (int j = 1; j <= BoardSize; j++)
        {
            if ((j-1) % SquareSize == 0)
                cout << "|";
            if (!isBlank(i,j))
                cout << " " << getCell(i,j) << " ";
            else
                cout << "   ";
        }
        cout << "|";
        cout << endl;
    }
    
    cout << " -";
    for (int j = 1; j <= BoardSize; j++)
        cout << "---";
    cout << "-";
    cout << endl;
}



void board::printCon()
//function to print conflicts                       written for project 4A
{
    cout<<"There are conflicts at the following places:"<<endl;
    //loop through each conflict vector and print out where there are conflicts
    for (int i = 1; i <= BoardSize; i++)
    {
        cout<<"Row "<<i<<" has the following numbers:";
        for (int j = 1; j <= BoardSize; j++)
        {
            if (rows[i-1][j-1])
                cout<<" "<<j;
        }
        cout<<endl;
    }
    
    for (int i = 1; i <= BoardSize; i++)
    {
        cout<<"Column "<<i<<" has the following numbers:";
        for (int j = 1; j <= BoardSize; j++)
        {
            if (cols[i-1][j-1])
                cout<<" "<<j;
        }
        cout<<endl;
    }
    
    for (int i = 1; i <= BoardSize; i++)
    {
        cout<<"Square "<<i<<" has the following numbers:";
        for (int j = 1; j <= BoardSize; j++)
        {
            if (squa[i-1][j-1])
                cout<<" "<<j;
        }
        cout<<endl;
    }
}


bool board::checkCon(int i, int j, ValueType val)
//checks if there is a conflict with setting val at i,j         written for project 4A
{
    int s = squareNumber(i, j);             //get square number
    
    if (!isBlank(i, j))                     //if not blank
        return true;
    else if(rows[i-1][val-1])               //if that number is in the row
        return true;
    else if(cols[j-1][val-1])               //if that number is in the column
        return true;
    else if(squa[s-1][val-1])               //if that number is in the square
        return true;
    else
        return false;
}


bool board::isSolved()
//check if board is solved                              written for project 4A
{
    //loop through each square, if anything is false AKA blank return false
    for (int i = 1; i <= BoardSize; i++)
    {
        for (int j = 1; j <= BoardSize; j++)
        {
            if (squa[i-1][j-1] == false)
            {
                return false;
            }
        }
    }
    //cout<<"Puzzle solved!"<<endl;
    return true;
}
