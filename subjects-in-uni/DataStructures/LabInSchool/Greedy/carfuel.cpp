#include <iostream>
#include <vector>
using namespace std;
int countStop(int totalDistance, int maxDistanceFullTank, vector<int> stopPoint)
{
    int count = 0;
    int fuel = maxDistanceFullTank;
    //check condition
    for (unsigned int i = 0; i < stopPoint.size() - 1; i++)
    {
        if (stopPoint[i + 1] - stopPoint[i] > maxDistanceFullTank)
            return -1;
    }
    if (totalDistance - stopPoint[stopPoint.size() - 1] > maxDistanceFullTank)
        return -1;
    if (stopPoint[0] > maxDistanceFullTank)
        return -1;
    for (unsigned int i = 0; i < stopPoint.size() - 1; i++)
    {
        fuel -= stopPoint[i];
        if (stopPoint[i + 1] - stopPoint[i] > fuel)
        {
            fuel = maxDistanceFullTank;
            count++;
        }
    }
    return count;
}
int main()
{
    vector<int> stopPoint;
    int arr[] = {2, 5, 7, 9, 11};
    stopPoint.insert(stopPoint.end(), arr, arr + 5);
    cout << countStop(15, 4, stopPoint);
}