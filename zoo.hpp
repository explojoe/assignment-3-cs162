#ifndef _ZOO_
#define _ZOO_

#include "monkey.hpp"
#include "seaotter.hpp"
#include "sloth.hpp"
#include "robot.hpp"

class Zoo {
	private:
		double money;
		double foodCost;
	
		Monkey* monkeys;
		SeaOtter* seaOtters;
		Sloth* sloths;
		Robot* robots;
		
		int numMonkeys;
		int numSeaOtters;
		int numSloths;
		int numRobots;
		
		std::string expenses;
		double totalExpenses;
		
	public:
		Zoo();
		
		double getMoney();
		
		void ageAnimals();
		
		void calculateRevenue(bool);
		
		double calculateBonusMonkeyCash();
		
		
		void sickness();
		
		void birth();
		
		bool checkBankruptcy();
		
		void subtractMoney(double);
		
		void adjustFeedCost();
		
		double calculateFeedCost();
		
		void printAnimals();
		
		void randEventAndRevenue(int);
		void purchase(int,int);
		
		int countAnimals();
		
		int countMonkeys();
		int countSeaOtters();
		int countSloths();
		int countRobots();
		
		int countAdultMonkeys();
		int countAdultSeaOtters();
		int countAdultSloths();
		int countAdultRobots();
		
		int countBabyMonkeys();
		int countBabySeaOtters();
		int countBabySloths();
		int countBabyRobots();
		
		void addMonkeys(int,bool);
		void addSeaOtters(int,bool);
		void addSloths(int,bool);
		void addRobots(int,bool);
		
		void removeMonkey(int);
		void removeSeaOtter(int);
		void removeSloth(int);
		void removeRobot(int);
		
		void addExpense(std::string);
		
		~Zoo();
		
		

};
#endif