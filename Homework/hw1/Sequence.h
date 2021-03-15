//
//  Sequence.h
//  Homework 1
//
//  Created by Junho Choi on 1/16/21.
//

#ifndef Sequence_h
#define Sequence_h

#include <iostream>
const int DEFAULT_MAX_ITEMS = 100;

using ItemType = unsigned long;

class Sequence{
public:
    Sequence();
    bool empty() const;
    int size() const;
    
    int insert(int pos, const ItemType& value);
    int insert(const ItemType& value);
    
    bool erase(int pos);
    int remove(const ItemType& value);
    
    bool get(int pos, ItemType& value) const;
    bool set(int pos, const ItemType& value);
    int find(const ItemType& value) const;
    
    void swap(Sequence& other);

    
private:
    ItemType _sequence[DEFAULT_MAX_ITEMS];
    int _sequenceSize;
};

#endif  /*Sequence_h */

