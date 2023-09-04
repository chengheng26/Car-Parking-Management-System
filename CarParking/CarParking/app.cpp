#include <string>
#include <iostream>
#include <fstream>
#include <ctime>
#include <time.h>
#include <iomanip>

#include "List.h"

using namespace std;

List list;
int count_car = 0;
bool readfile = false;

bool ReadFile(string, List *);
bool car_enter(List *);
bool car_exit(List *);
time_t get_datetime(string);
double calc_fare(string, string);
bool calc_total_fare(List *);
bool calc_car_no(List *);
bool update_data(List *);
int menu();


int main() {

	int choice = menu();
	string input = "";

	switch (choice) {
	case 1:

		system("cls");

		cout << "\t**************************************************" << endl;
		cout << "\t|                                                |" << endl;
		cout << "\t|                   READ THE FILE                |" << endl;
		cout << "\t|                                                |" << endl;
		cout << "\t**************************************************" << endl;


		if (ReadFile("CarRecord.txt", &list) == 0) {
			system("pause");
			system("cls");
			main();
		}

		cout << "\nRead the file successfully.\n\n";

		system("pause");
		system("cls");
		main();
		break;

	case 2:

		system("cls");

		cout << "\t**************************************************" << endl;
		cout << "\t|                                                |" << endl;
		cout << "\t|           CAR ENTER THE PARKING LOT            |" << endl;
		cout << "\t|                                                |" << endl;
		cout << "\t**************************************************" << endl;

		if (car_enter(&list)) 
			cout << "\nCar enter successfully.\n\n";

		system("pause");
		system("cls");
		main();
		break;

	case 3:

		system("cls");

		cout << "\t**************************************************" << endl;
		cout << "\t|                                                |" << endl;
		cout << "\t|           CAR EXIT THE PARKING LOT             |" << endl;
		cout << "\t|                                                |" << endl;
		cout << "\t**************************************************" << endl;

		car_exit(&list);
		system("pause");
		system("cls");
		main();
		break;

	case 4:

		system("cls");

		cout << "\t**************************************************" << endl;
		cout << "\t|                                                |" << endl;
		cout << "\t|     CHECK THE TOTAL AMOUNT OF MONEY EARNED     |" << endl;
		cout << "\t|                                                |" << endl;
		cout << "\t**************************************************" << endl;

		calc_total_fare(&list);

		system("pause");
		system("cls");
		main();
		break;

	case 5:

		system("cls");

		cout << "\t***********************************************************" << endl;
		cout << "\t|                                                         |" << endl;
		cout << "\t|    COUNT THE NUMBER OF CARS PARKED IN THE PARKING LOT   |" << endl;
		cout << "\t|                                                         |" << endl;
		cout << "\t***********************************************************" << endl;

		calc_car_no(&list);

		system("pause");
		system("cls");
		main();
		break;

	case 6:

		cout << "\nAre you sure you want to exit? (Yes=1, No=0) : ";
		cin >> input;

		if (input == "1") {

			update_data(&list);
			cout << "\nThank you and have a nice day ^o^\n\n";
			system("pause");
			exit(0);
		}
		else {
			system("cls");
			main();
		}
		break;

	default:
		system("cls");
		main();

	}
}

bool ReadFile(string filename, List *list) {
	Car car;
	string temp;
	ifstream infile;
	string carNumber[100];
	infile.open(filename);

	if (readfile) {
		cout << "The file already read.\n\n";
		return false;
	}

	if (infile.fail()) {
		cout << "\nOpps! Fail to open the file. Please try again.\n\n";
		return false;
	}

	//read the file
	while (!infile.eof()) {

		for (int i = 0; i < 3; i++)
		infile >> temp;
		infile >> car.car_plate_number;

		for (int i = 0; i < 2; i++)
			infile >> temp;
		getline(infile >> ws, temp);
		car.enter_datetime = temp;


		for (int i = 0; i < 2; i++)
			infile >> temp;
		getline(infile >> ws, temp);
		car.exit_datetime = temp;


		for (int i = 0; i < 2; i++)
			infile >> temp;
		infile >> car.total_fare;


		list->insert(car);

		if (car.exit_datetime == "-") {
			count_car++;
		}

	}
	readfile = true;
	infile.close();
	return true;
}

