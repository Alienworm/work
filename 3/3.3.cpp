#include "PathFind.h"
#include "Astar.h"
#include <iostream>
// #include <thread>

using namespace std;

struct avg {
	int mazeLength;
	int mazeHeight;
	char **maze;
};

void DfsPathFinding(avg *avgNode) {
    PathFind dfs;
    dfs.InitMaze(avgNode->maze, avgNode->mazeLength, avgNode->mazeHeight);
    dfs.ShowMaze();
    dfs.GetPath(1, 1);
    dfs.ShowShortPath();
    dfs.color(15);
}   

void AstarPathFinding(avg *avgNode) {
    AstarPathFind astr;
    astr.InitMaze(avgNode->maze, avgNode->mazeLength, avgNode->mazeHeight);
    astr.ShowMaze();
    astr.StartSearch();
	astr.color(15);
}

int main() {
    while (true) {
        int mazeLength, mazeHeight, mazeModel;
        cout << "Please input mazeLength : ";
        cin >> mazeLength;
        cout << "Please input mazeHeight : ";
        cin >> mazeHeight;
        cout << "Please input maze model(1:normal mzae 2:random maze): ";
        cin >> mazeModel;
        system("cls");
        Maze newMaze(mazeLength, mazeHeight);
		avg *avgNode = new avg;
		avgNode->mazeLength = mazeLength;
		avgNode->mazeHeight = mazeHeight;
        if (mazeModel == 1)
		    avgNode->maze = newMaze.CreateNormalMaze();
		if (mazeModel == 2)
            avgNode->maze = newMaze.CreateRandomMaze(4);
        /*
        thread astr(AstarPathFinding, avgNode);
		Sleep(100);
		thread dfs(DfsPathFinding, avgNode);
		Sleep(100);
        dfs.detach();
		astr.detach();
        */
        AstarPathFinding(avgNode);
        DfsPathFinding(avgNode);
		getch();
		system("cls");
    }
}