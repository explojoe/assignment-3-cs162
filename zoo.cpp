#include <iostream>
//#include <locale>
#include <cstdlib>
//#include <string>

#include "zoo.hpp"
//#include "animal.hpp"
#include "monkey.hpp"
#include "seaotter.hpp"
#include "sloth.hpp"
#include "robot.hpp"

using namespace std;

Zoo::Zoo(){
	money = 100000;
	foodCost = 50;
	
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
	double revenue;
	if(numMonkeys > 0){
		revenue += (double)numMonkeys*monkeys[0].getCost()*0.1;
		revenue += (double)countBabyMonkeys()*monkeys[0].getCost()*0.1;
		if(attendanceIsBooming){
			for(int i = 0; i < numMonkeys; i++){
				revenue += calculateBonusMonkeyCash();
			}
		}

	}
	if(numSeaOtters > 0){
		revenue += (double)numSeaOtters*seaOtters[0].getCost()*0.1;
		revenue += (double)countBabySeaOtters()*seaOtters[0].getCost()*0.1;
	}
	if(numSloths > 0){
		revenue += (double)numSloths*sloths[0].getCost()*0.1;
		revenue += (double)countBabySloths()*sloths[0].getCost()*0.1;
	}
	if(numRobots > 0){
		revenue += (double)numRobots*robots[0].getCost()*0.1;
		revenue += (double)countBabyRobots()*robots[0].getCost()*0.1;
	}
	

	
	money += revenue;
	
	cout << "You earned $" << revenue << " today." << endl;
	// clear purchase history
}

double Zoo::calculateBonusMonkeyCash(){
	// rand is between 0 and randMax
	// num should be between 0.75 and 1.25
	double num = (double)rand()/RAND_MAX;
	num *= 250;
	num += 250;
	//cout << "BONUS CASH: " << num << endl;
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
	int sum = numMonkeys+numSeaOtters+numSloths+numRobots;
	if(sum > 0){
		int num = rand() % sum;
		if(num > numMonkeys+numSeaOtters+numSloths-1){
			// animal is a robot
			num = num - numMonkeys - numSeaOtters - numSloths;
			int cost = robots[num].getSickCost();
			if(robots[num].isBaby()){
				cost *= 50;
			}
			if((money - cost) >= 0){
				// player can cover the cost
				money = money - cost;
				cout << "You spent $" << cost << " caring for an infected ";
				if(robots[num].isBaby()){
					cout << "baby ";
				}
				cout << "robot. The virus was removed!" << endl;
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
				money = money - cost;
				cout << "You spent $" << cost << " caring for a sick ";
				if(sloths[num].isBaby()){
					cout << "baby ";
				}
				cout << "sloth. It made a full recovery!" << endl;
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
				money = money - cost;
				cout << "You spent $" << cost << " caring for a sick ";
				if(seaOtters[num].isBaby()){
					cout << "baby ";
				}
				cout << "sea otter. It made a full recovery!" << endl;
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
				money = money - cost;
				cout << "You spent $" << cost << " caring for a sick ";
				if(monkeys[num].isBaby()){
					cout << "baby ";
				}
				cout << "monkey. It made a full recovery!" << endl;
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
	//cout << "passed1" << endl;
	if(num >= 6){
		// boom in zoo attendance
		cout << "Boom in zoo attendance" << endl;
		calculateRevenue(true);
		return;
	}
	else if(num >= 4){
		// animal gives birth
		cout << "Animal gives birth" << endl;
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
	//cout << "passed2" << endl;
	calculateRevenue(false);
}


void Zoo::purchase(int animal, int quantity){
	if(animal == 1){
		addMonkeys(quantity, false);
	}
	else if(animal == 2){
		addSeaOtters(quantity, false);
	}
	else if(animal == 3){
		addSloths(quantity, false);
	}
	else{
		addRobots(quantity, false);
	}
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
}


