#include "Maze.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

using namespace std;

const string icon[] = {"¡ý", "¡ú", "¡ü", "¡û", "¡õ", "¡ö"};

struct node {
    int x;
    int y;
    int dir;
    bool operator == (const node tmp) {
        if (this->x == tmp.x && this->y == tmp.y)
            return true;
        return false;
    }
};

void gotoxy(int x,int y) {  
	COORD pos = {x,y};
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOut,pos);
}

void color(int x) {
	if(x >= 0 && x <= 15)
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),x);
	else
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);	
}

class PathFind {
public:
    PathFind(int len, int hei, int model);
    void GetPath(int x, int y);
    void ShowMaze();  
    void ShowShortPath();  
    void InitRecode();
private:
    char **maze;
    int **recode;
    int mazeLength;
    int mazeHeight;
    int minStep;
private:
    Stack<node> mazeStack;
    Stack<node> shortPath;
    node start;
    node end;
};

PathFind::PathFind(int len, int hei, int model) {
    mazeLength = len;
    mazeHeight = hei;
    maze = new char *[mazeLength];
    recode = new int *[mazeLength];
    for (int i = 0; i < mazeLength; i++) {
        maze[i] = new char[mazeHeight];
        recode[i] = new int[mazeHeight];
    }
    Maze newMaze(len, hei);
    if (model == 0)
        maze = newMaze.CreateNormalMaze();
    if (model == 1) {
        int den;
        cout << "input wallDensity : ";
        cin >> den;
        maze = newMaze.CreateRandomMaze(den);
    }
    start.x = 1;
    start.y = 1;
    start.dir = 0;
    end.x = mazeLength - 2;
    end.y = mazeHeight - 2;
    mazeStack.Push(start);
    minStep = 0x3f3f3f3f;
}

void PathFind::InitRecode() {
    Stack<node>tmpStack = mazeStack;
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
            Stack<node>tmpPath = mazeStack;
            while (!tmpPath.EmptyStack()) {
                node now = tmpPath.Pop();
                shortPath.Push(now);
            }
        }
        Stack<node>tmpStack;
        while (!mazeStack.EmptyStack()) {
            node now = mazeStack.Pop();
            tmpStack.Push(now);
        }
        while (!tmpStack.EmptyStack()) {
            node now = tmpStack.Pop();
            mazeStack.Push(now);
            color(14);
            gotoxy(now.x * 2, now.y);
            cout << icon[now.dir];
            Sleep(100);
        }
        tmpStack = mazeStack;
        while (!tmpStack.EmptyStack()) {
            node now = tmpStack.Pop();
            gotoxy(now.x * 2, now.y);
            cout << "  ";
            Sleep(100);
        }
        return;
    }
    for (int i = 0; i < 4; i++) {
        int next[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        node now;
        now.x = x + next[i][0];
        now.y = y + next[i][1];
        now.dir = i;
        if (now.x < 1 || now.x > mazeLength || now.y < 1 || now.y > mazeHeight)
            continue;
        if (maze[now.x][now.y] != '#' && recode[now.x][now.y] == 0) {
            node top = mazeStack.Pop();
            top.dir = i;
            mazeStack.Push(top);
            recode[now.x][now.y] = 1;
            mazeStack.Push(now);
            GetPath(now.x, now.y);
            recode[now.x][now.y] = 0;
            mazeStack.Pop();
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
        node now = shortPath.Pop();
        if (now.x == start.x && now.y == start.y)
            continue;
        if (now.x == end.x && now.y == end.y)
            break;
        gotoxy(now.x * 2, now.y);
        cout << icon[now.dir];
        Sleep(100);
    }
    color(7);
    gotoxy(0, mazeHeight);
    cout << "²½ÊýÎª : " << minStep << endl;
}

void PathFind::ShowMaze() {
    for (int i = 0; i < mazeLength; i++) {
        for (int j = 0; j < mazeHeight; j++) {
            gotoxy(i * 2, j);
            if (maze[i][j] == '#')
                cout << icon[5];
            else
                cout << "  ";
        }
    }
}

int main() {
    while (true) {
        int len, hei, model;
        cout << "input mazeLength : ";
        cin >> len;
        cout << "input mazeHeight : ";
        cin >> hei;
        cout << "input maze model : ";
        cin >> model;
        PathFind test(len, hei, model);
        test.ShowMaze();
        test.InitRecode();
        test.GetPath(1, 1);
        test.ShowShortPath();
        system("pause");
        system("cls");
    }
}
