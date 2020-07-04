#pragma once
#ifndef _STRING_H_
#define _STRING_H_
#include <iostream>
#define NPOS 1024 

using namespace std;

class String{
    friend bool operator==(String&, String&);
private:   
    char* str;
    size_t len, inflen;
public:
    explicit String();
    String(size_t, char);
    String(const String&, size_t, size_t  count = NPOS);
    String(const char*);
    String(const String&);
    size_t size()const;
    String& operator=(const String&);
    String& operator=(const char*);
    String& operator=(char);
    String& operator+=(const String&);
    String& operator+=(const char* s);
    void print()const;
    void resize(size_t);
    void swap(String&);
    size_t find(const String&, size_t pos = 0)const;
    size_t find_first_of(const char*, size_t, size_t)const;
    size_t find_first_not_of(const char*, size_t, size_t)const;
    size_t find_last_not_of(const char*, size_t, size_t)const;
    size_t rfind(const String&, size_t pos = NPOS)const;
    String& append(const String&, size_t, size_t);
    void resize(size_t, char);
    ~String();
};

#endif // !_STRING_H_
