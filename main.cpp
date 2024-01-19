#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <cstdio>
using namespace std;

void printMenu();
int main();

vector < string > getUserData() {
	string filename = "bank-data.csv";
	ifstream file(filename);
	if (!file.is_open()) {
		throw runtime_error("We are unable to open your files");
	}
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

void writeToFileInfo(vector < string > rows) {
	string filename = "bank-data.csv";
	ofstream file(filename);
	if (!file.is_open()) {
		throw runtime_error("We are unable to open our files");
		return;
	}
	ostringstream combinedRowsString;
	for (const auto& str: rows) {
		combinedRowsString << str << ",";
	}
	string finalString = combinedRowsString.str();
	if (finalString.empty()) {
		throw runtime_error("Something went wrong writing to our files, please try again later");
		return;
	}
	if (!finalString.empty()) {
		finalString.pop_back();
	}
	file << finalString;
	file.close();
	system("clear");
	cout << "Your account has been updated" << endl << endl;
	printMenu();
	return;
}

void printBalance() {
	system("clear");
	vector < string > rows = getUserData();
	string balance = rows[2];
	cout << "Your current balance is: " << balance << endl << endl;
	printMenu();
}

void withdrawalOrDeposite(bool operation) {
	vector < string > rows = getUserData();
	string balanceString = rows[2];
	cout << "Your current balance is " << balanceString << endl;
	balanceString.erase(remove(balanceString.begin(), balanceString.end(), '$'), balanceString.end());
	double currentBalance = stod(balanceString);
	double amount;
	cout << endl << "How much would you like to " << (operation ? "deposite? ": "withdrawal? ") << endl << endl << "Amount: ";
	cin >> amount;
	if (cin.fail()) {
		cin.clear();
		cin.ignore(numeric_limits < streamsize > ::max(), '\n');
		system("clear");
		cout << "Please enter a valid amount to " << (operation ? "deposite ": "withdrawal ") << "from your account" << endl << endl;
		withdrawalOrDeposite(operation);
	}
	double newAmount = operation ? currentBalance + amount:
	currentBalance - amount;
	if (!operation && newAmount < 0) {
		system("clear");
		cout << "You cannot withdrawal this amount from your account. You have insufficient funds" << endl << endl;
		withdrawalOrDeposite(operation);
	} else {
		int answer;
		bool confirmed = false;
		while (!confirmed) {
			cout << endl << "confirm you want to " << (operation ? "deposite ": "withdrawal ") << amount << (operation ? " to ": " from ") << "your account" << endl << endl << "Your new balance will be " << fixed << setprecision(2) << newAmount << endl << endl << "Confirm 1 for yes, 2 for no: ";
			cin >> answer;
			if (cin.fail()) {
				cin.clear();
				cin.ignore(numeric_limits < streamsize > ::max(), '\n');
				system("clear");
				cout << "Please confirm with 1 or 2." << endl << "1 for Yes" << endl << "2 for No" << endl << endl;
			} else {
				if (answer == 1) {
					vector < string > newRows = rows;
					ostringstream formattedAmount;
					formattedAmount << fixed << setprecision(2) << newAmount;
					newRows[2] = formattedAmount.str();
					try {
						writeToFileInfo(newRows);
						confirmed = true;
						return;
					} catch (const exception& e) {
						cout << endl << "Something went wrong with committing your transaction. Please give us time to fix the issue and come back later";
						confirmed = true;
					}
				}
				if (answer == 2) {
					system("clear");
					printMenu();
					return;
				}
			}
		}
	}
}

void changeName() {
	system("clear");
	vector < string > rows = getUserData();
	cout << "What would you like to change your username to?" << endl << endl;
	string newName;
	cout << "New Name: ";
	cin >> newName;
	bool confirmed = false;
	int answer;
	while (!confirmed) {
		cout << endl << "Confirm you want to change your username to " << newName << endl << endl << "Confirm 1 for yes 2 for no: ";
		cin >> answer;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(numeric_limits < streamsize > ::max(), '\n');
			system("clear");
			cout << "Please confirm with 1 or 2." << endl << "1 for Yes" << endl << "2 for No" << endl << endl;
		}
		if (answer == 1) {
			vector < string > newRows = rows;
			newRows[0] = newName;
			try {
				writeToFileInfo(newRows);
				confirmed = true;
				return;
			} catch (const exception& e) {
				cout << endl << e.what() << "Something went wrong with committing your transaction. Please give us time to fix the issue and come back later";
				confirmed = true;
			}
		} else if (answer == 2) {
			cout << endl << "Okay, canceling.. ";
			confirmed = true;
			return;
		} else {
			system("clear");
			cout << "Please confirm with 1 or 2." << endl << "1 for Yes" << endl << "2 for No" << endl << endl;
		}
	}
}

