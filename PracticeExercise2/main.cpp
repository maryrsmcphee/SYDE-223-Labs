/** SYDE 223, W2020, PRACTICE EXERCISE 2
 Mary McPhee, 20717047
 Sammy Robens-Paradise, 20719541
 */

#include <iostream>
#include <string>
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
     if (!T)
         return;

    // update the ongoing sum with the current value for T
    int new_sum = cur_sum + T->value;
    // update the current path string
    char valToAddToBuffer = '0' + T->value;
    string new_buffer = buffer + " " + valToAddToBuffer;
    // if the desired sum is found, print the corresponding path
    if (new_sum == desired_sum)
        cout << new_buffer << endl;
    // TODO: continue down theleft subtree
    find_and_print_sum_of_nodes(T->left,desired_sum,new_sum,new_buffer);
    // TODO: continue down theright subtree
    find_and_print_sum_of_nodes(T->right,desired_sum,new_sum,new_buffer);
    if(buffer == ""){
        new_sum = 0;
        find_and_print_sum_of_nodes(T->left,desired_sum,new_sum,new_buffer);
        find_and_print_sum_of_nodes(T->right,desired_sum,new_sum,new_buffer);

    }
    // TODO: restart from the left subtree if buffer = “”
    // TODO: restart from the right subtreeif buffer = “”
}

int main() {
    struct BinaryTreeNode * root = createNode(5);
    root->left = createNode(4);
    root->right = createNode(7);
    root->left->left = createNode(2);
    root->left->right = createNode(3);
    printPreOrder(root);
    return 0;
}
