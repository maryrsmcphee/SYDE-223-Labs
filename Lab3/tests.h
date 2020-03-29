#ifndef LAB3_TESTS_H
#define LAB3_TESTS_H

#define ASSERT_TRUE(T) if (!(T)) return false;
#define ASSERT_FALSE(T) if ((T)) return false;

#include <algorithm>
#include <sstream>
#include <queue>

#include "priority_queue.h"
#include "binary_search_tree.h"

class PriorityQueueTest {
public:
    // PURPOSE: Tests if the new queue is valid
    bool test1() {
        PriorityQueue q(5);
        ASSERT_TRUE(q.empty());
        ASSERT_TRUE(!q.full());
        ASSERT_TRUE(q.get_size() == 0);
        return true;
    }

    // PURPOSE: Tests enqueue of one item and then dequeue of that item
    bool test2() {
        PriorityQueue test(4);
        ASSERT_TRUE(test.capacity == 4)
        PriorityQueue::TaskItem t1(1, "testItem1");
        PriorityQueue::TaskItem t2(2, "testItem2");
        PriorityQueue::TaskItem t3(3, "testItem3");
        PriorityQueue::TaskItem t4(4, "testItem4");
        ASSERT_TRUE(test.enqueue(t1))
        ASSERT_TRUE(test.enqueue(t2))
        ASSERT_TRUE(test.enqueue(t3))
        ASSERT_TRUE(test.enqueue(t4))
        ASSERT_TRUE(test.max() == t4)
        ASSERT_TRUE(test.get_size() == 4)
        ASSERT_TRUE(test.full())
        ASSERT_TRUE(test.capacity == 4)
        ASSERT_TRUE(test.dequeue())
        ASSERT_TRUE(test.dequeue())
        ASSERT_TRUE(test.dequeue())
        ASSERT_TRUE(test.dequeue())
        ASSERT_TRUE(test.get_size() == 0)
        ASSERT_FALSE(test.full())
        PriorityQueue test1(1);
        ASSERT_TRUE(test1.enqueue(t1))
        ASSERT_TRUE(test1.get_size() == 1)
        ASSERT_TRUE(test1.dequeue())
        ASSERT_TRUE(test1.get_size() == 0)
        return true;
    }

    // PURPOSE: Tests enqueue too many
    bool test3() {
        int testSize = 6;
        PriorityQueue test2(testSize);
        PriorityQueue::TaskItem t1(1, "testItem1");
        PriorityQueue::TaskItem t2(2, "testItem2");
        PriorityQueue::TaskItem t3(3, "testItem3");
        PriorityQueue::TaskItem t4(4, "testItem4");
        PriorityQueue::TaskItem t5(5, "testItem5");
        PriorityQueue::TaskItem t6(6, "testItem6");
        PriorityQueue::TaskItem t7(7, "testItem7");
        PriorityQueue::TaskItem t8(8, "testItem8");
        ASSERT_TRUE(test2.enqueue(t1))
        ASSERT_TRUE(test2.enqueue(t2))
        ASSERT_TRUE(test2.enqueue(t3))
        ASSERT_TRUE(test2.enqueue(t4))
        ASSERT_TRUE(test2.enqueue(t5))
        ASSERT_TRUE(test2.enqueue(t6))
        ASSERT_FALSE(test2.enqueue(t7))
        ASSERT_FALSE(test2.enqueue(t8))
        return true;
    }

    // PURPOSE: Tests enqueue too many then dequeue too many
    bool test4() {
        int testSize = 7;
        PriorityQueue test(testSize);
        PriorityQueue::TaskItem t1(1, "testItem1");
        PriorityQueue::TaskItem t2(2, "testItem2");
        PriorityQueue::TaskItem t3(3, "testItem3");
        PriorityQueue::TaskItem t4(4, "testItem4");
        PriorityQueue::TaskItem t5(5, "testItem5");
        PriorityQueue::TaskItem t6(6, "testItem6");
        PriorityQueue::TaskItem t7(7, "testItem7");
        PriorityQueue::TaskItem t8(8, "testItem8");
        ASSERT_TRUE(test.enqueue(t1))
        ASSERT_TRUE(test.enqueue(t2))
        ASSERT_TRUE(test.enqueue(t3))
        ASSERT_TRUE(test.enqueue(t4))
        ASSERT_TRUE(test.enqueue(t5))
        ASSERT_TRUE(test.enqueue(t6))
        ASSERT_TRUE(test.enqueue(t7))
        ASSERT_FALSE(test.enqueue(t8))

        // Dequeues all elements except t1.
        for (int i = 1; i < 7; i++) {
            ASSERT_TRUE(test.dequeue())
        }
        // Dequeues at size = 1
        test.dequeue();
        ASSERT_TRUE(test.empty())
        // should fail if dequeuing when empty
        ASSERT_FALSE(test.dequeue())
        return true;
    }
};

