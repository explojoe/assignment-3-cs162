/*********************************************************************
** Program Filename: zoo.cpp
** Author: Joshua Wentzel
** Date: 2/15/2018
** Description: Play Zoo Tycoon.
** Input: Playing cards to guess for.
** Output: Zoo Tycoon gameplay.
*********************************************************************/

#include <iostream>
#include <cstdlib>
#include <stdlib.h>
#include <iomanip>
#include <sstream>

#include "zoo.hpp"
#include "monkey.hpp"
#include "seaotter.hpp"
#include "sloth.hpp"
#include "robot.hpp"
#include "implementation.hpp"

using namespace std;

Zoo::Zoo(){
	money = 100000;
	foodCost = 50;
	totalExpenses = 0;
	
	monkeys = new Monkey[0];
	seaOtters = new SeaOtter[0];
	sloths = new Sloth[0];
	robots = new Robot[0];
	
	numMonkeys = 0;
	numSeaOtters = 0;
	numSloths = 0;
	numRobots = 0;
}

double Zoo::getMoney(){return money;}

void Zoo::ageAnimals(){
	// increase the age of all animals by 1
	for(int i = 0; i < numMonkeys; i++){
		monkeys[i].ageOneDay();
	}
	for(int i = 0; i < numSeaOtters; i++){
		seaOtters[i].ageOneDay();
	}
	for(int i = 0; i < numSloths; i++){
		sloths[i].ageOneDay();
	}
	for(int i = 0; i < numRobots; i++){
		robots[i].ageOneDay();
	}
}

void Zoo::calculateRevenue(bool attendanceIsBooming){
	// this will calculate revenue and print balance sheet
	
	string stringText;
	stringstream stream;
	stream.imbue(locale(""));
	stream << fixed << setprecision(2);
	
	cout << endl;
	cout << "====== Balance Sheet ========" << endl;
	
	cout << "EXPENSES:" << endl;
	cout << expenses;
	cout << "  ----------" << endl;
	addBalanceStatementLine("  Total expenses: ", totalExpenses);
	
	cout << endl;
	cout << "INCOME:" << endl;
	

	double totalRevenue = 0;
	double subtotal = 0;
	if(numMonkeys > 0){
		subtotal += (double)numMonkeys*monkeys[0].getCost()*0.1;
		addBalanceStatementLine("  Monkeys: ", subtotal);
		totalRevenue += subtotal;
		
		if(countBabyMonkeys() > 0){
			subtotal = 0;
			subtotal += (double)countBabyMonkeys()*monkeys[0].getCost()*0.1;
			addBalanceStatementLine("  Baby monkeys: ", subtotal);
			totalRevenue += subtotal;
			
		}
		if(attendanceIsBooming){
			subtotal = 0;
			for(int i = 0; i < numMonkeys; i++){
				subtotal += calculateBonusMonkeyCash();
			}
			addBalanceStatementLine("  Booming attendance monkey bonus: ", subtotal);
			totalRevenue += subtotal;
		}

	}
	if(numSeaOtters > 0){
		subtotal += (double)numSeaOtters*seaOtters[0].getCost()*0.05;
		addBalanceStatementLine("  Sea otters: ", subtotal);
		totalRevenue += subtotal;
		
		if(countBabySeaOtters() > 0){
			subtotal = 0;
			subtotal += (double)countBabySeaOtters()*seaOtters[0].getCost()*0.05;
			addBalanceStatementLine("  Baby sea otters: ", subtotal);
			totalRevenue += subtotal;
		}
		
	}
	if(numSloths > 0){
		subtotal = 0;
		subtotal += (double)numSloths*sloths[0].getCost()*0.05;
		addBalanceStatementLine("  Sloths: ", subtotal);
		totalRevenue += subtotal;
		
		if(countBabySloths() > 0){
			subtotal = 0;
			subtotal += (double)countBabySloths()*sloths[0].getCost()*0.05;
			addBalanceStatementLine("  Baby sloths: ", subtotal);
			totalRevenue += subtotal;
		}
	}
	if(numRobots > 0){
		subtotal = 0;
		subtotal += (double)numRobots*robots[0].getCost()*0.05;
		addBalanceStatementLine("  Robots: ", subtotal);
		totalRevenue += subtotal;
		
		if(countBabyRobots() > 0){
			subtotal = 0;
			subtotal += (double)countBabyRobots()*robots[0].getCost()*0.05;
			addBalanceStatementLine("  Baby robots: ", subtotal);
			totalRevenue += subtotal;
		}
		
	}
	
	double netEarningsNumber = totalRevenue-totalExpenses;
	cout << "  ----------" << endl;
	addBalanceStatementLine("  Total income: ", totalRevenue);
	cout << endl;
	addBalanceStatementLine("NET EARNINGS: ", netEarningsNumber);
	addBalanceStatementLine("  Ending balance: ", money);
	cout << "=============================" << endl;
	
	money += totalRevenue;
	
	// clear purchase history
	expenses = "";
	totalExpenses = 0;

}

