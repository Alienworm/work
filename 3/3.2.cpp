#include "Queue.h"
#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <windows.h>

using namespace std;

int main() {
    for (int windows = 0; windows < 10; windows++) {
        Queue<int> guest;
        int cashierTime[100] = {0};
        int totalTime = 0, averageTime = 0, departs = 0;
        for (int cnt = 1; cnt <= 100; cnt++)
            guest.Push(cnt * 15);
        while (!guest.IsEmpty()) {
            for (int i = 0; i <= windows; i++) {
                if (!guest.IsEmpty()) {
                    int now = guest.Pop();
                    if (now > cashierTime[i])
                        departs = now + 120;
                    else
                        departs = cashierTime[i] + 120;
                    cashierTime[i] = departs;
                    totalTime += departs - now;
                }
            }
        }
        cout << totalTime << endl;       
    }
    system("pause");
}