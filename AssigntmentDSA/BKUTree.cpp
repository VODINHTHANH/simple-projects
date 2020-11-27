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
        typename AVLTree::Node *point = AVLTree::add(newEntry);
        typename AVLTree::Node *point1 = SplayTree::add(newEntry);
        point->corr = point1;
        point1->corr = point;
    }
    void remove(K key);
    V search(K key, vector<K> &traversedList);

    void traverseNLROnAVL(void (*func)(K key, V value));
    void traverseNLROnSplay(void (*func)(K key, V value));

    void clear();

    class SplayTree
    {
    public:
        class Node
        {
            Entry *entry;
            Node *left;
            Node *right;
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
        Node *rightRotate(Node *&x)
        {
            Node *y = x->left;
            x->left = y->right;
            y->right = x;
            return y;
        }

        Node *leftRotate(Node *&x)
        {
            Node *y = x->right;
            x->right = y->left;
            y->left = x;
            return y;
        }
        Node *splay(Node *&r, int key)
        {
            // Base cases: root is NULL or
            // key is present at root
            if (r == NULL || r->entry->key == key)
                return r;

            // Key lies in left subtree
            if (r->entry->key > key)
            {
                // Key is not in tree, we are done
                if (r->left == NULL)
                    return r;

                // Zig-Zig (Left Left)
                if (r->left->key > key)
                {
                    // First recursively bring the
                    // key as root of left-left
                    r->left->left = splay(r->left->left, key);

                    // Do first rotation for root,
                    // second rotation is done after else
                    r = rightRotate(r);
                }
                else if (r->left->key < key) // Zig-Zag (Left Right)
                {
                    // First recursively bring
                    // the key as root of left-right
                    r->left->right = splay(r->left->right, key);

                    // Do first rotation for root->left
                    if (r->left->right != NULL)
                        r->left = leftRotate(r->left);
                }

                // Do second rotation for root
                return (r->left == NULL) ? r : rightRotate(r);
            }
            else // Key lies in right subtree
            {
                // Key is not in tree, we are done
                if (r->right == NULL)
                    return r;

                // Zig-Zag (Right Left)
                if (r->right->key > key)
                {
                    // Bring the key as root of right-left
                    r->right->left = splay(r->right->left, key);

                    // Do first rotation for r->right
                    if (r->right->left != NULL)
                        r->right = rightRotate(r->right);
                }
                else if (r->right->key < key) // Zag-Zag (Right Right)
                {
                    // Bring the key as r of
                    // right-right and do first rotation
                    r->right->right = splay(r->right->right, key);
                    r = leftRotate(r);
                }

                // Do second rotation for r
                return (r->right == NULL) ? r : leftRotate(r);
            }
        }
        Node *insert(Node *&r, Node *newNode)
        {

            r = splay(r, newNode);

            // If key is already present, then return
            if (r->entry->key == newNode->entry->key)
                return r;

            // Otherwise allocate memory for new Node

            // If r's key is greater, make
            // r as right child of newNode
            // and copy the left child of r to newNode
            if (r->entry->key > newNode->entry->key)
            {
                newNode->right = r;
                newNode->left = r->left;
                r->left = NULL;
            }

            // If r's key is smaller, make
            // r as left child of newNode
            // and copy the right child of r to newNode
            else
            {
                newNode->left = r;
                newNode->right = r->right;
                r->right = NULL;
            }

            return newNode; // newNode becomes new root
        }
        void add(K key, V value);
        Node *add(Entry *entry)
        {
            Node *newNode = new Node(entry, NULL, NULL); //create new Node with entry
            if (root == NULL)
            {
                root = newNode;
                return root;
            }
            insert(root, newNode);
        }
        void remove(K key);
        V search(K key);

        void traverseNLR(void (*func)(K key, V value));

        void clear();
    };

    class AVLTree
    {
    public:
        class Node
        {
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
        Node *insertRec(Node *&r, Node *&newNode)
        {

            if (newNode->entry->key < r->entry->key)
                r->left = insertRec(r->left, newNode);
            else
                r->right = insertRec(r->right, newNode);

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
        Node *add(Entry *entry)
        {
            Node *newNode = new Node(entry, NULL, NULL); //create new Node with entry
            if (root == NULL)
            {
                root = newNode;
                root->balance = 0;
                return root;
            }
            insertRec(root, newNode);
        }

        void remove(K key);
        V search(K key);

        void traverseNLR(void (*func)(K key, V value));

        void clear();
    };
};

int main()
{
}