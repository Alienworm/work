#include "PathFind.h"
#include "Astar.h"
#include <iostream>
#include <process.h>

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
        int mazeLength, mazeHeight;
        cin >> mazeLength >> mazeHeight;
        Maze newMaze(mazeLength, mazeHeight);
        avg *avgNode = new avg;
        avgNode->mazeLength = mazeLength;
        avgNode->mazeHeight = mazeHeight;
        avgNode->maze = newMaze.CreateNormalMaze();
        DfsPathFinding(avgNode);
        AstarPathFinding(avgNode);
        system("pause");
        system("cls");
    }
}