//
//  ScoreList.h
//  Homework 1
//
//  Created by Junho Choi on 1/16/21.
//

#ifndef ScoreList_h
#define ScoreList_h

#include <iostream>
#include "Sequence.h"
#include <limits>

const unsigned long NO_SCORE = std::numeric_limits<unsigned long>::max();

class ScoreList{
public:
    ScoreList();

    bool add(unsigned long score);
    bool remove(unsigned long score);
    int size() const;

    unsigned long minimum() const;
    unsigned long maximum() const;

private:
    Sequence sequence;
};

#endif /* ScoreList_h */
