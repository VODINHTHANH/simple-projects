#include <iostream>
#include <list>
using namespace std;
class Node
{
public:
    int data;
    Node *next;

    Node() : data(0), next(nullptr) {}

    Node(int data, Node *next)
    {
        this->data = data;
        this->next = next;
    }

    int getData()
    {
        return this->data;
    }

    void setData(int data)
    {
        this->data = data;
    }

    Node *getNext()
    {
        return this->next;
    }

    void setNext(Node *next)
    {
        this->next = next;
    }
};
void reduceDuplicate(Node *root)
{
    if (root == NULL)
        return;

    Node *curr = root;
    Node *aux;

    while (curr->getNext() != NULL)
    {
        if (curr->getData() == curr->getNext()->getData())
        {
            aux = curr->getNext()->getNext();
            delete curr->getNext();
            curr->setNext(aux);
        }
        else
        {
            curr = curr->getNext();
        }
    }
}
void print(Node *root)
{
    Node *current;

    current = root;

    while (current != nullptr)
    {
        cout << current->getData() << " ";
        current = current->getNext();
    }
    cout << endl;
}
int main()
{
    Node *node1 = new Node(1, nullptr);
    Node *node2 = new Node(1, node1);
    Node *node3 = new Node(0, node2);
    Node *node4 = new Node(0, node3);
    print(node4);
    reduceDuplicate(node4);
    print(node4);
}