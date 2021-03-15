//
//  Sequence.cpp
//  Project 2
//
//  Created by Junho Choi on 1/20/21.
//

#include "Sequence.h"

Sequence::Sequence()
:_head(nullptr), _size(0){} // initialize emtpy sequence

Sequence::~Sequence(){
    while(erase(0)){} // keep deleting head node until head node points to nullptr.
}

Sequence::Sequence(const Sequence& src)
:_head(nullptr), _size(0){
    ItemType val;
    
    for(int i = 0; i < src.size(); ++i){
        src.get(i, val);
        insert(i, val);
    }
}
Sequence& Sequence::operator=(const Sequence &src){
    if(this == &src) // if this and src are aliases
        return *this;
    
    /* delete each item of this */
    while(erase(0)){} // keep deleting head node until head node points to nullptr.

    ItemType val;
    /* add each item of src into this */
    for(int i = 0; i < src.size(); ++i){
        src.get(i, val);
        insert(i, val);
    }
    return *this;
    
}

bool Sequence::empty() const{return _head == nullptr;}

int Sequence::size() const{return _size;}

int Sequence::insert(int pos, const ItemType& value){
    if(pos > size() || pos < 0)
        return -1;
    else if(pos == 0){
        Node* newNode = new Node;
        newNode->value = value;
        newNode->prev = nullptr;
        if(empty()){ // if node to add is first and only node
            newNode->next = nullptr;
        }else{ // if there are more than one nodes before new node
            newNode->next = _head;
            _head->prev = newNode;
        }
        _head = newNode; // added node must become head
        
        _size++; // increment size of sequence
        return pos;
    }else{
        Node* newNode = new Node;
        newNode->value = value;

        Node* p = _head;
        for(int i = 0; i < (pos - 1); ++i){ // iterate to position one before pos
            p = p->next;
        }
        if(p != nullptr && p->next != nullptr) // if node after pos exists
            p->next->prev = newNode;
        newNode->next = p->next;
        newNode->prev = p;
        p->next = newNode;
        
        _size++; // increment size of sequence
        return pos;

    }
}

int Sequence::insert(const ItemType& value){
    if(empty()){ // if there're no nodes in list
        Node* newNode = new Node;
        newNode->value = value;
        newNode->prev = nullptr;
        newNode->next = nullptr;
        
        _head = newNode;
        
        _size++;
        return 0;
    }else{ // if there're items in list
        int index = 0; // counts index
        
        Node* p = _head;
        
        if(p != nullptr && p->value >= value) // when head value is greater
            return insert(0, value);
        while(p != nullptr){
            if(p->next == nullptr){ // if we are at the last node
                index = size();
                break;
            }
            index++;
            if(p->next->value >= value) // iterate until next value is greater than (or equal to) passed value
                break;
            p = p->next;
        }
        return insert(index, value); // use insert function to add to correct index.
    }
}

bool Sequence::erase(int pos){
    if(pos >= size() || pos < 0)
        return false;
    else if(empty()) // if there are no items
        return false;
    else if(pos == 0){ // if deleting current head node
        Node* deleteNode = _head;
        _head = deleteNode->next;
        if(_head != nullptr) // if there are more than one item before deletion
            _head->prev = nullptr;
        
        _size--; // decrement size
        delete deleteNode;
        return true;
    }else{
        Node* p = _head;
        for(int i = 0; i != pos; ++i){
            p = p->next;
        }
        
        Node* deleteNode = p;
        deleteNode->prev->next = deleteNode->next; // prev node points to next next node
        if(deleteNode->next != nullptr) // if there is at least one more item after
            deleteNode->next->prev = deleteNode->prev; // next node points to prev prev node
        
        _size--;
        delete deleteNode;
        return true;
    }
}

