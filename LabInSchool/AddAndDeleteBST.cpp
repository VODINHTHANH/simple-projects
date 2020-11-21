#include <iostream>
#include <string>
#include <sstream>
using namespace std;
#define SEPARATOR "#<ab@17943918#@>#"
template <class T>
class BinarySearchTree
{
public:
    class Node;

private:
    Node *root;

public:
    BinarySearchTree() : root(nullptr) {}
    ~BinarySearchTree()
    {
        // You have to delete all Nodes in BinaryTree. However in this task, you can ignore it.
    }

    //Helping function
    Node *insert(Node *node, T key)
    {
        /* Otherwise, recur down the tree */
        if (node == NULL)
        {
            node = new Node(key);
            return node;
        }
        if (key <= node->value)
            node->pLeft = insert(node->pLeft, key);
        else if (key > node->value)
            node->pRight = insert(node->pRight, key);

        /* return the (unchanged) node pointer */
        return node;
    }
    void add(T value)
    {
        //TODO
        if (root == NULL)
        {
            root = new Node(value);
            return;
        }
        insert(root, value);
    }
    Node *minValueNode(Node *node)
    {
        Node *current = node;

        /* loop down to find the leftmost leaf */
        while (current && current->pLeft != NULL)
            current = current->pLeft;

        return current;
    }

    Node *deleteRec(Node *node, T key)
    { // base case
        if (node == NULL)
            return node;

        // If the key to be deleted is
        // smaller than the node's
        // key, then it lies in left subtree
        if (key < node->value)
            node->pLeft = deleteRec(node->pLeft, key);

        // If the key to be deleted is
        // greater than the node's
        // key, then it lies in right subtree
        else if (key > node->value)
            node->pRight = deleteRec(node->pRight, key);

        // if key is same as node's key, then This is the node
        // to be deleted
        else
        {
            // node with only one child or no child
            if (node->pLeft == NULL)
            {
                Node *temp = node->pRight;
                free(node);
                return temp;
            }
            else if (node->pRight == NULL)
            {
                Node *temp = node->pLeft;
                free(node);
                return temp;
            }

            // node with two children: Get the inorder successor
            // (smallest in the right subtree)
            Node *temp = minValueNode(node->pRight);

            // Copy the inorder successor's content to this node
            node->value = temp->value;

            // Delete the inorder successor
            node->pRight = deleteRec(node->pRight, temp->value);
        }
        return node;
    }
    void deleteNode(T value)
    {
        //TODO
        if (root == NULL)
        {
            return;
        }
        if (root->pLeft == NULL && root->pRight == NULL)
        {
            if (root->value == value)
            {
                delete root;
                root = NULL;
                return;
            }
        }
        deleteRec(root, value);
    }
    string inOrderRec(Node *root)
    {
        stringstream ss;
        if (root != nullptr)
        {
            ss << inOrderRec(root->pLeft);
            ss << root->value << " ";
            ss << inOrderRec(root->pRight);
        }
        return ss.str();
    }

    string inOrder()
    {
        return inOrderRec(this->root);
    }

    class Node
    {
    private:
        T value;
        Node *pLeft, *pRight;
        friend class BinarySearchTree<T>;

    public:
        Node(T value) : value(value), pLeft(NULL), pRight(NULL) {}
        ~Node() {}
    };
};
int main()
{
    BinarySearchTree<int> bst;
    bst.add(9);
    bst.add(2);
    bst.add(10);
    bst.add(8);
    cout << bst.inOrder() << endl;
    bst.add(11);
    bst.deleteNode(9);
    cout << bst.inOrder();
}
