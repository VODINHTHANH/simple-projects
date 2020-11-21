#include <sstream>
#include <iostream>
#include <type_traits>
using namespace std;
template <class T>
class Sorting {
private:
    static T* Partition(T* start, T* end) ;
public:
    static void QuickSort(T* start, T* end) ;
};
template <class T>
T* Sorting<T>::Partition(T* start, T* end) {
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
void Sorting<T>::QuickSort(T* start, T* end) {
    // TODO
    // In this question, you must print out the index of pivot in subarray after everytime calling method Partition.
     static bool x = true;
    if (start < end)
    {
        T* pi  = Partition(start, end);
       if(x == false) cout << " ";
        cout << pi - start;
        x = false;
        QuickSort(start, pi);
        QuickSort(pi + 1, end);
    }
}
int main()
{
int array[] = { 3, 5, 7, 10 ,12, 14, 15, 13, 1, 2, 9, 6, 4, 8, 11, 16, 17, 18, 20, 19 };
cout << "Index of pivots: ";
Sorting<int>::QuickSort(&array[0], &array[20]);
cout << "\n";
cout << "Array after sorting: ";
for (int i : array) cout << i << " ";
}
