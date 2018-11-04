#include <cstring>
#include <malloc.h>
#include <iostream>

template <class T>
struct QueueNode {
    T data;
    struct QueueNode<T> *next;
};

template <class T>
class Queue {
public:
    Queue();
    bool IsEmpty();
    void PushFront(T data);
    void PushBack(T data);
    T PopFront();
    T PopBack();
    T Front();
    T Back();
    int Length();
private:
    QueueNode<T> *head;
    QueueNode<T> *tail;
    int queueLength;
};

template <class T>
Queue<T>::Queue() {
    tail = new QueueNode<T>;
    head = new QueueNode<T>;
    tail->next = head;
    queueLength = 0;
}

template <class T>
void Queue<T>::PushBack(T data) {
    QueueNode<T> *newNode = new QueueNode<T>;
    newNode->data = data;
    newNode->next = tail->next;
    tail->next = newNode;
    queueLength++;
}

template <class T>
void Queue<T>::PushFront(T data) {
    QueueNode<T> *newNode = new QueueNode<T>;
    newNode->data = data;
    QueueNode<T> *tmpTail = tail;
    while (tmpTail->next != head) 
        tmpTail = tmpTail->next;
    newNode->next = tmpTail->next;
    tmpTail->next = newNode;
    queueLength++;
}

template <class T>
T Queue<T>::PopFront() {
    if (queueLength > 0) {
        QueueNode<T> *tmpTail = tail;
        while (tmpTail->next->next != head)
            tmpTail = tmpTail->next;
        QueueNode<T> *tmpHead = tmpTail->next;
        T tmpData = tmpHead->data;
        tmpTail->next = tmpHead->next;
        delete(tmpHead);
        queueLength--;
        return tmpData;
    }
}

template <class T>
T Queue<T>::PopBack() {
    if (queueLength > 0) {
        QueueNode<T> *tmp = tail->next;
        T tmpData = tmp->data;
        tail->next = tmp->next;
        delete(tmp);
        queueLength--;
        return tmpData;
    }
}

template <class T>
T Queue<T>::Front() {
    if (queueLength > 0) {
        QueueNode<T> *tmpTail = tail;
        while (tmpTail->next != head)
            tmpTail = tmpTail->next;
        return tmpTail->data;
    }
}

template <class T>
T Queue<T>::Back() {
    if (queueLength > 0)
        return tail->next->data;
}

template <class T>
bool Queue<T>::IsEmpty() {
    return queueLength == 0 ? true : false;
}

template <class T>
int Queue<T>::Length() {
    return queueLength;
}