bool car_enter(List *list) {


	Car car;
	Car car_temp;
	

	cout << "Please enter the car plate number:";

	cin >> car.car_plate_number;

	int size = list->size();

	for (int i = 1; i <= size; i++) {

		list->get(i, car_temp);
		if (car.car_plate_number == car_temp.car_plate_number && car_temp.exit_datetime == "-") {
			 //have the car with same car plate number in the parking lot
			cout << "\nOpps! There have same car plate number car in parking lot.\n\n";
			return false;
			
		}
	}

	if (count_car >= 100) {
		cout << "\nSorry. No more parking lot. Only maximum of 100 cars can be parked\n\n";
		return false;
	}

	_putenv_s("TZ", "GMT-8:00");

	time_t mytime = time(NULL);
	struct tm* mytm = localtime(&mytime);
	char* ptr = asctime(mytm);
	string s = ptr;

	car.enter_datetime = s;


	list->insert(car);

	cout << "\nThe time for now: " << car.enter_datetime;

	count_car++;

	return true;

}

bool car_exit(List *list) {

	if (list->empty()) {
		cout << "\nOpps! No car in the parking lot. \n\n";
		return false;
	}


	string car_plate_number;
	Car car;
	int size = list->size();


	cout << "Please enter the car plate number:";

	cin >> car_plate_number;


	for (int i = 1; i <= size; i++) {

		list->get(i, car);

		if (car.car_plate_number == car_plate_number && car.exit_datetime == "-") {
			
			_putenv_s("TZ", "GMT-8:00");

			time_t mytime = time(NULL);
			struct tm* mytm = localtime(&mytime);
			char* ptr = asctime(mytm);
			string s_exit_datetime = ptr;

			car.exit_datetime = s_exit_datetime;

			cout << "\n\nThe time when car enter: \t" << car.enter_datetime << endl;
			cout << "The time for now: \t\t" << car.exit_datetime << endl;

			
			car.total_fare = calc_fare(car.enter_datetime, car.exit_datetime);
		
			cout << "\nYou need to pay $" << fixed << setprecision(2) << car.total_fare << ".\n" << endl;

			list->set(i, car);

			count_car--;

			return true;
		}
		
		
	}

	cout << "\nOpps! No this car.\n\n";
	return false;

}

time_t get_datetime(string s) {

	char wday[4], month[4];
	struct tm timeStruct = {};
	
	sscanf_s(s.c_str(), "%3s %3s %d %d:%d:%d %d", wday, sizeof(wday), month, sizeof(month), &timeStruct.tm_mday,
		&timeStruct.tm_hour, &timeStruct.tm_min, &timeStruct.tm_sec, &timeStruct.tm_year);


	if (strcmp(month, "Jan") == 0) {
		timeStruct.tm_mon = 0;
	}
	if (strcmp(month, "Feb") == 0) {
		timeStruct.tm_mon = 1;
	}
	if (strcmp(month, "Mar") == 0) {
		timeStruct.tm_mon = 2;
	}
	if (strcmp(month, "Apr") == 0) {
		timeStruct.tm_mon = 3;
	}
	if (strcmp(month, "May") == 0) {
		timeStruct.tm_mon = 4;
	}
	if (strcmp(month, "Jun") == 0) {
		timeStruct.tm_mon = 5;
	}
	if (strcmp(month, "Jul") == 0) {
		timeStruct.tm_mon = 6;
	}
	if (strcmp(month, "Aug") == 0) {
		timeStruct.tm_mon = 7;
	}
	if (strcmp(month, "Sep") == 0) {
		timeStruct.tm_mon = 8;
	}
	if (strcmp(month, "Oct") == 0) {
		timeStruct.tm_mon = 9;
	}
	if (strcmp(month, "Nov") == 0) {
		timeStruct.tm_mon = 10;
	}
	if (strcmp(month, "Dec") == 0) {
		timeStruct.tm_mon = 11;
	}

	timeStruct.tm_year -= 1900;

	time_t t  = mktime(&timeStruct); // Convert to a valid tm struct

	return t;
}

