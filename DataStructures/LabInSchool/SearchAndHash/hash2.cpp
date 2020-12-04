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
void reverse(string &str)
{
    string x = str;
    str = "";
    for (int i = x.length() - 1; i >= 0; i--)
        str += x[i];
}
long int midSquare(long int seed)
{
    seed = pow(seed, 2);
    string seedS = NumberToString(seed);
    int len = seedS.length();
    string x;
    for (int i = len - 3; i >= len - 6; i--)
    {
        x += seedS[i];
    }
    reverse(x);
    return StringToNumber(x);
}
long int moduloDivision(long int seed, long int mod)
{
    long int x = seed % mod;
    return x;
}
long int digitExtraction(long int seed, int *extractDigits, int size)
{
    string seedS = NumberToString(seed);
    string x = "";
    for (int i = 0; i < size; i++)
    {
        x += seedS[extractDigits[i]];
    }
    return StringToNumber(x);
}
int main()
{
    cout << midSquare(9452);
}