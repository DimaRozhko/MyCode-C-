#include "CDepot.h"

int main(){
    try{
        CDepot depot;
        depot.loadDataFromCSV("input.csv");
        CCar* car = new CCar(6, 0, 70, 10000, 24.3);
        depot.AddCar(car);
        CTrain* tr = new CTrain(8, 1, 90, 14000, 15.4);
        depot.AddTrain(tr);
        depot.RemoveVehicle(6);
        list<CVehicle*> rs = depot.SQL("max_distance", "le", "500");
        depot. ShowRecordSet(rs);
        CVehicle* ve = depot.VehiclesAvailable(10000, 50, 200000000);
        ve->Display();
        depot.ShowAll();
        depot.ChangeCostPerMile(1, 3.6);
        depot.ShowAll();
    }
    catch(logic_error err){
        cout << err.what() << endl;
    }
    return 0;
}