double calc_fare(string t_enter, string t_exit) {

	double fare = 0;

	time_t time_enter = get_datetime(t_enter);
	time_t time_exit = get_datetime(t_exit);

	int differenceSeconds = difftime(time_exit, time_enter);
	int hours = differenceSeconds / 3600;
	int minutes = (differenceSeconds / 60) % 60;
	int total_minutes = hours * 60 + minutes;

	cout << "Parking duration: " << hours <<" hour(s) and "<< minutes<<" minute(s)"<< endl;
	
	char wday[4];
	struct tm* timeStruct_enter = localtime(&time_enter); // Convert to struct tm
	

	int year_enter = timeStruct_enter->tm_year + 1900;
	int month_enter = timeStruct_enter->tm_mon + 1;
	int day_enter = timeStruct_enter->tm_mday;
	int hour_enter = timeStruct_enter->tm_hour;
	int minute_enter = timeStruct_enter->tm_min;
	int wday_number_enter = 0;


	//convert day of week to number
	strftime(wday, sizeof(wday), "%a", timeStruct_enter);
	if (strcmp(wday, "Sun") == 0) wday_number_enter = 0;
	if (strcmp(wday, "Mon") == 0) wday_number_enter = 1;
	if (strcmp(wday, "Tue") == 0) wday_number_enter = 2;
	if (strcmp(wday, "Wed") == 0) wday_number_enter = 3;
	if (strcmp(wday, "Thu") == 0) wday_number_enter = 4;
	if (strcmp(wday, "Fri") == 0) wday_number_enter = 5;
	if (strcmp(wday, "Sat") == 0) wday_number_enter = 6;


	// Convert to struct tm
	struct tm* timeStruct_exit = localtime(&time_exit); 

	//create a time on end of the first day
	struct tm customTm = {};
	customTm.tm_year = year_enter - 1900; // Year since 1900 (e.g., 2023 - 1900)
	customTm.tm_mon = month_enter -1;   // Month (0-based)
	customTm.tm_mday = day_enter + 1; // Day
	customTm.tm_hour = 0; // Hour
	customTm.tm_min = 0;   // Minute
	customTm.tm_sec = 0;   // Second

	// Convert the custom datetime to time_t
	time_t lastmin_firstday = mktime(&customTm);
	
	//calculate the duration on first day
	int differenceSeconds_firstday = difftime(lastmin_firstday, time_enter) ;
	int hours_firstday = differenceSeconds_firstday / 3600;
	int minutes_firstday = (differenceSeconds_firstday / 60) % 60;
	int total_minutes_firstday = hours_firstday * 60 + minutes_firstday;

	//if the parking duration more than 24 hours
	if (total_minutes > 1440) {


		int days_of_weekend = 0;
		int days_of_weekday = 0;

		//if the car enter time in between office hours
		if (total_minutes_firstday > 420 && total_minutes_firstday <= 900) {

			//if first day is weekday
			if (wday_number_enter != 0 && wday_number_enter != 6) {

				if (total_minutes_firstday - 420 > 60) {
					fare += 0.2 + 0.5 + ((total_minutes_firstday - 420 - 60)*1.6 / 30);
				}
				else if (total_minutes_firstday - 420 > 30) {
					fare += 0.2 + 0.5;
				}
				else {
					fare += 0.2;
				}

				//move the day of week to nextday
				if (++wday_number_enter > 6) wday_number_enter = 0;

				total_minutes -= total_minutes_firstday;
				

				//loop if have the whole day in the duration
				while (total_minutes > 1440) {

					if (wday_number_enter != 0 && wday_number_enter != 6) {
						fare += 16 * 1.6;
						days_of_weekday++;
					}
					else days_of_weekend++;

					if (++wday_number_enter > 6) wday_number_enter = 0;
					total_minutes -= 1440;
				}


				if (wday_number_enter != 0 && wday_number_enter != 6) {
					
					//if the car exit time in between office hours
					if (total_minutes > 540 && total_minutes < 1020) {
						fare += ((total_minutes - 540) * 1.6 / 30);
					}
					//if the car enter time is after working time
					else if (total_minutes > 1020) {
						fare += 16 * 1.6;
					}

					if (timeStruct_exit->tm_hour >= hour_enter) {
						days_of_weekday++;
					}
				}
				else {
					if (timeStruct_exit->tm_hour >= hour_enter) {
						days_of_weekend++;
					}
				}

			}
			else { //if first day is weekend
		

				if (++wday_number_enter > 6) wday_number_enter = 0; //move the day of week to nextday

				total_minutes -= total_minutes_firstday;


				while (total_minutes > 1440) {
					if (wday_number_enter != 0 && wday_number_enter != 6) {
						fare += 16 * 1.6;
						days_of_weekday++;
					}
					else {
						days_of_weekend++;
					}

					if (++wday_number_enter > 6) wday_number_enter = 0; //move the day of week to nextday
					total_minutes -= 1440;
				}


				if (wday_number_enter != 0 && wday_number_enter != 6) {

					if (total_minutes > 540 && total_minutes < 1020) {
						fare += ((total_minutes - 540) * 1.6 / 30);
					}
					else if (total_minutes > 1020) {
						fare += 16 * 1.6;
					}

					if (timeStruct_exit->tm_hour >= hour_enter) {
						days_of_weekday++;
					}
				}
				else {
					if (timeStruct_exit->tm_hour >= hour_enter) {
						days_of_weekend++;
					}
				}
			}

		}
		else if (total_minutes_firstday > 900) {
			if (wday_number_enter != 0 && wday_number_enter != 6) {

				fare += 16 * 1.6;

				if (++wday_number_enter > 6) wday_number_enter = 0; //move the day of week to nextday

				total_minutes -= total_minutes_firstday;


				while (total_minutes > 1440) {
					if (wday_number_enter != 0 && wday_number_enter != 6) {
						fare += 16 * 1.6;
						days_of_weekday++;
					}
					else days_of_weekend++;

					if (++wday_number_enter > 6) wday_number_enter = 0; //move to day of week nextday
					total_minutes -= 1440;
				}


				if (wday_number_enter != 0 && wday_number_enter != 6) {

					if (total_minutes > 540 && total_minutes < 1020) {
						fare += ((total_minutes - 540) * 1.6 / 30);
					}
					else if (total_minutes > 1020) {
						fare += 16 * 1.6;
					}

					if (timeStruct_exit->tm_hour >= hour_enter) {
						days_of_weekday++;
					}
				}
				else {
					if (timeStruct_exit->tm_hour >= hour_enter) {
						days_of_weekend++;
					}
				}

			}
			else {

				if (++wday_number_enter > 6) wday_number_enter = 0; //move the day of week to nextday

				total_minutes -= total_minutes_firstday;


				while (total_minutes > 1440) {
					if (wday_number_enter != 0 && wday_number_enter != 6) {
						fare += 16 * 1.6;
						days_of_weekday++;
					}
					else {
						days_of_weekend++;
					}

					if (++wday_number_enter > 6) wday_number_enter = 0; //move the day of week to nextday
					total_minutes -= 1440;
				}


				if (wday_number_enter != 0 && wday_number_enter != 6) {

					if (total_minutes > 540 && total_minutes < 1020) {
						fare += ((total_minutes - 540) * 1.6 / 30);
					}
					else if (total_minutes > 1020) {
						fare += 16 * 1.6;
					}

					if (timeStruct_exit->tm_hour >= hour_enter) {
						days_of_weekday++;
					}
				}
				else {
					if (timeStruct_exit->tm_hour >= hour_enter) {
						days_of_weekend++;
					}
				}
			}
			
		}
		else {

			if (++wday_number_enter > 6) wday_number_enter = 0; //move the day of week to nextday

			total_minutes -= total_minutes_firstday;


			while (total_minutes > 1440) {
				if (wday_number_enter != 0 && wday_number_enter != 6) {
					fare += 16 * 1.6;
					days_of_weekday++;
				}
				else days_of_weekend++;

				if (++wday_number_enter > 6) wday_number_enter = 0; //move the day of week to nextday
				total_minutes -= 1440;
			}

			if (wday_number_enter != 0 && wday_number_enter != 6) {

				if (total_minutes > 540 && total_minutes < 1020) {
					fare += ((total_minutes - 540) * 1.6 / 30);
				}
				else if (total_minutes > 1020) {
					fare += 16 * 1.6;
				}

				if (timeStruct_exit->tm_hour >= hour_enter) {
					days_of_weekday++;
				}
			}
			else {
				if (timeStruct_exit->tm_hour >= hour_enter) {
					days_of_weekend++;
				}
			}
		}

		//charge extra $50 per day on weekday and $25 per day on weekday
		fare += days_of_weekday * 50 + days_of_weekend * 25;

	}
	else {
		if (timeStruct_exit->tm_mday != day_enter){
			
			if (total_minutes_firstday > 420 && total_minutes_firstday <= 900) {
				if (wday_number_enter != 0 && wday_number_enter != 6) {
					
					if (total_minutes_firstday - 420 > 60) {
						fare += 0.2 + 0.5 + ((total_minutes_firstday - 420 - 60)*1.6 / 30);
					}
					else if (total_minutes_firstday - 420 > 30) {
						fare += 0.2 + 0.5;
					}
					else {
						fare += 0.2;
					}

					if (++wday_number_enter > 6) wday_number_enter = 0; //move the day of week to nextday

					total_minutes -= total_minutes_firstday;


					if (wday_number_enter != 0 && wday_number_enter != 6) {

						if (total_minutes > 540 && total_minutes < 1020) {
							fare += ((total_minutes - 540) * 1.6 / 30);
						}
						else if (total_minutes > 1020) {
							fare += 16 * 1.6;
						}

					}
				}
				else {

					if (++wday_number_enter > 6) wday_number_enter = 0; //move the day of week to nextday
									   
					total_minutes -= total_minutes_firstday;


					if (wday_number_enter != 0 && wday_number_enter != 6) {

						if (total_minutes > 540 && total_minutes < 1020) {
							fare += ((total_minutes - 540) * 1.6 / 30);
						}
						else if (total_minutes > 1020) {
							fare += 16 * 1.6;
						}

					}
				}
			}
			else if (total_minutes_firstday > 900) {
				if (wday_number_enter != 0 && wday_number_enter != 6) {

					fare += 16 * 1.6;

					if (++wday_number_enter > 6) wday_number_enter = 0; //move the day of week to nextday

					total_minutes -= total_minutes_firstday;


					if (wday_number_enter != 0 && wday_number_enter != 6) {

						if (total_minutes > 540 && total_minutes < 1020) {
							fare += ((total_minutes - 540) * 1.6 / 30);
						}
						else if (total_minutes > 1020) {
							fare += 16 * 1.6;
						}

					}

				}
				else {

					if (++wday_number_enter > 6) wday_number_enter = 0; //move the day of week to nextday

					total_minutes -= total_minutes_firstday;


					if (wday_number_enter != 0 && wday_number_enter != 6) {

						if (total_minutes > 540 && total_minutes < 1020) {
							fare += ((total_minutes - 540) * 1.6 / 30);
						}
						else if (total_minutes > 1020) {
							fare += 16 * 1.6;
						}
					}
				}

			}
			else {

				if (++wday_number_enter > 6) wday_number_enter = 0; //move the day of week to nextday

				total_minutes -= total_minutes_firstday;


				if (wday_number_enter != 0 && wday_number_enter != 6) {

					if (total_minutes > 540 && total_minutes < 1020) {
						fare += ((total_minutes - 540) * 1.6 / 30);
					}
					else if (total_minutes > 1020) {
						fare += 16 * 1.6;
					}

				}
			}
		}
		else {
			if (wday_number_enter != 0 && wday_number_enter != 6) {

				if (hour_enter < 9 || (hour_enter == 9 && minute_enter == 0)) {

					if (timeStruct_exit->tm_hour >= 17) {
						fare += 16 * 1.6;
					}
					else if (timeStruct_exit->tm_hour >= 9) {

						int hours2 = timeStruct_exit->tm_hour - 9;
						int min2 = timeStruct_exit->tm_min;
						int total_min = hours2 * 60 + min2;

						fare += total_min * 1.6 / 30;

					}
					else
						return 0;


				}
				else if (hour_enter < 17 ) {

					if (timeStruct_exit->tm_hour >= 17) {
						
						//calculate the duration from car enter time to 5:00pm
						int hours2 = 17 - hour_enter;
						int min2 = 60 - minute_enter;

						if (min2 != 60) {
							hours2--;
						}
						else min2 = 0;

						int total_min = hours2 * 60 + min2;

						if (total_min > 60) {
							fare += 0.2 + 0.5 + ((total_min - 60)*1.6 / 30);
						}
						else if (total_min > 30) {
							fare += 0.2 + 0.5;
						}
						else {
							fare += 0.2;
						}


					}
					else {   //both enter/exit time is in office hours

						if (total_minutes > 60) {
							fare += 0.2 + 0.5 + ((total_minutes - 60)*1.6 / 30);
						}
						else if (total_minutes > 30) {
							fare += 0.2 + 0.5;
						}
						else {
							fare += 0.2;
						}						
					}
				}
				else
					return 0;
			}
			else
				return 0;
		}	
	}
	return fare;
}

