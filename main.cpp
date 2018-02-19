#include <iostream>
#include <locale>
#include <string>
#include <iomanip>

#include "zoo.hpp"

using namespace std;

void printDate(int);

int main(){
	int daysPassed = -1;
	//int money = 100000;
	//double foodCost = 50;
	Zoo* playerZoo = new Zoo;
	cout.imbue(locale(""));
	//cout << "^[[2J" << endl;
	cout << "\033[2J";
	cout << "Welcome to Zoo Tycoon, no cowculators required!" << endl;
	//while(daysPassed < 150){
	while(1){
		daysPassed++;
		cout << endl << "-----------------" << endl;
		printDate(daysPassed);
		cout << fixed;
		cout << "You have $" << setprecision(2) << playerZoo->getMoney() << endl;
		playerZoo->ageAnimals();
		playerZoo->printAnimals();
		
		//cout << to_string(1000) << endl;
		
		cout << "You may buy up to two animals of the same species." << endl;
		cout << "Monkeys cost $15,000 each" << endl;
		cout << "Sea otters cost $5,000 each" << endl;
		cout << "Sloths cost $2,000 each" << endl;
		cout << "Robots cost $30,000 each" << endl;
		
		cout << "To not purchase any animals, press enter." << endl;
		cout << "To select monkeys, enter 1." << endl;
		cout << "To select sea otters, enter 2." << endl;
		cout << "To select sloths, enter 3." << endl;
		cout << "To select robots, enter 4." << endl;
		int choiceAnimal = 0;
		int choiceQuantity = 0;
		
		std::string choicePurchase;
		
		//cin.get();
		getline(std::cin, choicePurchase);
		if(choicePurchase == "1"){
			choiceAnimal = 1;
		}
		else if(choicePurchase == "2"){
			choiceAnimal = 2;
		}
		else if(choicePurchase == "3"){
			choiceAnimal = 3;
		}
		else if(choicePurchase == "4"){
			choiceAnimal = 4;
		}
		
		if((choiceAnimal > 0) && (choiceAnimal < 5)){
			cout << "To cancel today's purchasing, press enter." << endl;
			cout << "To purchase one, enter 1." << endl;
			cout << "To purchase two, enter 2." << endl;
			std::string choiceQuantity;
		
			//cin.get();
			getline(std::cin, choiceQuantity);
			if(choiceQuantity == "1"){
				playerZoo->purchase(choiceAnimal,1);
			}
			else if(choiceQuantity == "2"){
				playerZoo->purchase(choiceAnimal,2);
			}
		}
		double feedCost = playerZoo->calculateFeedCost();
		
		cout << "It is time to feed your animals." << endl;
		cout << "To use cheap feed, it will cost $" << feedCost/2 << endl;
		cout << "To use premium feed, it will cost $" << feedCost*2 << endl;
		cout << "To use regular feed, it will cost $" << feedCost << endl;
		
		cout << "To select cheap feed, enter 1." << endl;
		cout << "To select premium feed, enter 3." << endl;
		cout << "To select regular feed, press enter." << endl;
		std::string choiceFeed;
		int choiceFeedNum;
		
		//cin.get(choiceFeed);
		//cin.get();
		getline(std::cin, choiceFeed);
		if(choiceFeed == "1"){
			feedCost = feedCost/2;
			choiceFeedNum = 1;
		}
		else if(choiceFeed == "3"){
			feedCost = feedCost*2;
			choiceFeedNum = 3;
		}
		else{
			choiceFeedNum = 2;
		}
		//cout << "passed" << endl;
		playerZoo->subtractMoney(feedCost);
		bool outOfMoney = playerZoo->checkBankruptcy();
		if(outOfMoney){
			// game over
			cout << "You've ran out of money! Better luck next time!" << endl;
			break;
		}
		//cout << "passed" << endl;
		playerZoo->randEventAndRevenue(choiceFeedNum);
	
	
		cout << "The day is over. To quit, enter \'Q\', or press enter to continue.";
		cout << endl;
		std::string input;
		getline(std::cin, input);
		if((input == "q")||(input == "Q")){
			// player wants to quit
			cout << "See you next time!" << endl;
			break;
		}
	}
	// free memory;
	
	delete playerZoo;
	return 0;
}

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
	
	//cout << " ||||| " << daysPassed << " ||||| ";
	if(days == 1){
		cout << "   || Day: 1" << endl;
	}
	else
	{
		cout << "   || Day: " << days << endl;
	}
}




