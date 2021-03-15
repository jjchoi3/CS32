//
//  mazequeue.cpp
//  Homework 2
//
//  Created by Junho Choi on 2/2/21.
//
#include <iostream>
#include <string>
#include <queue>

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
    queue<Coord> coordQueue;
    coordQueue.push(Coord(sr, sc));
    maze[sr][sc] = '#'; // set starting position as visited
    while(!coordQueue.empty()){
        Coord top = coordQueue.front(); // get front of queue
        coordQueue.pop(); // dequeue
        if(top.r() == er && top.c() == ec) // check if at ending point
            return true;

        /* North */
        if(top.r() - 1 >= 0 && maze[top.r() - 1][top.c()] == '.'){
            coordQueue.push(Coord(top.r() - 1, top.c())); // enqueue
            maze[top.r() - 1][top.c()] = '#'; // mark as visited
        }
        /* East */
        if(top.c() + 1 < nCols && maze[top.r()][top.c() + 1] == '.'){
            coordQueue.push(Coord(top.r(), top.c() + 1));
            maze[top.r()][top.c() + 1] = '#';
        }
        /* South */
        if(top.r() + 1 < nRows && maze[top.r() + 1][top.c()] == '.'){
            coordQueue.push(Coord(top.r() + 1, top.c()));
            maze[top.r() + 1][top.c()] = '#';
        }
        /* West */
        if(top.c() - 1 >= 0 && maze[top.r()][top.c() - 1] == '.'){
            coordQueue.push(Coord(top.r(), top.c() - 1));
            maze[top.r()][top.c() - 1] = '#';
        }
    }
    return false; // return false if queue is empty and end pos is never reached
}
