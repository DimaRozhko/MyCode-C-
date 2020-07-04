#pragma once
#ifndef __DATABASE_H__
#define __DATABASE_H__
#include "Manager.h"
#include <vector>

class Database{ 
public:
	Database(){};
	~Database(){};//no need in destructor
	//creates “flat” database
    bool LoadFromFile(const char *file); // create
	//arranges "flat" database after loading from the file
	void ArrangeSubordinates();
    //hire a new employee
	Person* HireEmployee(Person *p);
	void DisplayDepartmentEmployees(string _department);	
	//fire the employee
    bool FireEmployee(int id);
	void DisplayAll();
	vector<Person*> SQL(const char *field, const char * cond, 
    const char* value);
    void ShowRecordSet(vector<Person*> rs);
    //Add here whatever you need
private:
	vector<Person*> employees;
};

#endif // !__DATABASE_H__
