#include <iostream>
#include <math.h>
#include <queue>
using namespace std;
#define SEPARATOR "#<ab@17943918#@>#"

enum BalanceValue
{
    LH = -1,
    EH = 0,
    RH = 1
};

void printNSpace(int n)
{
    for (int i = 0; i < n - 1; i++)
        cout << " ";
}

void printInteger(int &n)
{
    cout << n << " ";
}

template <class T>
class AVLTree
{
public:
    class Node;

private:
    Node *root;

protected:
    int getHeightRec(Node *node)
    {
        if (node == NULL)
            return 0;
        int lh = this->getHeightRec(node->pLeft);
        int rh = this->getHeightRec(node->pRight);
        return (lh > rh ? lh : rh) + 1;
    }

public:
    AVLTree() : root(nullptr) {}
    ~AVLTree() {}
    int getHeight()
    {
        return this->getHeightRec(this->root);
    }
    void printTreeStructure()
    {
        int height = this->getHeight();
        if (this->root == NULL)
        {
            cout << "NULL\n";
            return;
        }
        queue<Node *> q;
        q.push(root);
        Node *temp;
        int count = 0;
        int maxNode = 1;
        int level = 0;
        int space = pow(2, height);
        printNSpace(space / 2);
        while (!q.empty())
        {
            temp = q.front();
            q.pop();
            if (temp == NULL)
            {
                cout << " ";
                q.push(NULL);
                q.push(NULL);
            }
            else
            {
                cout << temp->data;
                q.push(temp->pLeft);
                q.push(temp->pRight);
            }
            printNSpace(space);
            count++;
            if (count == maxNode)
            {
                cout << endl;
                count = 0;
                maxNode *= 2;
                level++;
                space /= 2;
                printNSpace(space / 2);
            }
            if (level == height)
                return;
        }
    }

    int bf(Node *n)
    {
        if (n->pLeft && n->pRight)
        {
            return getHeightRec(n->pLeft) - getHeightRec(n->pRight);
        }
        else if (n->pLeft && n->pRight == NULL)
        {
            return getHeightRec(n->pLeft);
        }
        else if (n->pLeft == NULL && n->pRight)
        {
            return -getHeightRec(n->pRight);
        }
        return -1;
    }
    Node *llrotation(Node *n)
    {
        Node *p;
        Node *tp;
        p = n;
        tp = p->pLeft;

        p->pLeft = tp->pRight;
        tp->pRight = p;

        return tp;
    }

    Node *rrrotation(Node *n)
    {
        Node *p;
        Node *tp;
        p = n;
        tp = p->pRight;

        p->pRight = tp->pLeft;
        tp->pLeft = p;

        return tp;
    }

    Node *rlrotation(Node *n)
    {
        Node *p;
        Node *tp;
        Node *tp2;
        p = n;
        tp = p->pRight;
        tp2 = p->pRight->pLeft;

        p->pRight = tp2->pLeft;
        tp->pLeft = tp2->pRight;
        tp2->pLeft = p;
        tp2->pRight = tp;

        return tp2;
    }

    Node *lrrotation(Node *n)
    {
        Node *p;
        Node *tp;
        Node *tp2;
        p = n;
        tp = p->pLeft;
        tp2 = p->pLeft->pRight;

        p->pLeft = tp2->pRight;
        tp->pRight = tp2->pLeft;
        tp2->pRight = p;
        tp2->pLeft = tp;

        return tp2;
    }
    Node *insertRec(Node *&r, const T &data)
    {
        if (r == NULL)
        {
            r = new Node(data);
            return r;
        }
        if (data < r->data)
            r->pLeft = insertRec(r->pLeft, data);
        else
            r->pRight = insertRec(r->pRight, data);

        if (bf(r) == 2 && bf(r->pLeft) == 1)
        {
            r = llrotation(r);
        }
        else if (bf(r) == -2 && bf(r->pRight) == -1)
        {
            r = rrrotation(r);
        }
        else if (bf(r) == -2 && bf(r->pRight) == 1)
        {
            r = rlrotation(r);
        }
        else if (bf(r) == 2 && bf(r->pLeft) == -1)
        {
            r = lrrotation(r);
        }

        return r;
    }
    void insert(const T &value)
    {
        //TODO
        if (root == NULL)
        {
            root = new Node(value);
            return;
        }
        insertRec(root, value);
    }

    class Node
    {
    private:
        T data;
        Node *pLeft, *pRight;
        BalanceValue balance;
        friend class AVLTree<T>;

    public:
        Node(T value) : data(value), pLeft(NULL), pRight(NULL), balance(EH) {}
        ~Node() {}
    };
};
int main()
{
    AVLTree<int> avl;
    for (int i = 0; i < 9; i++)
    {
        avl.insert(i);
    }
    avl.printTreeStructure();
}