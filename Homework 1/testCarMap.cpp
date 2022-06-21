#include "CarMap.h"
#include <iostream>
using namespace std;
#include <cassert>
#include <string>

int main() {
    CarMap m1;
    m1.addCar("Fred");
    m1.addCar("Utkarsh");
    cerr << m1.miles("Utkarsh") << endl;
    m1.drive("Fred", 330);
    m1.addCar("Apple");
    cerr << m1.drive("Utkarsh", 220) << endl;
    cerr << m1.drive("Utkarsh", 100) << endl;
    cerr << m1.drive("Putkarsh",100) << endl;
    cerr << "Utkarsh new miles :" << m1.miles("Utkarsh") << endl;
    CarMap m2;
    m2.addCar("Cole");
    cerr << "Size 2: "<< m2.fleetSize() << endl;
    cerr << "Size of 1: " << m1.fleetSize() << endl;

    m1.print();
    cerr << "-----------";
    m2.print();

}