void changePin() {
	system("clear");
	vector < string > rows = getUserData();
	cout << "What would you like to change your pin to? It must be a 4-digit number" << endl << endl;
	int confirmPin;
	int newPin;
	bool confirmedPin = false;
	while (!confirmedPin) {
		cout << "Confirm your current pin: ";
		cin >> confirmPin;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(numeric_limits < streamsize > ::max(), '\n');
			system("clear");
			cout << "Invalid pin entry, try again" << endl << endl;
		}
		bool compare = to_string(confirmPin) == rows[1];
		if (compare) {
			confirmedPin = true;
		} else {
			system("clear");
			cout << "The pin you have entered does not match. Please try again and input your current pin to authorize a change" << endl << endl;
		}
	}
	bool settingNewPin = true;
	while (settingNewPin) {
		cout << endl << endl << "What would you like your new pin to be? ";
		cin >> newPin;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(numeric_limits < streamsize > ::max(), '\n');
			system("clear");
			cout << "Your pin must be a 4-digit number" << endl << endl;
		} else {
			if (to_string(newPin).size() != 4) {
				cout << endl << endl << "Your pin must be 4 digits";
			} else {
				vector < string > newRows = rows;
				rows[1] = newPin;
				writeToFileInfo(newRows);
				system("clear");
				cout << "Your new pin has been set" << endl << endl;
				printMenu();
				settingNewPin = false;
			}
		}
	}
}

void logout() {
	main();
}

void deleteAccount() {
	const char* filename = "bank-data.csv";
	const int res = remove(filename);
	system("clear");
	cout << "Your account has been deleted" << endl;
	main();
}

void exitApp() {
	system("clear");
	return;
}

bool checkForExistingAccount() {
	string filename = "bank-data.csv";
	ifstream file(filename);
	if (!file.is_open()) {
		return false;
	} else {
		vector < string > data = getUserData();
		if (data.size() == 4) {
			return true;
		} else {
			return false;
		}
	}
}

bool writeToFile(string username, int pin) {
	string filename = "bank-data.csv";
	ofstream file(filename);
	if (!file.is_open()) {
		throw runtime_error("We are unable to open your files");
		return false;
	}
	file << username << "," << to_string(pin) << ",$0.00" << ",d - $0.00";
	file.close();
	return true;
}

