#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;
#define SEPARATOR "#<ab@17943918#@>#"
template <class T>
class Heap
{
protected:
    T *elements;
    int capacity;
    int count;

public:
    Heap()
    {
        this->capacity = 10;
        this->count = 0;
        this->elements = new T[capacity];
    }
    ~Heap()
    {
        delete[] elements;
    }
    void push(T item);
    void clear();

    bool isEmpty();
    bool contains(T item);
    T peek();
    bool pop();
    int size();

    void printHeap()
    {
        cout << "Max Heap [ ";
        for (int i = 0; i < count; i++)
            cout << elements[i] << " ";
        cout << "]\n";
    }

private:
    void ensureCapacity(int minCapacity);
    void reheapUp(int position);
    void reheapDown(int position);
};
template <class T>
int Heap<T>::size()
{
    return count;
}

template <class T>
bool Heap<T>::isEmpty()
{
    return count == 0;
}

template <class T>
T Heap<T>::peek()
{
    if (this->isEmpty() == false)
        return elements[0];
    return -1;
}

template <class T>
bool Heap<T>::contains(T item)
{
    for (int i = 0; i < count; i++)
    {
        if (elements[i] == item)
            return true;
    }
    return false;
}

template <class T>
bool Heap<T>::pop()
{
    if (this->isEmpty() == false)
    {
        elements[0] = elements[count - 1];
        count--;
        for (int i = count / 2; i >= 0; i--)
        {
            reheapDown(i);
        }
        return true;
    }
    return false;
}
template <class T>
void Heap<T>::push(T item)
{
    ensureCapacity(count + 1);
    elements[count] = item;
    count++;
    reheapUp(count - 1);
}

template <class T>
void Heap<T>::ensureCapacity(int minCapacity)
{
    if (minCapacity > capacity)
    {
        T *temp = elements;
        int newCapacity = minCapacity * 1.5;
        temp = new T[newCapacity];
        for (int i = 0; i < capacity; i++)
        {
            temp[i] = elements[i];
        }
        delete[] elements;
        elements = temp;
        capacity = newCapacity;
    }
}
template <class T>
void Heap<T>::reheapUp(int position)
{
    if (position > 0)
    {
        int parent = (position - 1) / 2;
        if (elements[position] > elements[parent])
        {
            T t = elements[position];
            elements[position] = elements[parent];
            elements[parent] = t;
            reheapUp(parent);
        }
    }
}