#include <iostream>
#include <string>
#include <windows.h>
#include <conio.h>

using namespace std;

typedef int Element;

typedef struct node {
    Element data;
    struct node *next;
}ListNode;

class List {
public:
    void InitList();                                // 初始化链表
    bool DestoryList();                             // 销毁链表
    bool ClearList();                               // 清除链表
    bool EmptyList();                               // 判断链表是否为空
    bool ListInsert(Element item, int insertPos);   // 在指定位置插入item
    bool ListDelete(Element item);                  // 删除item
    int ListLength();                               // 返回链表长度
    int LocateItem(Element item);                   // 获取item位置
    Element GetItem(int itemPos);                   // 获取指定位置的item
    void ShowList(int x, int y);                    // 打印链表
    void ShowTips();                                // 打印提示信息
    void GetCmd();                                  // 执行操作
    void gotoxy(int x, int y);                      // 将光标移动到指定坐标 
    void createCell(int x, int y, string data);     // 创建一个单元格
    void getMaxLength();                            // 获取单元格大小
private:
    ListNode *root;
    int cellLength;
};

void List::gotoxy(int x,int y) { // 将光标移动到指定坐标 
	COORD pos = {x,y};
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOut,pos);
}

void List::getMaxLength() { // 获取单元格大小
    ListNode *tmp = root;
    while (tmp) {
        string tmpData = to_string(tmp->data);
        if (cellLength < tmpData.length() + 2)
            cellLength = tmpData.length() + 2;
        tmp = tmp->next;
    }
}

void List::createCell(int x, int y, string data) { // 创建一个单元格
    gotoxy(x, y);
    cout << '+';
    gotoxy(x, y + 2);
    cout << '+';
    gotoxy(x + cellLength - 1, y);
    cout << '+';
    gotoxy(x + cellLength - 1, y + 2);
    cout << '+';
    gotoxy(x, y + 1);
    cout << '|';
    gotoxy(x + cellLength - 1, y + 1);
    cout << '|';
    for (int i = 1; i <= cellLength - 2; i++) {
        gotoxy(x + i, y);
        cout << '-';
        gotoxy(x + i, y + 2);
        cout << '-';
        if (i == (cellLength - 2 - data.length()) / 2 + 1) {
            gotoxy(x + i, y + 1);
            cout << data;
        }
    }   
}

void List::InitList() { // 初始化链表
    root = new node;
    root->data = NULL;
    root->next = NULL;
    cellLength = 0;
}

bool List::DestoryList() { // 销毁链表
    ListNode *tmp = root;
    while (root) {
        tmp = root;
        root = root->next;
        delete tmp;
    }
    return true;
}

bool List::ClearList() { // 清空链表
    ListNode *tmp = root;
    while (tmp) {
        tmp->data = NULL;
        tmp = tmp->next;
    }
    return true;
}

bool List::EmptyList() { // 判断链表是否为空
    if (root->next)
        return false;
    return true;
}

bool List::ListInsert(Element item, int insertPos) { // 在指定位置插入item
    ListNode *tmp = root;
    ListNode *newNode = new node;
    int cnt = 0;
    while (tmp && cnt < insertPos - 1) {
        tmp = tmp->next;
        cnt++;
    }
    if (!tmp)
        return false;
    newNode->data = item;
    newNode->next = tmp->next;
    tmp->next = newNode;
    getMaxLength();
    return true;
}

bool List::ListDelete(Element item) { // 删除item
    ListNode *tmp = root;
    while (tmp) {
        if (tmp->next->data == item) {
            ListNode *newNode = new node;
            newNode = tmp->next;
            tmp->next = tmp->next->next;
            delete newNode;
            return true;
        }
        if (!tmp->next->next)
            break;
        tmp = tmp->next;
    }
    return false;
}

int List::ListLength() {// 返回链表长度
    ListNode *tmp = root;
    int cnt = 0;
    while (tmp) {
        cnt++;
        tmp = tmp->next;
    }
    return cnt;
}

int List::LocateItem(Element item) { // 获取item位置
    if (!root)
        return -1;
    ListNode *tmp = root;
    int cnt = 0;
    while (tmp) {
        if (tmp->data == item)
            return cnt;
        tmp = tmp->next;
        cnt++;
    }
    return -1;
}

