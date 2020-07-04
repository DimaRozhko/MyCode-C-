/*******************************************
*file: Bus.cpp
*last modified: 01.05.2020
*********************************************/
#include "Bus.h"

ostream& operator<<(ostream& stream, Bus &obj){
    return stream << "\t|" << obj.bus_number << "\t|" << obj.driver << "\t|" << obj.route_number << "\t|" << endl;
}

bool operator==(Bus& obj1, Bus& obj2){
    if(strcmp(obj1.bus_number, obj2.bus_number) == 0 &&
        strcmp(obj1.driver, obj2.driver) == 0 &&
        strcmp(obj1.route_number, obj2.route_number) == 0)
        return true;
    else return false;
}

char* Bus::GetRouteNum(){
    return route_number;
}

char* Bus::GetBusNum(){
    return bus_number;
}

char* Bus::GetDriver(){
    return driver;        
}

void Bus::setDriver(const char* drv){
    strcpy(this->driver, drv);
}

void Bus::setAllFields(string str){
    bus_number = new char[225];
    driver = new char[225];
    route_number = new char[225];
    string strTmp;
    strTmp = str;
    strTmp.resize(strTmp.find_first_of(';'));
    strcpy(bus_number, strTmp.c_str());
    str.erase(0, str.find_first_of(';') + 1);
    strTmp = str;
    strTmp.resize(strTmp.find_first_of(';'));
    strcpy(driver, strTmp.c_str());
    str.erase(0, str.find_first_of(';') + 1);
    strTmp = str;
    strcpy(route_number, strTmp.c_str());
}