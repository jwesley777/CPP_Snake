// CPPapp1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <conio.h>
#include <Windows.h>


void set_console_color() { // default color
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}
void set_console_color(int color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

class Map {
	private:
		int height;
		int width;
		int mapSize;
		int food = 3;
	public:
		int map[160000];
		void setHeight(int h) {
			height = h;
		}
		int getHeight() {
			return height;
		}

		void setWidth(int w) {
			width = w;
		}
		int getWidth() {
			return width;
		}

		void setFood(int f) {
			food = f;
		}
		int getFood() {
			return food;
		}
		void generateFood() {
			int cell = 0;
			do {
				cell = (rand() % (height - 2) + 1)*width + rand() % (width - 2) + 1;
			} while (map[cell] != 0);
			map[cell] = -2;
		}

		void printMap() {
			for (int i = 0; i < height; i++) {
				for (int j = 0; j < width; j++) {
					int current = map[i*width + j];
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
			for (int i = 1; i < height - 1; i++)
				for (int j = 1; j < width - 1; j++)
					if (map[i*width + j]>0)
						map[i*width + j]--;
		}
};

enum Move { up , right, down, left, no_move };

class Snake {
	private:
		int headX;
		int headY;
		Move move = up;
	public:
		void setHeadX(int x) {
			headX = x;
		}
		int getHeadX() {
			return headX;
		}

		void setHeadY(int y) {
			headY = y;
		}
		int getHeadY() {
			return headY;
		}

		void setMove(Move m) {
			move = m;
		}
		Move getMove() {
			return move;
		}
};


class Game {
	public:
		Map map;
		Snake snake;
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

			int newx = dx + snake.getHeadX();
			int newy = dy + snake.getHeadY();

			int current = newy*map.getWidth() + newx;
			if (map.map[current] == -2) { // food
				map.setFood(map.getFood()+1);
				map.generateFood();
			}
			else if (map.map[current] != 0) { // wall 
				running = false;
			}
			
			snake.setHeadX(newx);
			snake.setHeadY(newy);

			map.map[current] = map.getFood() + 1;
		}

		void start() {
			snake.setHeadX(3);
			snake.setHeadY(3);
			snake.setMove(right);
			
			for (int i = 0; i < map.getHeight()*map.getWidth(); i++)
				map.map[i] = 0;
			for (int i = 0; i < map.getHeight(); i++) {
				map.map[i*map.getWidth()] = -1;
				map.map[(i + 1)*map.getWidth() - 1] = -1;
			}
			for (int i = 0; i < map.getWidth(); i++) {
				map.map[i] = -1;
				map.map[map.getWidth()*(map.getHeight() - 1) + i] = -1;
			}
			map.generateFood();
		}

		void runGame() {
			running = 1;
			start();
			map.printMap();
			while (running) {
				if (_kbhit()) {
					char c = _getch();
					snake.setMove(getMove(c));
				}
				processMove(snake.getMove());
				map.updateMap();
				system("cls");
				map.printMap();
				Sleep(500/map.getFood());
			}
			std::cout << "Game over. Your score is: " << map.getFood() << '\n';
			char c;
			while (true) {
				c = _getch();
				if (c == 'r') {
					map.setFood(3);
					runGame();
				}
			}
			std::cin.ignore();
		}
};

int main()
{
	Snake snake;
	Map map;
	map.setHeight(15);
	map.setWidth(15);

	Game game;
	game.map = map;
	game.snake = snake;

	game.runGame();	
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



