#include "life.h"
#include <time.h>
#include <stdlib.h>

#define COLOR_AGE 5 // when to color the old cell
#define DEATH_AGE 0 // when to kill the old cell 0 is no death
#define BRING_ALIVE 3 // number of adjacent pieces to become alive
#define MAX_ALIVE 3 // max number of cells that can be touching and still be alive
#define MIN_ALIVE 2 // min number of cells to stay alive

#define ALIVE_NUM 1 // number representing alive in PlayingSquare
#define DEAD_NUM 2 // number representing dead in Playing Square


// After initializing the square, this function will also call ShowSquare();
Life::Life(int X, int Y, WINDOW *new_window) {
	srand(time(NULL));
	Window = new_window;
	PosX = PosY = CheckX = CheckY = MaxCheckX = MaxCheckY = Count = 0;
	WinX = X;
	WinY = Y;
	SizeX = WinX - 4;
	SizeY = WinY - 4;
	PlayingSquare = new int[SizeX * SizeY];
	CountSquare = new int[SizeX * SizeY];
	AgeSquare = new int[SizeX * SizeY];

	for (int i = 0; i<SizeY; i++) {
		for (int j = 0; j<SizeX; j++) {
			SetArray(PlayingSquare,j,i,rand()%2+1);
			SetArray(AgeSquare,j,i,0);
		}
	}
	ShowSquare();
}

// After initializing the square, this function will also call ShowSquare();
void Life::Reset(int X, int Y, WINDOW *new_window) {
	delete [] PlayingSquare;
	delete [] CountSquare;
	delete [] AgeSquare;
	srand(time(NULL));
	Window = new_window;
	PosX = PosY = CheckX = CheckY = MaxCheckX = MaxCheckY = Count = 0;
	WinX = X;
	WinY = Y;
	SizeX = WinX - 4;
	SizeY = WinY - 4;
	PlayingSquare = new int[SizeX * SizeY];
	CountSquare = new int[SizeX * SizeY];
	AgeSquare = new int[SizeX * SizeY];

	for (int i = 0; i<SizeY; i++) {
		for (int j = 0; j<SizeX; j++) {
			SetArray(PlayingSquare,j,i,rand()%2+1);
			SetArray(AgeSquare,j,i,0);
		}
	}
	ShowSquare();
}

Life::~Life() {
	delete[] PlayingSquare;
	delete[] CountSquare;
	delete[] AgeSquare;

}

// This function is used to update the ncurses window with appropriate colors
void Life::ShowSquare() {
	for (int i=0;i<SizeY;i++) {
		for (int j=0;j<SizeX;j++) {
			if (GetArray(PlayingSquare,j,i) == ALIVE_NUM) {

				if ((GetArray(AgeSquare,j,i) >= COLOR_AGE) &&
					(COLOR_AGE != 0)) {
					wattron(Window,COLOR_PAIR(4));
				} else {
					wattron(Window,COLOR_PAIR(1));
				}

				if (GetArray(AgeSquare,j,i) >= 10) {
					mvwprintw(Window, i+2, j+2, "%i", (GetArray(AgeSquare,j,i)/10)%9);
				} else {
					mvwprintw(Window, i+2, j+2, "%i", GetArray(AgeSquare,j,i));
				}

				if ((GetArray(AgeSquare,j,i) >= COLOR_AGE) &&
					(COLOR_AGE != 0)) {
					wattroff(Window,COLOR_PAIR(4));
				} else {
					wattroff(Window,COLOR_PAIR(1));
				}

			} else {
				wattrset(Window,COLOR_PAIR(2));
				mvwprintw(Window, i+2,j+2, " ");
				wattroff(Window,COLOR_PAIR(2));
			}
		}
	}
	wrefresh(Window);
}

// used to update the values in the square for use in ShowSquare();
void Life::UpdateSquare() {
	for (int i=0;i<SizeY;i++) {
		for (int j=0;j<SizeX;j++) {
			SetArray(CountSquare,j,i,0);
		}
	}

	for (PosY=0;PosY<SizeY;PosY++) {
		for (PosX=0;PosX<SizeX;PosX++) {
			Count = 0;
			CheckX = PosX-1;
			MaxCheckX = CheckX+2;
			CheckY = PosY-1;
			MaxCheckY = CheckY+2;
			for (CheckY;CheckY<=MaxCheckY;CheckY++) {
				for (CheckX;CheckX<=MaxCheckX;CheckX++) {
					if ((CheckX >= 0 && CheckY >= 0) && 
						(CheckX < SizeX && CheckY < SizeY) &&
						!(CheckX == PosX && CheckY == PosY) && 
						GetArray(PlayingSquare,CheckX,CheckY) == ALIVE_NUM) {
							Count++;
						}
				}
				CheckX = PosX-1;
				SetArray(CountSquare,PosX,PosY,Count);
			}
		}
	}
	
	// modify the original square with the 4 rules and set age
	for (int i=0; i<SizeY; i++) {
		for (int j=0; j<SizeX; j++) {
			switch (GetArray(CountSquare,j,i)) {

				case BRING_ALIVE:
					SetArray(PlayingSquare,j,i,ALIVE_NUM);
					if (GetArray(AgeSquare,j,i) == 0) {
						SetArray(AgeSquare,j,i,1);
					} else {
						SetArray(AgeSquare,j,i,GetArray(AgeSquare,j,i) + 1);
					}
					break;
				
				default:
					if ((GetArray(CountSquare,j,i) < MIN_ALIVE) || 
						(GetArray(CountSquare,j,i) > MAX_ALIVE)) {
						SetArray(PlayingSquare,j,i,DEAD_NUM);
						SetArray(AgeSquare,j,i,0);
					}
					if (GetArray(PlayingSquare,j,i) == ALIVE_NUM) {
						SetArray(AgeSquare,j,i,GetArray(AgeSquare,j,i) + 1);
					}
					break;

			}
			if ((GetArray(AgeSquare,j,i) >= DEATH_AGE) && 
				(DEATH_AGE != 0)) {
				SetArray(PlayingSquare,j,i,DEAD_NUM);
				SetArray(AgeSquare,j,i,0);
			}
		}
	}
	ShowSquare();
}

// TODO: create 2d dynamic array class

// My 2d Dynamic array get array
int Life::GetArray(int *MyArray, int X, int Y) {
	return MyArray[X + (Y * SizeX)];
}
// my 2d Dynamic set array
void Life::SetArray(int *MyArray, int X, int Y, int Value) {
	MyArray[X + (Y * SizeX)] = Value;
}
