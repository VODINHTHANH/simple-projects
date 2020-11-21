
#include <iostream>
#include <string>

using namespace std;
int hashString(string a) {
    int hashed = 0;
    for(unsigned int i = 0; i < a.length(); i++) { 
        hashed += a[i] * 7; // Timed by a prime to make the hash more unique?
    } 
    return hashed;
}
bool isPermutation(string a, string b) {
    if(a.length() != b.length()) return false;
    return hashString(a) == hashString(b);
}


int main()
{
string a = "abbac";
string b="baba";
cout << isPermutation(a, b);

    return 0;
}
