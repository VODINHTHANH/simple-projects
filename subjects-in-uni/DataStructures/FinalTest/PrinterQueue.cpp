#include <iostream>
#include <vector>
#include <string.h>
#include <string>
using namespace std;
class PrinterQueue
{
    vector<PrinterQueue> v;
    int prior;
    string filen;

public:
    // your methods
    PrinterQueue(int priority, string fileName)
    {
        prior = priority;
        filen = fileName;
    }
    PrinterQueue()
    {
    }
    void addNewRequest(int priority, string fileName)
    {
        if (v.empty() == true)
        {
            v.push_back(PrinterQueue(priority, fileName));
            return;
        }
        for (unsigned int i = 0; i < v.size(); i++)
        {
            if (v[i].prior < priority)
            {
                v.insert(v.begin() + i, PrinterQueue(priority, fileName));
                return;
            }
        }
        v.push_back(PrinterQueue(priority, fileName));
        return;
    }

    void print()
    {
        // your code here
        // After some logic code, you have to print fileName with endl
        if (v.empty() == true)
        {
            cout << "No file to print" << endl;
        }
        else
        {
            cout << v.front().filen << endl;
            v.erase(v.begin());
        }
    }
};
int main()
{
    PrinterQueue *myPrinterQueue = new PrinterQueue();
    myPrinterQueue->addNewRequest(1, "hello.pdf");
    myPrinterQueue->addNewRequest(2, "goodbye.pdf");
    myPrinterQueue->addNewRequest(2, "goodnight.pdf");
    myPrinterQueue->print();
    myPrinterQueue->print();
    myPrinterQueue->print();
}