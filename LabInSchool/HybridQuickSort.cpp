#include <iostream>
using namespace std;

template <class T>
class Sorting
{
private:
    static T *Partition(T *start, T *end);

public:
    static void printArray(T *start, T *end)
    {
        int size = end - start;
        for (int i = 0; i < size - 1; i++)
            cout << start[i] << ", ";
        cout << start[size - 1];
        cout << endl;
    }

    static void insertionSort(T *start, T *end);

    static void hybridQuickSort(T *start, T *end, int min_size);
};
template <class T>
T *Sorting<T>::Partition(T *start, T *end)
{
     // TODO: return the pointer which points to the pivot after rearrange the array.
    T pivot = *start;  
    T* left = start+1;
    T* right = end-1;
    while(true){
        while(left <= right && (*left) < pivot) left++;
        while(right >= left && (*right) >= pivot) right--;
        if (left >= right) break;
        T t = *left;
    *left = *right;
    *right = t;
        left++;
        right--;
    }
    T t = *start;
    *start = *right;
    *right = t;
    return right;
}
template <class T>
void Sorting<T>::hybridQuickSort(T* start, T* end, int min_size) {
    if(end-start< min_size && end-start > 0)
    {
        cout << "Insertion sort: ";
        printArray(start,end);
        insertionSort(start,end);
        
    }
   if(end-start>=min_size)
    {   cout << "Quick sort: ";
        printArray(start,end);
        T* pi  = Partition(start, end);
        hybridQuickSort(start, pi, min_size);
        hybridQuickSort(pi + 1, end, min_size);
    }
}
template <class T>
void Sorting<T>::insertionSort(T *start, T *end)
{
     for(T* i=start+1;i<end;i++) 
    { 
      T val = *i ; 
      T* j = i ; 
    while (j>start && *(j-1)>val) 
      { 
        *j= *(j-1) ; 
      j-= 1; 
    } 
    *j= val ; 
    }  
}
int main()
{
int array[] = {2, 6, 4, 12, 23, 1, 0, -12};
int min_size = 4;
Sorting<int>::QuickSort(&array[0], &array[8], min_size);
cout << endl;
for (int i : array) cout << i << " ";
}
