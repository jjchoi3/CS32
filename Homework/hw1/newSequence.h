//
//  newSequence.h
//  Homework 1
//
//  Created by Junho Choi on 1/16/21.
//

#ifndef newSequence_h
#define newSequence_h

#include <iostream>
const int DEFAULT_MAX_ITEMS = 100;

using ItemType = unsigned long;

class Sequence{
public:
    Sequence();
    Sequence(int size);
    Sequence(const Sequence& source);
    
    ~Sequence();
    
    Sequence& operator=(const Sequence& source);
    
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
    ItemType* _sequence;
    int _sequenceSize;
    int _sequenceCapacity;
};

#endif /* newSequence_h */
