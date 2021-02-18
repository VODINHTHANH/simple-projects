#include <list>
#include <math.h>
#include <iostream>
using namespace std;

long long largestNumber(list<int> listNumber)
{
    // static long long result = 0;
    // if (listNumber.empty())
    // {
    //     result /= 10;
    //     return result;
    // }
    // listNumber.sort();
    // result += listNumber.back();
    // result *= 10;
    // listNumber.pop_back();
    // return largestNumber(listNumber);
    if (listNumber.empty())
        return 0;
    listNumber.sort();
    int temp = listNumber.front();
    listNumber.pop_front();
    return temp + largestNumber(listNumber) * 10;
}
int main()
{
    int arr[] = {1, 2, 3, 6, 5, 6};
    list<int> listNumber;
    for (unsigned int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
        listNumber.push_back(arr[i]);
    cout << largestNumber(listNumber);
}