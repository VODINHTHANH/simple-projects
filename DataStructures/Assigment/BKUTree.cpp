#include <iostream>
#include <queue>
#include <vector>
using namespace std;

template <class K, class V>
class BKUTree
{
public:
    class AVLTree;
    class SplayTree;

    class Entry
    {
    public:
        K key;
        V value;

        Entry(K key, V value) : key(key), value(value) {}
    };

private:
    AVLTree *avl;
    SplayTree *splay;
    queue<K> keys;
    int maxNumOfKeys;

public:
    BKUTree(int maxNumOfKeys = 5)
    {
        avl = new AVLTree();
        splay = new SplayTree();
    }
    ~BKUTree() { this->clear(); }

    void add(K key, V value)
    {
        Entry *newEntry = new Entry(key, value);
        typename AVLTree::Node *point = avl->AVLTree::add(newEntry);
        typename SplayTree::Node *point1 = splay->SplayTree::add(newEntry);
        point->corr = point1;
        point1->corr = point;
    }
    void remove(K key);
    V search(K key, vector<K> &traversedList);

    void traverseNLROnAVL(void (*func)(K key, V value))
    {
        avl->traverseNLR(func);
    }
    void traverseNLROnSplay(void (*func)(K key, V value))
    {
        splay->traverseNLR(func);
    }

    void clear();

    class SplayTree
    {
    public:
        class Node
        {
        public:
            Entry *entry;
            Node *left;
            Node *right;
            Node *parent;
            typename AVLTree::Node *corr;

            Node(Entry *entry = NULL, Node *left = NULL, Node *right = NULL)
            {
                this->entry = entry;
                this->left = left;
                this->right = right;
                this->corr = NULL;
            }
        };

    public:
        Node *root;

        SplayTree() : root(NULL){};
        ~SplayTree() { this->clear(); };
        void left_rotate(Node *x)
        {
            Node *y = x->right;
            x->right = y->left;
            if (y->left != NULL)
            {
                y->left->parent = x;
            }
            y->parent = x->parent;
            if (x->parent == NULL)
            { //x is root
                root = y;
            }
            else if (x == x->parent->left)
            { //x is left child
                x->parent->left = y;
            }
            else
            { //x is right child
                x->parent->right = y;
            }
            y->left = x;
            x->parent = y;
        }

        void right_rotate(Node *x)
        {
            Node *y = x->left;
            x->left = y->right;
            if (y->right != NULL)
            {
                y->right->parent = x;
            }
            y->parent = x->parent;
            if (x->parent == NULL)
            { //x is root
                root = y;
            }
            else if (x == x->parent->right)
            { //x is left child
                x->parent->right = y;
            }
            else
            { //x is right child
                x->parent->left = y;
            }
            y->right = x;
            x->parent = y;
        }
        void splay(Node *n)
        {
            while (n->parent != NULL)
            { //node is not root
                if (n->parent == root)
                { //node is child of root, one rotation
                    if (n == n->parent->left)
                    {
                        right_rotate(n->parent);
                    }
                    else
                    {
                        left_rotate(n->parent);
                    }
                }
                else
                {
                    Node *p = n->parent;
                    Node *g = p->parent; //grandparent

                    if (n->parent->left == n && p->parent->left == p)
                    { //both are left children
                        right_rotate(g);
                        right_rotate(p);
                    }
                    else if (n->parent->right == n && p->parent->right == p)
                    { //both are right children
                        left_rotate(g);
                        left_rotate(p);
                    }
                    else if (n->parent->right == n && p->parent->left == p)
                    {
                        left_rotate(p);
                        right_rotate(g);
                    }
                    else if (n->parent->left == n && p->parent->right == p)
                    {
                        right_rotate(p);
                        left_rotate(g);
                    }
                }
            }
        }
        void insert(Node *n)
        {
            Node *y = NULL;
            Node *temp = root;
            while (temp != NULL)
            {
                y = temp;
                if (n->entry->key < temp->entry->key)
                    temp = temp->left;
                else
                    temp = temp->right;
            }
            n->parent = y;

            if (y == NULL) //newly added node is root
                root = n;
            else if (n->entry->key < y->entry->key)
                y->left = n;
            else
                y->right = n;

            splay(n);
        }
        void add(K key, V value);
        Node *add(Entry *&entry)
        {
            Node *n = new Node(entry);
            if (root == NULL)
            {
                root = n;
                return root;
            }
            insert(n);
            return root;
        }
        void remove(K key);
        V search(K key);

