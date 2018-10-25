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
    void InitList();                                // ��ʼ������
    bool DestoryList();                             // ��������
    bool ClearList();                               // �������
    bool EmptyList();                               // �ж������Ƿ�Ϊ��
    bool ListInsert(Element item, int insertPos);   // ��ָ��λ�ò���item
    bool ListDelete(Element item);                  // ɾ��item
    int ListLength();                               // ������������
    int LocateItem(Element item);                   // ��ȡitemλ��
    Element GetItem(int itemPos);                   // ��ȡָ��λ�õ�item
    void ShowList(int x, int y);                    // ��ӡ����
    void ShowTips();                                // ��ӡ��ʾ��Ϣ
    void GetCmd();                                  // ִ�в���
    void gotoxy(int x, int y);                      // ������ƶ���ָ������ 
    void createCell(int x, int y, string data);     // ����һ����Ԫ��
    void getMaxLength();                            // ��ȡ��Ԫ���С
private:
    ListNode *root;
    int cellLength;
};

void List::gotoxy(int x,int y) { // ������ƶ���ָ������ 
	COORD pos = {x,y};
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOut,pos);
}

void List::getMaxLength() { // ��ȡ��Ԫ���С
    ListNode *tmp = root;
    while (tmp) {
        string tmpData = to_string(tmp->data);
        if (cellLength < tmpData.length() + 2)
            cellLength = tmpData.length() + 2;
        tmp = tmp->next;
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

void List::InitList() { // ��ʼ������
    root = new node;
    root->data = NULL;
    root->next = NULL;
    cellLength = 0;
}

bool List::DestoryList() { // ��������
    ListNode *tmp = root;
    while (root) {
        tmp = root;
        root = root->next;
        delete tmp;
    }
    return true;
}

bool List::ClearList() { // �������
    ListNode *tmp = root;
    while (tmp) {
        tmp->data = NULL;
        tmp = tmp->next;
    }
    return true;
}

bool List::EmptyList() { // �ж������Ƿ�Ϊ��
    if (root->next)
        return false;
    return true;
}

bool List::ListInsert(Element item, int insertPos) { // ��ָ��λ�ò���item
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

bool List::ListDelete(Element item) { // ɾ��item
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

int List::ListLength() {// ������������
    ListNode *tmp = root;
    int cnt = 0;
    while (tmp) {
        cnt++;
        tmp = tmp->next;
    }
    return cnt;
}

int List::LocateItem(Element item) { // ��ȡitemλ��
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

Element List::GetItem(int itemPos) { // ��ȡָ��λ�õ�item
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

void List::ShowList(int x, int y) { // ��ӡ����
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
    for (int i = 0; i < 20; i++) 
        newList.ListInsert(i, i);
    newList.GetCmd();
    system("pause");
}