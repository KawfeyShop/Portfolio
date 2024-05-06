#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// Data structure to store a binary tree node
struct Node
{
    int data;
    Node* left, * right;

    Node(int data)
    {
        this->data = data;
        this->left = this->right = nullptr;
    }
};

// Function to check if a given binary tree is a min-heap or not
bool isHeap(Node* root)
{
    // an empty tree is a heap. 
    if (root == nullptr)
        return true;

    // checking to see if the left or right child is nullptr. If it is this means that the heap is not complete. At the same time comparing root and left and right child 
    // to make sure that root/partent is less than kids. 
    if (root->left != nullptr && root->data > root->left->data) {
        return false;
    }
    if (root->right != nullptr && root->data > root->right->data) {
        return false;
    }
    // recursively do the functions above. If it makes it to this return function, that means that it's going to return true. 
    return isHeap(root->left) && isHeap(root->right);
}

int main()
{
    /* Construct the following tree
               2
             /   \
            /     \
           3       4
          / \     / \
         /   \   /   \
        5     6 8    10
    */

    Node* root = new Node(2);
    root->left = new Node(3);
    root->right = new Node(4);
    root->left->left = new Node(5);
    root->left->right = new Node(6);
    root->right->left = new Node(8);
    root->right->right = new Node(10);

    if (isHeap(root)) {
        cout << "The given binary tree is a min-heap";
    }
    else {
        cout << "The given binary tree is not a min-heap";
    }

    return 0;
}
