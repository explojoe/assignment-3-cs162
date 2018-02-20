/*********************************************************************
** Program Filename: main.cpp
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

#include "zoo.hpp"
#include "implementation.hpp"

using namespace std;

int main(){
	int daysPassed = -1;
	Zoo* playerZoo = new Zoo();
	cout.imbue(locale(""));		// this formats numbers to include commas
	cout << "\033[2J";			// clear the screen
	cout << "Welcome to Zoo Tycoon, no cowculators required!" << endl;
	while(1){
		daysPassed++;
		cout << endl << "-----------------" << endl;
		printDate(daysPassed);
		cout << fixed;
		cout << "You have $" << setprecision(2) << playerZoo->getMoney() << endl;
		playerZoo->ageAnimals();
		playerZoo->printAnimals();
		
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
		
		int choiceFeedNum = 2;
		cout << "It is time to feed your animals." << endl;
		if(playerZoo->countAnimals() == 0){
			cout << "You have no animals to feed, you should buy some." << endl;
		}
		else{
			double feedCost = playerZoo->calculateFeedCost();
			
			
			cout << "To use cheap feed, it will cost $" << feedCost/2 << endl;
			cout << "To use premium feed, it will cost $" << feedCost*2 << endl;
			cout << "To use regular feed, it will cost $" << feedCost << endl;
			
			cout << "To select cheap feed, enter 1." << endl;
			cout << "To select premium feed, enter 3." << endl;
			cout << "To select regular feed, press enter." << endl;
			std::string choiceFeed;
			
			getline(std::cin, choiceFeed);
			stringstream stream;
			stream.imbue(locale(""));
			stream << fixed << setprecision(2);
			if(choiceFeed == "1"){
				// cheap feed
				feedCost = feedCost/2;
				choiceFeedNum = 1;
				stream << "  Cheap animal feed: ";
				
			}
			else if(choiceFeed == "3"){
				// premium feed
				feedCost = feedCost*2;
				choiceFeedNum = 3;
				stream << "  Premium animal feed: ";
			}
			else{
				// regular feed [defualt]
				stream << "  Regular animal feed: ";
			}
			string s = stream.str();
			padTo(s,40, false);
			playerZoo->addExpense(s);
			
			playerZoo->subtractMoney(feedCost);
		}
		bool outOfMoney = playerZoo->checkBankruptcy();
		if(outOfMoney){
			// game over
			cout << "You've ran out of money! Better luck next time!" << endl;
			break;
		}
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
	cout.imbue(locale("C"));	// free the cout stream imbue memory
	delete playerZoo;			// free zoo memory
	return 0;
}