bool calc_total_fare(List *list) {

	int year_t1;
	int month_t1;
	int day_t1;
	int hour_t1;

	int year_t2;
	int month_t2;
	int day_t2;
	int hour_t2;

	double total_fare = 0;

	cout << "To calculate total amount of money earned from T1 to T2\nPlease key in the details.\n";

	cout << "\nYear of T1 (ex:2023): ";
	cin >> year_t1;
	cout << "\nMonth of T1 (ex:1-12): ";
	cin >> month_t1;
	cout << "\nDay of T1 (ex:1-31): ";
	cin >> day_t1;
	cout << "\nHour of T1 (ex:0-23): ";
	cin >> hour_t1;

	cout << "\nYear of T2 (ex:2023): ";
	cin >> year_t2;
	cout << "\nMonth of T2 (ex:1-12): ";
	cin >> month_t2;
	cout << "\nDay of T2 (ex:1-31): ";
	cin >> day_t2;
	cout << "\nHour of T2 (ex:0-23): ";
	cin >> hour_t2;

	struct tm Tm_1 = {};
	Tm_1.tm_year = year_t1 - 1900; // Year since 1900 (e.g., 2023 - 1900)
	Tm_1.tm_mon = month_t1 - 1;   // Month (0-based)
	Tm_1.tm_mday = day_t1; // Day
	Tm_1.tm_hour = hour_t1; // Hour
	Tm_1.tm_min = 0;   // Minute
	Tm_1.tm_sec = 0;   // Second

	struct tm Tm_2 = {};
	Tm_2.tm_year = year_t2 - 1900; // Year since 1900 (e.g., 2023 - 1900)
	Tm_2.tm_mon = month_t2 - 1;   // Month (0-based)
	Tm_2.tm_mday = day_t2; // Day
	Tm_2.tm_hour = hour_t2; // Hour
	Tm_2.tm_min = 0;   // Minute
	Tm_2.tm_sec = 0;   // Second

	// Convert the custom datetime to time_t
	time_t Time_1 = mktime(&Tm_1);
	time_t Time_2 = mktime(&Tm_2);

	Car car;

	for (int i = 1; i <= (list->size()); i++) {
		list->get(i, car);

		time_t Time_exit = get_datetime(car.exit_datetime);

		if (Time_exit < Time_2 && Time_exit > Time_1 ) {
			total_fare += car.total_fare;
		}

	}

	cout << "\nThe total amount of money earned from T1 to T2 is $" << fixed << setprecision(2) << total_fare << endl << endl;


	return true;

}

