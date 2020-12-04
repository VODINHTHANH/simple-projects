#include <iostream>
#include <cmath>
using namespace std;
int interpolationSearch(int arr[], int left, int right, int x)
{
    static int n = right;
    if (right >= left)
    {
        int mid = left + ((right - left) / (arr[right] - arr[left])) * (x - arr[left]);
        if (mid >= 0 && mid <= n)
        {
            cout << "We traverse on index: ";
            cout << mid << endl;
        }
        if (arr[mid] == x)
        {
            return mid;
        }
        if (arr[mid] > x)
        {
            return interpolationSearch(arr, left, mid - 1, x);
        }
        return interpolationSearch(arr, mid + 1, right, x);
    }
    return -1;
}
int main()
{
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int n = sizeof(arr) / sizeof(arr[0]);
    int x = 6;
    int result = interpolationSearch(arr, 0, n - 1, x);
    (result == -1) ? cout << "Element is not present in array"
                   : cout << "Element is present at index " << result;
}