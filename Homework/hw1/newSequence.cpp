//
//  newSequence.cpp
//  Homework 1
//
//  Created by Junho Choi on 1/16/21.
//

#include "newSequence.h"
#include <cstdlib>

Sequence::Sequence(){
    _sequence = new ItemType[DEFAULT_MAX_ITEMS];
    _sequenceSize = 0;
    _sequenceCapacity = DEFAULT_MAX_ITEMS;
}

Sequence::Sequence(int size){
    if(size < 0){
        std::cout << "Sequence sizes cannot be negative." << std::endl;
        exit(1);
    }
    _sequence = new ItemType[size];
    _sequenceSize = 0;
    _sequenceCapacity = size;
}

Sequence::~Sequence(){
    delete [] _sequence;
}
Sequence::Sequence(const Sequence& source){
    this->_sequence = new ItemType[source._sequenceSize];
    for(int i = 0; i < source._sequenceSize; ++i){
        this->_sequence[i] = source._sequence[i];
    }
    this->_sequenceSize = source._sequenceSize;
    this->_sequenceCapacity = source._sequenceCapacity;
}

Sequence& Sequence::operator=(const Sequence& source){
    if(this == &source)
        return *this;
    delete [] this->_sequence;
    
    this->_sequence = new ItemType[source._sequenceSize];
    for(int i = 0; i < source._sequenceSize; ++i){
        this->_sequence[i] = source._sequence[i];
    }
    this->_sequenceSize = source._sequenceSize;
    this->_sequenceCapacity = source._sequenceCapacity;
    return *this;
}

bool Sequence::empty() const{
    return _sequenceSize == 0;
}

int Sequence::size() const{
    return _sequenceSize;
}

int Sequence::insert(int pos, const ItemType &value){
    if(pos < 0 || pos > size() || size() + 1 > _sequenceCapacity)
        return -1;
    for(int i = size(); i > pos; --i){
            _sequence[i] = _sequence[i-1];
        }
        _sequence[pos] = value;
        _sequenceSize++;
    return pos;

}

int Sequence::insert(const ItemType &value){
    if(size() + 1 > _sequenceCapacity)
        return -1;
    int i = 0;
    while(value > _sequence[i] && i < size()){
        ++i;
    }
    for(int j = size(); j > i; --j){
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
    ItemType* temp = this->_sequence;
    this->_sequence = other._sequence;
    other._sequence = temp;
    
    int tempSize = this->_sequenceSize;
    this->_sequenceSize = other._sequenceSize;
    other._sequenceSize = tempSize;
    
    int tempCap = this->_sequenceCapacity;
    this->_sequenceCapacity = other._sequenceCapacity;
    other._sequenceCapacity = tempCap;
}