bool calc_car_no(List *list) {

	int year_t1;
	int month_t1;
	int day_t1;
	int hour_t1;

	int year_t2;
	int month_t2;
	int day_t2;
	int hour_t2;

	int count_car_2 = 0;

	cout << "To count the number of cars parked in the parking lot from T1 to T2.\nPlease key in the details.\n";

	cout << "\nYear of T1 (ex:2023): ";
	cin >> year_t1;
	cout << "\nMonth of T1 (ex:1-12): ";
	cin >> month_t1;
	cout << "\nDay of T1 (ex:1-31): ";
	cin >> day_t1;
	cout << "\nHour of T1 (ex:0-23): ";
	cin >> hour_t1;

	cout << "\nYear of T2 (ex:2023): ";
	cin >> year_t2;
	cout << "\nMonth of T2 (ex:1-12): ";
	cin >> month_t2;
	cout << "\nDay of T2 (ex:1-31): ";
	cin >> day_t2;
	cout << "\nHour of T2 (ex:0-23): ";
	cin >> hour_t2;

	struct tm Tm_1 = {};
	Tm_1.tm_year = year_t1 - 1900; // Year since 1900 (e.g., 2023 - 1900)
	Tm_1.tm_mon = month_t1 - 1;   // Month (0-based)
	Tm_1.tm_mday = day_t1; // Day
	Tm_1.tm_hour = hour_t1; // Hour
	Tm_1.tm_min = 0;   // Minute
	Tm_1.tm_sec = 0;   // Second

	struct tm Tm_2 = {};
	Tm_2.tm_year = year_t2 - 1900; // Year since 1900 (e.g., 2023 - 1900)
	Tm_2.tm_mon = month_t2 - 1;   // Month (0-based)
	Tm_2.tm_mday = day_t2; // Day
	Tm_2.tm_hour = hour_t2; // Hour
	Tm_2.tm_min = 0;   // Minute
	Tm_2.tm_sec = 0;   // Second

	// Convert the custom datetime to time_t
	time_t Time_1 = mktime(&Tm_1);
	time_t Time_2 = mktime(&Tm_2);

	Car car;

	for (int i = 1; i <= (list->size()); i++) {
		list->get(i, car);

		time_t Time_enter = get_datetime(car.enter_datetime);
		time_t Time_exit = get_datetime(car.exit_datetime);

		if (Time_enter < Time_1 && Time_exit > Time_2 || Time_1 > Time_enter && car.exit_datetime == "-") {
			count_car_2++;
			cout << endl << car.car_plate_number;
		}

	}

	cout << "\nThe number of cars parked in the parking lot from T1 to T2 is " << count_car_2 << endl << endl;


	return true;
}

