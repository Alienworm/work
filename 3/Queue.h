#include <cstring>
#include <malloc.h>
#include <iostream>

template <class T>
struct node {
    T data;
    struct node<T> *next;
};

template <class T>
class Queue {
public:
    Queue();
    void Push(T data);
    T Pop();
    T Front();
    T Back();
    int Length();
private:
    node<T> *head;
    node<T> *tail;
    int queueLength;
};

template <class T>
Queue<T>::Queue() {
    tail = new node<T>;
    tail->next = NULL;
    head = tail;
    queueLength = 0;
}

template <class T>
void Queue<T>::Push(T data) {
    node<T> *newNode = new node<T>;
    newNode->data = data;
    newNode->next = tail->next;
    tail->next = newNode;
    queueLength++;
    if (queueLength == 1)
        head = newNode;
}

template <class T>
T Queue<T>::Pop() {
    if (queueLength > 0) {
        node<T> *tmpHead = head;
        T tmpData = tmpHead->data;
        node<T> *tmpNode = tail;
        while (tmpNode->next != head) 
            tmpNode = tmpNode->next;
        head = tmpNode;
        delete(tmpHead);
        queueLength--;
        return tmpData;
    }
}

template <class T>
T Queue<T>::Front() {
    if (queueLength > 0)
        return head->data;
}

template <class T>
T Queue<T>::Back() {
    if (queueLength > 0)
        return tail->next->data;
}

template <class T>
int Queue<T>::Length() {
    return queueLength;
}