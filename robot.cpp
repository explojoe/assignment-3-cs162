/*********************************************************************
** Program Filename: robot.cpp
** Author: Joshua Wentzel
** Date: 2/15/2018
** Description: Play Zoo Tycoon.
** Input: Playing cards to guess for.
** Output: Zoo Tycoon gameplay.
*********************************************************************/

#include <iostream>

#include "robot.hpp"

using namespace std;

Robot::Robot(){
	cost = 30000;
	babyCount = 1;
	foodMultiplier = 2;
}