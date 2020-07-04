#include <iostream>
#include "String.h"

int main(){
    String o1, o2(5, 'a'), o3("asdfghjk"), o4(o3);
    try{
        o1.print();
        o2.print();
        o3.print();
        o4.print();
        o1 = o3;
        o1.print();
        o1 = 's';
        o1.print();
        o1 = "afdadspoo";
        o1.print();
        o1 += o3;
        o1.print();
        o2 += "25y";
        o2.print();
        o1.resize(10);
        o1.print();
        o1.swap(o2);
        o2.print();
        o1.print();
        o3 = o4;
        if(o3 == o4)
            cout << "true" << endl;
        else cout << "false" << endl; 
        cout << endl << o1.find("25") << endl;
        cout << o1.find_first_of("a2g", 4, 3) << endl;
        cout << o1.find_first_not_of("a2g", 4, 3) << endl;
        cout << o1.find_last_not_of("2g", 6, 10) << endl;
        String o5("25fvgbhn");
        o3 = o1.append(o5, 1, 4);
        o1.print();
        o3.print();;
        cout << o1.rfind("25", 1) << endl;
        o1.resize(15, 's');
        o1.print();
        String o6(o5, 1, 6);
        o6.print();
    }
    catch(const exception& xp){
        cout << "ERROR: " << xp.what() << endl;
    }
    return 0; 
}