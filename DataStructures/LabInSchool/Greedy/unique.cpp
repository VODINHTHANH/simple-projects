#include <iostream>
using namespace std;
int getSum(int n)
{
    int sum = 0;
    while (n != 0)
    {
        sum = sum + n % 10;
        n = n / 10;
    }
    return sum;
}
int uniqueNumber(int x)
{
    // TODO: return the smallest number satisfying conditions, otherwise return -1.
    if (x > 1 && x < 10)
        return x;
    if (x < 1 || x > 45)
        return -1;
    int k = 10;
    int c;
    while (k < 90)
    {
        c = k + 9;
        if (getSum(c) == x)
            return c;
        k += 10;
    }
    k = 100;
    while (k < 800)
    {
        c = k + 89;
        if (getSum(c) == x)
            return c;
        k += 100;
    }
    k = 1000;
    while (k < 7000)
    {
        c = k + 789;
        if (getSum(c) == x)
            return c;
        k += 1000;
    }
    k = 10000;
    while (k < 60000)
    {
        c = k + 6789;
        if (getSum(c) == x)
            return c;
        k += 10000;
    }
    k = 100000;
    while (k < 500000)
    {
        c = k + 56789;
        if (getSum(c) == x)
            return c;
        k += 100000;
    }
    k = 1000000;
    while (k < 4000000)
    {
        c = k + 456789;
        if (getSum(c) == x)
            return c;
        k += 1000000;
    }
    k = 10000000;
    while (k < 30000000)
    {
        c = k + 3456789;
        if (getSum(c) == x)
            return c;
        k += 10000000;
    }
    k = 100000000;
    while (k < 200000000)
    {
        c = k + 23456789;
        if (getSum(c) == x)
            return c;
        k += 100000000;
    }
    k = 1000000000;
    while (k < 1000000000)
    {
        c = k + 123456789;
        if (getSum(c) == x)
            return c;
        k += 1000000000;
    }

    return 1;
}
int main()
{
    int n = 45;
    cout << uniqueNumber(n);
}