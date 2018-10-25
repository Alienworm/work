#include <iostream>
#include <cstring>
#include <malloc.h>
#include <windows.h>
#include <string>
#include <conio.h>

#define LIST_INIT_SIZE 20
#define LISTINCREAMENT 10

using namespace std;

typedef int Element;

typedef struct {
    Element *elem;
    int length;
    int listSize;
}SeqList;

class List {
public:
    void InitList();                                // 初始化顺序表
    bool DestoryList();                             // 销毁顺序表
    bool ClearList();                               // 清空顺序表
    bool EmptyList();                               // 判断顺序表是否为空
    bool addListLength();                           // 增加顺序表存储空间
    bool ListInsert(Element item, int insertPos);   // 在指定位置插入item
    bool ListDelete(Element item);                  // 删除item
    int LocateItem(Element item);                   // 获取item位置
    int ListLength();                               // 返回顺序表长度
    void ShowList(int x, int y);                    // 打印顺序表
    void ShowTips();                                // 打印提示信息
    void GetCmd();                                  // 执行操作
    Element GetItem(int itemPos);                   // 获取指定位置的item
    void gotoxy(int x, int y);                      // 将光标移动到指定坐标 
    void createCell(int x, int y, string data);     // 创建一个单元格
    void getMaxLength();                            // 获取单元格大小
private:
    SeqList *root;
    int cellLength;
};

void List::gotoxy(int x,int y) { // 将光标移动到指定坐标 
	COORD pos = {x,y};
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOut,pos);
}

void List::getMaxLength() { // 获取单元格大小
    for (int i = 0; i < root->length; i++) {
        string tmp = to_string(root->elem[i]);
        if (cellLength < tmp.length() + 2)
            cellLength = tmp.length() + 2;
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

void List::InitList() { // 初始化顺序表
    root = new SeqList;
    root->elem = new int[LIST_INIT_SIZE];
    root->listSize = LIST_INIT_SIZE;
    root->length = 0;
    cellLength = 0;
}

bool List::DestoryList() { // 销毁顺序表
    delete root->elem;
    delete root;
    return true;
}

bool List::ClearList() { // 清空顺序表
    for (int i = 0; i < root->length; i++) 
        root->elem[i] = NULL;
    return true;
}

bool List::EmptyList() { // 判断顺序表是否为空
    if (root->elem[0] != NULL)
        return false;
    return true;
}

bool List::addListLength() { // 增加顺序表存储空间
    int *tmp = new int[LISTINCREAMENT + root->listSize];
    memcpy(tmp, root->elem, _msize(root->elem));
    delete root->elem;
    root->elem = tmp;
    root->listSize += LISTINCREAMENT;
    return true;
}

bool List::ListInsert(Element item, int insertPos) { // 在指定位置插入item
    if (insertPos > root->length || insertPos < 0)
        return false;
    if (root->length + 1 > root->listSize) 
        addListLength();
    for (int i = root->length; i > insertPos; i--)
        root->elem[i] = root->elem[i - 1];
    root->elem[insertPos] = item;
    root->length++;
    getMaxLength();
    return true;
}

bool List::ListDelete(Element item) { // 删除item
    int flag = 0;
    for (int i = 0; i < root->length; i++) {
        if (root->elem[i] == item)
            flag = 1;
        if (flag == 1)
            root->elem[i] = root->elem[i + 1];
    }
    root->length--;
    getMaxLength();
    if (flag)
        return true;
    return false;
}
int List::LocateItem(Element item) { // 获取item位置
    for (int i = 0; i < root->length; i++) 
        if (item == root->elem[i])
            return i;
    return -1;
}

int List::ListLength() { // 返回顺序表长度
    return root->length;    
}

Element List::GetItem(int itemPos) { // 获取指定位置的item
    if (itemPos > root->length || itemPos < 0)
        return -1;
    return root->elem[itemPos];
}

void List::ShowList(int x, int y) { // 打印顺序表
    for (int i = 0, j = 0; i < root->length; i++) {
        if (i % 10 == 0 && i != 0)
            j += 3;
        createCell((i % 10) * cellLength + x, j + y, to_string(root->elem[i]));
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
    for (int i = 0; i < 10; i++)
        newList.ListInsert(i, i);
    newList.GetCmd();
    system("pause");
}