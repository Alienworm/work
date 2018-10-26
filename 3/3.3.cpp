#include "Stack.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

using namespace std;

const string icon[] = {"↓", "→", "↑", "←", "□", "■"};

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

class Maze {
public:
    Maze(int len, int hei);
    void CreateMaze(int den);
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

Maze::Maze(int len, int hei) {
    mazeLength = len;
    mazeHeight = hei;
    maze = new char *[mazeLength];
    recode = new int *[mazeLength];
    for (int i = 0; i < mazeLength; i++) {
        maze[i] = new char[mazeHeight];
        recode[i] = new int[mazeHeight];
    }
    minStep = 0x3f3f3f3f;
}

void Maze::CreateMaze(int den) {
    srand(time(NULL));
    if (den == 0)
        den = 1;
    for (int i = 0; i < mazeLength; i++) {
        for (int j = 0; j < mazeHeight; j++) {
            int wall = rand() % den;
            maze[i][j] = '.';
            if (wall == 1) 
                maze[i][j] = '#';
            maze[0][j] = '#';
            maze[mazeLength - 1][j] = '#';
        }
        maze[i][0] = '#';
        maze[i][mazeHeight - 1] = '#';
    }
    maze[1][1] = '.';
    maze[mazeLength - 2][mazeHeight - 2] = '.';
    start.x = 1;
    start.y = 1;
    start.dir = 0;
    end.x = mazeLength - 2;
    end.y = mazeHeight - 2;
    mazeStack.Push(start);
}


void Maze::InitRecode() {
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

void Maze::GetPath(int x, int y) {
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
            gotoxy(now.x * 2, now.y);
            cout << icon[now.dir];
        }
        tmpStack = mazeStack;
        while (!tmpStack.EmptyStack()) {
            node now = tmpStack.Pop();
            gotoxy(now.x * 2, now.y);
            cout << "  ";
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

void Maze::ShowShortPath() {
    while (!shortPath.EmptyStack()) {
        node now = shortPath.Pop();
        gotoxy(now.x * 2, now.y);
        cout << icon[now.dir];
        Sleep(100);
    }
    gotoxy(0, mazeHeight);
    cout << "最小步数 : " << minStep << endl;
}

void Maze::ShowMaze() {
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
        int len, hei, den;
        cout << "input mazeLength : ";
        cin >> len;
        cout << "input mazeHeight : ";
        cin >> hei;
        cout << "input wallDensity : ";
        cin >> den;
        Maze test(len, hei);
        test.CreateMaze(den);
        test.ShowMaze();
        test.InitRecode();
        test.GetPath(1, 1);
        test.ShowShortPath();
        system("pause");
        system("cls");
    }
}