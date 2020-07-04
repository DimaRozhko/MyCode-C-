#pragma once
#ifndef __DEPOT_H__
#define __DEPOT_H__
#include "CCar.h"
#include "CTrain.h"
#include <list>


class CDepot {//add whatever you need

public:
	bool loadDataFromCSV(string path) ;
	CVehicle* AddCar(CCar* truck);
	CVehicle* AddTrain(CTrain* train); 
	void RemoveVehicle(int id);
	void ShowAll();
	list<CVehicle*>  FindCheapest(double weight, double dist); 
	list<CVehicle*> SQL(const char *field, const char * cond, const char* value);
	void ShowRecordSet(list<CVehicle*> rs);
	CVehicle* VehiclesAvailable(double weight, double dist, double cost);
	void ChangeCostPerMile(int id, double new_cost);

	 
private:
	list<CVehicle*> vehicles;
};

#endif