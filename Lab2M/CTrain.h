#pragma once
#ifndef __TRAIN_H__
#define __TRAIN_H__
#include "CVahicle.h"

class CTrain: public CVehicle{
//Add here whatever you need
//. . . 
public:
	CTrain(){};
	CTrain(int _id, int _v_type, double _average_speed, double _load_capacity,
 double _cost_per_mile) : 
	CVehicle(_id, _v_type, _average_speed, _load_capacity, _cost_per_mile){};
	double CalculateCost(int weight, int dist);
	double CalculateTime(int dist);
	void Display();
	void setMax(int);
	void setType(string);
	int GetMaxDist(){return max_distance;}

protected:
	string type;//diesel / electrical
	int max_distance;// max distance without refueling if diesel

};

#endif