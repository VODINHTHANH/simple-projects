#include <bits/stdc++.h>
using namespace std;

int jumpSearch(int arr[], int x, int n)
{
    cout << 0 << " ";
    if (arr[0] == x)
    {
        return 0;
    }
    int step = sqrt(n);
    cout << step << " ";
    while (arr[step] < x)
    {
        step += sqrt(n);
        cout << step << " ";
        if (step >= n)
        {
            break;
        }
    }
    if (step < n && arr[step] == x)
    {
        return step;
    }
    if (step >= n)
    {
        int k = sqrt(n);
        int prev = step - k;
        cout << prev << " ";
        while (prev < n)
        {
            if (arr[prev] == x)
            {
                return prev;
            }
            prev++;
            if (prev != n)
                cout << prev << " ";
        }
    }
    else
    {
        int k = sqrt(n);
        int prev = step - k;
        cout << prev << " ";
        while (prev < step)
        {
            if (arr[prev] == x)
            {
                return prev;
            }
            prev++;
            if (prev != (step))
                cout << prev << " ";
        }
    }

    return -1;
}

// Driver program to test function
int main()
{
    int arr[] = {0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610, 611, 612, 613};
    int x = 614;
    int n = sizeof(arr) / sizeof(arr[0]);
    int index = jumpSearch(arr, x, n);

    if (index != -1)
    {
        cout << "\nNumber " << x << " is at index " << index;
    }
    else
    {
        cout << "\n"
             << x << " is not in array!";
    }
}
// int arr[] = { 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610, 611, 612, 613 };
// int x = 612;
// int n = sizeof(arr) / sizeof(arr[0]);
// int index = jumpSearch(arr, x, n);

// if (index != -1) {
//     cout << "\nNumber " << x << " is at index " << index;
// }
// else {
//     cout << "\n" << x << " is not in array!";
// }
// 0 4 8 12 16 17
// Number 612 is at index 17

// int arr[] = { 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610, 611, 612, 613 };
// int x = 614;
// int n = sizeof(arr) / sizeof(arr[0]);
// int index = jumpSearch(arr, x, n);

// if (index != -1) {
//     cout << "\nNumber " << x << " is at index " << index;
// }
// else {
//     cout << "\n" << x << " is not in array!";
// }
// 0 4 8 12 16 17 18 19
// 614 is not in array!

// int arr[] = { 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610, 611, 612, 613, 1000, 1002, 2000, 2003, 2004, 2005, 2006 };
// int x = 36;
// int n = sizeof(arr) / sizeof(arr[0]);
// int index = jumpSearch(arr, x, n);

// if (index != -1) {
//     cout << "\nNumber " << x << " is at index " << index;
// }
// else {
//     cout << "\n" << x << " is not in array!";
// }
// 0 5 10 5 6 7 8 10
// 36 is not in array

// int arr[] = { 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610 };
// int x = 55;
// int n = sizeof(arr) / sizeof(arr[0]);
// int index = jumpSearch(arr, x, n);

// if (index != -1) {
//     cout << "\nNumber " << x << " is at index " << index;
// }
// else {
//     cout << "\n" << x << " is not in array!";
// }
// 0 4 8 12 9 10
// Number 55 is at index 10

// int arr[] = { 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610 };
// int x = 144;
// int n = sizeof(arr) / sizeof(arr[0]);
// int index = jumpSearch(arr, x, n);

// if (index != -1) {
//     cout << "\nNumber " << x << " is at index " << index;
// }
// else {
//     cout << "\n" << x << " is not in array!";
// }
// 0 4 8 12
// Number 144 is at index 12