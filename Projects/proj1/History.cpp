//
//  History.cpp
//  Project 1
//
//  Created by Junho Choi on 1/8/21.
//
#include <iostream>
#include "History.h"

using namespace std;

History::History(int nRows, int nCols)
        :m_rows(nRows), m_cols(nCols){
    for(int r=0; r < nRows; ++r){
        for(int c=0; c < nCols; ++c){
            m_grid[r][c] = '.'; // Initialize grid with dots
        }
    }
}

bool History::record(int r, int c){
    if(r >= 0 && r < m_rows &&
       c >= 0 && c < m_cols){
        if(m_grid[r][c] == '.')
            m_grid[r][c] = 65; // set to A
        else if(m_grid[r][c] < 90)
            m_grid[r][c]++; // if less than Z, increment
        return true;
    }
    return false;
}

void History::display() const{
    clearScreen();
    for(int r=0; r < m_rows; ++r){
        for(int c=0; c < m_cols; ++c){
            cout << m_grid[r][c];
        }
        cout << endl;
    }
    cout << endl;
}