void createAccount() {
	string filename = "bank-data.csv";
	ofstream newFile(filename);
	newFile.close();
	ifstream file(filename);
	if (!file.is_open()) {
		throw runtime_error("We are unable to open your files");
	}
	string username;
	bool inputName = true;
	while (inputName) {
		cout << endl << "Let's create you a new account with our bank" << endl << endl;
		cout << "Enter your name: ";
		cin >> username;
		if (cin.fail()) {
			cout << endl <<"This username will not be accepted, please try a different username" << endl;
			cin.clear();
			cin.ignore(numeric_limits < streamsize > ::max(), '\n');
		} else {
			inputName = false;
		}
	}
	int pin;
	bool inputPin = true;
	while (inputPin) {
		cout << endl << "Enter a 4-digit secret pin for your account: ";
		cin >> pin;
		if (cin.fail()) {
			cout << endl << "Your pin must be a 4-digit number" << endl;
			cin.clear();
			cin.ignore(numeric_limits < streamsize > ::max(), '\n');
		} else {
			string stringifiedPin = to_string(pin);
			if (stringifiedPin.size() != 4) {
				cout << endl << "Your new pin must be exactly 4-digits" << endl;
			} else {
				inputPin = false;
			}
		}
	}
	bool fileWrite = false;
	try {
		fileWrite = writeToFile(username, pin);
	} catch (const exception& e) {
		system("clear");
		cout << e.what() << endl << "We are so sorry about this inconvenience. But we cannot create an account for you at this time. We are working on fixing the issue immediately. Please come back later." << endl;
	}
	if (fileWrite) {
		system("clear");
		cout << "Your new username is " << username << endl;
		cout << "Your new pin is " << pin << endl;
	} else {
		system("clear");
		cout << endl << "We were unable to create you account. Please try again later." << endl;
	}
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

int getPin() {
	cout << "*** Bank of CPP ***" << endl << endl;
	bool validPin = false;
	while (validPin == false) {
		cout << "Enter your 4-digit pin: ";
		int pin;
		cin >> pin;
		if (cin.fail()) {
			system("clear");
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
			system("clear");
			cout << "Invalid pin. Please input a valid pin of 4 digits, not " << lengthOfPin << endl << endl;
		}
	}
	return 0;
}

void printMenu() {
	vector < string > userData;
	try {
		userData = getUserData();
	} catch (const exception& e) {
		cout << e.what() << endl << "We are so sorry about this inconvenience. We are working on fixing the issue immediately. Please come back later." << endl;
	}
	vector < string > options = {
		{
			"1. Print balance",
			"2. Withdrawal",
			"3. Deposite",
			"4. Change Name",
			"5. Change Pin",
			"6. Logout",
			"7. Delete Account",
			"8. Exit"
		},
	};
	cout << "*** Bank Of CPP ***" << endl;
	cout << "Hello " << userData[0] << endl << "How can we assist you today?" << endl;
	for (int i = 0; i < options.size(); ++i) {
		cout << endl << options[i] << endl;
	}
	cout << endl << "Option: ";
	int option;
	cin >> option;
	if (cin.fail()) {
		system("clear");
		cin.clear();
		cin.ignore(numeric_limits < streamsize > ::max(), '\n');
		cout << "Please enter a valid option" << endl << endl;
		printMenu();
	}
	if (option < 1 || option > 8) {
		system("clear");
		cout << "Please enter a valid option 1 - 5" << endl << endl;
		printMenu();
	}
	switch (option) {
		case 1:
		printBalance();
		break;
		case 2:
		system("clear");
		withdrawalOrDeposite(false);
		break;
		case 3:
		withdrawalOrDeposite(true);
		break;
		case 4:
		changeName();
		break;
		case 5:
		changePin();
		break;
		case 6:
		logout();
		break;
		case 7:
		deleteAccount();
		break;
		case 8:
		exitApp();
		break;
	}
}

int main() {
	system("clear");
	int tries = 0;
	bool runPin = true;
	bool accountExists = checkForExistingAccount();
	while (!accountExists) {
		try {
			createAccount();
			accountExists = true;
		} catch (const exception& e) {
			cout << e.what() << endl << "We are so sorry about this inconvenience. But we cannot create an account for you at this time. We are working on fixing the issue immediately. Please come back later." << endl;
		}
	}
	while (runPin) {
		if (tries == 3) {
			cout << endl << "You're attempting your pin too many times for this session. Your account is now locked" << endl;
			return 0;
		}
		int pin = getPin();
		bool validPin = validatePin(pin);
		if (validPin) {
			system("clear");
			printMenu();
			runPin = false;
		} else {
			system("clear");
			cout << endl << "The pin you have entered is invalid, try again" << endl << endl;
			tries++;
		}
	}
	return 0;
}