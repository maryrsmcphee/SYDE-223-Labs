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
    // TODO: continue down the left subtree
    find_and_print_sum_of_nodes(T->left,desired_sum,new_sum,new_buffer);
    // TODO: continue down the right subtree
    find_and_print_sum_of_nodes(T->right,desired_sum,new_sum,new_buffer);
    // since we always start with an empty buffer
    // restart from the left subtree if buffer = “”
    // restart from the right subtree if buffer = “”
    if(buffer == ""){
        cur_sum = 0;
        find_and_print_sum_of_nodes(T->left,desired_sum,cur_sum,"");
        find_and_print_sum_of_nodes(T->right,desired_sum,cur_sum,"");

    }

}

int find_max_sum_of_nodes (BinaryTreeNode* T, int &temp_max_sum) {
    // exit if T is NULLif (!T) return0;
    // derivethe maximum sum for the left subtree
    int left_sum = find_max_sum_of_nodes(T->left, temp_max_sum);
    // derivethe maximum sum for the right subtree
    int right_sum= find_max_sum_of_nodes(T->right, temp_max_sum);
    // TODO: compare T->value, left_sum + T->value, and right_sum + T->value; store as max1
    // TODO: compare max1, left_sum + right_sum + T->value; store as max2
    // TODO: update temp_max_sum with the new max
    // TODO: return max1
}

int find_max_sum_of_nodes(BinaryTreeNode *T) {
    int temp_max_sum = INT_MIN;
    find_max_sum_of_nodes(T, temp_max_sum);return temp_max_sum;
}

int main() {
    struct BinaryTreeNode * root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(5);
    root->left->left = createNode(3);
    root->left->right = createNode(4);
    root->right->left = createNode(6);
    root->right->right = createNode(7);
    printPreOrder(root);
    cout << endl;
    // test - should print 1 2 3, 2 4, 6
    find_and_print_sum_of_nodes (root, 6, 0, "");
    return 0;
}
