//
// Created by evy18 on 19/12/2021.
//

#include "Stack.h"
using std::vector;

Stack::Stack ()=default;


Stack::Stack (std::vector<std::pair<double, double>> coordinates){
    //a loop to insert every pair to the stack
    for (const auto &pair: coordinates){
        Apartment my_apartment = Apartment(pair);
        this->stack.push_back(my_apartment);
    }
}

void Stack::push (const Apartment &apartment){
    this->stack.push_back(apartment);
}

void Stack::pop (){
    if (this->stack.empty()){
        throw std::out_of_range(EMPTY_STACK);
    }
    this->stack.pop_back();
}

bool Stack::empty () const{
    return this->stack.empty();
}

size_t Stack::size () const{
    return this->stack.size();
}

Apartment& Stack::top (){
    if (this->stack.empty()){
        throw std::out_of_range(EMPTY_STACK);
    }
    return this->stack.back();
}

Apartment Stack::top () const{
    if (this->stack.empty()){
        throw std::out_of_range(EMPTY_STACK);
    }
    return this->stack.back();
}

Stack::iterator Stack::begin (){
    if (this->stack.empty()){
        throw std::out_of_range(EMPTY_STACK);
    }
    return this->stack.rbegin();
}

Stack::const_iterator Stack::begin () const{
    if (this->stack.empty()){
        throw std::out_of_range(EMPTY_STACK);
    }
    return this->stack.rbegin();
}

Stack::const_iterator Stack::cbegin() const {
    if (this->stack.empty()){
        throw std::out_of_range(EMPTY_STACK);
    }
    return this->stack.crbegin();
}

Stack::iterator Stack::end(){
    if (this->stack.empty()){
        throw std::out_of_range(EMPTY_STACK);
    }
    return this->stack.rend();
}

Stack::const_iterator Stack::end() const{
    if (this->stack.empty()){
        throw std::out_of_range(EMPTY_STACK);
    }
    return this->stack.rend();
}

Stack::const_iterator Stack::cend() const {
    if (this->stack.empty()){
        throw std::out_of_range(EMPTY_STACK);
    }
    return this->stack.crend();
}