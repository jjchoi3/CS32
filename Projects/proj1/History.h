//
//  History.h
//  Project 1
//
//  Created by Junho Choi on 1/8/21.
//

#include "globals.h"

#ifndef History_h
#define History_h

class History{
public:
    History(int nRows, int nCols);
    bool record(int r, int c);
    void display() const;
private:
    char m_grid[MAXROWS][MAXCOLS];
    int m_rows;
    int m_cols;
};

#endif /* History_h */
