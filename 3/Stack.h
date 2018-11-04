#include <cstring>
#include <malloc.h>
#include <iostream>

#define STACK_ADD_LEN 50
#define STACK_MAX_LEN 100000 

template <class T>
class Stack {
public:
    Stack();                // ��ʼ��
    void ShowStack();       // ��ӡջԪ��
    bool FullStack();       // �ж�ջ�Ƿ����
    bool EmptyStack();      // �ж�ջ�Ƿ�Ϊ��
    bool ClearStack();      // ���ջ   
    bool Push(T item);      // ��ջ��ѹ������
    void addStackLength();  // ��̬����ջ�ռ�
    bool isSame(T item);    // �жϸ�Ԫ���Ƿ����ջ��
    int Size();             // ��ȡջ����
    T Pop();                // ɾ��ջ������
    T Top();                // ��ȡջ������
private:
    T *stack;               // ջ
    int stackLength;        // ջ���ݸ���
    int stackSize;          // ջ�ռ��С
};

template <class T>
Stack<T>::Stack() {
    stackSize = 100;
    stack = new T[stackSize];
    stackLength = 0;
}

template <class T>
void Stack<T>::addStackLength() { 
    T *tmp = new T[STACK_ADD_LEN + stackSize];
    for (int i = 1; i <= stackLength; i++)
        tmp[i] = stack[i];
    stack = tmp;
    stackSize += STACK_ADD_LEN;
}

template <class T>
bool Stack<T>::Push(T item) {
    if (stackLength + 1 > stackSize && stackSize <= STACK_MAX_LEN)
        addStackLength();
    else if (stackLength + 1 > STACK_MAX_LEN)
        return false;
    stackLength++;    
    stack[stackLength] = item;
    return true;
}

template <class T>
T Stack<T>::Pop() {
    if (stackLength > 0) 
        return stack[stackLength--];
}

template <class T>
T Stack<T>::Top() {
    if (stackLength > 0)
        return stack[stackLength];
}

template <class T>
bool Stack<T>::isSame(T item) {
    for (int i = 0; i < stackLength; i++) 
        if (stack[i] == item)
            return true;
    return false;
}

template <class T>
int Stack<T>::Size() {
    return stackLength;
}

template <class T>
void Stack<T>::ShowStack() {
    for (int i = stackLength; i > 0; i--)
        std::cout << stack[i];
    std::cout << std::endl;
}

template <class T>
bool Stack<T>::FullStack() {
    return stackSize == STACK_MAX_LEN ? true : false;
}

template <class T>
bool Stack<T>::EmptyStack() {
    return stackLength == 0 ? true : false;
}

template <class T>
bool Stack<T>::ClearStack() {
    while (stackLength) 
        Pop();
    Stack();
    return true;
}