Element List::GetItem(int itemPos) { // 获取指定位置的item
    if (!root) 
        return -1;
    ListNode *tmp = root;
    int cnt = 0;
    while (tmp && cnt < itemPos) {
        tmp = tmp->next;
        cnt++;
    }
    if (!tmp)
        return -1;
    return tmp->data;
}

void List::ShowList(int x, int y) { // 打印链表
    ListNode *tmp = root;
    int i = 0, j = 0;
    while (tmp->next) {
        if (i % 10 == 0 && i != 0)
            j += 3;
        createCell((i % 10) * cellLength + x, j + y, to_string(tmp->data));
        tmp = tmp->next;
        i++;
    }
    cout << endl;
}

void List::ShowTips() { // 打印提示信息
    gotoxy(60,10);
    cout << "+" << "------------" << "+" << endl;
    gotoxy(60,11);
    cout << "|" << "1: 插入数据 " << "|" << endl;
    gotoxy(60,12);
    cout << "|" << "2: 查找数据 " << "|" << endl;
    gotoxy(60,13);
    cout << "|" << "3: 删除数据 " << "|" << endl;
    gotoxy(60,14);
    cout << "|" << "4:顺序表长度" << "|" << endl;
    gotoxy(60,15);
    cout << "|" << "5:清空顺序表" << "|" << endl;
    gotoxy(60,16);
    cout << "|" << "6:销毁顺序表" << "|" << endl;
    gotoxy(60,17);
    cout << "|" << "7:打印顺序表" << "|" << endl;
    gotoxy(60,18);
    cout << "+" << "------------" << "+" << endl;
}

void List::GetCmd() { // 顺序表操作
    while (true) {
        ShowTips();
        char choice = getch();
        system("cls");
        switch (choice) {
        case '1': // 插入
            Element item;
            int insertPos;
            gotoxy(60,10);
            cout << "需要插入的数据为:";
            cin >> item;
            gotoxy(60,11);
            cout << "插入数据的位置为:";
            cin >> insertPos;
            gotoxy(60,12);
            if (ListInsert(item, insertPos))
                cout << "数据插入成功" << endl;
            else 
                cout << "数据插入失败" << endl;
            break;
        case '2': // 查找
            gotoxy(60,10);
            cout << "+" << "------------------" << "+" << endl;
            gotoxy(60,11);
            cout << "|" << "1:查找指定数据位置" << "|" << endl;
            gotoxy(60,12);
            cout << "|" << "2:查找指定位置数据" << "|" << endl;
            gotoxy(60,13);
            cout << "+" << "------------------" << "+" << endl;
            switch(getch()) {
            case '1':
                system("cls");
                gotoxy(60,10);
                cout << "需要查找的数据:";
                cin >> item;
                gotoxy(60,11);
                if (LocateItem(item) != -1)
                    cout << "数据位置为: " << LocateItem(item) << endl;
                else    
                    cout << "查找失败" << endl;
                break;
            case '2':  
                system("cls");
                int itemPos;
                gotoxy(60,10);
                cout << "需要查找数据的位置:";
                cin >> itemPos;
                gotoxy(60,11);
                if (GetItem(itemPos) != -1)
                    cout << "数据为: " << GetItem(itemPos) << endl;
                else    
                    cout << "查找失败" << endl;
                break;
            }
            break;
        case '3': // 删除
            gotoxy(60,10);
            cout << "需要删除的数据:";
            cin >> item;
            gotoxy(60,11);
            if (ListDelete(item))
                cout << "删除成功" << endl;
            else
                cout << "删除失败" << endl;
            break;  
        case '4': // 获取链表长度
            gotoxy(60,10);
            cout << "顺序表长度为:" << ListLength() << endl; 
            break;
        case '5': // 清除顺序表
            gotoxy(60,10);
            if (ClearList())
                cout << "清除成功" << endl;
            else
                cout << "清除失败" << endl;
            break;
        case '6': // 销毁顺序表
            gotoxy(60,10);
            if (DestoryList())
                cout << "销毁成功" << endl;
            else
                cout << "销毁失败" << endl;
            break;
        case '7': // 打印顺序表
            ShowList(0, 0);
            break;
        }
        getch();
        system("cls");
    }
}

int main() {
    List newList;
    newList.InitList();
    for (int i = 0; i < 20; i++) 
        newList.ListInsert(i, i);
    newList.GetCmd();
    system("pause");
}