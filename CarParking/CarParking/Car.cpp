#include "Car.h"
#include <string>
#include <iomanip>

using namespace std;

Car::Car()
{
	car_plate_number = "-";
	enter_datetime = "-";
	exit_datetime = "-";
	total_fare = 0;
}

bool Car::compareName1(Car p2)
{
	if (car_plate_number >= p2.car_plate_number)
		return true;
	return false;
}

bool Car::compareName2(Car p2)
{
	if (car_plate_number == p2.car_plate_number)
		return true;
	return false;
}

void Car::print(ostream &out)
{
	out << "\n\n\nCar Plate Number: " << car_plate_number;
	out << "\nEnter Datetime: " << enter_datetime;
	out << "\nExit Datetime: " << exit_datetime;
	out << "\nTotal Fare: " << fixed << setprecision(2) << total_fare;

}