// CPPapp1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <conio.h>
#include <Windows.h>

const int mapheight = 15;
const int mapwidth  = 15;

const int mapsize = mapheight * mapwidth;

int map[mapsize];

enum Move { up , right, down, left, no_move };
Move move = up;
int head_x;
int head_y;
int food = 3;
bool running;


Move getMove(char key) {
	switch (key) { //arrows
	case 'w':
		return up;
		break;
	case 'd':
		return right;
		break;
	case 's':
		return down;
		break;
	case 'a':
		return left;
		break;
	}
	return no_move;
}
void generateFood() {
	int cell = 0;
	do {
		cell = (rand() % (mapheight - 2) + 1)*mapwidth + rand() % (mapwidth - 2) + 1;
	} while (map[cell] != 0);
	map[cell] = -2;
}
void processMove(Move m) {
	int dx, dy;
	switch (m) {
	case up:
		dx = 0;
		dy = -1;
		break;
	case right:
		dx = 1;
		dy = 0;
		break;
	case down:
		dx = 0;
		dy = 1;
		break;
	case left:
		dx = -1;
		dy = 0;
		break;
	case no_move:
		dx = 0;
		dy = 0;
		break;
	}

	int newx = dx + head_x;
	int newy = dy + head_y;

	int current = newy*mapwidth + newx;
	if (map[current] == -2) { // food
		food++;
		generateFood();
	}
	else if (map[current] != 0) { // wall 
		running = false;
	}
	
	head_x = newx;
	head_y = newy;

	map[current] = food + 1;
}


void start() {
	head_x = 3;
	head_y = 3;
	move = right;
	for (int i = 0; i < mapsize; i++)
		map[i] = 0;
	for (int i = 0; i < mapheight; i++) {
		map[i*mapwidth] = -1;
		map[(i + 1)*mapwidth - 1] = -1;
	}
	for (int i = 0; i < mapwidth; i++) {
		map[i] = -1;
		map[mapwidth*(mapheight - 1) + i] = -1;
	}
	generateFood();
}
void printMap() {
	for (int i = 0; i < mapheight; i++) {
		for (int j = 0; j < mapwidth; j++) {
			int current = map[i*mapwidth + j];
			if (current == 0)
				std::cout << '_';
			else if (current == -1)
				std::cout << 'X';
			else if (current > 0)
				std::cout << 'o';
			else
				std::cout << 'F';
			std::cout << " ";
		}
		std::cout << '\n';
	}
}
void updateMap() {
	for (int i = 1; i < mapheight - 1; i++)
		for (int j = 1; j < mapwidth - 1; j++)
			if (map[i*mapwidth + j]>0)
				map[i*mapwidth + j]--;
}


void set_console_color() { // default color
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}
void set_console_color(int color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}


int main()
{
	running = 1;
	start();
	printMap();
	while (running) {
		if (_kbhit()) {
			char c = _getch();
			move = getMove(c);
		}
		processMove(move);
		updateMap();
		system("cls");
		printMap();
		Sleep(500/food);
	}
	std::cout << "Game over. Your score is: " << food << '\n';
	char c;
	while (true) {
		c = _getch();
		if (c == 'r') {
			food = 3;
			main();
		}
	}
	std::cin.ignore();
}




// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file



