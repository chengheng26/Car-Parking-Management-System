# Car-Parking-Management-System

In general, the system shall be able to

1.) Record car plate number when it enters the parking lot

2.) Record date and time when it enters and/or exits the parking lot 

3.) Calculate parking duration

4.) Calculate and generate bill with the parking rate mentioned below when it exits the parking lot

5.) Calculate total amount of money earned for a particular period

6.) Count the number of cars parked in the parking lot for a particular period.


Only maximum of 100 cars can be parked at any given time. The program was written in C++

## Description of the system
This system can record all the parking details such as the car plate number, the datetime of the cars enter and exit, and the total fare need to pay by driver. 

When the system starts, users need to read the 'CarRecord.txt' file to retrieve data from the database and save it to a list. Users can input the car plate number into the system, which indicates that the car is entering the parking lot. The entry time will be recorded. The system will check whether there are more than 100 cars inside the parking lot or not. Additionally, the system will verify if there is a car with the same plate number already inside. If so, the data will not be saved.

Users can input the car plate number again to indicate that the car is exiting the parking lot. If the car's entry data is not found in the database, the system will return to the main menu. Otherwise, the system will calculate the total fare that the driver needs to pay and the parking duration. These details will then be displayed on the system.
If the car exit, it can enter again the parking lot. 

User key in the period to find there have how many cars are there in the period. 

User can also key in the period to calculate the total amount of money earned for a particular period. 

When the user closes the system properly, the data in list will be update to the “CarRecord.txt” file. 

