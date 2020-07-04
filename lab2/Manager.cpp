#include "Manager.h"
#include <cstdio>

Manager::Manager(const Manager &m){
    subordinates = m.subordinates;
}

Manager& Manager::operator=(const Manager &m){
    subordinates = m.subordinates;
}

Person* Manager::AddSubordinate(Person *p){
    subordinates.push_back(p);
    return p;
}

int Manager::GetSizeOfList(){
    return subordinates.size();
}

void Manager::RecSubordById(int i, int count, int id){
    if(i < count){
        Person* per = subordinates.front();
        Employee* emp = dynamic_cast<Employee*>(per);
        subordinates.pop_front();
        if(emp->GetId() != id){
            RecSubordById(++i, count, id);
            subordinates.push_front(per);
        }
    }
}


bool Manager::Display(bool cond){
    if(cond == true){
        cout << "\nEmployee type: manager" << endl;
        cout << "id: " << id << endl;
        cout << f_name << " "<< l_name;
        cout << "  age: " << age;
        cout << " salary: " << salary << endl;
        cout << "departament: " << department << endl;
        cout << "subordinates" << endl;
        int count = subordinates.size();
        if(count == 0)
            cout << "\t\tnone\n";
        else{
            list<Person*> subTmp;
            subTmp.assign(subordinates.begin(), subordinates.end());
            flagOutputMan = true;
            for(int i = 0; i < count; i++){
                subTmp.front()->Display(true);
                subTmp.pop_front();
            }     
            flagOutputMan = false;
        }
    }
    return true;
}

void Manager::DisplaySubordinates(){
    cout << department << endl;
    cout << salary << endl;
    cout << id << endl;
    cout << f_name << endl;
    cout << l_name << endl;
    cout << age << endl;
}