#include <iostream>
#include <sstream>
#include <string>
#include <cmath>
using namespace std;

template <typename T>
string NumberToString(T Number)
{
    std::ostringstream ss;
    ss << Number;
    return ss.str();
}
template <typename T>
int StringToNumber(T s)
{
    stringstream geek(s);
    int x = 0;
    geek >> x;
    return x;
}
int foldShift(long long key, int addressSize)
{
    string keyS = NumberToString(key);
    int size = keyS.length();
    string arr[20];
    int index = 0;
    for (int i = 0; i < size; i++)
    {
        arr[index] += keyS[i];
        int len = arr[index].length();
        if (len >= addressSize)
            index++;
    }
    int cryp = 0;
    for (unsigned int i = 0; i <= index; i++)
    {
        int temp = StringToNumber(arr[i]);
        cryp += temp;
    }
    int x = (int)pow(10, addressSize);
    if (cryp >= x)
        cryp = cryp % x;
    return cryp;
}

int rotation(long long key, int addressSize)
{
    string keyS = NumberToString(key);
    int size = keyS.length();
    int lastDigit = key % 10;
    key = key / 10;
    key += pow(10, size - 1) * lastDigit;
    return foldShift(key, addressSize);
}
int main()
{
    cout << rotation(600101, 2);
}