double Zoo::calculateBonusMonkeyCash(){
	// rand is between 0 and randMax
	// num should be between 0.75 and 1.25
	double num = (double)rand()/RAND_MAX;
	num *= 250;
	num += 250;
	return num;
}

void Zoo::birth(){
	// pick a random ADULT animal and add the necessary number of babies to the species
	/*
	1 monkey
	10 otters
	4 sloths
	8 robots
	
	sum = 23
	
	
	2 monkeys
	1 otter
	
	0-2
	
	*/
	int adultMonkeys = countAdultMonkeys();
	int adultSeaOtters = countAdultSeaOtters();
	int adultSloths = countAdultSloths();
	int adultRobots = countAdultRobots();
	
	int sum = adultMonkeys+adultSeaOtters+adultSloths+adultRobots;
	if(sum > 0){
		int num = rand() % sum;
		if(num > adultMonkeys+adultSeaOtters+adultSloths-1){
			// animal is a robot
			addRobots(robots[0].getBabyCount(),true);
			
		}
		else if(num > adultMonkeys+adultSeaOtters-1){
			// animal is a sloth
			addSloths(sloths[0].getBabyCount(),true);
		}
		else if(num > adultMonkeys-1){
			// animal is a sea otter
			addSeaOtters(seaOtters[0].getBabyCount(),true);
		}
		else{
			// animal is a monkey
			addMonkeys(monkeys[0].getBabyCount(),true);
		}
	}
	
	
	
	
	
	
	
}

