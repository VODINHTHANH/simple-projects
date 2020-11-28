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

        void add(K key, V value);

        Node *rightRotate(Node *x)
        {
            Node *y = x->left;
            x->left = y->right;
            y->right = x;
            return y;
        }

        // A utility function to left
        // rotate subtree rooted with x
        // See the diagram given above.
        Node *leftRotate(Node *x)
        {
            Node *y = x->right;
            x->right = y->left;
            y->left = x;
            return y;
        }
        Node *splay(Node *&r, Entry *&entry)
        {
            // Base cases: r is NULL or
            // key is present at r
            if (r == NULL || r->entry->key == entry->key)
                return r;

            // Key lies in left subtree
            if (r->entry->key > entry->key)
            {
                // Key is not in tree, we are done
                if (r->left == NULL)
                    return r;

                // Zig-Zig (Left Left)
                if (r->left->entry->key > entry->key)
                {
                    // First recursively bring the
                    // key as r of left-left
                    r->left->left = splay(r->left->left, entry);

                    // Do first rotation for r,
                    // second rotation is done after else
                    r = rightRotate(r);
                }
                else if (r->left->entry->key < entry->key) // Zig-Zag (Left Right)
                {
                    // First recursively bring
                    // the key as r of left-right
                    r->left->right = splay(r->left->right, entry);

                    // Do first rotation for r->left
                    if (r->left->right != NULL)
                        r->left = leftRotate(r->left);
                }

                // Do second rotation for r
                return (r->left == NULL) ? r : rightRotate(r);
            }
            else // Key lies in right subtree
            {
                // Key is not in tree, we are done
                if (r->right == NULL)
                    return r;

                // Zig-Zag (Right Left)
                if (r->right->entry->key > entry->key)
                {
                    // Bring the key as r of right-left
                    r->right->left = splay(r->right->left, entry);

                    // Do first rotation for r->right
                    if (r->right->left != NULL)
                        r->right = rightRotate(r->right);
                }
                else if (r->right->entry->key < entry->key) // Zag-Zag (Right Right)
                {
                    // Bring the key as r of
                    // right-right and do first rotation
                    r->right->right = splay(r->right->right, entry);
                    r = leftRotate(r);
                }

                // Do second rotation for r
                return (r->right == NULL) ? r : leftRotate(r);
            }
        }
        Node *insert(Node *&r, Entry *&entry)
        {
            // Simple Case: If tree is empty
            if (r == NULL)
            {
                if (r == NULL)
                {
                    Node *r = new Node(entry, NULL, NULL); //create new Node with entry
                    return r;
                }
            }
            // Bring the closest leaf Node to root
            r = splay(r, entry);

            // If key is already present, then return
            if (r->entry->key == entry->key)
                return r;

            // Otherwise allocate memory for new Node
            Node *newNode = new Node(entry, NULL, NULL);

            // If root's key is greater, make
            // root as right child of newNode
            // and copy the left child of root to newNode
            if (r->entry->key > entry->key)
            {
                newNode->right = r;
                newNode->left = r->left;
                r->left = NULL;
            }

            // If root's key is smaller, make
            // root as left child of newNode
            // and copy the right child of root to newNode
            else
            {
                newNode->left = r;
                newNode->right = r->right;
                r->right = NULL;
            }

            return newNode; // newNode becomes new root
        }
        Node *add(Entry *&entry)
        {
            Node *r = root;
            return insert(r, entry);
        }
        void remove(K key);
        V search(K key);

        void traverseNLR(void (*func)(K key, V value))
        {
            Node *r = root;
            if (r == NULL)
                return;

            /* first print data of node */
            func(r->entry->key, r->entry->value);
            /* then recur on left sutree */
            r = r->left;
            traverseNLR(func);

            /* now recur on right subtree */
            r = r->right;
            traverseNLR(func);
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
                r->balance = 0;
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
            Node *r = root;
            return insertRec(r, entry);
        }

        void remove(K key);
        V search(K key);

        void traverseNLR(void (*func)(K key, V value))
        {
            Node *r = root;
            if (r == NULL)
                return;

            /* first print data of node */
            func(r->entry->key, r->entry->value);
            /* then recur on left sutree */
            r = r->left;
            traverseNLR(func);

            /* now recur on right subtree */
            r = r->right;
            traverseNLR(func);
        }

        void clear();
    };
};

int main()
{
}