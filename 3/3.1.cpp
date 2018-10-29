#include "Stack.h"
#include <iostream>
#include <string>

using namespace std;

int main() {
    Stack<char>test;
    while (true) {
        string str;
        cout << "Please input a string : ";
        cin >> str;
        for (int i = 0; i < str.length(); i++) {
            if (str[i] == '{' || str[i] == '[' || str[i] == '(')
                test.Push(str[i]);
            switch (str[i]) {
            case '}':
                if (test.Top() == '{')
                    test.Pop();
                break;
            case ']':
                if (test.Top() == '[')
                    test.Pop();
                break;
            case ')':
                if (test.Top() == '(')
                    test.Pop();
                break;
            }
        }
        if (test.Top() != NULL)
            cout << "BAD!!!" << endl;
        else
            cout << "GOOD!!!" << endl;
        test.ClearStack();
    }
    system("pause");
}