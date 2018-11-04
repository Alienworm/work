#include "Maze.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

using std::string;
using std::cout;
using std::endl;

string icon[] = {"¡ý", "¡ú", "¡ü", "¡û", "¡õ", "¡ö"};

struct PathNode {
    int x;
    int y;
    int dir;
    bool operator == (const PathNode tmp) {
        if (this->x == tmp.x && this->y == tmp.y)
            return true;
        return false;
    }
};

class PathFind {
public:
    void InitMaze(char **_maze, int _mazeLength, int _mazeHeight);
    void GetPath(int x, int y);
    void ShowMaze();  
    void ShowShortPath();  
    void InitRecode();
    void gotoxy(int x, int y);
    void color(int x);
private:
    char **maze;
    int **recode;
    int mazeLength;
    int mazeHeight;
    int minStep;
private:
    Stack<PathNode> mazeStack;
    Stack<PathNode> shortPath;
    PathNode start;
    PathNode end;
    int next[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
};

void PathFind::gotoxy(int x,int y) {
    x += mazeLength * 2;  
	COORD pos = {x,y};
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOut,pos);
}

void PathFind::color(int x) {
	if(x >= 0 && x <= 15)
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),x);
	else
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);	
}

void PathFind::InitMaze(char **_maze, int _mazeLength, int _mazeHeight) {
    mazeLength = _mazeLength;
    mazeHeight = _mazeHeight;
    maze = new char *[mazeLength];
    recode = new int *[mazeLength];
    for (int i = 0; i < mazeLength; i++) {
        maze[i] = new char[mazeHeight];
        recode[i] = new int[mazeHeight];
    }
    maze = _maze;
    start.x = 1;
    start.y = 1;
    start.dir = 0;
    end.x = mazeLength - 2;
    end.y = mazeHeight - 2;
    mazeStack.Push(start);
    minStep = 0x3f3f3f3f;
}

void PathFind::InitRecode() {
    Stack<PathNode>tmpStack = mazeStack;
    for (int i = 0; i < mazeLength; i++) {
        for (int j = 0; j < mazeHeight; j++) {
            if (maze[i][j] == '#')
                recode[i][j] = 1;
            else
                recode[i][j] = 0;
        }
    }
}

void PathFind::GetPath(int x, int y) {
    if (x == end.x && y == end.y) {
        if (minStep > mazeStack.Size()) {
            minStep = mazeStack.Size();
            shortPath.ClearStack();
            Stack<PathNode>tmpPath = mazeStack;
            while (!tmpPath.EmptyStack()) {
                PathNode now = tmpPath.Pop();
                shortPath.Push(now);
            }
        }
        return;
    }
    for (int i = 0; i < 4; i++) {
        PathNode now;
        now.x = x + next[i][0];
        now.y = y + next[i][1];
        now.dir = i;
        if (now.x < 1 || now.x > mazeLength || now.y < 1 || now.y > mazeHeight)
            continue;
        if (maze[now.x][now.y] != '#' && recode[now.x][now.y] == 0) {
            PathNode top = mazeStack.Pop();
            top.dir = i;
            mazeStack.Push(top);
            recode[now.x][now.y] = 1;
            mazeStack.Push(now);
            color(14);
            gotoxy(now.x * 2, now.y);
            cout << icon[now.dir];
            // Sleep(100);
            GetPath(now.x, now.y);
            recode[now.x][now.y] = 0;
            mazeStack.Pop();
            gotoxy(now.x * 2, now.y);
            cout << "  ";
            // Sleep(100);
        }
    }
}

void PathFind::ShowShortPath() {
    color(12);
    gotoxy(start.x * 2, start.y);
    cout << icon[4];
    gotoxy(end.x * 2, end.y);
    cout << icon[4];
    color(14);
    while (!shortPath.EmptyStack()) {
        PathNode now = shortPath.Pop();
        if (now.x == start.x && now.y == start.y)
            continue;
        if (now.x == end.x && now.y == end.y)
            break;
        gotoxy(now.x * 2, now.y);
        cout << icon[5];
        Sleep(100);
    }
    color(15);
}

void PathFind::ShowMaze() {
	color(15);
    for (int i = 0; i < mazeLength; i++) {
        for (int j = 0; j < mazeHeight; j++) {
            gotoxy(i * 2, j);
            if (maze[i][j] == '#')
                cout << icon[5];
            else
                cout << "  ";
        }
    }
    InitRecode();
}
