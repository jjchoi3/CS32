//
//  testnewSequence.cpp
//  Homework 1
//
//  Created by Junho Choi on 1/16/21.
//


#include "newSequence.h"
#include <cassert>

void test(){
    Sequence a;
    assert(a.empty());
    assert(a.size() == 0);
    assert(a.find(42) == -1);
    assert(a.insert(42) == 0);

    assert(a.insert(57) == 1);
    assert(a.find(42) == 0);
    
    Sequence b = a;
    assert(b.find(42) == 0);

    assert(a.size() == b.size());
    assert(a.find(57) == b.find(57));

    Sequence g;

    for (int i = 0; i < DEFAULT_MAX_ITEMS; ++i){
      g.insert(i);
    }
    
    assert(g.insert(12) == -1);
    assert(g.insert(3,13) == -1);


}
int main(){
    test();
    std::cout << "Passed all tests" << std::endl;
}