void Zoo::sickness(){			
	stringstream stream;
	stream.imbue(locale(""));
	stream << fixed << setprecision(2);
	int sum = numMonkeys+numSeaOtters+numSloths+numRobots;
	if(sum > 0){
		int num = rand() % sum;
		if(num > numMonkeys+numSeaOtters+numSloths-1){
			// animal is a robot
			num = num - numMonkeys - numSeaOtters - numSloths;
			int cost = robots[num].getSickCost();
			if(robots[num].isBaby()){
				cost *= 2;
			}
			if((money - cost) >= 0){
				// player can cover the cost
				
				stream << "  Treatment for infected ";
				if(robots[num].isBaby()){
					stream << "baby ";
				}
				stream << "robot: ";
				string s = stream.str();
				padTo(s, 40, false);
				addExpense(s);
				subtractMoney(cost);
			}
			else{
				// player cannot cover the cost
				
				cout << "You were not able to pay $" << cost << " to care for an infected ";
				if(robots[num].isBaby()){
					cout << "baby ";
				}
				cout << "robot. It became fatally corrupted." << endl;
				removeRobot(num);
			}
		}
		else if(num > numMonkeys+numSeaOtters-1){
			// animal is a sloth
			num = num - numMonkeys - numSeaOtters;
			int cost = sloths[num].getSickCost();
			if(sloths[num].isBaby()){
				cost *= 2;
			}
			if((money - cost) >= 0){
				// player can cover the cost
				
				stream << "  Treatment for sick ";
				if(sloths[num].isBaby()){
					stream << "baby ";
				}
				stream << "sloth: ";
				string s = stream.str();
				padTo(s, 40, false);
				addExpense(s);
				subtractMoney(cost);
			}
			else{
				// player cannot cover the cost
				
				cout << "You were not able to pay $" << cost << " to care for a sick ";
				if(sloths[num].isBaby()){
					cout << "baby ";
				}
				cout << "sloth. It passed away." << endl;
				removeSloth(num);
			}
		}
		else if(num > numMonkeys-1){
			// animal is a sea otter
			num = num - numMonkeys;
			int cost = seaOtters[num].getSickCost();
			if(seaOtters[num].isBaby()){
				cost *= 2;
			}
			if((money - cost) >= 0){
				// player can cover the cost
				
				stream << "  Treatment for sick ";
				if(seaOtters[num].isBaby()){
					stream << "baby ";
				}
				stream << "sea otter: ";
				string s = stream.str();
				padTo(s, 40, false);
				addExpense(s);
				subtractMoney(cost);
			}
			else{
				// player cannot cover the cost
				
				cout << "You were not able to pay $" << cost << " to care for a sick ";
				if(seaOtters[num].isBaby()){
					cout << "baby ";
				}
				cout << "sea otter. It passed away." << endl;
				removeSeaOtter(num);
			}
		}
		else{
			// animal is a monkey
			int cost = monkeys[num].getSickCost();
			if(monkeys[num].isBaby()){
				cost *= 2;
			}
			if((money - cost) >= 0){
				// player can cover the cost
				
				stream << "  Treatment for sick ";
				if(monkeys[num].isBaby()){
					stream << "baby ";
				}
				stream << "monkey: ";
				string s = stream.str();
				padTo(s, 40, false);
				addExpense(s);
				subtractMoney(cost);
			}
			else{
				// player cannot cover the cost
				
				cout << "You were not able to pay $" << cost << " to care for a sick ";
				if(monkeys[num].isBaby()){
					cout << "baby ";
				}
				cout << "monkey. It passed away." << endl;
				removeMonkey(num);
			}
		}
	}
}

bool Zoo::checkBankruptcy(){
	if(money >= 0){
		return false;
	}
	else
	{
		return true;
	}
}

void Zoo::subtractMoney(double cost){
	money -= cost;
	stringstream stream;
	//stream.width(20);
	stream.imbue(locale(""));
	//stream << std::right;
	stream << fixed << setprecision(2);
	stream << "$" << cost << endl;
	string s = stream.str();
	padTo(s, 30, true);
	totalExpenses += cost;
	addExpense(s);
}

void Zoo::adjustFeedCost(){
	// rand is between 0 and randMax
	// num should be between 0.75 and 1.25
	double num = (double)rand()/RAND_MAX;
	num /= 2;
	num += 0.75;
	num *= foodCost;
	cout << "BASE FEED COST: " << foodCost << endl;
	foodCost = num;
}

double Zoo::calculateFeedCost(){
	// go through all animals and sum up the costs
	int foodConsumed = 0;
	if(numMonkeys > 0)
		foodConsumed += numMonkeys*monkeys[0].getFoodMultiplier();
	if(numSeaOtters > 0)
		foodConsumed += numSeaOtters*seaOtters[0].getFoodMultiplier();
	if(numSloths > 0)
		foodConsumed += numSloths*sloths[0].getFoodMultiplier();
	if(numRobots > 0)
		foodConsumed += numRobots*robots[0].getFoodMultiplier();
	
	double total = (double)foodConsumed*foodCost;
	//cout << "total  food needed: " << foodConsumed << endl;
	adjustFeedCost();
	
	return total;
}

