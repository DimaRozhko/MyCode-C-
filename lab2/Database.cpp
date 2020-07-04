#include "Database.h"
#include <fstream>
#include <iostream>

using namespace std;

bool Database::LoadFromFile(const char* file){
    if(file == NULL) throw runtime_error("ERROR: NULL in name of file");
    ifstream fl;
    string strTmp;
    fl.open(file, ifstream::in);
    bool cond = true;
    if (fl.is_open() == false){
        cond = false;
        throw runtime_error("ERROR: file not exist");
    }
    else{
        string strTmp, name, surname, dep;
        int id, age, salary;
        bool mang; 
        Manager* mng; 
        Employee* emp;  
        Person* per;
        while (fl >> strTmp){
            mang = atoi(strTmp.c_str());
            strTmp = strTmp.erase(0, strTmp.find_first_of(';') + 1);
            id = atoi(strTmp.c_str());
            strTmp = strTmp.erase(0, strTmp.find_first_of(';') + 1);
            name = strTmp;
            name.resize(name.find_first_of(';'));
            strTmp = strTmp.erase(0, strTmp.find_first_of(';') + 1);
            surname = strTmp;
            surname.resize(surname.find_first_of(';'));
            strTmp = strTmp.erase(0, strTmp.find_first_of(';') + 1);
            age = atoi(strTmp.c_str());
            strTmp = strTmp.erase(0, strTmp.find_first_of(';') + 1);
            dep = strTmp;
            dep.resize(dep.find_first_of(';'));
            strTmp = strTmp.erase(0, strTmp.find_first_of(';') + 1);
            salary = atoi(strTmp.c_str()); 
            if(mang == false){
                emp = new Employee(name, surname, age, id);
                emp->SetDepartment(dep);
                emp->SetSalary(salary);
                per = emp;
                employees.push_back(per);
            }
            else{
                mng = new Manager(name, surname, age, id);
                mng->SetDepartment(dep);
                mng->SetSalary(salary);
                per = mng;
                employees.push_back(per);
            }        
        }
    }
    fl.close();
    return cond;
}

void Database::ArrangeSubordinates(){
    Employee* emp;
    Manager* man;
    for(int i = 0, count = employees.size(); i < count; i++){
        if(employees.at(i)->Display(false) == true){
            man = dynamic_cast<Manager*>(employees.at(i));
            for(int j = 0; j < count; j++){
                if(employees.at(j)->Display(false) == false){
                    emp = dynamic_cast<Employee*>(employees.at(j));
                    if(man->GetDepartment() == emp->GetDepartment())
                        man->AddSubordinate(employees.at(j)); 
                }
            }
            cout << endl;
        }
    }
}

Person* Database::HireEmployee(Person* p){
    if(p != NULL){
        Employee* emp = dynamic_cast<Employee*>(p);
        Manager* man;
        bool condAdd = false;
        for(int i = 0, count = employees.size(); i < count; i++){
            if(employees.at(i)->Display(false) == true){
                man = dynamic_cast<Manager*>(employees.at(i));
                if(man->GetDepartment() == emp->GetDepartment()){
                    man->AddSubordinate(p);
                    condAdd = true;
                    break;
                }
            }
        }
        employees.push_back(p);
        if(condAdd == false) p = NULL;
    }
    return p;
}

bool Database::FireEmployee(int id){
    Employee* emp;
    Manager* man;
    bool condFire = false;
    for(int i = 1, count = employees.size(); i < count; i++){
        if(employees.at(i)->Display(false) == true){
            man = dynamic_cast<Manager*>(employees.at(i));
            if(man->GetId() == id){
                employees.erase(employees.begin() + i);
                count--;
                condFire = true;
            }
            else
                man->RecSubordById(0, man->GetSizeOfList(), id);
        }
        else{
            emp = dynamic_cast<Employee*>(employees.at(i));
            if(emp->GetId() == id) {
                employees.erase(employees.begin() + i);
                count--;
                condFire = true;
            }
        }
    }
    return condFire;
}

vector<Person*> Database::SQL(const char* field, const char* cond, const char* value){
    if(field == NULL) throw runtime_error("ERROR: NULL in SQL(field ..)");
    if(cond == NULL) throw runtime_error("ERROR: NULL in SQL(..cond..)");
    if(value == NULL) throw runtime_error("ERROR: NULL in SQL(..value)");
    vector<Person*> empSQL;
    Employee* emp;
    Person* per;
    int valConvert = atoi(value);
    bool fieldCon = false, condCon = false;
    string str;
    str.assign(field);
    if(str.compare("age") != 0 && str.compare("salary") != 0)
        throw runtime_error("ERROR: uncorrect 'field' in SQL");
    if(str.compare("age") == 0) fieldCon = true;
    str.assign(cond);
    if(str.compare("le") != 0 && str.compare("ge") != 0)
        throw runtime_error("ERROR: uncorrect 'cond' in SQL");
    if(str.compare("le") == 0) condCon = true;
    for(int i = 1, count = employees.size(); i < count; i++){
        emp = dynamic_cast<Employee*>(employees.at(i));
        if(fieldCon == true){
            if(condCon == true){
                if(emp->GetAge() <= valConvert){
                    per = emp;
                    empSQL.push_back(per);
                }
            }
            else{
                if(emp->GetAge() >= valConvert){
                    per = emp;
                    empSQL.push_back(per);
                }
            }
        }
        else{
            if(condCon == true){
                if(emp->GetSalary() <= valConvert){
                    per = emp;
                    empSQL.push_back(per);
                }
            }
            else{
                if(emp->GetSalary() >= valConvert){
                    per = emp;
                    empSQL.push_back(per);
                }
            }
        }
    }
    return empSQL;
}

void Database::DisplayAll(){
    for(int i = 0, count = employees.size(); i < count; i++)
        employees.at(i)->Display(true);
    cout << "__________________________________________\n";
}

void Database::ShowRecordSet(vector<Person*> rs){
    for(int i = 0, count = rs.size(); i < count; i++)
        rs.at(i)->Display(true);
    cout << "__________________________________________\n";
}
