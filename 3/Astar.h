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

string sing[] = {"¡ý", "¡ú", "¡ü", "¡û", "¡õ", "¡ö"};

struct AstarNode {
    int x, y;
    int f, g, h;
    int dir;
    AstarNode() {
        f = 0;
        g = 0;
        h = 0;
    }
};

class AstarPathFind {
public:
    void InitMaze(char **_maze, int _mazeLength, int _mazeHeight);
    void ShowMaze();
    void GetPath(int x, int y);
    int GetH(AstarNode first, AstarNode second);
    bool IsInclude(Queue<AstarNode> set, AstarNode qur);
    void StartSearch();
    void gotoxy(int x, int y);
    void color(int x);
    Queue<AstarNode> FindMinNodeF(Queue<AstarNode> set);
private:
    Queue<AstarNode> openSet;
    Queue<AstarNode> closeSet;
private:
    AstarNode **nodeMaze;
    AstarNode **path;
    AstarNode start, finish;
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
    path = new AstarNode *[mazeLength];
    nodeMaze = new AstarNode *[mazeLength];
    for (int i = 0; i < mazeLength; i++) {
        maze[i] = new char[mazeHeight];
        path[i] = new AstarNode[mazeHeight];
        nodeMaze[i] = new AstarNode[mazeHeight];
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
    color(15);
    for (int i = 0; i < mazeLength; i++) {
        for (int j = 0; j < mazeHeight; j++) {
            gotoxy(i * 2, j);
            if (maze[i][j] == '#')
                cout << sing[5];
            else
                cout << "  ";
        }
    }
}

void AstarPathFind::GetPath(int x, int y) {
    color(12);
    gotoxy(start.x * 2, start.y);
    cout << sing[4];
    gotoxy(finish.x * 2, finish.y);
    cout << sing[4];
    color(14);
    gotoxy(x * 2, y);
    cout << sing[5];
    if (x == start.x && y == start.y) {
        color(12);
        gotoxy(start.x * 2, start.y);
        cout << sing[4];
        return;
    }
    Sleep(100);
    GetPath(path[x][y].x, path[x][y].y);
}

int AstarPathFind::GetH(AstarNode first, AstarNode second) {
    int x = abs(first.x - second.x) * 10;
    int y = abs(first.y - second.y) * 10;
    return x + y;
}

bool AstarPathFind::IsInclude(Queue<AstarNode> set, AstarNode qur) {
    Queue<AstarNode> tmpSet;
    while (!set.IsEmpty()) {
        AstarNode now = set.PopFront();
        tmpSet.PushBack(now);
    }
    int flag = 0;
    while (!tmpSet.IsEmpty()) {
        AstarNode now = tmpSet.PopFront();
        set.PushBack(now);
        if (now.x == qur.x && now.y == qur.y)
            flag = 1;
    }
    if (flag == 1)
        return true;
    return false;
}

Queue<AstarNode> AstarPathFind::FindMinNodeF(Queue<AstarNode> set) {
    int minF = 0x3f3f3f3f, cnt = 0;
    int len = set.Length();
    AstarNode recode;
    for (int i = 0; i < len; i++) {
        AstarNode now = set.PopFront();
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
        AstarNode now = openSet.Front();
        color(10);
        gotoxy(now.x * 2, now.y);
        cout << sing[now.dir];
        if (now.x == finish.x && now.y == finish.y) {
            GetPath(finish.x, finish.y);
            break;
        }
        openSet.PopFront();
        closeSet.PushFront(now);
        for (int i = 0; i < 4; i++) {
            flag = 0;
            int tx = now.x + next[i][0];
            int ty = now.y + next[i][1];
            AstarNode nei = nodeMaze[tx][ty];
            nei.dir = i;
            if (maze[tx][ty] == '#' || tx > mazeLength || tx < 1 || ty > mazeHeight || ty < 1)
                continue;
            if (IsInclude(closeSet, nei))
                continue;
            AstarNode tmp;
            tmp.g = now.g + 10;
            if (!IsInclude(openSet, nei)) {
                path[tx][ty].x = now.x;
                path[tx][ty].y = now.y;
                openSet.PushFront(nei);
                flag = 1;
                color(10);
                gotoxy(now.x * 2, now.y);
                cout << sing[now.dir];
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
            color(10);
            gotoxy(now.x * 2, now.y);
            cout << sing[now.dir];
        }
       Sleep(100);
    }
}