class BinarySearchTreeTest {
public:
    bool insert_nodes(BinarySearchTree &tree, int *in, int nin) {
        for (int i = 0; i < nin; i++) {
            ASSERT_TRUE(tree.insert(BinarySearchTree::TaskItem(in[i], "Test Task")));
        }
        return true;
    }

    // PURPOSE: Traverse the tree using breadth-first traversal
    // Output is as follows: "val1 val2 ... valN"
    std::string level_order(BinarySearchTree::TaskItem *root) {
        if (!root) {
            return "";
        }

        std::stringstream ss;
        std::queue<BinarySearchTree::TaskItem *> node_queue;
        node_queue.push(root);
        while (!node_queue.empty()) {
            BinarySearchTree::TaskItem *cur_node = node_queue.front();
            node_queue.pop();
            ss << cur_node->priority << " ";
            if (cur_node->left) {
                node_queue.push(cur_node->left);
            }
            if (cur_node->right) {
                node_queue.push(cur_node->right);
            }
        }

        std::string level_order_str = ss.str();

        return level_order_str.substr(0, level_order_str.size() - 1);
    }

    // PURPOSE: Tests if the new tree is valid
    bool test1() {
        std::string expected_tree_level_order = "";
        BinarySearchTree bst_test;
        ASSERT_TRUE(bst_test.get_root_node() == NULL);
        ASSERT_TRUE(bst_test.size == 0 && bst_test.get_size() == 0);
        // compare the tree's representation to the expected tree
        std::string tree_level_order = level_order(bst_test.root);
        ASSERT_TRUE(tree_level_order.compare(expected_tree_level_order) == 0)
        return true;
    }

    // PURPOSE: Tests a tree with one node
    bool test2() {
        BinarySearchTree bst;
        BinarySearchTree::TaskItem t1(1, "testItem1");
        ASSERT_TRUE(bst.insert(t1));
        ASSERT_TRUE(bst.get_size() == 1)
        ASSERT_TRUE(bst.height() == 1)
        ASSERT_TRUE(bst.remove(t1));
        ASSERT_TRUE(bst.get_size() == 0)
        ASSERT_TRUE(bst.height() == 0)
        ASSERT_FALSE(bst.remove(t1))
        return true;
    }

    // PURPOSE: Tests insert, remove, and size on linear list formation with three elements
    bool test3() {
        BinarySearchTree bst;
        BinarySearchTree::TaskItem t1(5, "testItem5");
        BinarySearchTree::TaskItem t2(6, "testItem6");
        BinarySearchTree::TaskItem t3(3, "testItem3");
        ASSERT_TRUE(bst.insert(t1));
        ASSERT_TRUE(bst.get_size() == 1)
        ASSERT_TRUE(bst.height() == 1)
        ASSERT_TRUE(bst.insert(t2));
        ASSERT_TRUE(bst.get_size() == 2)
        ASSERT_TRUE(bst.height() == 2)
        ASSERT_TRUE(bst.insert(t3))
        ASSERT_TRUE(bst.get_size() == 3)
        ASSERT_TRUE(bst.height() == 2)
        cerr<<" - Print: test3"<<endl;
        bst.print();
        ASSERT_TRUE(bst.remove(t3));
        ASSERT_TRUE(bst.get_size() == 2);
        ASSERT_TRUE(bst.height() == 2)
        cerr <<" remove node, then: "<<endl;
        bst.print();
        ASSERT_TRUE(bst.remove(t2));
        ASSERT_TRUE(bst.get_size() == 1);
        ASSERT_TRUE(bst.height() == 1)
        cerr <<" remove node, then: "<<endl;
        bst.print();
        ASSERT_FALSE(bst.remove(t2));
        ASSERT_TRUE(bst.remove(t1));
        ASSERT_TRUE(bst.get_size() == 0);
        ASSERT_TRUE(bst.height() == 0)
        cerr <<" remove node, then: "<<endl;
        bst.print();
        return true;
    }

