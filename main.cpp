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
	string filename = "bank-data.csv";
	ofstream newFile(filename);
	newFile.close();
}

bool validatePin(int pin) {
	string filename = "bank-data.csv";
	ifstream file(filename);
	string line;
	getline(file, line);
	string value;
	stringstream ss(line);
	vector < string > row;
	while(getline(ss, value, ',')) {
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

vector < string > getUserData() {
	string filename = "bank-data.csv";
	ifstream file(filename);
	string line;
	getline(file, line);
	string value;
	stringstream ss(line);
	vector < string > row;
	while(getline(ss, value, ',')) {
		row.push_back(value);
	}
	return row;
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

void printMenu() {
	system("clear");
	vector < string > userData = getUserData();
	vector < string > options = {
		{
			"1. Print balance",
			"2. Withdrawal",
			"3. Deposite",
		},
	};
	cout << endl << "*** Bank Of CPP ***" << endl;
	cout << "Hello " << userData[0] << endl << "How can we assist you today?" << endl;
	for (int i = 0; i < options.size(); ++i) {
		cout << endl << options[i] << endl;
	}
}

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
			cout << endl << "The pin you have entered is invalid, try again" << endl << endl;
			tries++;
		}
	}
	return 0;
}