void Zoo::printAnimals(){
	// print out babies and adults of each species
	cout << "Animals: " << endl << endl;
	
	cout << "Monkeys: " << countMonkeys() << endl;
	cout << "  Adult monkeys: " << countAdultMonkeys() << endl;
	cout << "  Baby monkeys: " << countBabyMonkeys() << endl << endl;
	
	cout << "Sea otters: " << countSeaOtters() << endl;
	cout << "  Adult sea otters: " << countAdultSeaOtters() << endl;
	cout << "  Baby sea otters: " << countBabySeaOtters() << endl << endl;
	
	cout << "Sloths: " << countSloths() << endl;
	cout << "  Adult sloths: " << countAdultSloths() << endl;
	cout << "  Baby sloths: " << countBabySloths() << endl << endl;
	
	cout << "Robots: " << countRobots() << endl;
	cout << "  Adult robots: " << countAdultRobots() << endl;
	cout << "  Baby robots: " << countBabyRobots() << endl << endl;
	
}

void Zoo::randEventAndRevenue(int feedChoice){
	int num = rand() % 8; // num between 0-7 inclusive
	// 6, 7 = boom in zoo attendance
	// 4, 5 = animal gives birth
	// 3 = sickness happens
	// 2 = sickness happens, nothing if FC = 3
	// 1 = nothing, sickness if FC = 1
	// 0 = nothing
	
	// FC:  2 = regular, 1 = cheap, 3 = premium
	if(num >= 6){
		// boom in zoo attendance
		cout << "Boom in zoo attendance" << endl;
		calculateRevenue(true);
		return;
	}
	else if(num >= 4){
		// animal gives birth
		//cout << "Animal gives birth" << endl;
		birth();
	}
	else if(num >= feedChoice){
		// sickness
		//cout << "Sickness" << endl;
		sickness();
	}
	else{
		// nothing happens
		cout << "Nothing happens" << endl;
	}
	calculateRevenue(false);
}


void Zoo::purchase(int animal, int quantity){
	stringstream stream;
	stream.imbue(locale(""));
	stream << fixed << setprecision(2);
	if(animal == 1){
		stream << "  Bought " << quantity << " monkey";
		if(quantity != 1){
			stream << "s: ";
		}
		else{
			stream << ": ";
		}
		string s = stream.str();
		padTo(s, 40, false);
		addExpense(s);
		addMonkeys(quantity, false);
	}
	else if(animal == 2){
		stream << "  Bought " << quantity << " sea otter";
		if(quantity != 1){
			stream << "s: ";
		}
		else{
			stream << ": ";
		}
		string s = stream.str();
		padTo(s,40, false);
		addExpense(s);
		addSeaOtters(quantity, false);
	}
	else if(animal == 3){
		stream << "  Bought " << quantity << " sloth";
		if(quantity != 1){
			stream << "s: ";
		}
		else{
			stream << ": ";
		}
		string s = stream.str();
		padTo(s,40, false);
		addExpense(s);
		addSloths(quantity, false);
	}
	else{
		stream << "  Bought " << quantity << " robot";
		if(quantity != 1){
			stream << "s: ";
		}
		else{
			stream << ": ";
		}
		string s = stream.str();
		padTo(s,40, false);
		addExpense(s);
		addRobots(quantity, false);
	}

}

int Zoo::countAnimals(){
	return numMonkeys + numSeaOtters + numSloths + numRobots;
}

int Zoo::countMonkeys(){return numMonkeys;}
int Zoo::countSeaOtters(){return numSeaOtters;}
int Zoo::countSloths(){return numSloths;}
int Zoo::countRobots(){return numRobots;}

int Zoo::countAdultMonkeys(){
	int total = 0;
	for(int i = 0; i < numMonkeys; i++){
		if(monkeys[i].isAdult())
			total++;
	}
	return total;
}
int Zoo::countAdultSeaOtters(){
	int total = 0;
	for(int i = 0; i < numSeaOtters; i++){
		if(seaOtters[i].isAdult())
			total++;
	}
	return total;
}
int Zoo::countAdultSloths(){
	int total = 0;
	for(int i = 0; i < numSloths; i++){
		if(sloths[i].isAdult())
			total++;
	}
	return total;
}
int Zoo::countAdultRobots(){
	int total = 0;
	for(int i = 0; i < numRobots; i++){
		if(robots[i].isAdult())
			total++;
	}
	return total;
}



