//
//  testNewScore.cpp
//  Homework 1
//
//  Created by Junho Choi on 1/19/21.
//

#include "ScoreList.h"
#include <cassert>

void test(){
    ScoreList math;

    assert(math.size() == 0);
    assert(!math.remove(35));
    assert(math.minimum() == NO_SCORE);
    assert(math.maximum() == NO_SCORE);
    assert(math.add(70));

    
    ScoreList cs;
    assert(!cs.add(446));
    assert(cs.add(70));
    assert(cs.add(79));

    assert(cs.size() == 2);
    
    assert(cs.add(83));
    assert(cs.add(95));

    
    assert(cs.remove(83) && cs.size() == 3);

}
int main(){
    test();
    std::cout << "Passed all tests" << std::endl;
}
