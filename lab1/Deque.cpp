#include "Deque.h"
#include <exception>
//g++ -Wall -pedantic-errors -Wunreachable-code -Wextra -Winit-self -Wold-style-cast -Wconversion -Wsign-conversion -g Deque.cpp UseDeque.cpp -o deque -fsanitize=address
using namespace std;

static int numId = 0;

Deque::Deque(){
    numId++;
    id = numId;
    conteiner = NULL;
    lenData = 0;
    len = 0;
}


Deque::Deque(int _Count, int _Val){
    if(_Count >= 0){
        numId++;
        id = numId;
        len = _Count;
        lenData = _Count;
        conteiner = new int[_Count];
        for(int i = 0; i < _Count; i++)
            conteiner[i] = _Val;
    }
    else throw out_of_range("INCORRECT COUNT");
}

Deque::Deque(const Deque& origin){
    numId++;
    id = numId;
    this->lenData = origin.lenData;
    this->len = origin.len;
    this->conteiner = new int[len];
    for(int i = 0; i < this->len; i++)
        this->conteiner[i] = origin.conteiner[i];
}

Deque::Deque(const int *v, int vsz, int sz){
    if(vsz >= 0 && sz >= 0){
        if(v != NULL){
            numId++;
            id = numId;
            len = sz;
            lenData = vsz;
            conteiner = new int[sz];
            int i;
            for(i = 0; i < vsz && i < sz; i++)
                conteiner[i] = v[i];
            while(i < sz)
                conteiner[i++] = 0;
            }
        else throw invalid_argument("INCORRECT NULL POINTER");
    }
    else throw out_of_range("INCORRECT SIZE");
}

Deque::~Deque(){
    delete[] conteiner;
}

Deque& Deque::operator=(const Deque& origin){
    this->lenData = origin.lenData;
    this->len = origin.len;
    this->conteiner = new int[len];
    for(int i = 0; i < this->len; i++)
        this->conteiner[i] = origin.conteiner[i];
    return *this;
}

int Deque::size(){
    return lenData;
}

int& Deque::at(int pos){
    if(pos >= 0 && pos <= len)
        return *(conteiner + pos -1);
    else throw out_of_range("INCORRECT POSITION");
}

void Deque::pop_front(){
    int* tmp = new int[--len]; 
    for(int i = 0; i < len; i++)
        tmp[i] = conteiner[i + 1];
    delete[] conteiner;
    conteiner = tmp;
    if(lenData > 0) lenData--;
}

void Deque::push_front(int elem){
    if(lenData == len) len++;
    int lenTmp = len;
    int* tmp = new int[len+1]; 
    tmp[0] = elem; 
    for(int i = 0; i < lenTmp; i++)
        tmp[i + 1] = conteiner[i];
    delete[] conteiner;
    conteiner = tmp;
    lenData++;
}

void Deque::pop_back(){
    int* tmp = new int[--len];
    lenData--; 
    for(int i = 0; i < lenData; i++)
        tmp[i] = conteiner[i];
    delete[] conteiner;
    conteiner = tmp;
}

void Deque::push_back(int elem){
    if(lenData == len) len++;
    int* tmp = new int[len]; 
    for(int i = 0; i < lenData; i++)
        tmp[i] = conteiner[i];
    tmp[lenData] = elem;
    lenData++;
    delete[] conteiner;
    conteiner = tmp;
}

int& Deque::front(){
    return *conteiner;
}

const int& Deque::const_front(){
    return *conteiner;
}

int& Deque::back(){
    return *(conteiner + lenData - 1);
}

const int& Deque::const_back(){
    return *(conteiner + lenData - 1);
}

int Deque::capacity(){
    return len;
}

void Deque::clear(){
    delete[] conteiner;
    lenData = 0;
    conteiner = new int[len];
}

void Deque::eraze(int pos){
    if(pos >= 0 && pos <= len){
        int* tmp = new int[len - 1], i; 
        pos--;
        for(i = 0; i < pos; i++)
            tmp[i] = conteiner[i];
        for(i++ ; i < len; i++)
            tmp[i-1] = conteiner[i];
        delete[] conteiner;
        conteiner = tmp;
        if(pos < lenData) lenData--;
        len--;
    }
    else throw out_of_range("INCORRECT POSITION");
}

