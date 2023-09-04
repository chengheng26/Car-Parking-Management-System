#ifndef Car_type
#define Car_type

#include <string>

using namespace std;

struct Car
{
	string car_plate_number;
	string enter_datetime;
	string exit_datetime;
	double total_fare;


	Car();

	bool compareName1(Car); //use >=
	bool compareName2(Car); //use ==
	void print(ostream &);

};

#endif