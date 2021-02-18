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
        this->maxNumOfKeys = maxNumOfKeys;
    }
    ~BKUTree() { this->clear(); }
    bool isPresentBKU(typename AVLTree::Node *rt, int key)
    {
        if (rt == NULL)
            return false;
        if (key == rt->entry->key)
            return true;
        if (key < rt->entry->key)
            return isPresentBKU(rt->left, key);

        return isPresentBKU(rt->right, key);
    }
    void add(K key, V value)
    {
        if (isPresentBKU(avl->root, key) == true)
            throw "Duplicate key";
        Entry *newEntry = new Entry(key, value);
        avl->AVLTree::add(newEntry);
        typename AVLTree::Node *point = avl->isPresent(avl->root, key);
        splay->SplayTree::add(newEntry);
        point->corr = splay->root;
        splay->root->corr = point;
        pushQ(keys, key);
    }
    void remove(K key)
    {
        splay->SplayTree::remove(key);
        avl->AVLTree::remove(key);
        queue<K> temp;
        while (keys.empty() == false)
        {
            if (keys.front() != key)
            {
                temp.push(keys.front());
                keys.pop();
            }
            else
            {
                keys.pop();
            }
        }
        while (temp.empty() == false)
        {

            keys.push(temp.front());
            temp.pop();
        }
        pushQ(keys, splay->root->entry->key);
    }
    void pushQ(queue<K> &k, K key)
    {
        int size = k.size();
        if (size >= maxNumOfKeys)
            k.pop();
        k.push(key);
    }
    bool isPresentInQueue(K key)
    {
        queue<K> temp;
        bool flag = false;
        while (keys.empty() == false)
        {
            if (keys.front() == key)
            {
                temp.push(keys.front());
                keys.pop();
                flag = true;
            }
            else
            {
                temp.push(keys.front());
                keys.pop();
            }
        }
        while (temp.empty() == false)
        {
            keys.push(temp.front());
            temp.pop();
        }
        return flag;
    }
    V search(K key, vector<K> &traversedList)
    {
        if (splay->root->entry->key == key)
        {
            return splay->root->entry->value;
        }
        else if (isPresentInQueue(key))
        {
            typename SplayTree::Node *p = splay->searchTrav(splay->root, key, traversedList);
            splay->splayOne(p);
            return p->entry->value;
        }
        else
        {
            typename AVLTree::Node *r = splay->root->corr;

            typename AVLTree::Node *p1 = avl->searchTrav(r, key, traversedList); //find from this corr
            if (p1 != NULL)
            {
                pushQ(keys, p1->entry->value);
                typename SplayTree::Node *f = p1->corr;
                splay->splayOne(f);
                return f->entry->value;
            }
            else // find from root if not found
            {
                typename AVLTree::Node *p2 = avl->findFromRoot(avl->root, r, key, traversedList);
                if (p2 == NULL)
                {
                    throw "Not found";
                }
                typename SplayTree::Node *p3 = p2->corr;
                splay->splayOne(p3);
                pushQ(keys, p2->entry->value);
                return p2->entry->value;
            }
        }
        return -1;
    }

    void traverseNLROnAVL(void (*func)(K key, V value))
    {
        avl->traverseNLR(func);
    }
    void traverseNLROnSplay(void (*func)(K key, V value))
    {
        splay->traverseNLR(func);
    }

    void clear()
    {
        avl->clear();
        splay->clear();
    }

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

            Node(Entry *entry = NULL, Node *left = NULL, Node *right = NULL, Node *parent = NULL)
            {
                this->entry = entry;
                this->left = left;
                this->right = right;
                this->parent = parent;
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
            Node *k = x->parent;
            Node *t;
            if (k != NULL)
                t = k->right;
            if (x->parent == NULL)
            { //x is root
                root = y;
            }
            else if (x == t)
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
        void splayOne(Node *n)
        {
            //node is not root
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
        Node *add(K key, V value)
        {
            if (isPresent(root, key) != NULL)
                throw "Duplicate key";
            Entry *entry = new Entry(key, value);
            return add(entry);
        }
        Node *isPresent(Node *rt, int key)
        {
            if (rt == NULL)
                return NULL;
            if (key == rt->entry->key)
                return rt;
            if (key < rt->entry->key)
                return isPresent(rt->left, key);

            return isPresent(rt->right, key);
        }
        Node *searchTrav(Node *rt, int key, vector<K> &traverseList)
        {
            if (rt == NULL)
                return NULL;
            if (key == rt->entry->key)
                return rt;
            traverseList.push_back(rt->entry->key);
            if (key < rt->entry->key)
                return searchTrav(rt->left, key, traverseList);

            return searchTrav(rt->right, key, traverseList);
        }
        Node *add(Entry *entry)
        {
            if (isPresent(root, entry->key) != NULL)
                throw "Duplicate key";
            Node *n = new Node(entry);
            if (root == NULL)
            {
                root = n;
                return root;
            }
            insert(n);
            return root;
        }
        Node *maximum(Node *x)
        {
            while (x->right != NULL)
                x = x->right;
            return x;
        }
        void deleteNode(Node *n)
        {
            splay(n);

            SplayTree *left_subtree = new SplayTree();
            left_subtree->root = this->root->left;
            if (left_subtree->root != NULL)
                left_subtree->root->parent = NULL;

            SplayTree *right_subtree = new SplayTree();
            right_subtree->root = this->root->right;
            if (right_subtree->root != NULL)
                right_subtree->root->parent = NULL;

            delete n;
            if (right_subtree->root == NULL)
            {
                this->root = left_subtree->root;
                return;
            }
            if (left_subtree->root == NULL)
            {
                this->root = right_subtree->root;
                return;
            }
            if (left_subtree->root != NULL)
            {
                Node *m = maximum(left_subtree->root);
                left_subtree->splay(m);
                left_subtree->root->right = right_subtree->root;
                this->root = left_subtree->root;
            }
            else
            {
                this->root = right_subtree->root;
            }
        }
        void remove(K key)
        {
            Node *n = isPresent(root, key);
            if (n == NULL)
            {
                throw "Not found";
            }
            deleteNode(n);
        }
        V search(K key)
        {
            Node *n = isPresent(root, key);

            if (n == NULL)
            {
                throw "Not found";
            }
            else
            {
                splay(n);
                return n->entry->value;
            }
        }

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

        void deleteTree(Node *node)
        {
            if (node == NULL)
                return;
            deleteTree(node->left);
            deleteTree(node->right);
            delete node;
        }
        void clear()
        {
            deleteTree(root);
        }
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
            typename SplayTree::Node *corr;

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

        AVLTree() : root(NULL){};
        ~AVLTree() { this->clear(); };
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

        Node *insertRec(Node *&r, Entry *entry)
        {
            if (r == NULL)
            {
                Node *r = new Node(entry); //create new Node with entry
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
        Node *isPresent(Node *rt, int key)
        {
            if (rt == NULL)
                return NULL;
            if (key == rt->entry->key)
                return rt;
            if (key < rt->entry->key)
                return isPresent(rt->left, key);

            return isPresent(rt->right, key);
        }
        Node *searchTrav(Node *rt, int key, vector<K> &traversedList)
        {
            if (rt == NULL)
                return NULL;
            if (key == rt->entry->key)
                return rt;
            traversedList.push_back(rt->entry->key);
            if (key < rt->entry->key)
                return searchTrav(rt->left, key, traversedList);

            return searchTrav(rt->right, key, traversedList);
        }
        Node *findFromRoot(Node *rt, Node *&r, K key, vector<K> &traversedList)
        {
            if (rt == NULL)
                return NULL;
            if (rt == r)
                throw "Not found";
            if (key == rt->entry->key)
                return rt;
            traversedList.push_back(rt->entry->key);
            if (key < rt->entry->key)
                return searchTrav(rt->left, key, traversedList);

            return searchTrav(rt->right, key, traversedList);
        }
        Node *add(K key, V value)
        {
            if (isPresent(root, key) != NULL)
                throw "Duplicate key";
            Entry *entry = new Entry(key, value);
            return add(entry);
        }
        Node *add(Entry *entry)
        {
            if (isPresent(root, entry->key) != NULL)
                throw "Duplicate key";
            if (root == NULL)
            {
                root = new Node(entry);
                return root;
            }
            return insertRec(root, entry);
        }
        Node *inpre(Node *p)
        {
            while (p->right != NULL)
                p = p->right;
            return p;
        }
        Node *insuc(Node *p)
        {
            while (p->left != NULL)
                p = p->left;

            return p;
        }
        Node *deleteNode(Node *p, Node *n)
        {
            if (p->left == NULL && p->right == NULL)
            {
                if (p == this->root)
                    this->root = NULL;
                delete p;
                return NULL;
            }
            Node *q;
            if (p->entry->key < n->entry->key)
            {
                p->right = deleteNode(p->right, n);
            }
            else if (p->entry->key > n->entry->key)
            {
                p->left = deleteNode(p->left, n);
            }
            else
            {
                if (p->left != NULL)
                {
                    q = inpre(p->left);
                    p->entry->key = q->entry->key;
                    p->left = deleteNode(p->left, q);
                }
                else
                {
                    q = insuc(p->right);
                    p->entry->key = q->entry->key;
                    p->right = deleteNode(p->right, q);
                }
            }
            if (bf(p) == 2 && bf(p->left) == 1)
            {
                p = llrotation(p);
            }
            else if (bf(p) == 2 && bf(p->left) == -1)
            {
                p = lrrotation(p);
            }
            else if (bf(p) == 2 && bf(p->left) == 0)
            {
                p = llrotation(p);
            }
            else if (bf(p) == -2 && bf(p->right) == -1)
            {
                p = rrrotation(p);
            }
            else if (bf(p) == -2 && bf(p->right) == 1)
            {
                p = rlrotation(p);
            }
            else if (bf(p) == -2 && bf(p->right) == 0)
            {
                p = llrotation(p);
            }

            return p;
        }
        void remove(K key)
        {
            Node *n = isPresent(root, key);
            if (n == NULL)
            {
                throw "Not found";
            }
            root = deleteNode(root, n);
        }
        V search(K key)
        {
            Node *n = isPresent(root, key);
            if (n == NULL)
            {
                throw "Not found";
            }
            else
            {
                return n->entry->value;
            }
        }
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
        void deleteTree(Node *node)
        {
            if (node == NULL)
                return;
            deleteTree(node->left);
            deleteTree(node->right);
            delete node;
        }
        void clear()
        {
            deleteTree(root);
        }
    };
};
void printKey(int key, int value)
{
    cout << key << " ";
}
int main()
{
    BKUTree<int, int> *tree = new BKUTree<int, int>(3);
    int keys[] = {1, 3, 5, 7, 9, 2, 4};
    for (int i = 0; i < 7; i++)
        tree->add(keys[i], keys[i]);
    vector<int> x;
    cout << tree->search(9, x) << endl;
    for (auto i : x)
    {
        cout << i << " ";
    }
    cout << endl;
    tree->traverseNLROnSplay(printKey);
    cout << endl;
    tree->traverseNLROnAVL(printKey);
}