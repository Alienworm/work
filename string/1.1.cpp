#include "String.h"
#include <iostream>

using namespace std;

int main() {
    String str = "123";
    String test = "123";
    cout << str.Compare(test) << endl;
    cout << (str == test) << endl;
    cin >> test;
    cout << str.Compare(test) << endl;
    cout << (str == test) << endl;
    system("pause");
}