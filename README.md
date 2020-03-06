# CPP-Canteen-V2

The main goal of this project is to develop a C ++ program that simulates the operation of a “College Canteen”. The system should implement / simulate all the functionalities related to the functioning of a
canteen. In summary, the program is expected to implement features for:
* Organization by groups;
* Entrance queue at the canteen;
* Creating meals;
* Billing;
* Movement of canteen users;

### Description

The main entities of the program are the waiting list, table, students, meal and staff:
* The Entry Queue is represented by the number of students present, and by the set of students present;
* The table entity represents a table in the canteen, the table size varies between 2 and 5 seats, each table has an associated number of students and a table number. Each time the program is started, set of tables with random sizes until the maximum capacity of the canteen is filled;
* The student represents a student from the university, and is represented by the first and last name, number of student, group number, course and plafond;
* The staff entity is identified by the first and last name, number of employee, by the number of the department to which it belongs and plafond;
* The meal entity (or menu) represents the meals in the canteen each meal has an entry, main dish and total cost;

The canteen simulation is developed by cycles triggered by the user. Each time the user press the ‘s’ + ‘enter’ key a new cycle begins. In each cycle the system must do the following (in that order):
* Remove students and staff who have finished the meal;
* Charging meals to students and staff who finished the meal;
* Move students / staff from the waiting line to the canteen;
* Generate new students / staff to queue;
* In the first iteration, a meal must be created. Every 10 cycles meals should be changed, and in this case, the user is asked to enter the necessary data for the new meal;

The program also contains some interactions and options for manipulating data from users of the canteen.

### Notes

The development of this project includes:
* Use of dynamic arrays;
* Implementation of main sorting algorithms;
* Extraction of data from a text file, used to create random user names and courses;

## Authors

* **Pedro Henrique Santos Sousa**
