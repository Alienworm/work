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
    void InitList();                                // ��ʼ��˳���
    bool DestoryList();                             // ����˳���
    bool ClearList();                               // ���˳���
    bool EmptyList();                               // �ж�˳����Ƿ�Ϊ��
    bool addListLength();                           // ����˳����洢�ռ�
    bool ListInsert(Element item, int insertPos);   // ��ָ��λ�ò���item
    bool ListDelete(Element item);                  // ɾ��item
    int LocateItem(Element item);                   // ��ȡitemλ��
    int ListLength();                               // ����˳�������
    void ShowList(int x, int y);                    // ��ӡ˳���
    void ShowTips();                                // ��ӡ��ʾ��Ϣ
    void GetCmd();                                  // ִ�в���
    Element GetItem(int itemPos);                   // ��ȡָ��λ�õ�item
    void gotoxy(int x, int y);                      // ������ƶ���ָ������ 
    void createCell(int x, int y, string data);     // ����һ����Ԫ��
    void getMaxLength();                            // ��ȡ��Ԫ���С
private:
    SeqList *root;
    int cellLength;
};

void List::gotoxy(int x,int y) { // ������ƶ���ָ������ 
	COORD pos = {x,y};
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOut,pos);
}

void List::getMaxLength() { // ��ȡ��Ԫ���С
    for (int i = 0; i < root->length; i++) {
        string tmp = to_string(root->elem[i]);
        if (cellLength < tmp.length() + 2)
            cellLength = tmp.length() + 2;
    }
}

void List::createCell(int x, int y, string data) { // ����һ����Ԫ��
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

void List::InitList() { // ��ʼ��˳���
    root = new SeqList;
    root->elem = new int[LIST_INIT_SIZE];
    root->listSize = LIST_INIT_SIZE;
    root->length = 0;
    cellLength = 0;
}

bool List::DestoryList() { // ����˳���
    delete root->elem;
    delete root;
    return true;
}

bool List::ClearList() { // ���˳���
    for (int i = 0; i < root->length; i++) 
        root->elem[i] = NULL;
    return true;
}

bool List::EmptyList() { // �ж�˳����Ƿ�Ϊ��
    if (root->elem[0] != NULL)
        return false;
    return true;
}

bool List::addListLength() { // ����˳����洢�ռ�
    int *tmp = new int[LISTINCREAMENT + root->listSize];
    memcpy(tmp, root->elem, _msize(root->elem));
    delete root->elem;
    root->elem = tmp;
    root->listSize += LISTINCREAMENT;
    return true;
}

bool List::ListInsert(Element item, int insertPos) { // ��ָ��λ�ò���item
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

bool List::ListDelete(Element item) { // ɾ��item
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
int List::LocateItem(Element item) { // ��ȡitemλ��
    for (int i = 0; i < root->length; i++) 
        if (item == root->elem[i])
            return i;
    return -1;
}

int List::ListLength() { // ����˳�������
    return root->length;    
}

Element List::GetItem(int itemPos) { // ��ȡָ��λ�õ�item
    if (itemPos > root->length || itemPos < 0)
        return -1;
    return root->elem[itemPos];
}

void List::ShowList(int x, int y) { // ��ӡ˳���
    for (int i = 0, j = 0; i < root->length; i++) {
        if (i % 10 == 0 && i != 0)
            j += 3;
        createCell((i % 10) * cellLength + x, j + y, to_string(root->elem[i]));
    }
    cout << endl;
}

void List::ShowTips() { // ��ӡ��ʾ��Ϣ
    gotoxy(60,10);
    cout << "+" << "------------" << "+" << endl;
    gotoxy(60,11);
    cout << "|" << "1: �������� " << "|" << endl;
    gotoxy(60,12);
    cout << "|" << "2: �������� " << "|" << endl;
    gotoxy(60,13);
    cout << "|" << "3: ɾ������ " << "|" << endl;
    gotoxy(60,14);
    cout << "|" << "4:˳�������" << "|" << endl;
    gotoxy(60,15);
    cout << "|" << "5:���˳���" << "|" << endl;
    gotoxy(60,16);
    cout << "|" << "6:����˳���" << "|" << endl;
    gotoxy(60,17);
    cout << "|" << "7:��ӡ˳���" << "|" << endl;
    gotoxy(60,18);
    cout << "+" << "------------" << "+" << endl;
}   

void List::GetCmd() { // ˳�������
    while (true) {
        ShowTips();
        char choice = getch();
        system("cls");
        switch (choice) {
        case '1': // ����
            Element item;
            int insertPos;
            gotoxy(60,10);
            cout << "��Ҫ���������Ϊ:";
            cin >> item;
            gotoxy(60,11);
            cout << "�������ݵ�λ��Ϊ:";
            cin >> insertPos;
            gotoxy(60,12);
            if (ListInsert(item, insertPos))
                cout << "���ݲ���ɹ�" << endl;
            else 
                cout << "���ݲ���ʧ��" << endl;
            break;
        case '2': // ����
            gotoxy(60,10);
            cout << "+" << "------------------" << "+" << endl;
            gotoxy(60,11);
            cout << "|" << "1:����ָ������λ��" << "|" << endl;
            gotoxy(60,12);
            cout << "|" << "2:����ָ��λ������" << "|" << endl;
            gotoxy(60,13);
            cout << "+" << "------------------" << "+" << endl;
            switch(getch()) {
            case '1':
                system("cls");
                gotoxy(60,10);
                cout << "��Ҫ���ҵ�����:";
                cin >> item;
                gotoxy(60,11);
                if (LocateItem(item) != -1)
                    cout << "����λ��Ϊ: " << LocateItem(item) << endl;
                else    
                    cout << "����ʧ��" << endl;
                break;
            case '2':  
                system("cls");
                int itemPos;
                gotoxy(60,10);
                cout << "��Ҫ�������ݵ�λ��:";
                cin >> itemPos;
                gotoxy(60,11);
                if (GetItem(itemPos) != -1)
                    cout << "����Ϊ: " << GetItem(itemPos) << endl;
                else    
                    cout << "����ʧ��" << endl;
                break;
            }
            break;
        case '3': // ɾ��
            gotoxy(60,10);
            cout << "��Ҫɾ��������:";
            cin >> item;
            gotoxy(60,11);
            if (ListDelete(item))
                cout << "ɾ���ɹ�" << endl;
            else
                cout << "ɾ��ʧ��" << endl;
            break;  
        case '4': // ��ȡ��������
            gotoxy(60,10);
            cout << "˳�������Ϊ:" << ListLength() << endl; 
            break;
        case '5': // ���˳���
            gotoxy(60,10);
            if (ClearList())
                cout << "����ɹ�" << endl;
            else
                cout << "���ʧ��" << endl;
            break;
        case '6': // ����˳���
            gotoxy(60,10);
            if (DestoryList())
                cout << "���ٳɹ�" << endl;
            else
                cout << "����ʧ��" << endl;
            break;
        case '7': // ��ӡ˳���
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