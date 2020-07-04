#include "CCar.h"

void CCar::setMax(int max){
    max_distance = max;
}

void CCar::setMake(string str){
    make = str;
}

double CCar::CalculateTime(int dist){
    double time = -1;
    if(dist >= max_distance){
        time = dist / average_speed;
    }
    return time;
}

void CCar::Display(){
    cout << id << endl;
    cout << v_type << endl;
    cout << make << endl;
    cout << load_capacity << endl;
    cout << cost_per_mile << endl;
    cout << average_speed << endl;
    cout << max_distance << endl << endl;
}

double CCar::CalculateCost(int weight, int dist){
    double cost = -1;
    if(dist < max_distance){
        cost = cost_per_mile * dist * weight;
    }
    return cost;
}