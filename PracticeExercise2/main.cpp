/** SYDE 223, W2020, PRACTICE EXERCISE 2
 Mary McPhee, 20717047
 Sammy Robens-Paradise, 20719541
 */

#include <iostream>
#include <string>

using namespace std;
// setup for test node structure to create nodes to use
struct BinaryTreeNode {
    int value;
    struct BinaryTreeNode *left;
    struct BinaryTreeNode *right;
};

/**
 * sets value to data and
 * left and right pointers to NULL
 * @param data
 * @return struct node
 */
struct BinaryTreeNode *createNode(int data) {
    struct BinaryTreeNode *node = (struct BinaryTreeNode *) malloc(sizeof(struct BinaryTreeNode));
    // set node state
    node->value = data;
    node->left = NULL;
    node->right = NULL;
    return (node);
}

/**
 * preOrder helper function returns void
 * prints ROOT -> LEFT SUBTREE -> RIGHT SUBTREE
 * so       4
 *        /  \
 *       3   5
 * would print: 4 3 5
 * @param root
 */
void printPreOrder(struct BinaryTreeNode *root) {
    // ROOT -> LEFT SUBTREE -> RIGHT SUBTREE
    if (root == NULL)
        return;
    cout << root->value << " ";
    printPreOrder(root->left);
    printPreOrder(root->right);
}

/**
 * finds and prints the nodes that sum to
 * a desired input
 * @param T
 * @param desired_sum
 * @param cur_sum
 * @param buffer
 */
void find_and_print_sum_of_nodes(BinaryTreeNode *T, int desired_sum, int cur_sum, string buffer) {
    if (!T)
        return;

    // update the ongoing sum with the current value for T
    int new_sum = cur_sum + T->value;
    // update the current path string
    char valToAddToBuffer = '0' + T->value;
    if (T->value == desired_sum && T->left == T->right == NULL) {
        cout << valToAddToBuffer << endl;
    }
    string new_buffer = buffer + " " + valToAddToBuffer;
    // if the desired sum is found, print the corresponding path
    if (new_sum == desired_sum)
        cout << new_buffer << endl;
    // TODO: continue down the left subtree
    find_and_print_sum_of_nodes(T->left, desired_sum, new_sum, new_buffer);
    // TODO: continue down the right subtree
    find_and_print_sum_of_nodes(T->right, desired_sum, new_sum, new_buffer);
    // since we always start with an empty buffer
    // restart from the left subtree if buffer = “”
    // restart from the right subtree if buffer = “”
    if (buffer == "") {
        cur_sum = 0;
        find_and_print_sum_of_nodes(T->left, desired_sum, cur_sum, "");
        find_and_print_sum_of_nodes(T->right, desired_sum, cur_sum, "");

    }

}

int find_max_sum_of_nodes(BinaryTreeNode *T, int &temp_max_sum) {
    // exit if T is NULLif (!T) return0;
    if (!T)
        return 0;

    // derive the maximum sum for the left subtree
    int left_sum = find_max_sum_of_nodes(T->left, temp_max_sum);
    // derive the maximum sum for the right subtree
    int right_sum = find_max_sum_of_nodes(T->right, temp_max_sum);
    // compare T->value, left_sum + T->value, and right_sum + T->value; store as max1
    int max1;
    if (left_sum > right_sum) {
        max1 = left_sum;
    } else max1 = right_sum;
    int max2 = left_sum + right_sum + T->value;
    // compare max1, left_sum + right_sum + T->value; store as max2, update temp_max_sum with the new max
    if (max1 > max2) {
        temp_max_sum = max1;
    } else temp_max_sum = max2;
    // TODO: return max1
    // it says return max1 but I think we should be returning temp_max_sum, why else would we be comparing them?
    return temp_max_sum;
}

int find_max_sum_of_nodes(BinaryTreeNode *T) {
    int temp_max_sum = INT_MIN;
    find_max_sum_of_nodes(T, temp_max_sum);
    return temp_max_sum;
}

int main() {
    cout << "Testing for find_and_print_sum_of_nodes" << endl;
    cout << "****************************************" << endl;
    /** First test case */
    cout << "FIRST TEST CASE" << endl;
    struct BinaryTreeNode *root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(5);
    root->left->left = createNode(3);
    root->left->right = createNode(4);
    root->right->left = createNode(6);
    root->right->right = createNode(7);
    printPreOrder(root);
    cout << endl;
    cout << "should print 1 2 3, 2 4, 1 5, 6" << endl;
    find_and_print_sum_of_nodes(root, 6, 0, "");

    /** Second test case */
    cout << "SECOND TEST CASE" << endl;
    struct BinaryTreeNode *root2 = createNode(1);
    root2->left = createNode(2);
    root2->right = createNode(3);
    root2->left->left = createNode(4);
    root2->left->right = createNode(5);
    root2->right->left = createNode(6);
    root2->right->right = createNode(7);
    printPreOrder(root2);
    cout << endl;
    cout << "should print 1 2 4, 2 5, 7" << endl;
    find_and_print_sum_of_nodes(root2, 7, 0, "");

    /** Third test case */
    cout << "THIRD TEST CASE" << endl;
    struct BinaryTreeNode *root3 = createNode(7);
    root3->left = createNode(6);
    root3->right = createNode(5);
    root3->left->left = createNode(4);
    root3->left->left->left = createNode(22);
    root3->left->right = createNode(3);
    root3->left->right->left = createNode(3);
    root3->left->right->left->right = createNode(3);
    root3->right->left = createNode(2);
    root3->right->right = createNode(1);
    root3->right->right->right = createNode(1);
    root3->right->right->right->right = createNode(8);
    printPreOrder(root3);
    cout << endl;
    cout << "should print 7 6 3 3 3, 7 5 1 1 8, 22" << endl;
    find_and_print_sum_of_nodes(root3, 22, 0, "");

    cout << "Testing for find_max_sum_of_nodes" << endl;
    cout << "**********************************" << endl;

    /** First test case */
    cout << "FIRST TEST CASE" << endl;
    cout << "should print 18" << endl;
    cout << find_max_sum_of_nodes(root) << endl;

    /** Second test case */
    cout << "SECOND TEST CASE" << endl;
    cout << "should print 18" << endl;
    cout << find_max_sum_of_nodes(root2) << endl; // should be 18

    /** Third test case */
    cout << "THIRD TEST CASE" << endl;
    cout << "should print 18" << endl;
    cout << find_max_sum_of_nodes(root3) << endl; // should be 18

    cout << "~TEST RUN COMPLETE~" << endl;
    return 0;

}