void Deque::eraze(int first, int last){
    if(last >= first && first >= 0 && last >=0 && first <= len && last <= len){
        len -= last - first + 1; 
        lenData -= last - first + 1;
        int* tmp = new int[len], i; 
        first--;
        for(i = 0; i < first; i++)
            tmp[i] = conteiner[i];
        for(; i < len; i++)
            tmp[i] = conteiner[last++];
        delete[] conteiner;
        conteiner = tmp;
    }
    else throw out_of_range("INCORRECT DIAPASON");
}

void Deque::sort(){
    int min, imin;
    for(int i = 0; i < lenData; i++){
        imin = i;
        for(int j = i + 1; j < lenData; j++)
            if(conteiner[imin] > conteiner[j]) imin = j;
        min = conteiner[imin];
        conteiner[imin] = conteiner[i];
        conteiner[i] = min;
    }
}

int Deque::unique(){
    int* tmp = new int[len], checkElem = conteiner[0], j = 1;
    tmp[0] = conteiner[0];
    for(int i = 1; i < len; i++){
        if(checkElem != conteiner[i]){
            tmp[j] = conteiner[i];
            j++;
        }
        checkElem = conteiner[i];
    }
    lenData = j;
    delete[] conteiner;
    conteiner = tmp;
    return len;
}

void Deque::reverse(){
    int tmp, count = lenData / 2;
    for(int i = 0; i < count; i++){
        tmp = conteiner[i];
        conteiner[i] = conteiner[lenData - i - 1];
        conteiner[lenData - i - 1] = tmp;
    }
}

void Deque::swap(Deque& other){
    if(other != (long int)NULL){
        int* tmp = other.conteiner;
        other.conteiner = this->conteiner;
        this->conteiner = tmp;
        tmp = new int;
        tmp[0] = other.len;
        other.len = this->len;
        this->len = tmp[0];
        tmp[0] = other.lenData;
        other.lenData = this->lenData;
        this->lenData = tmp[0];
        delete tmp;
    }
    else throw invalid_argument("INCORRECT NULL POINTER");
}

void Deque::reserve(int size){
    if(size >= 0){
        int* tmp = new int[size];
        for(int i = 0; (i < lenData) && (i < size); i++)
            tmp[i] = conteiner[i];
        delete[] conteiner;
        conteiner = tmp;
        len = size;
        if(size < lenData) lenData = size;
    }
    else throw out_of_range("INCORRECT SIZE");
}

void Deque::assign(int count, int value){
    if(count >= 0){
        int countTmp = 0;
        for(int i = 0; i < len; i++)
            if(conteiner[i] == value) {
                if(countTmp < count) countTmp++;
                else break;
            }
        delete[] conteiner;
        lenData = countTmp;
        conteiner = new int[len];
        for(int i = 0; i < countTmp; i++)
            conteiner[i] = value;
    }
    else throw out_of_range("INCORRECT COUNT");
}

void Deque::assign(const Deque &other){
    if(other != (long int)NULL){
        delete[] conteiner;
        this->len = other.len;
        this->lenData = other.lenData;
        conteiner = new int[this->len];
        for(int i = 0; i < this->lenData; i++)
            this->conteiner[i] = other.conteiner[i];
    }
    else throw invalid_argument("INCORRECT NULL POINTER");
}

Deque::operator int() const{
    int sum = 0;
    for(int i = 0; i < lenData; i++) sum += conteiner[i];
    return sum;
}


bool Deque::operator==(const Deque& other){
    if(lenData == other.lenData){
        bool* condTh = new bool[lenData];
        int i, j;
        for(i = 0; i < lenData; i++) condTh[i] = false;
        for(i = 0; i < other.lenData; i++){
            for(j = 0; j < lenData; j++)
                if(this->conteiner[j] == other.conteiner[i]){
                    if(condTh[j] == false){
                        condTh[j] = true;
                        break;
                    }
                }
        }
        i = 0;
        while(i < lenData && condTh[i] == true) i++;
        delete[] condTh;
        if(i == lenData) return true;
        else return false;
    }
    else return false;
}

void Deque::print()const{
    cout << "+----------------------------------------------------------------------\n";
    cout << "|>OBJ" << id << endl;
    cout << "|Conteiner:\t\t-> ";
    for(int i = 0; i < lenData; i++) cout << conteiner[i] << ' ';
    cout << endl;
    cout << "|Length:\t\t-> " << len << endl;
    cout << "|Information length:\t-> " << lenData << endl;
    cout << "+----------------------------------------------------------------------\n";
}
