#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

bool checkForExistingAccount() {
	string filename = "bank-data.csv";
	ifstream file(filename);
	if (!file.is_open()) {
		return false;
	} else {
		return true;
	}
}

void createAccount() {
	
}

bool validatePin(int pin) {
	string filename = "bank-data.csv";
	ifstream file(filename);
	if (!file.is_open()) {
		ofstream newFile(filename);
		newFile.close();
		return false;
	}
	string line;
	getline(file, line);
	string value;
	stringstream ss(line);
	vector < string > row;
	while(getline(ss, value, ',')) {
		cout << endl << value << endl;
		row.push_back(value);
	}
	if (row.size() > 0) {
		string storedPin = row[1];
		if (to_string(pin) == storedPin) {
			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}
	return true;
}


int getPin() {
	cout << "*** Bank of CPP ***" << endl << endl;
	bool validPin = false;
	while (validPin == false) {
		cout << "Enter your 4-digit pin: ";
		int pin;
		cin >> pin;
		if (cin.fail()) {
			cout << "Invalid pin. You must enter a 4-digit number, not including letters and special characters" << endl << endl;
			cin.clear();
			cin.ignore(numeric_limits < streamsize > ::max(), '\n');
		} else {
			string pinString = to_string(pin);
			int lengthOfPin = pinString.length();
			if (lengthOfPin == 4) {
				validPin = true;
				return pin;
			}
			cout << "Invalid pin. Please input a valid pin of 4 digits, not " << lengthOfPin << endl << endl;
		}
	}
	return 0;
}

void printMenu() {}

int main() {
	int tries = 0;
	bool runPin = true;
	bool accountExists = checkForExistingAccount();
	while (!accountExists) {
		createAccount();
	}
	while (runPin) {
		if (tries == 3) {
			cout << endl << "You're attempting your pin too many times for this session. Your account is now locked" << endl;
			return 0;
		}
		int pin = getPin();
		bool validPin = validatePin(pin);
		if (validPin) {
			printMenu();
			runPin = false;
		} else {
			cout << endl << "The pin you have entered is invalid, try again" << endl;
			tries++;
		}
	}
	return 0;
}