bool update_data(List *list) {

	ofstream outfile;
	Car car;

	if (list->empty()) {
		cout << "\n\nSuccessfully save the data to database.\nThe system will be closed now.\n\n";
		return false;
	}

	outfile.open("CarRecord.txt");
	if (outfile.fail())
		return false;

	for (int i = 1; i <= (list->size()); i++) {
		list->get(i, car);
		car.print(outfile);
	}

	outfile.close();

	cout << "\n\nSuccessfully save the data to database.\nThe system will be closed now.\n\n";



	return true;

}

int menu() {
	int choice;

	cout << "\t\t**************************************************" << endl;
	cout << "\t\t|                                                |" << endl;
	cout << "\t\t|                      Menu                      |" << endl;
	cout << "\t\t|                                                |" << endl;
	cout << "\t\t**************************************************" << endl;
	cout << "\n\t------------------------------------------------------------------  " << endl;
	cout << "\t|\t1.Read the file.\t\t\t\t\t | " << endl;
	cout << "\t|\t2.Car enters the parking lot.\t\t\t\t | " << endl;
	cout << "\t|\t3.Car exits the parking lot. \t\t\t\t |" << endl;
	cout << "\t|\t4.Check the total amount of money earned. \t\t | " << endl;
	cout << "\t|\t5.Count the number of cars parked in the parking lot.\t | " << endl;
	cout << "\t|\t6.Exit. \t\t\t\t\t\t | " << endl;
	cout << "\t------------------------------------------------------------------  \n" << endl;

	cout << "\nEnter your choice: ";

	cin >> choice;
	return choice;
}