/*********************************************************************
** Program Filename: monkey.cpp
** Author: Joshua Wentzel
** Date: 2/15/2018
** Description: Play Zoo Tycoon.
** Input: Playing cards to guess for.
** Output: Zoo Tycoon gameplay.
*********************************************************************/

#include <iostream>

#include "monkey.hpp"

using namespace std;

Monkey::Monkey(){
	cost = 15000;
	babyCount = 1;
	foodMultiplier = 4;
}