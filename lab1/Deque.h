#pragma once
#ifndef _DEQUE_H_
#define _DEQUE_H_
#include <iostream>

using namespace std;

class Deque{
private:   
    int* conteiner, len, lenData, numCurObj, id;
public:
    Deque();
    Deque(int, int);
    Deque(const Deque&);
    Deque(const int *, int, int);
    Deque& operator=(const Deque&);
    int& at(int);
    void pop_front();
    void push_front(int);
    void pop_back();
    void push_back(int);
    int & front();
    const int & const_front();
    int & back();
    const int & const_back();
    int capacity();
    void clear();
    void eraze(int);
    void eraze(int, int);
    void sort();
    int size();
    int unique();
    void reverse();
    void swap(Deque&);
    void reserve(int);
    void assign(int, int);
    void assign(const Deque&);
    operator int() const;
    bool operator==(const Deque &);
    void print()const;
    ~Deque();
};


#endif // !_DEQUE_H_
