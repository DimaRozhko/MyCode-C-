#include "Database.h"

int main(){
    try{
        Database base;
        base.LoadFromFile("input.csv");
        base.ArrangeSubordinates();
        
        Employee* emp = new Employee("Bilbo", "Begins", 40, 7);
        emp->SetSalary(1000);
        emp->SetDepartment("IT");
        Person* p = emp;
        base.HireEmployee(p);
        base.FireEmployee(1);
        base.DisplayAll();
        vector<Person*> rs = base.SQL("age", "ge", "44");;
        base.ShowRecordSet(rs);
    }
    catch(logic_error err){
        cout << err.what() << endl;
    }
    catch(runtime_error err){
        cout << err.what() << endl;
    }
    return 0;
}