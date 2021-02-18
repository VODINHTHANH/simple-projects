#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

void reheapUpRec(int position, int elements[])
{
    if (position > 0)
    {
        int parent = (position - 1) / 2;
        if (elements[position] > elements[parent])
        {
            int t = elements[position];
            elements[position] = elements[parent];
            elements[parent] = t;
            reheapUpRec(parent, elements);
        }
    }
}
void reheapUp(int maxHeap[], int numberOfElements, int index)
{
    if (index < numberOfElements)
    {
        reheapUpRec(index, maxHeap);
    }
}
void reheapDown(int maxHeap[], int numberOfElements, int index)
{
    if (index < numberOfElements)
    {
        int leftChild = index * 2 + 1;
        int rightChild = index * 2 + 2;
        int largeChild;
        if (leftChild < numberOfElements)
        {
            if (rightChild < numberOfElements && maxHeap[rightChild] > maxHeap[leftChild])
            {
                largeChild = rightChild;
            }
            else
            {
                largeChild = leftChild;
            }
            if (maxHeap[largeChild] > maxHeap[index])
            {
                int t = maxHeap[largeChild];
                maxHeap[largeChild] = maxHeap[index];
                maxHeap[index] = t;
                reheapDown(maxHeap, numberOfElements, largeChild);
            }
        }
    }
}
int main()
{
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8};
    int size = sizeof(arr) / sizeof(arr[0]);
    reheapDown(arr, size, 0);
    cout << "[ ";
    for (int i = 0; i < size; i++)
        cout << arr[i] << " ";
    cout << "]";
}
