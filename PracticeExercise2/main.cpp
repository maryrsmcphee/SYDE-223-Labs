/** SYDE 223, W2020, PRACTICE EXERCISE 2
 Mary McPhee, 20717047
 Sammy Robens-Paradise, 20719541
 */

#include <iostream>
using namespace std;
// setup for test node structure to create nodes to use
struct BinaryTreeNode
{
    int value;
    struct BinaryTreeNode *left;
    struct BinaryTreeNode *right;
};
/**
 * @param data
 * @return struct node
 */
struct BinaryTreeNode* createNode(int data)
{
    struct BinaryTreeNode* node = (struct BinaryTreeNode*)malloc(sizeof(struct BinaryTreeNode));
    // set node state
    node->value = data;
    node->left = NULL;
    node->right = NULL;
    return(node);
}
void printPreOrder(struct BinaryTreeNode *root){
    // ROOT -> LEFT SUBTREE -> RIGHT SUBTREE
    if(root == NULL)
        return;
    cout<<root->value<<" ";
    printPreOrder(root->left);
    printPreOrder(root->right);
}

// function of interest
void find_and_print_sum_of_nodes (BinaryTreeNode* T, int desired_sum, int cur_sum, string buffer) {
    // exit if T is NULLif (!T) return;
    // update the ongoing sum with the current value for T
    int new_sum = cur_sum + T->value;
    // update the current path string
  //  string new_buffer = buffer + " " + int2ascii(T->value);
    // if the desired sum is found, print the corresponding path
  //  if (new_sum == desired_sum)cout << new_buffer << endl;
    // TODO: continue down theleft subtree
    // TODO: continue down theright subtree
    // TODO: restart from the left subtree if buffer = “”
    // TODO: restart from the right subtreeif buffer = “”
}

int main() {
    struct BinaryTreeNode * root = createNode(1);
    root->left = createNode(5);
    root->right = createNode(7);
    root->left->left = createNode(10);
    printPreOrder(root);
    return 0;
}

// Starter code
/*
void find_and_print_sum_of_nodes (BinaryTreeNode* T, int desired_sum, int cur_sum, string buffer) {
    // exit if T is NULLif (!T) return;
    // update the ongoing sum with the current value for T
    int new_sum = cur_sum + T->value;
    // update the current path string
    string new_buffer = buffer + " " + int2ascii(T->value);
    // if the desired sum is found, print the corresponding path
    if (new_sum == desired_sum)cout << new_buffer << endl;
    // TODO: continue down theleft subtree
    // TODO: continue down theright subtree
    // TODO: restart from the left subtree if buffer = “”
    // TODO: restart from the right subtreeif buffer = “”
}
 */