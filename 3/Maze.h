#include "Stack.h"
#include <string>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

using std::cout;
using std::string;
using std::endl;

class Maze {
public:
	Maze(int len, int hei);
	char **CreateNormalMaze();
    char **CreateRandomMaze(int den);
	bool isFullMark();
private:
    struct node {
        int x, y;
        bool isVisit;
    };
private:
	node head;
	Stack<node>mazeStack;
	node **nodeMaze;
	char **maze;
	int mazeLength;
	int mazeHeight;
};

Maze::Maze(int len, int hei) {
	mazeLength = len;
	mazeHeight = hei;
	maze = new char *[mazeLength];
	nodeMaze = new node *[mazeLength];
	for (int i = 0; i < mazeLength; i++) {
		maze[i] = new char[mazeHeight];
		nodeMaze[i] = new node[mazeHeight];
		for (int j = 0; j < mazeHeight; j++) {
			nodeMaze[i][j].isVisit = false;
			maze[i][j] = '#';
		}
	}
	maze[1][1] = '.';
	head.x = 1;
	head.y = 1;
	head.isVisit = true;
	nodeMaze[1][1].isVisit = true;
}

bool Maze::isFullMark() {
	for (int i = 1; i < mazeLength - 1; i += 2)
		for (int j = 1; j < mazeHeight - 1; j += 2)
			if (!nodeMaze[i][j].isVisit) {
				return false;
			}
	return true;
}

char** Maze::CreateNormalMaze() {
	srand(time(NULL));
	while (!isFullMark()) {
		node neighbor[4];
		int cnt = 0;
		for (int i = 0; i < 4; i++) {
			int nextDir[4][2] = { {0, 2}, {0, -2}, {2, 0}, {-2, 0} };
			node now;
			now.x = head.x + nextDir[i][0];
			now.y = head.y + nextDir[i][1];
			if (now.x < 1 || now.x > mazeLength - 1 || now.y < 1 || now.y > mazeHeight - 1)
				continue;
			if (!nodeMaze[now.x][now.y].isVisit && maze[now.x][now.y] == '#') 
				neighbor[cnt++] = now;
		}
		if (cnt != 0) {
			node now = neighbor[rand() % cnt];
			if (head.x == now.x) {
				maze[head.x][(head.y + now.y) / 2] = '.';
				nodeMaze[head.x][(head.y + now.y) / 2].isVisit = true;
			}
			if (head.y == now.y) {
				maze[(head.x + now.x) / 2][head.y] = '.';
				nodeMaze[(head.x + now.x) / 2][now.y].isVisit = true;
			}
			maze[now.x][now.y] = '.';
			nodeMaze[now.x][now.y].isVisit = true;
			now.isVisit = true;
			mazeStack.Push(now);
			head = now;
		}
		else if (cnt == 0 && !mazeStack.EmptyStack())
			head = mazeStack.Pop();
	}
	for (int i = 0; i < mazeLength; i++) {
		maze[i][0] = '#';
		maze[i][mazeHeight - 1] = '#';
	}
	for (int i = 0; i < mazeHeight; i++) {
		maze[0][i] = '#';
		maze[mazeLength - 1][i] = '#';
	}
	return maze;
}

char **Maze::CreateRandomMaze(int den) {
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
    return maze;
}
