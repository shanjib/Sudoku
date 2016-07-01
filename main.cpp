//
//  main.cpp
//  sudoku
//
//  Created by Istiaque Shanjib on 10/24/15.
//  Copyright © 2015 Istiaque Shanjib. All rights reserved.
//

#include <iostream>
#include "board.hpp"
using namespace std;

int n;

int main()
{
    ifstream fin;
    
    // Read the sample grid from the file.
    string fileName;

    cout<<"Please input name of file"<<endl; 
    getline(cin, fileName);
    
    fin.open(fileName.c_str());
    if (!fin)
    {
        cerr << "Cannot open " << fileName << endl;
        exit(1);
    }
    
    try
    {
        board b1(SquareSize);
        vector<int> avg;
        int sum = 0;
        
        while (fin && fin.peek() != 'Z')
        {
            n = 0;
            b1.initialize(fin);
            b1.print();
            b1.solve(n);
            avg.push_back(n);
            if (b1.isSolved())
                cout<<"Solved!"<<endl;
        }
        
        for (int i = 0; i < avg.size(); i++)
            sum += avg[i];
        cout<<"Average recursion call is "<<sum/avg.size()<<endl;
    }
    catch  (indexRangeError &ex)
    {
        cout << ex.what() << endl;
        exit(1);
    }
}
