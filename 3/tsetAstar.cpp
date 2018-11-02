#include "Astar.h"
#include "Maze.h"
#include <iostream>

using namespace std;

void color(int x) {
	if(x >= 0 && x <= 15)
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),x);
	else
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);	
}

int main () {
    int mazeLength, mazeHeight;
    while (true) {
        color(7);
        cin >> mazeLength >> mazeHeight;
        Maze maze(mazeLength, mazeHeight);
        AstarPathFind Astar;
        Astar.InitMaze(maze.CreateRandomMaze(4), mazeLength, mazeHeight);
        Astar.ShowMaze();
        Astar.StartSearch();
        system("pause");
        system("cls");
    }
}
