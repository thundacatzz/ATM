#include <fstream>
#include <iostream>
#include <string>
#include <iomanip>
#include <cmath>
using namespace std;
// This program performs functions similar to an ATM, reading data from an input file and performing withdrawal, deposit, and balance report functions.
// Written by Logan Skura, 9/9/2022

/* This is where we declare our variables for both calling the input and output files, the global variables that will be used throughout the program.
and the functions that are defined later. */
ifstream custData;
ofstream results;
string fName, lName;
double accBalance, accDelta;
char transCode;
void PrintName();
void PrintData();
void Withdraw();
void Deposit();

int main()
{
	// This opens the input file. If it fails, it cancels the program.
	custData.open("customer.txt");
	if (custData.fail())
	{
		cout << "Failed to open input file";
		return 1;
	}

	// This opens the output file. If it fails, it cancels the program.
	results.open("statement.txt");
	if (results.fail())
	{
		cout << "Failed to open output file";
		return 2;
	}

	/* This operation reads the input file from left to right, assuming a certain order of data, then performs the correct transactional function,
	terminating its reading when it reaches end of file. */
	while (!custData.eof())
	{
		cout.setf(ios::fixed);
		cout << setprecision(2);
		custData >> fName >> lName >> accBalance >> transCode >> accDelta;
		switch (transCode)
		{
		case 'W':
			PrintName();
			PrintData();
			Withdraw();
			break;
		case 'D':
			PrintName();
			PrintData();
			Deposit();
			break;
		case 'R':
			PrintName();
			PrintData();
			cout << "\n";
			results << "\n";
			break;
		default:
			PrintName();
			PrintData();
			cout << "\n" << transCode << " is not a valid transaction. Transaction canceled." << endl;
			results << "\n" << transCode << " is not a valid transaction. Transaction canceled." << endl;
			break;
		}
	}
	// These close the input and output files before terminating the program.
	custData.close();
	results.close();
	return 0;
}

// This function prints the customer's name to the console and output file.
void PrintName()
{
	cout << "\nCustomer Name: " << lName << " " << fName;
	results << "\nCustomer Name: " << lName << " " << fName;
}

// This function prints the other input data besides the customer's name to the console and output file.
void PrintData()
{
	cout << "\nChecking balance before transaction : $ " << accBalance << "\nTransaction type : " << transCode << "\nTransaction amount : $" << accDelta;
	results << "\nChecking balance before transaction : $ " << accBalance << "\nTransaction type : " << transCode << "\nTransaction amount : $" << accDelta;
}

// This function checks the customer's inputs and final account balance and reacts accordingly. It also performs simple subtraction and outputs a final balance.
void Withdraw()
{
	if (accDelta < 0)
	{
		cout << "\nTransaction amount cannot be less than zero. Transaction canceled." << endl;
		results << "\nTransaction amount cannot be less than zero. Transaction canceled." << endl;
	}
	else if ((accBalance - accDelta) < 0)
	{
		cout << "\nInsufficient funds to perform transaction. Transaction canceled." << endl;
		results << "\nInsufficient funds to perform transaction. Transaction canceled." << endl;
	}
	else if ((accBalance - accDelta) < 300)
	{
		cout << "\nWarning: account is below minimum: $ 300.00" << "\nChecking balance after transaction : $ " << accBalance - accDelta << endl;
		results << "\nWarning: account is below minimum: $ 300.00" << "\nChecking balance after transaction : $ " << accBalance - accDelta << endl;
	}
	else
	{
		cout << "\nChecking balance after transaction : $ " << accBalance - accDelta << endl;
		results << "\nChecking balance after transaction : $ " << accBalance - accDelta << endl;
	}
}

// This function checks the customer's inputs and reacts accordingly. It also performs simple addition and outputs a final balance.
void Deposit()
{
	if (accDelta < 0)
	{
		cout << "\nTransaction amount cannot be less than zero. Transaction canceled." << endl;
		results << "\nTransaction amount cannot be less than zero. Transaction canceled." << endl;
	}
	else
	{
		cout << "\nChecking balance after transaction : $ " << accBalance + accDelta << endl;
		results << "\nChecking balance after transaction : $ " << accBalance + accDelta << endl;
	}
}