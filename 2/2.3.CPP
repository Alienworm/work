#include <iostream>
#include <string>
#include <ctype.h>

using namespace std;

struct Polynomial {
    int coe; // 系数
    int ind; // 指数
    struct Polynomial *next;
};

class List {
public:
    List();                                 // 初始化
    void ListInsert(int coe, int ind);      // 插入coe和ind
    void StrToList(string str);             // 把输入转化为List
    void GetCoeAndInd(string str);          // 获取coe和ind
    void SimplyPolynomial();                // 化简多项式
    string ShowPolynomial();                // 打印并返回多项式
public:
    Polynomial *root;
};

List::List() { // 初始化
    root = new Polynomial;
    root->coe = 0;
    root->ind = 0;
    root->next = NULL;
}

void List::ListInsert(int coe, int ind) { // 插入coe和ind
    Polynomial *tmp = root;
    Polynomial *newNode = new Polynomial;
    newNode->coe = coe;
    newNode->ind = ind;
    newNode->next = NULL;
    if (!root)
        root = newNode;
    tmp = root;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = newNode;
}

void List::GetCoeAndInd(string str) { // 获取coe和ind
    if (str[0] != '+' && str[0] != '-') 
        str = '+' + str;
    string coe = "";
    string ind = "";
    int coeFlag = 0, indFlag = 0;
    for (int i = 1; i < str.length(); i++) {
        if (str[i] == 'x' || str[i] == '^') 
            coeFlag = 1;
        if (str[i] == '-')
            indFlag = 1;
        if (isdigit(str[i])) {
            if (coeFlag)
                ind += str[i];
            else
                coe += str[i];
        }
    }
    if (coe == "")
        coe = "1";
    if (ind == "" && coeFlag)
        ind = "1";
    else if (ind == "" && !coeFlag)
        ind = "0";
    coe = str[0] + coe;
    if (indFlag)
        ind = '-' + ind;
    ListInsert(atoi(coe.c_str()), atoi(ind.c_str()));
}

void List::StrToList(string str) { // 把输入转化为List
    if (str == "Y=0")
        str = "Y=0x^0";
    int cnt = 0;
    while ((cnt = str.find(' ', cnt)) != string::npos)
        str.erase(cnt, 1);
    str += '+';
    string tmp = "";
    for (int i = 2; i < str.length(); i++) {
        if (str[i] == '+' || (str[i] == '-' && str[i-1] != '^')) {
            GetCoeAndInd(tmp);
            tmp = "";
        }
        tmp += str[i];
    }
    SimplyPolynomial();
}

void List::SimplyPolynomial() { // 化简多项式
    Polynomial *tmp = root->next;
    while (tmp) {
        Polynomial *now = tmp->next;
        while (now) {
            if (now->ind == tmp->ind) {
                tmp->coe += now->coe;
                now->coe = 0;
            }
            now = now->next;
        }
        tmp = tmp->next;
    }
}

string List::ShowPolynomial() { // 输出答案
    Polynomial *now = root->next;
    string poly = "Y =";
    while(now) {
        if (now->coe > 0)
            poly += '+';
        if (now->coe == 0) {
            now = now->next;
            continue;
        }
        else if (now->ind == 0)
            poly += to_string(now->coe);
        else if (now->coe == 1 && now->ind == 1)
            poly += "X";
        else if (now->coe == 1 && now->ind != 1)
            poly += "X^" + to_string(now->ind);
        else if (now->coe != 1 && now->ind == 1)
            poly += to_string(now->coe) + "X";
        else if (now->coe != 1 && now->ind != 1)
            poly += to_string(now->coe) + "X^" + to_string(now->ind); 
        now = now->next;
    }
    if (poly == "Y =")
        poly += "0";
    if (poly[3] == '+')
        poly[3] = ' ';
    return poly;
}

List combine(List L1, List L2, int model) { // 合并链表
    List ans, tmpList = L2;
    Polynomial *tmp1 = L1.root->next;
    while (tmp1) {
        Polynomial *tmp = tmpList.root->next;
        int coe = tmp1->coe;
        while (tmp) {
            if (tmp1->ind == tmp->ind && model == 0) {
                coe += tmp->coe;
                tmp->coe = 0;
            }
            if (tmp1->ind == tmp->ind && model == 1) {
                coe -= tmp->coe;
                tmp->coe = 0;
            }
            tmp = tmp->next;
        }
        ans.ListInsert(coe, tmp1->ind);
        tmp1 = tmp1->next;
    }
    while (tmpList.root) {
        ans.ListInsert(tmpList.root->coe, tmpList.root->ind);
        tmpList.root = tmpList.root->next;
    }
    return ans;
}

int main() { 
    int n, model;
    cout << "input a number: ";
    cin >> n;
    cout << "imput model: ";
    cin >> model;
    string polynomial;
    getline(cin, polynomial);  
    List ansList;
    for (int i = 0; i < n - 1; i++) {
        List tmpList, newList;
        if (i == 0) {
            cout << "input a polynomial: ";
            getline(cin, polynomial);  
            ansList.StrToList(polynomial);
        }
        cout << "input a polynomial: ";
        getline(cin, polynomial);  
        tmpList.StrToList(polynomial);
        newList = combine(ansList, tmpList, model);
        ansList = newList;
    }
    cout << "answer: " << ansList.ShowPolynomial() << endl;
    system("pause");
}