#include "CarMap.h"
#include <iostream>
using namespace std;

CarMap::CarMap() {
}

bool CarMap::addCar(std::string license) {
	return m_car.insert(license, 0);
}

double CarMap::miles(std::string license) const {
	double distance = 0;
	if (m_car.contains(license) == 0)
		return -1;
	else {
		m_car.get(license, distance);
		return distance;
	}
}

bool CarMap::drive(std::string license, double distance) {
	if (distance < 0) {
		return false;
	}
	double initial_distance = 0;
	m_car.get(license, initial_distance);
	return m_car.update(license, initial_distance + distance);
}

int CarMap::fleetSize() const {
	return m_car.size();
}

void CarMap::print() const {
	for (int i = 0; i < m_car.size(); i++) {
		KeyType kk;
		ValueType vv;
		m_car.get(i, kk, vv);
		cout << kk << " " << vv << endl;
	}
}