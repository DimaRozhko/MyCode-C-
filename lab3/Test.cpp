/*******************************************
*file: Test.cpp
*last modified: 01.05.2020
*********************************************/
#include "List.h"

int main(){
    try{
        List<Bus> inPark(1,true);                   // empty list bus in park
        // // Default constructor exist, but it create number of bus park and condition flag
        // // to check buses on the way to the park. 
        // // If flag is "true", list contains buses in park, else buses in way
        inPark.load("input.csv");                   // load data from file
        Bus* objNode = new Bus(); 
        objNode->setAllFields("1547;George;A103");  // initialisation all fields "Bus" 
        inPark.push_front(*objNode);                // add object to list
        inPark.Print();                             // print list
        inPark.PrintFindBus("F216");                // find and print all bus on the route "F216"
        inPark.changeNameByNumBus("0010", "Frank"); // change driver by the bus number
        inPark.Print();                  
        List<Bus> inWay(1,false);                   // empty list bus in way
        List<Bus>::iterator it;
        it = inPark.begin();                        // take iterator first node of list
        inPark.splice(it, inWay);                   // replace node form park to way
        it = inPark.end();                          // take iterator last node of list
        inPark.splice(it, inWay);
        objNode->setAllFields("0001;John;F317");
        it = inPark.find(*objNode);                 // find "objNode" in park
        inPark.splice(it, inWay);
        inWay.Print();
        inPark.Print();
        it = inWay.end();
        inWay.splice(it, inPark);                   // replace node form way to park
        inWay.Print();
        inPark.Print();
        objNode->setAllFields("0011;James;A720");
        inPark.remove(*objNode);
        inPark.Print();
        cout << "Size \"inWay\": " << inWay.size() << endl;
        cout << "Size \"inPark\": " << inPark.size() << endl;
        if(inWay.empty() == true)
            cout << "Empty \"inWay\"" << endl;
        else cout << "No empty \"inWay\"" << endl;
        if(inPark.empty() == true)
            cout << "Empty \"inPark\"" << endl;
        else cout << "No empty \"inPark\"" << endl;
        inWay.clear();
        inPark.clear();
        if(inWay.empty() == true)
            cout << "Empty \"inWay\"" << endl;
        else cout << "No empty \"inWay\"" << endl;
        if(inPark.empty() == true)
            cout << "Empty \"inPark\"" << endl;
        else cout << "No empty \"inPark\"" << endl;
        inWay.Print();
        inPark.Print();
        delete objNode;
    }
    catch(logic_error err){
        cout << err.what() << endl;
    }
    catch(runtime_error err){
        cout << err.what() << endl;
    }
    return 0;
}
