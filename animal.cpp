/*********************************************************************
** Program Filename: animal.cpp
** Author: Joshua Wentzel
** Date: 2/15/2018
** Description: Play Zoo Tycoon.
** Input: Playing cards to guess for.
** Output: Zoo Tycoon gameplay.
*********************************************************************/

#include <iostream>

#include "animal.hpp"

using namespace std;

Animal::Animal(){}

void Animal::ageOneDay(){
	age++;
}

bool Animal::isBaby(){
	if(age < 30){
		return true;
	}
	else
	{
		return false;
	}
}


bool Animal::isAdult(){
	if(age >= 1095){
		return true;
	}
	else
	{
		return false;
	}
	
}

double Animal::getSickCost(){return cost/2;}
double Animal::getCost(){return cost;}
int Animal::getBabyCount(){return babyCount;}
int Animal::getFoodMultiplier(){return foodMultiplier;}

void Animal::setAge(int ageInDays){
	age = ageInDays;
}