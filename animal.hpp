#ifndef _ANIMAL_
#define _ANIMAL_

class Animal {
	protected:
		int age = 0;
		double cost;
		int babyCount;
		int foodMultiplier;
		
	public:
		Animal();
		
		void ageOneDay();
		void giveBirth();
		int generateRevenue();
		
		bool isBaby();
		bool isAdult();
		
		double getSickCost();
		double getCost();
		int getBabyCount();
		
		int getFoodMultiplier();
		
		void setAge(int);
};
#endif