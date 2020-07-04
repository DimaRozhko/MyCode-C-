#include "CDepot.h"
#include <fstream>
#include <iostream>

bool CDepot::loadDataFromCSV(string path){
    ifstream file;
    file.open(path, ifstream::in);
    bool isOpen = true;
    if (file.is_open() == false){
        isOpen = false;
        throw logic_error("file not exist");
    }
    else{
        string row, make_type;
        int id, v_type, max_distance;
        double average_speed, load_capacity, cost_per_mile;
        CCar* truck;
        CTrain* train;
        CVehicle* veh;
        while(file >> row){
            id = atoi(row.c_str());
            row = row.erase(0, row.find_first_of(';') + 1);
            v_type = atoi(row.c_str());
            row = row.erase(0, row.find_first_of(';') + 1);
            make_type = row;
            make_type.resize(make_type.find_first_of(';'));
            row = row.erase(0, row.find_first_of(';') + 1);
            load_capacity = atof(row.c_str());
            row = row.erase(0, row.find_first_of(';') + 1);
            cost_per_mile = atof(row.c_str());
            row = row.erase(0, row.find_first_of(';') + 1);
            average_speed = atof(row.c_str());
            row = row.erase(0, row.find_first_of(';') + 1);
            max_distance = atoi(row.c_str());
            row.clear();
            if(v_type == 0){
                truck = new CCar(id, v_type, average_speed, load_capacity,cost_per_mile);
                truck->setMake(make_type);
                truck->setMax(max_distance);
                veh = truck;
                vehicles.push_back(veh);
            }
            else{
                train = new CTrain(id, v_type, average_speed, load_capacity,cost_per_mile);
                train->setType(make_type);
                train->setMax(max_distance);
                veh = train;
                vehicles.push_back(veh);
            }
            
        }
    }
    file.close();
    return isOpen;
}

void CDepot::ShowAll(){
    if(vehicles.empty() == false){
        CVehicle* ve = vehicles.front();
        ve->Display();
        vehicles.pop_front();
        ShowAll();
        vehicles.push_front(ve);
    }
}

CVehicle* CDepot::AddCar(CCar* truck){
    if(truck == NULL) throw logic_error("uncorrect null");
    unsigned int len = vehicles.size();
    CVehicle* ve = truck;
    vehicles.push_back(ve);
    if(vehicles.size() != len + 1) ve = NULL;
    return ve;
}

CVehicle* CDepot::AddTrain(CTrain* train){
    if(train == NULL) throw logic_error("uncorrect null");
    unsigned int len = vehicles.size();
    CVehicle* ve = train;
    vehicles.push_back(ve);
    if(vehicles.size() != len + 1) ve = NULL;
    return ve;
}

void CDepot::RemoveVehicle(int id){
    if(vehicles.empty() == false){
        CVehicle* ve = vehicles.front();
        vehicles.pop_front();
        if(ve->GetId() != id){
            RemoveVehicle(id);
            vehicles.push_front(ve);
        }
    }
}

list<CVehicle*> CDepot::SQL(const char *field, const char * cond, const char* value){
    list<CVehicle*> veSQL, lstSave;
    CCar* car;
    CTrain* train;
    CVehicle* ve;
    double val = atof(value);
    bool fld = false, cnd = false;
    string str;
    str.assign(field);
    if(str != "max_distance" && str != "average_speed")
        throw logic_error("uncorrect SQL");
    if(str.compare("max_distance") == 0) fld = true;
    str.assign(cond);
    if(str != "ge" && str != "le")
        throw logic_error("uncorrect SQL");
    if(str.compare("le") == 0) cnd = true;
    while(vehicles.empty() == false){
        ve = vehicles.front();
        lstSave.push_back(ve);
        vehicles.pop_front();
        if(fld == true){
            if(ve->GetType() == 0){
                car = (CCar*)ve;
                if(cnd == false){
                    if(car->GetMaxDist() >= val)
                        veSQL.push_back(ve);
                }
                else{
                    if(car->GetMaxDist() <= val)
                        veSQL.push_back(ve);
                }
            }
            else{
                train = (CTrain*)ve;
                if(cnd == false){
                    if(train->GetMaxDist() >= val)
                        veSQL.push_back(ve);
                }
                else{
                    if(train->GetMaxDist() <= val)
                        veSQL.push_back(ve);
                }
            }
            
        }
        else{
            if(cnd == false){
                if(ve->GetAverSpeed() >= val)
                    veSQL.push_back(ve);
            }
            else{
                if(ve->GetAverSpeed() <= val)
                    veSQL.push_back(ve);
            }
        }
    }
    vehicles = lstSave;
    return veSQL;
}

void CDepot::ShowRecordSet(list<CVehicle*> rs) {
    if(rs.empty() == false){
        CVehicle* ve = rs.front();
        ve->Display();
        rs.pop_front();
        ShowRecordSet(rs);
        rs.push_front(ve);
    }
}

CVehicle* CDepot::VehiclesAvailable(double weight, double dist, double cost){
    CVehicle* ve = NULL;
    if(vehicles.empty() == false){
        CVehicle* veSave = vehicles.front();
        ve = veSave;
        // cout << weight << "\t" << ve->GetCapacity() << endl;
        // cout << cost << "\t" << ve->CalculateCost(weight,dist) << endl;
        vehicles.pop_front();
        if(weight > ve->GetCapacity() || cost < ve->CalculateCost(weight, dist)){
            ve = VehiclesAvailable(weight, dist, cost);
        }
        vehicles.push_front(veSave);
    }
    return ve;
}

void CDepot::ChangeCostPerMile(int id, double new_cost){
    if(vehicles.empty() == false){
        CVehicle* ve = vehicles.front();
        vehicles.pop_front();
        if(ve->GetId() == id)
            ve->SetCostPerMile(new_cost);
        else
            ChangeCostPerMile(id, new_cost);
        vehicles.push_front(ve);
    }
}
