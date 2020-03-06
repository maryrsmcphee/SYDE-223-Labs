#include "lab3_priority_queue.hpp"

using namespace std;

// PURPOSE: Parametric constructor
// initializes heap to an array of (n_capacity + 1) elements
PriorityQueue::PriorityQueue(unsigned int n_capacity) {
}

// PURPOSE: Explicit destructor of the class PriorityQueue
PriorityQueue::~PriorityQueue() {
}

// PURPOSE: Returns the number of elements in the priority queue
unsigned int PriorityQueue::get_size() const {
    return 0;
}

// PURPOSE: Returns true if the priority queue is empty; false, otherwise
bool PriorityQueue::empty() const {
    return false;
}

// PURPOSE: Returns true if the priority queue is full; false, otherwise
bool PriorityQueue::full() const {
    return false;
}

// PURPOSE: Prints the contents of the priority queue; format not specified
void PriorityQueue::print() const {
}

// PURPOSE: Returns the max element of the priority queue without removing it
// if the priority queue is empty, it returns (-1, "N/A")
PriorityQueue::TaskItem PriorityQueue::max() const {
    return TaskItem(-1, "NULL");
}

// PURPOSE: Inserts the given value into the priority queue
// re-arranges the elements back into a heap
// returns true if successful and false otherwise
// priority queue does not change in capacity
bool PriorityQueue::enqueue( TaskItem val ) {
    return false;
}

// PURPOSE: Removes the top element with the maximum priority
// re-arranges the remaining elements back into a heap
// returns true if successful and false otherwise
// priority queue does not change in capacity
bool PriorityQueue::dequeue() {
    return false;
}
