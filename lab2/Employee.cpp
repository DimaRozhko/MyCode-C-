#include "Employee.h"

Employee::Employee(const Employee &e){
    department = e.department;
    salary = e.salary;
    id = e.id;
    f_name = e.f_name;
    l_name = e.l_name;
    age = e.age;
}

Employee& Employee::operator=(const Employee &e){
    department = e.department;
    salary = e.salary;
    id = e.id;
    f_name = e.f_name;
    l_name = e.l_name;
    age = e.age;
    return *this;
}

void Employee::SetSalary(int s){
    salary = s;
}

void Employee::SetDepartment(string dept){
    department = dept;
}

void Employee::SetId(int n){
    id = n;
}

int Employee::GetId(){
    return id;
}

string Employee::GetDepartment(){
    return department;
}

int Employee::GetAge(){
    return age;
}

int Employee::GetSalary(){
    return salary;
}

bool Employee::flagOutputMan = false;

bool Employee::Display(bool cond){
    if(cond == true){
        if(flagOutputMan == false){
            cout << "\nEmployee type: employee" << endl;
            cout << "id: " << id << endl;
            cout << f_name << " "<< l_name;
            cout << "  age: " << age;
            cout << " salary: " << salary << endl;
            cout << "departament: " << department << endl;
        }
        else{
            cout << "\n\t\tEmployee type: employee" << endl;
            cout << "\t\tid: " << id << endl;
            cout <<  "\t\t" << f_name << " "<< l_name;
            cout << "  age: " << age;
            cout << " salary: " << salary << endl;
            cout << "\t\tdepartament: " << department << endl;
        }
    }
    return false;
}
