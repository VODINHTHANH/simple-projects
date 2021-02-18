#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
bool checkZO(vector<int> v)
{
    for (int it : v)
    {
        if (it != 0 && it != 1)
            return false;
    }
    return true;
}

void makeFinalVector(vector<int> &holdResult, long long int n)
{
    if (n == 0 || n == 1)
    {
        holdResult.push_back(n);
        return;
    }
    vector<int> v;
    v.push_back(n);

    while (true)
    {
        for (int it : v)
        {
            if (it != 1 && it != 0)
            {
                holdResult.push_back((int)floor(it / 2));
                holdResult.push_back(it % 2);
                holdResult.push_back((int)floor(it / 2));
            }
            else
            {
                holdResult.push_back(it);
            }
        }
        if (checkZO(holdResult) == true)
        {
            return;
        }
        else
        {
            v = holdResult;
            holdResult.clear();
        }
    }
}

long long int sumOfOnes(long long int n, long long int l, long long int r)
{
    if (l == r)
        return 0;
    long long int sum = 0;
    vector<int> holdResult;
    makeFinalVector(holdResult, n);
    if (l > r || l >= holdResult.size() || r >= holdResult.size())
        return 0;
    for (int i = l; i <= r; i++)
    {
        sum += holdResult[i];
    }
    return sum;
}
int main()
{
    cout << sumOfOnes(1, 7, 12);
}