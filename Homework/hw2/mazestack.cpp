//
//  mazestack.cpp
//  Homework 2
//
//  Created by Junho Choi on 2/2/21.
//

#include <iostream>
#include <stack>
#include <string>

using namespace std;

class Coord{
public:
    Coord(int rr, int cc) : m_row(rr), m_col(cc) {}
    int r() const {return m_row;}
    int c() const {return m_col;}
private:
    int m_row;
    int m_col;
};

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec){
    stack<Coord> coordStack;
    coordStack.push(Coord(sr, sc));
    maze[sr][sc] = '#'; // set starting position as visited
    while(!coordStack.empty()){
        Coord top = coordStack.top(); // get top of stack
        coordStack.pop(); // pop the top
        if(top.r() == er && top.c() == ec) // check if at ending point
            return true;

        /* North */
        if(top.r() - 1 >= 0 && maze[top.r() - 1][top.c()] == '.'){
            coordStack.push(Coord(top.r() - 1, top.c())); // push onto stack
            maze[top.r() - 1][top.c()] = '#'; // mark as visited
        }
        /* East */
        if(top.c() + 1 < nCols && maze[top.r()][top.c() + 1] == '.'){
            coordStack.push(Coord(top.r(), top.c() + 1));
            maze[top.r()][top.c() + 1] = '#';
        }
        /* South */
        if(top.r() + 1 < nRows && maze[top.r() + 1][top.c()] == '.'){
            coordStack.push(Coord(top.r() + 1, top.c()));
            maze[top.r() + 1][top.c()] = '#';
        }
        /* West */
        if(top.c() - 1 >= 0 && maze[top.r()][top.c() - 1] == '.'){
            coordStack.push(Coord(top.r(), top.c() - 1));
            maze[top.r()][top.c() - 1] = '#';
        }
    }
    return false; // return false if stack is empty and end pos is never reached
}