int Zoo::countBabyMonkeys(){
	int total = 0;
	for(int i = 0; i < numMonkeys; i++){
		if(monkeys[i].isBaby())
			total++;
	}
	return total;
}
int Zoo::countBabySeaOtters(){
	int total = 0;
	for(int i = 0; i < numSeaOtters; i++){
		if(seaOtters[i].isBaby())
			total++;
	}
	return total;
}
int Zoo::countBabySloths(){
	int total = 0;
	for(int i = 0; i < numSloths; i++){
		if(sloths[i].isBaby())
			total++;
	}
	return total;
}
int Zoo::countBabyRobots(){
	int total = 0;
	for(int i = 0; i < numRobots; i++){
		if(robots[i].isBaby())
			total++;
	}
	return total;
}


void Zoo::addMonkeys(int num, bool isBirth){
	Monkey* tempMonkeys = new Monkey[numMonkeys+num];
	for(int i = 0; i < numMonkeys; i++){
		tempMonkeys[i] = monkeys[i];
	}
	delete [] monkeys;
	numMonkeys += num;
	monkeys = new Monkey[numMonkeys];
	for(int i = 0; i < numMonkeys; i++){
		monkeys[i] = tempMonkeys[i];
	}
	delete [] tempMonkeys;
	for(int i = 0; i < num; i++){
		if(isBirth){
			monkeys[numMonkeys-i-1].setAge(0);
		}
		else
		{
			monkeys[numMonkeys-i-1].setAge(1095);
		}
	}
	if(isBirth){
		if(num == 1){
			cout << "A monkey gave birth to a new monkey!" << endl;
		}
		else
		{
			cout << "A monkey gave birth to " << num << " new baby monkeys!" << endl;
		}
	}
	else
	{
		subtractMoney(num * monkeys[0].getCost());
	}
}
void Zoo::addSeaOtters(int num, bool isBirth){
	SeaOtter* tempSeaOtters = new SeaOtter[numSeaOtters+num];
	for(int i = 0; i < numSeaOtters; i++){
		tempSeaOtters[i] = seaOtters[i];
	}
	delete [] seaOtters;
	numSeaOtters += num;
	seaOtters = new SeaOtter[numSeaOtters];
	for(int i = 0; i < numSeaOtters; i++){
		seaOtters[i] = tempSeaOtters[i];
	}
	delete [] tempSeaOtters;
	for(int i = 0; i < num; i++){
		if(isBirth){
			seaOtters[numSeaOtters-i-1].setAge(0);
		}
		else
		{
			seaOtters[numSeaOtters-i-1].setAge(1095);
		}
	}	
	
	if(isBirth){
		if(num == 1){
			cout << "A sea otter gave birth to a new sea otter!" << endl;
		}
		else
		{
			cout << "A sea otter gave birth to " << num << " new baby sea otters!" << endl;
		}
	}
	else
	{
		subtractMoney(num * seaOtters[0].getCost());
	}
}
void Zoo::addSloths(int num, bool isBirth){
	Sloth* tempSloths = new Sloth[numSloths+num];
	for(int i = 0; i < numSloths; i++){
		tempSloths[i] = sloths[i];
	}
	delete [] sloths;
	numSloths += num;
	sloths = new Sloth[numSloths];
	for(int i = 0; i < numSloths; i++){
		sloths[i] = tempSloths[i];
	}
	delete [] tempSloths;
	for(int i = 0; i < num; i++){
		if(isBirth){
			sloths[numSloths-i-1].setAge(0);
		}
		else
		{
			sloths[numSloths-i-1].setAge(1095);
		}
	}	
	if(isBirth){
		if(num == 1){
			cout << "A sloth gave birth to a new baby sloth!" << endl;
		}
		else
		{
			cout << "A sloth gave birth to " << num << " new baby sloths!" << endl;
		}
	}
	else
	{
		subtractMoney(num * sloths[0].getCost());
	}
}

