#include "CTrain.h"


void CTrain::setMax(int max){
    max_distance = max;
}

void CTrain::setType(string ty){
    type = ty;
}

double CTrain::CalculateCost(int weight, int dist){
    double cost = -1;
    if(dist < max_distance){
        cost = cost_per_mile * dist * weight;
    }
    return cost;
}

double CTrain::CalculateTime(int dist){
    double time = -1;
    if(dist >= max_distance){
        time = dist / average_speed;
    }
    return time;
}

void CTrain::Display(){
    cout << id << endl;
    cout << v_type << endl;
    cout << type << endl;
    cout << load_capacity << endl;
    cout << cost_per_mile << endl;
    cout << average_speed << endl;
    cout << max_distance << endl << endl;
}