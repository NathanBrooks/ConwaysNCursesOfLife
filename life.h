// Life.h
// This class is used to create an ncurses conways game of life.
// Author: Demonix_Fox

#ifndef _Life_H
#define _Life_H 1

#include <ncurses.h>

class Life {
private:
	int PosX, PosY, CheckX, CheckY, MaxCheckX, 
		MaxCheckY, Count, SizeX, SizeY, WinX, WinY;
	int *PlayingSquare;
	int *CountSquare;
	int *AgeSquare;
	WINDOW *Window;
	void ShowSquare(); // update screen with new square
	int GetArray(int *,int,int); // get value from 2d array
	void SetArray(int *,int,int,int); // set value in 2d Array
public:
	Life(int, int, WINDOW *);
	~Life();
	void Reset(int,int, WINDOW *);
	void UpdateSquare(); // update square values and display
};



#endif