        void traverseRec(Node *r, void (*func)(K key, V value))
        {
            if (r == NULL)
                return;
            func(r->entry->key, r->entry->value);
            traverseRec(r->left, func);
            traverseRec(r->right, func);
        }
        void traverseNLR(void (*func)(K key, V value))
        {
            if (root == NULL)
                return;
            traverseRec(root, func);
        }

        void clear();
    };

    class AVLTree
    {
    public:
        class Node
        {
        public:
            Entry *entry;
            Node *left;
            Node *right;
            int balance;
            typename SplayTree::Node *corr;

            Node(Entry *entry = NULL, Node *left = NULL, Node *right = NULL)
            {
                this->entry = entry;
                this->left = left;
                this->right = right;
                this->balance = 0;
                this->corr = NULL;
            }
        };

    public:
        Node *root;

        AVLTree() : root(NULL){};
        ~AVLTree() { this->clear(); };
        int getHeight()
        {
            return this->getHeightRec(this->root);
        }
        int getHeightRec(Node *Node)
        {
            if (Node == NULL)
                return 0;
            int lh = this->getHeightRec(Node->left);
            int rh = this->getHeightRec(Node->right);
            return (lh > rh ? lh : rh) + 1;
        }
        int bf(Node *n)
        {
            if (n->left && n->right)
            {
                return getHeightRec(n->left) - getHeightRec(n->right);
            }
            else if (n->left && n->right == NULL)
            {
                return getHeightRec(n->left);
            }
            else if (n->left == NULL && n->right)
            {
                return -getHeightRec(n->right);
            }
            return -1;
        }
        Node *llrotation(Node *n)
        {
            Node *p;
            Node *tp;
            p = n;
            tp = p->left;

            p->left = tp->right;
            tp->right = p;

            return tp;
        }

        Node *rrrotation(Node *n)
        {
            Node *p;
            Node *tp;
            p = n;
            tp = p->right;

            p->right = tp->left;
            tp->left = p;

            return tp;
        }

        Node *rlrotation(Node *n)
        {
            Node *p;
            Node *tp;
            Node *tp2;
            p = n;
            tp = p->right;
            tp2 = p->right->left;

            p->right = tp2->left;
            tp->left = tp2->right;
            tp2->left = p;
            tp2->right = tp;

            return tp2;
        }

        Node *lrrotation(Node *n)
        {
            Node *p;
            Node *tp;
            Node *tp2;
            p = n;
            tp = p->left;
            tp2 = p->left->right;

            p->left = tp2->right;
            tp->right = tp2->left;
            tp2->right = p;
            tp2->left = tp;

            return tp2;
        }
        Node *insertRec(Node *&r, Entry *&entry)
        {
            if (r == NULL)
            {
                Node *r = new Node(entry, NULL, NULL); //create new Node with entry
                return r;
            }
            if (entry->key < r->entry->key)
                r->left = insertRec(r->left, entry);
            else
                r->right = insertRec(r->right, entry);

            if (bf(r) == 2 && bf(r->left) == 1)
            {
                r = llrotation(r);
            }
            else if (bf(r) == -2 && bf(r->right) == -1)
            {
                r = rrrotation(r);
            }
            else if (bf(r) == -2 && bf(r->right) == 1)
            {
                r = rlrotation(r);
            }
            else if (bf(r) == 2 && bf(r->left) == -1)
            {
                r = lrrotation(r);
            }

            return r;
        }

        void add(K key, V value);
        Node *add(Entry *&entry)
        {
            if (root == NULL)
            {
                root = new Node(entry);
                return root;
            }
            return insertRec(root, entry);
        }

        void remove(K key);
        V search(K key);
        void traverseRec(Node *r, void (*func)(K key, V value))
        {
            if (r == NULL)
                return;
            func(r->entry->key, r->entry->value);
            traverseRec(r->left, func);
            traverseRec(r->right, func);
        }
        void traverseNLR(void (*func)(K key, V value))
        {
            if (root == NULL)
                return;
            traverseRec(root, func);
        }

        void clear();
    };
};
void printKey(int key, int value)
{
    cout << key << endl;
}
int main()
{
    BKUTree<int, int> *tree = new BKUTree<int, int>();
    int keys[] = {1, 3, 5, 7, 9, 2, 4};
    for (int i = 0; i < 7; i++)
        tree->add(keys[i], keys[i]);
    tree->traverseNLROnSplay(printKey);
}