int Sequence::remove(const ItemType& value){
    if(empty())
        return 0;
    
    int counter = 0;
    Node* p = _head;
    for (int i = 0; i < size(); ++i){ // iterate through every node in Sequence
        if(p->value == value){
            counter++;
            Node* deleteNode = p;
            if(p == _head){ // if node to be removed is at head
                if(p->next != nullptr){ // if there's more than one item
                    p->next->prev = nullptr;
                    _head = p->next;
                    p = _head;
                    delete deleteNode;
                    continue; // move to next iteration (i.e. already iterated)
                }else{ // if there's one item left
                    _head = nullptr;
                    p = nullptr;
                    delete deleteNode;
                }
            }else{
                p->prev->next = p->next;
                if(p->next != nullptr)
                    p->next->prev = p->prev;
                p = p->prev; // move p pointer back to node before deleted node
                delete deleteNode;
            }
        }
        if(p == nullptr){
            break;
        }
        p = p->next;
    }
    _size -= counter;
    return counter;
    
}

bool Sequence::get(int pos, ItemType& value) const{
    if(pos >= size() || pos < 0)
        return false;
    Node* p = _head;
    for(int i = 0; i != pos; ++i){ // iterate to appropriate position
        p = p->next;
    }
    value = p->value; // set value equal to node's value
    return true;
}

bool Sequence::set(int pos, const ItemType&value){
    if(pos >= size() || pos < 0)
        return false;
    Node* p = _head;
    for(int i = 0; i < pos; ++i){ // iterate to appropriate position
        p = p->next;
    }
    p->value = value;// set node's value equal to node
    return true;
}

int Sequence::find(const ItemType& value) const{
    Node* p = _head;
    for(int i = 0; i < size(); ++i){
        if(p->value == value) // iterate until possibly values match
            return i;
        p = p->next;
    }
    return -1;
}
void Sequence::swap(Sequence& other){
    // swap head
    Node* tempHead = this->_head;
    this->_head = other._head;
    other._head = tempHead;
    
    // swap size
    int tempSize = this->_size;
    this->_size = other._size;
    other._size = tempSize;
}

void Sequence::dump() const{
    std::cerr << "(";
    for(Node* p = _head; p != nullptr; p = p->next){
        std::string comma = (p->next != nullptr) ? "," : "";
        std::cerr << p->value << comma;
    }
    std::cerr << ")" << std::endl;
}

int subsequence(const Sequence& seq1, const Sequence& seq2){
    if(seq2.size() > seq1.size() || seq1.size() == 0 || seq2.size() == 0) // check for initial conditions
        return -1;
    int index;
    
    ItemType val1;
    ItemType val2;
    for(int i = 0; i < seq1.size(); ++i){ // iterate through seq1
        index = 0;
        // get values of seq1 and seq2
        seq1.get(i, val1);
        seq2.get(0, val2);
        if(val1 == val2){
            index = 1; // check values starting from second node in seq2
            for(int j = i + 1; index < seq2.size(); ++j, ++index){ // iterate through seq2
                if(!seq1.get(j, val1))
                    return -1;
                
                seq2.get(index, val2);
                if(val1 != val2){ // go to next node in seq1 if a value doesn't equal each other
                    break;
                }
            }
            if(index == seq2.size()) // if values matched for all values of seq2
                return i;
        }
    }
    
    return -1;
}

void interleave(const Sequence& seq1, const Sequence& seq2, Sequence& result){
    // make copies of seq1 and seq2 in case that result aliases one of them
    Sequence seq1_copy(seq1);
    Sequence seq2_copy(seq2);
    
    
    // delete all existing items in result
    while(result.erase(0)){}
    
    // get smaller size of the 2 sequences
    int minSize = seq1_copy.size();
    ItemType val;
    
    if(minSize > seq2_copy.size())
        minSize = seq2_copy.size();
    
    int index = 0;
    for(int i = 0; i < minSize; ++i){
        // insert seq1 item
        seq1_copy.get(i, val);
        result.insert(index, val);
        index++;
        
        // insert seq2 item
        seq2_copy.get(i, val);
        result.insert(index, val);
        index++;
    }

    if(seq1_copy.size() > seq2_copy.size()){ // if seq1 has items left over
        int size = seq1_copy.size();
        for(int i = minSize; i < size; ++i){
            seq1_copy.get(i, val);
            result.insert(index, val);
            index++;
        }
    }else if (seq1_copy.size() < seq2_copy.size()){ // if seq2 has items left over
        int size = seq2_copy.size();
        for(int i = minSize; i < size; ++i){
            seq2_copy.get(i, val);
            result.insert(index, val);
            index++;
        }
    }
}
