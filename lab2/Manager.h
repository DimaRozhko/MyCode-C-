#pragma once
#ifndef __MANAGER_H__
#define __MANAGER_H__
#include "Employee.h"
#include <list>



class Manager : public Employee {
public:
	Manager(){};
	Manager(string _f_name, string _l_name, int _age, int _id) : 
	Employee(_f_name, _l_name, _age, _id){};
	Manager(const Manager &m);
	Manager& operator=(const Manager &m);
	virtual bool Display(bool);
	//add an employee to the subordinates list
	Person* AddSubordinate(Person *p);
	void DisplaySubordinates();
    //Add here whatever you need
	int GetSizeOfList();
	void RecSubordById(int, int, int);
private:
	list<Person*> subordinates;//список підлеглих
};

#endif // !__MANAGER_H__