void Zoo::addRobots(int num, bool isBirth){
	Robot* tempRobots = new Robot[numRobots+num];
	for(int i = 0; i < numRobots; i++){
		tempRobots[i] = robots[i];
	}
	delete [] robots;
	numRobots += num;
	robots = new Robot[numRobots];
	for(int i = 0; i < numRobots; i++){
		robots[i] = tempRobots[i];
	}
	delete [] tempRobots;
	for(int i = 0; i < num; i++){
		if(isBirth){
			robots[numRobots-i-1].setAge(0);
		}
		else
		{
			robots[numRobots-i-1].setAge(1095);
		}
	}
	
	if(isBirth){
		if(num == 1){
			cout << "A robot generated a new baby robot!" << endl;
		}
		else
		{
			cout << "A robot generated " << num << " new baby robots!" << endl;
		}
	}
	else
	{
		subtractMoney(num * robots[0].getCost());
	}
}

void Zoo::removeMonkey(int index){
	// this is a result of sickness
	Monkey* tempMonkeys = new Monkey[numMonkeys-1];
	for(int i = 0; i < numMonkeys; i++){
		if(i < index){
			tempMonkeys[i] = monkeys[i];
		}
		if(i > index){
			tempMonkeys[i-1] = monkeys[i];
		}
	}
	delete [] monkeys;
	numMonkeys--;
	monkeys = new Monkey[numMonkeys];

	for(int i = 0; i < numMonkeys; i++){
		monkeys[i] = tempMonkeys[i];
	}
	delete [] tempMonkeys;
}
void Zoo::removeSeaOtter(int index){
	// this is a result of sickness
	SeaOtter* tempSeaOtters = new SeaOtter[numSeaOtters-1];
	for(int i = 0; i < numSeaOtters; i++){
		if(i < index){
			tempSeaOtters[i] = seaOtters[i];
		}
		if(i > index){
			tempSeaOtters[i-1] = seaOtters[i];
		}
	}
	delete [] seaOtters;
	numSeaOtters--;
	seaOtters = new SeaOtter[numSeaOtters];

	for(int i = 0; i < numSeaOtters; i++){
		seaOtters[i] = tempSeaOtters[i];
	}
	delete [] tempSeaOtters;
}
void Zoo::removeSloth(int index){
	// this is a result of sickness
	Sloth* tempSloths = new Sloth[numSloths-1];
	for(int i = 0; i < numSloths; i++){
		if(i < index){
			tempSloths[i] = sloths[i];
		}
		if(i > index){
			tempSloths[i-1] = sloths[i];
		}
	}
	delete [] sloths;
	numSloths--;
	sloths = new Sloth[numSloths];

	for(int i = 0; i < numSloths; i++){
		sloths[i] = tempSloths[i];
	}
	delete [] tempSloths;
}

void Zoo::removeRobot(int index){
	// this is a result of sickness
	Robot* tempRobots = new Robot[numRobots-1];
	for(int i = 0; i < numRobots; i++){
		if(i < index){
			tempRobots[i] = robots[i];
		}
		if(i > index){
			tempRobots[i-1] = robots[i];
		}
	}
	delete [] robots;
	numRobots--;
	robots = new Robot[numRobots];

	for(int i = 0; i < numRobots; i++){
		robots[i] = tempRobots[i];
	}
	delete [] tempRobots;
}

void Zoo::addExpense(std::string newExpense){
	expenses += newExpense;
}

Zoo::~Zoo(){
	delete [] monkeys;
	delete [] seaOtters;
	delete [] sloths;
	delete [] robots;
}


