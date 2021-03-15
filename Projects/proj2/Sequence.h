//
//  Sequence.h
//  Project 2
//
//  Created by Junho Choi on 1/20/21.
//

#ifndef Sequence_h
#define Sequence_h

#include <iostream>
#include <string>
using ItemType = unsigned long;

class Sequence{
public:
    Sequence();
    Sequence(const Sequence& src);
    ~Sequence();
    Sequence& operator=(const Sequence& src);
    
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
    void dump() const;
    
private:
    struct Node{
        ItemType value;
        Node* prev;
        Node* next;
    };
    Node* _head;
    int _size;
};

int subsequence(const Sequence& seq1, const Sequence& seq2);
void interleave(const Sequence& seq1, const Sequence& seq2, Sequence& result);

#endif /* Sequence_h */
