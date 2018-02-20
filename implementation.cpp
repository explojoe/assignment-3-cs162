/*********************************************************************
** Program Filename: implementation.cpp
** Author: Joshua Wentzel
** Date: 2/15/2018
** Description: Play Zoo Tycoon.
** Input: Playing cards to guess for.
** Output: Zoo Tycoon gameplay.
*********************************************************************/

#include <iostream>
#include <locale>
#include <string>
#include <iomanip>
#include <sstream>

using namespace std;

void printDate(int daysPassed){
	int years = daysPassed / 365; // there are 365 days in a year.
	int days = daysPassed % 365; // remainder
	
	if(years == 1){
		cout << "Year: 1";
	}
	else
	{
		cout << "Year: " << years;
	}
	if(days == 1){
		cout << "   || Day: 1" << endl;
	}
	else
	{
		cout << "   || Day: " << days << endl;
	}
}

void padTo(std::string &str, const int num, bool insertBefore){
	//cout << str.size() << endl;
	if(!str.empty()){
		if(num > str.size()){
			if(insertBefore){
				str.insert(0, num - str.size(), ' ');
			}
			else
			{
				str.insert(str.size(), num - str.size(), ' ');
			}
			
		}
	}
}

void addBalanceStatementLine(const std::string text, const double amount){
	string stringText = text;
	stringstream stream;
	stream.imbue(locale(""));
	stream << fixed << setprecision(2);
	padTo(stringText, 40, false);
	cout << stringText;
	
	stream << "$" << amount << endl;
	stringText = stream.str();
	padTo(stringText, 30, true);
	cout << stringText;
}