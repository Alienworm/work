#include "Queue.h"
#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <windows.h>

using namespace std;

struct guest {
    double arriveTime;
    double leaveTime;
};

void showWindows(int windows) {
    Queue<guest>guestQueue;
    int totalTime = 0;
    int otherTime[11] = {0};
    for (int i = 0; i < 100; i++) {
        guest tmp;
        tmp.arriveTime = i * 15;
        guestQueue.Push(tmp);
    }
    while (!guestQueue.IsEmpty()) {
        for (int i = 0; i <= windows; i++) {
            if (!guestQueue.IsEmpty()) {
                guest now = guestQueue.Pop();
                if (now.arriveTime > otherTime[i])
                    now.leaveTime = now.arriveTime + 120;
                else
                    now.leaveTime = otherTime[i] + 120;
                otherTime[i] = now.leaveTime;
                totalTime += now.leaveTime - now.arriveTime;
            }
        }
    }
    cout << totalTime / 100 << endl;
}

int main() {
    for (int windows = 0; windows <= 10; windows++) {
        showWindows(windows);
    }
    system("pause");
}