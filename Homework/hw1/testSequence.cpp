//
//  main.cpp
//  Homework 1
//
//  Created by Junho Choi on 1/15/21.
//

#include "Sequence.h"
#include <cassert>
void test(){
    Sequence s;
    assert(s.empty());
    assert(s.find(42) == -1);
    assert(s.insert(42) == 0);
    assert(s.size() == 1  &&  s.find(42) == 0);
}

int main(){
    test();
    std::cout << "Passed all tests" << std::endl;
}
