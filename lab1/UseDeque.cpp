#include "Deque.h"

int main(){
    int v[] = {1, 5, 6, 8};
    Deque obj1, obj2(5,8), obj3(obj2), obj4(v, 4, 10);
    try{
        obj1.print();
        obj2.print();
        obj3.print();
        obj4.print();
        obj1 = obj4;
        obj1.print();
        cout << "NUM ELEM 'obj1':\t" << obj1.size() << endl;
        cout << "CAPACITY 'obj1':\t" << obj1.capacity() << endl;
        cout << "INDEX 2  'obj1':\t" << obj1.at(2) << endl;
        const int& el1 = static_cast<const int&>(obj1.const_front());
        printf("FIRST ELEM 'obj1':\t%d\n", el1);
        obj1.print();
        int& el2 = static_cast<int&>(obj1.back());
        el2 = 48;
        printf("LAST ELEM 'obj1':\t%d\n", el2);
        obj1.print();
        cout << "FIRST ELEM 'obj1':\t" << el2 << endl;
        obj1.pop_front();
        obj1.print();
        obj1.push_front(35);
        obj1.print();
        obj1.pop_back();
        obj1.print();
        obj1.push_back(65);
        obj1.print();
        obj1.eraze(2);
        obj1.print();
        obj1.push_front(85);
        obj1.push_front(5);
        obj1.push_front(75);
        obj1.push_front(65);
        obj1.push_front(95);
        obj1.push_front(85);
        obj1.print();
        obj1.eraze(4, 6);
        obj1.print();
        obj1.sort();
        obj1.print();
        obj1.reverse();
        obj1.print();
        obj1.swap(obj4);
        obj1.print();
        obj4.print();
        obj4.reserve(10);
        obj4.print();
        obj4.push_back(6);
        obj4.push_back(6);
        obj4.push_back(6);
        obj4.print();
        obj4.assign(3, 6);
        obj4.print();
        obj4.assign(obj1);
        obj4.print();
        int sum(obj1);
        cout << "SUM OF ELEM  'obj1':\t" << sum << endl; 
        Deque obj5(v, 4, 10), obj6(v, 4, 10);
        if(obj5 == obj6) cout << "TRUE" << endl;
        else cout << "FALSE" << endl;
    }
    catch(const exception& ex){
        cout << "ERROR: " << ex.what() << endl;
    }
    return 0; 
}