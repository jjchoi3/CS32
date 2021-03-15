//
//  ScoreList.cpp
//  Homework 1
//
//  Created by Junho Choi on 1/16/21.
//

#include "ScoreList.h"

ScoreList::ScoreList(){}
bool ScoreList::add(unsigned long score){
    if(score < 0 || score > 100 || sequence.size() == 150)
        return false;
    
    return (sequence.insert(score) == -1 ? false : true);
}

bool ScoreList::remove(unsigned long score){
    int pos = sequence.find(score);
    if(pos == -1)
        return false;
    else
        sequence.erase(pos);
    return true;
}

int ScoreList::size() const{return sequence.size();}

unsigned long ScoreList::minimum() const{
    for(int i = 0; i <= 100; ++i){
        if(sequence.find(i) != -1)
            return i;
    }
    return NO_SCORE;
}

unsigned long ScoreList::maximum() const{
    for(int i = 100; i >= 0; --i){
        if(sequence.find(i) != -1)
            return i;
    }
    return NO_SCORE;
}

