#include "priority_queue.h"
#include <iostream>

# define GET_LEFT(i, heap){return heap[i*2];}
using namespace std;
#define GET_CHILD(i, type)(type == "R"? (i*2+1): (i*2));

// PURPOSE: Parametric constructor
// initializes heap to an array of (n_capacity + 1) elements
PriorityQueue::PriorityQueue(unsigned int n_capacity) {
    heap = new TaskItem *[n_capacity + 1];
    capacity = n_capacity;
    size = 0;
}

// TODO
// PURPOSE: Explicit destructor of the class PriorityQueue
PriorityQueue::~PriorityQueue() {
}

// PURPOSE: Returns the number of elements in the priority queue
unsigned int PriorityQueue::get_size() const {
    return size;
}

// PURPOSE: Returns true if the priority queue is empty; false, otherwise
bool PriorityQueue::empty() const {
    return size == 0;
}

// PURPOSE: Returns true if the priority queue is full; false, otherwise
bool PriorityQueue::full() const {
    return size == capacity;
}

// PURPOSE: Prints the contents of the priority queue; format not specified
void PriorityQueue::print() const {
    if (size == 0) {
        cerr << "Tree empty, nothing to print." << endl;
        return;
    }
    for (int i = 1; i <= size; i++) {
        cerr << heap[i]->priority << " ";
    }
    cerr << endl;
//    cerr << "\n order: depth D(i,n)\n" << endl;
//
//    cerr << '[';
//    for (int i = 1; i <= size; i++) {
//        cerr << "(";
//        cerr << heap[i]->priority << ", " << heap[i]->description << " ";
//        cerr << ")";
//
//    }
//    cerr << ']';
//    cerr << endl;
}

// PURPOSE: Returns the max element of the priority queue without removing it
// if the priority queue is empty, it returns (-1, "N/A")
PriorityQueue::TaskItem PriorityQueue::max() const {
    if (get_size() == 0) {
        return TaskItem(-1, "N/A");
    } else {
        /*
         * since it is a priority max queue we can
         * simply return the first value in the heap array
         * */
        return *heap[1];
    }
}

// PURPOSE: Inserts the given value into the priority queue
// re-arranges the elements back into a heap
// returns true if successful and false otherwise
// priority queue does not change in capacity
bool PriorityQueue::enqueue(TaskItem val) {
    if (size >= capacity) {
        return false;
    }
    if (size == 0) {
        heap[1] = new TaskItem(val);
    } else {
        int i = size + 1; // sets i to the index after the last node
        heap[i] = new TaskItem(val); // inserts val at last index
        // while i is greater than one, and that the parent is less than the current i - basically start at the bottom of the heap and work your way up
        while (i > 1 && heap[i / 2]->priority < heap[i]->priority) {
            TaskItem *temp = heap[i];
            heap[i] = heap[i / 2];
            heap[i / 2] = temp;
            i /= 2;
        }
    }
    size++;
    return true;
}

// PURPOSE: Removes the top element with the maximum priority
// re-arranges the remaining elements back into a heap
// returns true if successful and false otherwise
// priority queue does not change in capacity
bool PriorityQueue::dequeue() {
    if (size == 0) {
        cerr << "Nothing to dequeue, tree empty." << endl;
        return false;
    }
    if (size == 1) {
        TaskItem *temp = heap[1];
        delete temp;
        heap[1] = nullptr;
        size--;
        return true;
    } else {
        // sets bottom right leaf to temp and swaps
        TaskItem *temp = heap[size];
        heap[size] = heap[1];
        heap[1] = temp;
        //deletes heap at size (which was the root)
        delete heap[size];
        heap[size] = nullptr;
        int i = 1;
        size--;
        // iterates through tree to reorganize
        while (i < size - 1) { // iterates down the tree from the top node
            TaskItem *rightChild = heap[i * 2 + 1];
            TaskItem *leftChild = heap[i * 2];
            // iterates down the higher size to reorder
            if (leftChild->priority < rightChild->priority) {
                // switches the heap at i with the greater child
                heap[i * 2 + 1] = heap[i];
                heap[i] = rightChild;
                // sets i to be the right child
                i = i * 2 + 1;
            } else {
                heap[i * 2] = heap[i];
                heap[i] = leftChild;
                i = i * 2;
            }
            return true;
        }
    }
}
