#include "String.h"
#include <exception>

using namespace std;

String::String(){
    str = NULL;
    len = 0;
    inflen = 0;
}

String::~String(){
    delete[] str;
}

String::String(size_t count, char ch){
    len = count + 1;
    inflen = count;
    str = new char[len];
    for(size_t i = 0; i < count; i++)
        str[i] = ch;
    str[count] = '\0';
}

String::String(const char* s){
    inflen = 0;
    for(int i = 0; s[i] != '\0'; i++) inflen++;
    len = inflen + 1;
    str = new char[len];
    for(size_t i = 0; i < inflen; i++)
        str[i] = s[i];
    str[inflen] = '\0';
}

String::String(const String& s){
    this->len = s.len;
    this->inflen = s.inflen;
    this->str = new char[len];
    for(size_t i = 0; i < inflen; i++)
        this->str[i] = s.str[i];
    this->str[inflen] = '\0';
}

String::String(const String& other, size_t pos, size_t  count){
    if(pos < other.size() && pos < count && pos != 0){
        inflen = count - pos;
        len = inflen + 1;  
        this->str = new char[len];
        for(size_t i = pos - 1, j = 0; i < count && j < inflen; i++, j++)
            this->str[j] = other.str[i];
        str[inflen] = '\0';
    }
    else throw out_of_range("position uncorrect");
}

size_t String::size() const{
    return inflen;
}

String& String::operator=(const String& str){
    this->len = str.len;
    this->inflen = str.inflen;
    this->str = new char[len + 1];
    for(size_t i = 0; i < inflen; i++)
        this->str[i] = str.str[i];
    this->str[inflen] = '\0';
    return *this;
}

String& String::operator=(const char* s){
    inflen = 0;
    for(int i = 0; s[i] != '\0'; i++) inflen++;
    if(inflen >= len) len = inflen + 1;
    delete[] str;
    str = new char[len];
    for(size_t i = 0; i < inflen; i++)
        str[i] = s[i];
    this->str[inflen] = '\0';
    return *this;
}

String& String::operator=(char ch){
    inflen = 1;
    delete[] str;
    str = new char[len];
    str[0] = ch;
    str[1] = '\0';
    return *this;
}

String& String::operator+=(const String& str){
    size_t inftmp = inflen, i;
    inflen += str.inflen;
    if(inflen > len) len = inflen + 1;
    char* tmp = new char[len];
    for(i = 0; i < inftmp; i++)
        tmp[i] = this->str[i];
    for(size_t j = 0; i < inflen; j++, i++)
        tmp[i] = str.str[j];
    tmp[inflen] = '\0';
    delete[] this->str;
    this->str = tmp;
    return *this;
}

String& String::operator+=(const char* s){
    size_t inftmp = inflen, i;
    for(int i = 0; s[i] != '\0'; i++) inflen++;
    if(inflen > len) len = inflen + 1;
    char* tmp = new char[len];
    for(i = 0; i < inftmp; i++)
        tmp[i] = this->str[i];
    for(size_t j = 0; i < inflen; j++, i++)
        tmp[i] = s[j];
    tmp[inflen] = '\0';
    delete[] this->str;
    this->str = tmp;
    return *this;
}

void String::print()const{
    cout << endl << ">String:\t";
    for(size_t i = 0; i < inflen; i++) cout << str[i];
    cout << endl << ">Length:\t" << len << endl;
    cout << ">Information:\t" << inflen << endl;
}

void String::resize(size_t count){
    len = count + 1;
    if(inflen > count) inflen = count;
    char* tmp = new char[len];
    for(size_t i = 0; i < inflen; i++)
        tmp[i] = str[i];
    tmp[inflen] = '\0';
    delete[] str;
    str = tmp; 
}

void String::swap(String& other){
    char* tmp = other.str;
    other.str = this->str;
    this->str = tmp;
    size_t tmpD = other.len;
    other.len = this->len;
    this->len = tmpD;
    tmpD = other.inflen;
    other.inflen = this->inflen;
    this->inflen = tmpD;
}

bool operator==(String& lhs, String& rhs){
    size_t lenl = lhs.size();
    if(lenl == rhs.size()){
        bool flag = true;      
        for(size_t i = 0; i < lenl; i++){
            if(lhs.str[i] != rhs.str[i]){
                flag = false;
                break;
            }
        }
        return flag;
    }
    else return false;
}

size_t String::find(const String& str, size_t pos) const{
    bool flag = false;
    for(size_t i = pos, j = 0; i < inflen; i++){
        if(this->str[i] == str.str[j]) j++;
        if(j == str.inflen){
            pos = i + 2 - j;
            flag = true;
            break;
        }
    }
    if(flag == false) throw out_of_range("elem not foumd");
    return pos;
}

size_t String::find_first_of(const char* s, size_t pos, size_t count)const{
    bool flag = false;
    for(size_t i = pos - 1, j = 0; i < inflen; i++){
        while(this->str[i] == s[j] && j < count) j++;
        if(j != 0){
            pos = i + 1;
            flag = true;
            break;
        }
        j = 0;
    }
    if(flag == false) throw out_of_range("elem not foumd");
    return pos;
}

size_t String::find_first_not_of(const char* s, size_t pos, size_t count)const{
    bool flag = false;
    size_t lenl = 0;
    for(int i = 0; s[i] != '\0'; i++) lenl++;
    for(size_t i = pos - 1, j = 0; i < inflen; i++){
        while(this->str[i] != s[j] && j < count && j < lenl) j++;
        if(j == lenl){
            pos = i + 1;
            flag = true;
            break;
        }
        j = 0;
    }
    if(flag == false) throw out_of_range("elem not foumd");
    return pos;
}

size_t String::find_last_not_of(const char* s, size_t pos, size_t count)const{
    bool flag = false;
    size_t lenl = 0;
    for(int i = 0; s[i] != '\0'; i++) lenl++;
    for(size_t i = pos - 1, j = 0; i > 0; i--){
        while(this->str[i] != s[j] && j < count && j < lenl) j++;
        if(j == lenl){
            pos = i + 1;
            flag = true;
            break;
        }
        j = 0;
    }
    if(flag == false) throw out_of_range("elem not foumd");
    return pos;
}

size_t String::rfind(const String& str, size_t pos)const{
    bool flag = false;
    for(size_t i = pos - 1, j = 0; i < inflen; i++){
        if(this->str[i] == str.str[j]) j++;
        if(j == str.inflen){
            pos = i - j + 1;
            flag = true;
            j = 0;
        }
    }
    if(flag == false) throw out_of_range("elem not foumd");
    return pos;
}

String& String::append(const String& str, size_t pos, size_t count){
    if(pos < str.size()){
        size_t i;
        inflen = len + count - pos;  
        char* tmp = new char[inflen + 1];
        for(i = 0; i < len; i++) tmp[i] = this->str[i];
        if(count == 0) count = str.size(); 
        len = inflen;
        for(size_t j = pos - 1; j < count; j++, i++) tmp[i] = str.str[j];
        tmp[inflen] = '\0';
        delete[] this->str;
        this->str = tmp;
        return *this;
    }
    else throw out_of_range("position uncorrect");
}

void String::resize(size_t count, char ch){
    len = count + 1;
    if(inflen > count) inflen = count;
    char* tmp = new char[len + 1];
    size_t i;
    for(i = 0; i < inflen; i++)
        tmp[i] = str[i];
    while(i < len){
        tmp[i] = ch;
        i++;
    }
    inflen = len - 1;
    tmp[len] = '\0';
    delete[] str;
    str = tmp; 
}


