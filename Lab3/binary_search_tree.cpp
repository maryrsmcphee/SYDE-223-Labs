#include <iostream>
#include "binary_search_tree.h"

using namespace std;

// PURPOSE: Default/empty constructor
BinarySearchTree::BinarySearchTree() {
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
unsigned int BinarySearchTree::height() const {
    if (!root) return 0;
    int count = 1;
    TaskItem *temp = root;
    // since BST must have all elements at the furthest left position
    while (temp->left != NULL) {
        temp = temp->left;
        count++;
    }
    return count;
}

// PURPOSE: Prints the contents of the tree format not specified
// TODO: we never actually print anything here
void BinarySearchTree::print(struct BinarySearchTree::TaskItem *node) const {
    if (node == NULL) {
        return;
    } else {
        print(node->left);

        print(node->right);
    }
}

void BinarySearchTree::print() const {
    cout << "print pre-order" << endl;
    if (root == NULL) {
        cerr << "tree empty, nothing to print" << endl;
    } else {
        print(root);
    }
}


// PURPOSE: Returns true if a node with the value val exists in the tree
// otherwise, returns false
// TODO @Sammy
bool BinarySearchTree::exists(struct BinarySearchTree::TaskItem *val, int k) const {

    if (val == NULL) {
        return false;
    } else if (val->priority == k) {
        return true;
    } else if (k < val->priority) {
        exists(val->left, k);
    } else {
        exists(val->right, k);
    }
}

bool BinarySearchTree::exists(BinarySearchTree::TaskItem val) const { // I don't think this works... used in insert
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
bool BinarySearchTree::insert(BinarySearchTree::TaskItem *val, BinarySearchTree::TaskItem *node) {
    if (node == NULL) {
        root = val;
        size++;
        return true;
    } else if (node->left == NULL || node->right == NULL) {
        // reached the second last node depth
        if (val->priority > node->priority && node->right == NULL) {
            node->right = val;
        } else if (val->priority > node->priority && node->right != NULL) {
            node->left = val;
        } else if (val->priority < node->priority && node->left == NULL) {
            node->left = val;
        } else {
            node->right = val;
        }
        size++;
        return true;
    } else if (val->priority < node->priority) {
        return insert(val, node->left);
    } else {
        return insert(val, node->right);
    }
}

// PURPOSE: Removes the node with the value val from the tree
// returns true if successful; returns false otherwise
// TODO: remove when found
bool BinarySearchTree::remove(BinarySearchTree::TaskItem val) {
    if (root == NULL) {
        return false;
//    } else if (!exists(val)) { // expression always true, exists always returns false.
//        cerr << "!exists ";
//        return false;
    } else if (&val == root) {
        delete root;
        size--;
        return true;
    } else {
        return remove(root, val.priority);
    }

}

bool BinarySearchTree::remove(BinarySearchTree::TaskItem *val, int k) {
    if (val == NULL) {
        return false;
    } else if (val->priority == k) {
        cerr << "HERE!";
        // case where the node is found
        bool is_leaf_node = (val->left == NULL) && (val->right == NULL);
        bool has_one_child = val->left == NULL || val->right == NULL;
        bool has_two_children = val->left != NULL && val->right != NULL;
        if (is_leaf_node) {
            cerr << "is_leaf_node";
            delete val;
            size--;
            return true;
        } else if (has_one_child) {
            cerr << "has one child";

            if (val->left != NULL) {
                // swap then delete child
                TaskItem *temp = val;
                val = val->left;
                val->left = temp;
                delete val->left;
            } else {
                TaskItem *temp = val;
                val = val->right;
                val->right = temp;
                delete val->right;
            }
            size--;
            return true;
            /*
             * insert is wrong in how it organizes this
             * when used in test case 9, deleting t1,
             * it shouldn't have two children (it's the lowest, should be far left child)
             */
        } else if (has_two_children) {
            cerr << "has two children";

            TaskItem *current = val->right; // to be new parent of the mini-tree
            /* loop down to find the rightmost (highest) leaf */
            /*
             * it shouldn't swap with the highest value, it should swap with it's right child.
             * if it swaps with the highest val (makes that the parent) then all the right children will be lower, they should be higher.
             */
//            while (current->right != NULL) {
//                current = current->right;
//            }
            TaskItem *temp = val; // this is the pointed to be deleted - do we need to set a temp? can't we just delete val
            current->left = val->left; // make the left child pointers the same
            // current->right = val->right; // val->right is current so no
            // *val = *current; //I think this line should be deleted, we want to delete current and val shouldn't have the same priority
            // current = temp; // nope
            temp->left = NULL;
            temp->right = NULL;
            temp = nullptr;
            delete temp;
            size--;
            return true;
        }
    } else if (k < val->priority) {
        remove(val->left, k);
    } else {
        remove(val->right, k);
    }
}