    // PURPOSE: Tests removal of a node with one child
    bool test4() {
        BinarySearchTree bst;
        BinarySearchTree::TaskItem t3(3, "testItem3");
        BinarySearchTree::TaskItem t1(1, "testItem1");
        BinarySearchTree::TaskItem t4(4, "testItem4");
        BinarySearchTree::TaskItem t5(5, "testItem5");
        ASSERT_TRUE(bst.insert(t3))
        ASSERT_TRUE(bst.insert(t1));
        ASSERT_TRUE(bst.insert(t4));
        ASSERT_TRUE(bst.insert(t5))
        ASSERT_TRUE(bst.height() == 3);
        ASSERT_TRUE(bst.get_size() == 4);
        cerr<<" - Print: test4"<<endl;
        bst.print();
        //  remove nodes
        return true;
    }

    // PURPOSE: Tests insert of multiple elements and remove till nothing remains
    bool test5() {
        return false;
    }

    // PURPOSE: Tests removal of root node when both children of root have two children
    bool test6() {
        return false;
    }

    // PURPOSE: Tests depth with many inserts and some removes
    bool test7() {
        BinarySearchTree bst;
        BinarySearchTree::TaskItem t1(1, "testItem1");
        BinarySearchTree::TaskItem t2(2, "testItem2");
        BinarySearchTree::TaskItem t3(3, "testItem3");
        BinarySearchTree::TaskItem t4(4, "testItem4");
        BinarySearchTree::TaskItem t5(5, "testItem5");
        BinarySearchTree::TaskItem t6(6, "testItem6");
        BinarySearchTree::TaskItem t0(0, "testItem0");
        BinarySearchTree::TaskItem t_1(-1, "testItem0");
        ASSERT_FALSE(bst.remove(t1));
        ASSERT_TRUE(bst.insert(t1))
        ASSERT_TRUE(bst.insert(t2))
        ASSERT_TRUE(bst.insert(t3))
        ASSERT_TRUE(bst.insert(t4))
        ASSERT_TRUE(bst.insert(t5))
        ASSERT_TRUE(bst.insert(t6))
        cerr<<" - Print: test7"<<endl;
        bst.print();
        ASSERT_TRUE(bst.height() == 6)
        ASSERT_FALSE(bst.insert(t_1));
        ASSERT_TRUE(bst.insert(t0))
        ASSERT_TRUE(bst.height() == 6)
        bst.print();
       //   ASSERT_TRUE(bst.remove(t1))
     //   ASSERT_TRUE(bst.remove(t2))
     //   ASSERT_TRUE(bst.remove(t3))
     //   ASSERT_TRUE(bst.height() == 5)
        return true;
    }

    // PURPOSE: Tests lots of inserts and removes
    bool test8() {
        BinarySearchTree bst;
        BinarySearchTree::TaskItem t1(1, "testItem1");
        BinarySearchTree::TaskItem t2(2, "testItem2");
        BinarySearchTree::TaskItem t3(3, "testItem3");
        BinarySearchTree::TaskItem t4(4, "testItem4");
        BinarySearchTree::TaskItem t5(5, "testItem5");
        BinarySearchTree::TaskItem t6(6, "testItem6");
        ASSERT_TRUE(bst.insert(t1))
        ASSERT_FALSE(bst.insert(t1))
        ASSERT_TRUE(bst.insert(t2))
        ASSERT_TRUE(bst.insert(t3))
        ASSERT_TRUE(bst.insert(t4))
        ASSERT_TRUE(bst.insert(t5))
        ASSERT_TRUE(bst.insert(t6))
        ASSERT_TRUE(bst.get_size() == 6)
        cerr<<" - Print: test8"<<endl;
        bst.print();
        ASSERT_TRUE(bst.remove(t1))
        ASSERT_TRUE(bst.remove(t2))
        cerr << "about to print after remove 1 and 2 \n";
        bst.print();
        ASSERT_TRUE(bst.remove(t3))
        ASSERT_TRUE(bst.get_size() == 3)
        ASSERT_TRUE(bst.remove(t4))
        ASSERT_TRUE(bst.remove(t5))
        ASSERT_TRUE(bst.remove(t6))
        ASSERT_TRUE(bst.get_size() == 0)
        ASSERT_FALSE(bst.remove(t1))
       bst.print();
        return true;
    }
};

#endif
