#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

bool getData(int pin) {
	string filename = "bank-data.csv";
	ifstream file(filename);
	if (!file.is_open()) {
		cerr << "We can't open our files at this time, please come back later" << endl;
		return false;
	}
	if (file.is_open()) {
		cout << "File open";
	}
	string line;
	while (getline(file, line)) {
		vector < string > row;
		stringstream ss(line);
		string value;
		cout << line << endl;
	}
	return false;
}

int initialize() {
	cout << "*** Bank of CPP *** " << endl << endl;
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

int main() {
	int pin = initialize();
	bool getData(pin);
	return 0;
}