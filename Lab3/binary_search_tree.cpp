#include <iostream>
#include "binary_search_tree.h"

using namespace std;

// PURPOSE: Default/empty constructor
BinarySearchTree::BinarySearchTree() {
    root = NULL;
    size = 0;
}

// PURPOSE: Explicit destructor of the class BinarySearchTree
// TODO
BinarySearchTree::~BinarySearchTree() {
}

// PURPOSE: Returns the number of nodes in the tree
unsigned int BinarySearchTree::get_size() const {
    return size;
}

// PURPOSE: Returns the maximum value of a node in the tree
// if the tree is empty, it returns (-1, "N/A")
BinarySearchTree::TaskItem BinarySearchTree::max() const {
    if (!root) return BinarySearchTree::TaskItem(-1, "N/A");
    TaskItem *temp = root;
    while (temp->right) {
        temp = temp->right;
    }
    return *temp;
}

// PURPOSE: Returns the minimum value of a node in the tree
// if the tree is empty, it returns (-1, "N/A")
BinarySearchTree::TaskItem BinarySearchTree::min() const {
    if (!root) return BinarySearchTree::TaskItem(-1, "N/A");
    // since lower values in a bst are on the left (slide 9 lecture 8)
    TaskItem *temp = root;
    while (temp->left) {
        temp = temp->left;
    }
    return *temp;
}

// PURPOSE: Returns the tree height

unsigned int BinarySearchTree::height(BinarySearchTree::TaskItem *node, int h) const {
    if (node == NULL) {
        return h - 1;
    } else if (node->left == NULL && node->right != NULL) {
        // go right
        return height(node->right, h + 1);
    } else if (node->right == NULL && node->left != NULL) {
        // go left
        return height(node->left, h + 1);
    } else {
        // both are null and return height
        return h;
    }
}

unsigned int BinarySearchTree::height() const {
    if (root == NULL) {
        return 0;
    } else if (root != NULL && size == 1) {
        return 1;
    } else {
        int initHeight = 2;
        int leftH = height(root->left, initHeight);
        int rightH = height(root->right, initHeight);
        return leftH > rightH ? leftH : rightH;
    }
}

// PURPOSE: Prints the contents of the tree format not specified
// TODO: we never actually print anything here
void BinarySearchTree::print(struct BinarySearchTree::TaskItem *node) const {
    if (node == NULL) {
        cout << "\n";
        return;
    } else {
        cerr << node->priority << " ";
        print(node->left);
        print(node->right);
    }
}

void BinarySearchTree::print() const {
    cerr << "print pre-order" << endl;
    if (root == NULL) {
        cerr << "tree empty, nothing to print" << endl;
    } else {
        print(root);
    }
    cerr << endl;
}


// PURPOSE: Returns true if a node with the value val exists in the tree
// otherwise, returns false
// TODO always returns false
bool BinarySearchTree::exists(struct BinarySearchTree::TaskItem *val, int k) const {
    if (val == NULL) {
        return false;
    }
    if (val->priority == k) {
        return true;
    }
    /* then recur on left sutree */
    bool res1 = exists(val->left, k);
    if (res1) {
        return true;
    }  // node found, no need to look further
    /* node is not found in left, so recur on right subtree */
    bool res2 = exists(val->right, k);
    return res2;
}

bool BinarySearchTree::exists(BinarySearchTree::TaskItem val) const {
    if (root == NULL) {
        cerr << "Empty tree\n";
        return false;
    } else {
        exists(root, val.priority);
    }
}

// PURPOSE: Optional helper function that returns a pointer to the root node
BinarySearchTree::TaskItem *BinarySearchTree::get_root_node() {
    if (!root) {
        cerr << "Empty tree\n";
        return 0;
    }
    return root;
}

/**
 * PURPOSE: Optional helper function that
 * returns the root node pointer address
 * @return
 */
BinarySearchTree::TaskItem **BinarySearchTree::get_root_node_address() {
    return !root ? NULL : &root;
}

/**
 * PURPOSE: Optional helper function that gets the maximum depth for a given node
 * Takes n as root node initially
 * @param n
 * @return
 */
int BinarySearchTree::get_node_depth(BinarySearchTree::TaskItem *n) const {
    if (!n) {
        return 0;
    } else {
        // compute the depth of each subtree
        int ld = get_node_depth(n->left);
        int rd = get_node_depth(n->right);
        // choose larger
        if (ld > rd)
            return (ld + 1);
        else return (rd + 1);
    }
}


/**
 * PURPOSE: Inserts the value val into the tree if it is unique
 * returns true if successful; returns false if val already exists
 * @param val
 * @return bool
 */
bool BinarySearchTree::insert(BinarySearchTree::TaskItem val) {
    if (exists(val)) {
        return false;
    } else {
        return insert(&val, root);
    }
}

/**
 * PURPOSE: Inserts the value val into the tree if it is unique
 * returns true if successful; returns false if val already exists
 * @param val
 * @param node
 * @return bool
 */
// TODO: Re-sorting tree doesn't work properly
bool BinarySearchTree::insert(BinarySearchTree::TaskItem *val, BinarySearchTree::TaskItem *node) {
    if (node == NULL) {
        // if it is the first node
        if (node == root) {
            root = val;
            size++;
            return true;
        }
    } else if (node->right == NULL || node->left == NULL) {
        // else if the node has leaf nodes
        if (val->priority < node->priority) {
            // assign left if less
            if (node->left == NULL) {
                node->left = val;
            } else {
                return insert(val, node->left);
            }
        } else {
            // assign right if more
            if (node->right == NULL) {
                node->right = val;
            } else {
                return insert(val, node->right);
            }
        }
        size++;
        return true;
    } else if (val->priority >= node->priority) {
        // go right
        return insert(val, node->right);
    } else {
        // go left
        return insert(val, node->left);
    }
}

// PURPOSE: Removes the node with the value val from the tree
// returns true if successful; returns false otherwise
bool BinarySearchTree::remove(BinarySearchTree::TaskItem val) {
    if (root == NULL) {
        // if the tree is empty
        return false;
    } else if (val.priority == root->priority && size == 1) {
        // if the tree only has one node
        root = NULL;
        size--;
        return true;
    } else {
        // general case
        return remove(root, val.priority);
    }

}

// TODO: Only works when first called
bool BinarySearchTree::remove(BinarySearchTree::TaskItem *node, int k) {
    if(k == node->priority){
        // node found
        if(node->left == NULL && node->right == NULL){
            // case if leaf node
            node = NULL;
            delete node;
        }else if(node->left != NULL && node->right == NULL){
            // case if node has left branch
            if(node->left->left == NULL && node->left->right == NULL){
                // case that the child node is a leaf node
                node = node->left;
                node->left = NULL;
            }else{
                // case where a swap is required
            }
        }else if(node->right != NULL && node->left == NULL){
            // case if node has right branch
            if(node->right->left == NULL && node->right->right == NULL){
                // case that the child node is a leaf node
                node = node->right;
                node->right = NULL;
            }else{
                // case where a swap is required
            }
        }
        size--;
        return true;
    }else
    if(k < node->priority){
        // go left
        return remove(node->left,k);
    }else{
        // go right
        return remove(node->right,k);
    }

}

