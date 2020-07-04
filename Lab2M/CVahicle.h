#pragma once
#ifndef __VERHICLE_H__
#define __VERHICLE_H__
#include <string>
#include <iostream>

using namespace std;
//An abstract class
class CVehicle {
public:
	CVehicle() {};
	CVehicle(int _id, int _v_type, double _average_speed, double _load_capacity,
	double _cost_per_mile) :
		average_speed(_average_speed), load_capacity(_load_capacity), 
		cost_per_mile(_cost_per_mile),
		id(_id), v_type(_v_type){};
	virtual void Display() = 0;
	//вартість перевезення weight кг на dist км
	//якщо перевезення здійснюється вантажівкою, або дізелем і dist > //max_distance повертає -1
	virtual double CalculateCost( int weight, int dist) = 0;
	// час перевезення вантажів
	//якщо перевезення здійснюється вантажівкою або дизелем і dist > //max_distance повертає -1
	virtual	double CalculateTime(int dist) = 0;
	virtual int GetId(){return id;}
	int GetType(){return v_type;}
	double GetAverSpeed(){return average_speed;}
	double GetCapacity(){return load_capacity;}
	virtual	int GetMaxDist() = 0;
	void SetCostPerMile(double c) {
		cost_per_mile = c;
	}
protected:
	int v_type;//0- car, 1 - train
	int id;
	double average_speed;
	double load_capacity;
	double cost_per_mile;//вартість перевезення 1 кг на 1 милю
};

#endif