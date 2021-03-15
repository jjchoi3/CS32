//
//  Sequence.cpp
//  Homework 1
//
//  Created by Junho Choi on 1/16/21.
//

#include "Sequence.h"

Sequence::Sequence(){
    _sequenceSize = 0;
}

bool Sequence::empty() const{
    return _sequenceSize == 0;
}

int Sequence::size() const{
    return _sequenceSize;
}

int Sequence::insert(int pos, const ItemType& value){
    if(pos < 0 || pos > size() || size() + 1 > DEFAULT_MAX_ITEMS)
        return -1;
    for(int i = size(); i > pos; --i){
            _sequence[i] = _sequence[i-1];
        }
        _sequence[pos] = value;
        _sequenceSize++;
    return pos;

}

int Sequence::insert(const ItemType &value){
    if(size() + 1 > DEFAULT_MAX_ITEMS)
        return -1;
    int i = 0;
    while(value > _sequence[i] && i < size()){
        ++i;
    }
    for(int j = size(); j > i; --i){
        _sequence[j] = _sequence[j-1];
    }
    _sequence[i] = value;
    _sequenceSize++;
    return i;
}

bool Sequence::erase(int pos){
    if(pos < 0 || pos >= size())
        return false;
    for(int i = pos; i < size() - 1; ++i){
        _sequence[i] = _sequence[i+1];
    }
    _sequenceSize--;
    return true;
}

 int Sequence::remove(const ItemType &value){
     int count = 0;
     for(int i = 0; i < size(); ++i){
         if(_sequence[i] == value){
             for(int j = i; j < size() - 1; ++j){
                 _sequence[j] = _sequence[j+1];
             }
             count++;
             _sequenceSize--;
         }
     }
     return count;
 }
bool Sequence::get(int pos, ItemType &value) const{
    if(pos < 0 || pos >= size())
        return false;
    value = _sequence[pos];
    return true;
}

bool Sequence::set(int pos, const ItemType& value){
    if(pos < 0 || pos >= size())
        return false;
    _sequence[pos] = value;
    return true;
}

int Sequence::find(const ItemType& value) const{
    for(int i = 0; i < size(); ++i){
        if(_sequence[i] == value)
            return i;
    }
    return -1;
}

void Sequence::swap(Sequence& other){
    int tempSize = this->_sequenceSize;
    this->_sequenceSize = other._sequenceSize;
    other._sequenceSize = tempSize;
    
    ItemType temp;
    for(int i = 0; i < DEFAULT_MAX_ITEMS; i++){
        temp = this->_sequence[i];
        this->_sequence[i] = other._sequence[i];
        other._sequence[i] = temp;
    }
}

