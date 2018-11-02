#include "Queue.h"
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include <string>
#include <iostream>
#include <algorithm>
#include <math.h>

using std::string;
using std::cout;
using std::min;

struct node {
    int x, y;
    int f, g, h;
    int dir;
    node() {
        f = 0;
        g = 0;
        h = 0;
    }
};

const string icon[] = {"¡ý", "¡ú", "¡ü", "¡û", "¡õ", "¡ö"};

class AstarPathFind {
public:
    void InitMaze(char **_maze, int _mazeLength, int _mazeHeight);
    void ShowMaze();
    void ShowSetNode(Queue<node> set, int col);
    void ShowPath();
    void GetPath(int x, int y);
    int GetH(node first, node second);
    bool IsInclude(Queue<node> set, node qur);
    void StartSearch();
    void gotoxy(int x, int y);
    void color(int x);
    Queue<node> FindMinNodeF(Queue<node> set);
private:
    
private:
    Queue<node> openSet;
    Queue<node> closeSet;
private:
    node **nodeMaze;
    node **path;
    node start, finish;
    char **maze;
    int mazeLength;
    int mazeHeight;
    int minStep;
    int next[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
};

void AstarPathFind::gotoxy(int x,int y) {  
	COORD pos = {x,y};
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOut,pos);
}

void AstarPathFind::color(int x) {
	if(x >= 0 && x <= 15)
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),x);
	else
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);	
}

void AstarPathFind::InitMaze(char **_maze, int _mazeLength, int _mazeHeight) {
    mazeLength = _mazeLength;
    mazeHeight = _mazeHeight;
    maze = new char *[mazeLength];
    path = new node *[mazeLength];
    nodeMaze = new node *[mazeLength];
    for (int i = 0; i < mazeLength; i++) {
        maze[i] = new char[mazeHeight];
        path[i] = new node[mazeHeight];
        nodeMaze[i] = new node[mazeHeight];
        for (int j = 0; j < mazeHeight; j++) {
            maze[i][j] = _maze[i][j];
            nodeMaze[i][j].x = i;
            nodeMaze[i][j].y = j;
        }
    }
    start.x = 1;
    start.y = 1;
    start.f = 0;
    start.dir = 0;
    finish.x = mazeLength - 2;
    finish.y = mazeHeight - 2;
    finish.f = 0;
    finish.dir = 0;
}

void AstarPathFind::ShowMaze() {
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

void AstarPathFind::ShowSetNode(Queue<node> set, int col) {
    Queue<node> tmpSet;
    while (!set.IsEmpty()) {
        node now = set.PopFront();
        tmpSet.PushBack(now);
    }
    while (!tmpSet.IsEmpty()) {
        node now = tmpSet.PopFront();
        set.PushBack(now);
        color(col);
        gotoxy(now.x * 2, now.y);
        if (col == 4)
            cout << icon[now.dir];
        else
            cout << icon[now.dir];
    }
}

void AstarPathFind::ShowPath() {
    ShowSetNode(openSet, 4);
    ShowSetNode(closeSet, 14);
}

void AstarPathFind::GetPath(int x, int y) {
    if (x == start.x && y == start.y)
        return;
    GetPath(path[x][y].x, path[x][y].y);
    gotoxy(x * 2, y);
    cout << icon[5];
}

int AstarPathFind::GetH(node first, node second) {
    int h_dis = min(abs(first.x - second.x), abs(first.y - second.y));
    int h_str = abs(first.x - second.x) + abs(first.y - second.y);
    return (14 * h_dis + 10 * (h_str - 2 * h_dis));
}

bool AstarPathFind::IsInclude(Queue<node> set, node qur) {
    Queue<node> tmpSet;
    while (!set.IsEmpty()) {
        node now = set.PopFront();
        tmpSet.PushBack(now);
    }
    int flag = 0;
    while (!tmpSet.IsEmpty()) {
        node now = tmpSet.PopFront();
        set.PushBack(now);
        if (now.x == qur.x && now.y == qur.y)
            flag = 1;
    }
    if (flag == 1)
        return true;
    return false;
}

Queue<node> AstarPathFind::FindMinNodeF(Queue<node> set) {
    int minF = 0x3f3f3f3f, cnt = 0;
    int len = set.Length();
    node recode;
    for (int i = 0; i < len; i++) {
        node now = set.PopFront();
        if (now.f < minF) {
            if (cnt != 0)
                set.PushBack(recode);
            minF = now.f;
            recode = now;
            cnt++;
        }
        else {
            set.PushBack(now);
        }
    }
    set.PushFront(recode);
    return set;
}

void AstarPathFind::StartSearch() {
    int cnt = 0, flag = 0;
    openSet.PushFront(start);
    while (!openSet.IsEmpty()) {
        openSet = FindMinNodeF(openSet);
        node now = openSet.Front();
        if (now.x == finish.x && now.y == finish.y) {
            color(11);
            GetPath(finish.x, finish.y);
            break;
        }
        openSet.PopFront();
        closeSet.PushFront(now);
        for (int i = 0; i < 4; i++) {
            flag = 0;
            int tx = now.x + next[i][0];
            int ty = now.y + next[i][1];
            node nei = nodeMaze[tx][ty];
            nei.dir = i;
            if (maze[tx][ty] == '#' || tx > mazeLength || tx < 1 || ty > mazeHeight || ty < 1)
                continue;
            if (IsInclude(closeSet, nei))
                continue;
            node tmp;
            tmp.g = now.g + 10;
            if (!IsInclude(openSet, nei)) {
                path[tx][ty].x = now.x;
                path[tx][ty].y = now.y;
                openSet.PushFront(nei);
                flag = 1;
            }
            else if (tmp.g >= nei.g)
                continue;
            if (flag == 1)
                openSet.PopFront();
            path[tx][ty].x = now.x;
            path[tx][ty].y = now.y;
            nei.g = tmp.g;
            nei.h = GetH(nei, finish);
            nei.f = nei.g + nei.h;
            nodeMaze[tx][ty] = nei;
            openSet.PushFront(nei);
        }
        ShowPath();
        Sleep(100);
    }
    gotoxy(mazeHeight * 2+ 1, 0);
}