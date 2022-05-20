// This program calculates the user's pay
#include <iostream>

using namespace std;

int main(){
	double months, rate, pay;

	// Get the number of hours worked
	cout << "How many months did you work? ";
	cin >> months;

	// Get the hourly pay rate
	cout << "How much do you get paid per hour? ";
	cin >> rate;

	// Calculate the pay
	pay = rate * 40 * 4 * months;

	// Display the pay
	cout << "You have earned $" << pay << endl;
	return 0;
}