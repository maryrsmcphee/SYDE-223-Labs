// SYDE 223, W2020, LAB 3
// Mary McPhee, 20717047
// Sammy Robens-Paradise, 20719541

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
    // TODO: This could be done smarter, use k and val->priority to check which direction to search down.
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
        return exists(root, val.priority);
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
    TaskItem *newValToInsert = new TaskItem(val);
    TaskItem *prevValSeen = root;
    if (val.priority < 0) {
        return false;
    } else if (root == NULL) {
        root = newValToInsert;
        size++;
    } else {
        int index = 0;
        while (newValToInsert != NULL) {
            index++;
            if (newValToInsert->priority < prevValSeen->priority) {
                if (prevValSeen->left == NULL) {
                    prevValSeen->left = newValToInsert;
                    size++;
                    return true;
                } else {
                    prevValSeen = prevValSeen->left;
                }
            } else if (newValToInsert->priority > prevValSeen->priority) {
                if (prevValSeen->right == NULL) {
                    prevValSeen->right = newValToInsert;
                    size++;
                    return true;
                } else {
                    prevValSeen = prevValSeen->right;
                }
            } else if (val.priority == newValToInsert->priority) {
                return false;
            }
        }
    }
    return true;
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
    } else if (val.priority == root->priority){
        BinarySearchTree::TaskItem *replaceWithMeParent;
        BinarySearchTree::TaskItem *deleteMe = root;
        if (deleteMe->left == NULL) {
            // right leaf
            root = root->right;
            free(deleteMe);
        } else if (deleteMe->right == NULL) {
            // left leaf
            root = root->left;
            free(deleteMe);
        } else {
            // has grandchildren
            if (deleteMe->right->left != NULL) {
                replaceWithMeParent = deleteMe->right;
                while (replaceWithMeParent->left->left != NULL) {
                    replaceWithMeParent = replaceWithMeParent->left;
                }
                replaceWithMeParent->left->left = deleteMe->left;
                replaceWithMeParent->left->right = deleteMe->right;
                root = replaceWithMeParent->left;
                replaceWithMeParent->left = NULL;
                free(deleteMe);
            } else {
                replaceWithMeParent = deleteMe;
                replaceWithMeParent->right->left = deleteMe->left;
                root = replaceWithMeParent->right;
                free(deleteMe);
            }
        }
        size--;
        return true;
    } else {
        // general case
        return remove(root, val.priority);
    }
}

bool BinarySearchTree::remove(BinarySearchTree::TaskItem *node, int k) {
    // We've reached the end and since we have to delete a node from the parent we've failed.
    if (node->left == NULL && node->right == NULL) return false;

    bool goRight = k > node->priority;

    if (goRight && node->right != NULL) {
        if (node->right->priority == k) {
            // We've found it so delete.
            BinarySearchTree::TaskItem *replaceWithMeParent;
            BinarySearchTree::TaskItem *deleteMe = node->right;
            if (deleteMe->left == NULL && deleteMe->right == NULL){
                // a one-child situation
                free(deleteMe);
                node->right = NULL;
            } else if (deleteMe->left == NULL) {
                // right leaf
                replaceWithMeParent = deleteMe;
                node->right = replaceWithMeParent->right;
                free(deleteMe);
            } else if (deleteMe->right == NULL) {
                // left leaf
                replaceWithMeParent = deleteMe;
                node->right = replaceWithMeParent->left;
                free(deleteMe);
            } else {
                // Has grandchildren
                if (deleteMe->right->left != NULL) {
                    replaceWithMeParent = deleteMe->right;
                    while (replaceWithMeParent->left->left != NULL) {
                        // ends up being replaceWithMe's parent
                        replaceWithMeParent = replaceWithMeParent->left;
                    }
                    replaceWithMeParent->left->left = deleteMe->left;
                    replaceWithMeParent->left->right = deleteMe->right;
                    node->right = replaceWithMeParent->left;
                    replaceWithMeParent->left = NULL;
                    free(deleteMe);
                } else {
                    replaceWithMeParent = deleteMe;
                    replaceWithMeParent->right->left = deleteMe->left;
                    node->right = replaceWithMeParent->right;
                    free(deleteMe);
                }
            }
            size--;
            return true;
            // Else it's somewhere down this tree.
        } else return remove(node->right, k);
    } else if (!goRight && node->left != NULL) {
        if (node->left->priority == k) {
            // We've found it so delete.
            BinarySearchTree::TaskItem *replaceWithMeParent;
            BinarySearchTree::TaskItem *deleteMe = node->left;
            if (deleteMe->left == NULL && deleteMe->right == NULL){
                // a one-child situation
                free(deleteMe);
                node->left = NULL;
            } else if (deleteMe->left == NULL) {
                // right leaf
                replaceWithMeParent = deleteMe;
                node->left = replaceWithMeParent->right;
                free(deleteMe);
            } else if (deleteMe->right == NULL) {
                // left leaf
                replaceWithMeParent = deleteMe;
                node->left = replaceWithMeParent->left;
                free(deleteMe);
            } else {
                // Has grandchildren
                if (deleteMe->right->left != NULL) {
                    replaceWithMeParent = deleteMe->right;
                    while (replaceWithMeParent->left->left != NULL) {
                        // ends up being replaceWithMe's parent
                        replaceWithMeParent = replaceWithMeParent->left;
                    }
                    replaceWithMeParent->left->left = deleteMe->left;
                    replaceWithMeParent->left->right = deleteMe->right;
                    node->left = replaceWithMeParent->left;
                    replaceWithMeParent->left = NULL;
                    free(deleteMe);
                } else {
                    replaceWithMeParent = deleteMe;
                    replaceWithMeParent->right->left = deleteMe->left;
                    node->left = replaceWithMeParent->right;
                    free(deleteMe);
                }
            }
            size--;
            return true;
        } else return remove(node->left, k);
        // Else the node we're looking for is down a tree that doesn't exist so fail.
    } else return false;
}

