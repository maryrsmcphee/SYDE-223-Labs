# SYDE-223-Labs Winter 2020
## Contributors: 
### Mary McPhee
### Sammy Robens-Paradise 

## Description
This repository contains the code for the SYDE 223 Data Structure and Algorithms Course for the Winter 2020 semester.

## Structure
```
| SYDE-223-Labs
    | Lab1
    | Lab2
    | Lab3
```
# Lab Assignment 1

# Topic: Use List ADT in Software Design

```
 For this assignment, you must work in pairs.
 Include the name and ID for each group member in your files.
```
# For C/C++ implementation, you must separate class header and class implementation.

#  Please submit your completed assignment before the dropbox closes on LEARN.

# Polynomial Representation as an ADT

Let us implement the mathematical concept of a polynomial as an ADT using sequential list ADT as a template.

For C/C++ implementation, store your class definition as lab1_polynomial.hpp and your class
implementation as lab1_polynomial.cpp. Also, include main() inside the .cpp file for testing.

# Step1.

Create a class called **Polynomial** that will store coefficients of a polynomial expression as integers in an array.

As internal storage, you may use the <vector> library or a dynamically-sized integer array. To initialize a
dynamic array, use int* data = new int[size]. To delete the array, use delete [] data. You must
not use the <list> library from the Standard Template Library (STL).

Sample starter code for the <vector> and dynamically-sized integer array options, respectively:

```
class Polynomial {
vector<int> data;
// size already stored inside vector
Polynomial(int A[], int size) {
data.resize(size);
...
}
~Polynomial() {
// data will be deleted on its own
}
```
```
class Polynomial {
int* data;
int data_size;
Polynomial(int A[], int size) {
data = new int[size];
...
}
~Polynomial() {
delete [] data;
}
```
The coefficients should be stored in increasing order of exponents, from smallest (e.g., data[0] location) to
largest (e.g., data[size-1] location). You should store both positive and negative coefficients, but only handle
non-negative exponents. Coefficients that are 0 should also be stored.

For example, the polynomial 5x^5 + 3x^4 + (-2)x^3 + 1x^0 should be stored as an array
{1, 0, 0, -2, 3, 5}**.**


Polynomial(int A[], int size);

Implement a class constructor that takes as input two parameters: an array of integers, int A[], and the size
of the array, int size. The inputted array contains all the polynomial coefficients. The constructor creates the
matching Polynomial instance and populates an internal array with inputted values. See the above sample
starter code for details.

Polynomial();

Implement a special class constructor that takes no inputs and generates a polynomial of random size with
random coefficients. The constructor creates the matching Polynomial instance and populates an internal
array with randomly-generated values. The degree of the polynomial should range from 0 to 1000.
The coefficient should range from -1000 to 1000. To generate a random value between 0 and 1000, use rand()
% 1001. Also, call srand(time(0)) when appropriate to randomize the seed for random values. Alternatively,
you may use the <random> library from C++11.

Polynomial(string fileName);

Implement a class constructor that takes as input one parameter: name of the file in which polynomial
coefficient are stored, string fileName. Inside the file, the first line contains the polynomial size while other
lines contain polynomial coefficients, with one coefficient stored per line. The constructor creates the matching
Polynomial instance and populates an internal array with inputted values.

~Polynomial(); // destructor that performs cleanup if needed

# Step2.

bool operator==(const Polynomial& target); // performs *this == target

void print(); // prints the polynomial (e.g., 2x^3 + 1x^0)

Polynomial operator+(const Polynomial& target); // performs *this + target

Polynomial operator-(const Polynomial& target); // performs *this - target

Polynomial operator*(const Polynomial& target); // performs *this * target

Polynomial derivative(); // computes the derivative 풅풙풅 of *this


Implement the overloaded operators and functions defined above as member functions of the class.

For example, if p1 = 2x^3 + 1x^0 and second polynomial is p2 = 1x^4 + 2x^2 , then the result of p1 * p
should be **2x**^7 **+ 4x**^5 **+ x**^4 **+ 2x**^2 , which should be stored as **{0, 0, 2, 0, 1, 4, 0, 2}**.

# Step3.

Create a class called PolynomialTest and insert methods that test each Polynomial method implemented
in Step1 and Step2. Set PolynomialTest as friend of Polynomial, so you can access attributes directly.

Test regular operation along with boundary and special cases, such as empty polynomial, negative exponents,
and so on. Do not rely only on visual inspection. Instead, automate your tests as much as possible.

For example, to test if a constructor works correctly, individually compare the coefficients set inside the
Polynomial instance with the expected array of coefficients. Furthermore, once you have verified your
operator== implementation, you may use it to check the result of a specific operations such as addition.

If a test passed, print **“[TestName]** P **assed”** ; else, print **“[TestName]** F **ailed”**. You may also use
assertions from the <cassert> library or define your own assertion template.

Run all the included tests using a method called run() and invoke this method from your main() function.

```
class PolynomialTest {
public:
bool test_constructors1() {
...
return true;
}
...
```
```
void run() {
if (test_constructors1())
cout << "Test Constructors1 Passed" << endl;
else
cout << "Test Constructors1 Failed" << endl;
...
}
};
```
```
int main() {
PolynomialTest my_test;
my_test.run();
return 0;
}
```

# Lab Assignment # 2

# Topic: Linked List Data Structure and C++ Inheritance

 For this assignment, you must work in pairs or — exceptionally — in teams of three.

Include the name and ID for each group member in your files.

For C/C++ implementation, you must separate class header and class implementation. You may not

 use other languages for this assignment.


# Drone Fleet Management as an ADT

## Our company is in a possession of a small fleet of drones that we would like to make available to customers. We

## are tasked with programming a data structure for storage of drone records.

## Submit three files: lab2_drones_manager.cpp, lab2_drones_manager.hpp, and

## lab2_drones_manager_test.hpp. Do not modify the signatures for any of the functions listed below.

# Step 0. [see lab2_drones_manager.hpp]

## We are providing you with the implementation of the private DroneRecord class. Each drone is to be recorded

## as an instance of this class. Each record has a unique drone ID, which is stored as an unsigned integer. In addition,

## each DroneRecord also stores drone type, manufacturer, description, range, battery type, and year bought; range

## and year bought are to be stored as unsigned integers while others are to be stored as strings.

## We are also providing you with the declaration for the DronesManager class. This class will be used as a container

## to handle DroneRecord objects, and will be based on a doubly linked list implementation of List ADT.

## DronesManager includes relevant member attributes, and corresponding accessor and mutator functions.

## Finally, we are providing you with the declaration for the DronesManagerSorted that extends DronesManager ,

## and allows record storage in sorted ascending or descending order based on drone ID value.

# Step1. [see lab2_drones_manager.hpp]

## Implement all of the methods for the class DronesManager that are listed below.

# class DronesManager {...} [header already defined in lab2_drones_manager.hpp;

# provide your definitions in lab2_drones_manager.cpp]

## // EXPLICIT CONSTRUCTOR AND DESTRUCTOR

// PURPOSE: Creates a new empty DronesManager
DronesManager();


// PURPOSE: Destroys this instance and frees up all dynamically allocated memory
~DronesManager();
// PURPOSE: Comparison operator to compare two DroneRecord instances
friend bool operator==(const DronesManager::DroneRecord& lhs,
const DronesManager::DroneRecord& rhs);
// PURPOSE: Setup DronesManagerTest as friend so tests have access to private variables
friend class DronesManagerTest;

## // ACCESSORS

// PURPOSE: Returns the number of elements in the list
unsigned int get_size() const;
// PURPOSE: Checks if the list is empty; returns true if the list is empty, false otherwise
bool empty() const;
// PURPOSE: Returns the value at the given index in the list
// if index is invalid, returns last element; if the list is empty, returns DroneRecord(0)
DroneRecord select(unsigned int index) const;
// PURPOSE: Searches for the given value, and returns the index of this value if found
// if not found, returns the size of the list; if the list is empty, returns 0
unsigned int search(DroneRecord val) const;
// PURPOSE: Prints all the elements in the list to the console
void print() const;

## // MUTATORS

// PURPOSE: Inserts a value into the list at a given index; the list is not sorted
// if the index is invalid, insertion is rejected
bool insert(DroneRecord val, unsigned int index);
// PURPOSE: Inserts a value at the beginning of the list; the list is not sorted
bool insert_front(DroneRecord val);
// PURPOSE: Inserts a value at the end of the list; the list is not sorted
bool insert_back(DroneRecord val);
// PURPOSE: Deletes a value from the list at the given index
bool remove(unsigned int index);
// PURPOSE: Deletes a value from the beginning of the list
bool remove_front();
// PURPOSE: Deletes a value at the end of the list
bool remove_back();
// PURPOSE: Replaces value at the given index with the given value; the list is not sorted
// if the index is invalid, replacement is rejected
bool replace(unsigned int index, DroneRecord val);
// PURPOSE: Reverses the linked list
bool reverse_list();


# Step 2. [see lab2_drones_manager.hpp]

## Implement all of the methods for the class DronesManagerSorted that are listed below.

## class DronesManagerSorted : public DronesManager {...}

# [header in lab2_drones_manager.hpp;

# definition in lab2_drones_manager.cpp]

## // ACCESSORS

```
// PURPOSE: Returns true if the list is sorted in ascending (non-descending) order
bool is_sorted_asc() const;
// PURPOSE: Returns true if the list is sorted in descending (non-ascending) order
bool is_sorted_desc() const;
```
## // MUTATORS

```
// PURPOSE: Inserts a value so that the list remains sorted in ascending order
// if the list is not sorted in appropriate order, insertion is rejected
bool insert_sorted_asc(DroneRecord val);
// PURPOSE: Inserts a value so that the list remains sorted in descending order
// if the list is not sorted in appropriate order, insertion is rejected
bool insert_sorted_desc(DroneRecord val);
// PURPOSE: Sorts the list into ascending (non-descending) order
void sort_asc();
// PURPOSE: Sorts the list into descending (non-ascending) order
void sort_desc();
```
# Step 3. [see lab2_drones_manager_test.hpp]

 Implement all of the test case methods in the DronesManagerTest class that are listed below.

class DronesManagerTest {...}
[declared and implemented in lab2_drones_manager_test.hpp;

 test runner in lab 2 _main.cpp]

## // TEST CASES

// PURPOSE: New empty list is valid
bool test1();
// PURPOSE: insert_front() and insert_back() on zero-element list
bool test2();
// PURPOSE: select() and search() work properly
bool test3() ;


// PURPOSE: remove_front() and remove_back() on one-element list
bool test4();
// PURPOSE: replace() and reverse_list() work properly
bool test5();
// PURPOSE: insert_front() keeps moving elements forward
bool test6();
// PURPOSE: inserting at different positions in the list
bool test7();
// PURPOSE: try to remove too many elements, then add a few elements
bool test8();
// PURPOSE: lots of inserts and deletes, some of them invalid
bool test9();
// PURPOSE: inserts into an unsorted list, then sort the list
bool test10();
// PURPOSE: insert and remove into sorted manager in ascending order
bool test11();
// PURPOSE: insert and remove into sorted manager in descending order
bool test12();

# Lab Assignment #3  [Weight: ~6% of the Course Grade] 

Topic: Heap ADT and Binary Search Tree ADT Applications 

 For this assignment, you must work in pairs or — exceptionally — in teams of three.  

Include the name and ID for each group member in your files. 

For C/C++ implementation, you must separate class header and class implementation. You may not 

use other languages for this assignment to ensure adequate preparation for the final exam.

 Please submit your completed assignment before the dropbox closes on LEARN.

## Part1. Task Organizer using Heap ADT 

We are going to design a task organizer for management of daily personal tasks, and also for eventual sharing of tasks among different users.  


# Step0.  [see lab3_ priority_queue.hpp]

## Start by familiarizing yourself with the code in the provided header file.  

## Each task item will be recorded as an instance of  PriorityQueue::TaskItem class. Each record will 

## include item priority stored as an integer and item description stored as a string.  PriorityQueue  class will 

## be  used  as  a  container  to  handle  TaskItem objects.  PriorityQueue will  include  relevant  member 

## attributes and methods. The highest priority item will always be stored at the top. 

# Step1.  [see lab3_ priority_queue.cpp] 

## Implement all of the methods for the class  PriorityQueue  that are listed below. 

# class PriorityQueue {...} [header already defined in lab3_ priority_queue.hpp;  

#      provide your definitions in lab3_ priority_queue.cpp] 

## // CONSTRUCTOR AND DESTRUCTOR

// PURPOSE: Parametric constructor
// initializes heap to an array of (n_capacity + 1) elements
PriorityQueue(unsigned int n_capacity);
// PURPOSE: Explicit destructor of the class PriorityQueue
~PriorityQueue();


## // ACCESSORS

// PURPOSE: Returns the number of elements in the priority queue
unsigned int get_size() const;
// PURPOSE: Returns true if the priority queue is empty; false, otherwise
bool empty() const;
// PURPOSE: Returns true if the priority queue is full; false, otherwise
bool full() const;
// PURPOSE: Prints the contents of the priority queue; format not specified
void print() const;
// PURPOSE: Returns the max element of the priority queue without removing it
// if the priority queue is empty, it returns (‐1, "N/A")
TaskItem max() const;

## // MUTATORS

// PURPOSE: Inserts the given value into the priority queue
// re‐arranges the elements back into a heap
// returns true if successful and false otherwise
// priority queue does not change in capacity
bool enqueue(TaskItem val);
// PURPOSE: Removes the top element with the maximum priority
// re‐arranges the remaining elements back into a heap
// returns true if successful and false otherwise
// priority queue does not change in capacity
bool dequeue();

# Step2.  [see lab3_tests.cpp] 

## Ensure that your code passes all of the test case methods in  PriorityQueueTest listed below. 

# class PriorityQueueTest {...} [implemented in lab3_tests.cpp] 

## // TEST CASES

// PURPOSE: Tests if the new queue is valid
bool test1();
// PURPOSE: Tests enqueue of one item and then dequeue of that item
bool test2();
// PURPOSE: Tests enqueue too many
bool test3();
// PURPOSE: Tests enqueue too many then dequeue too many
bool test4();


# Part2. Task Organizer using Binary Search Tree ADT 

## For Part2, we are going to use Binary Search ADT to model and implement this prototype. Submit two files:  

## lab3_binary_search_tree.hpp and lab3_binary_search_tree.cpp . Do not modify the signatures 

## for any of the functions already implemented or listed below. 

# Step0.  [see lab3_binary_search_tree.hpp]

## Start by familiarizing yourself with the code in the provided header file.  

## Each task item will be recorded as an instance of a slightly modified  BinarySearchTree::TaskItem class. 

## Each record will include item priority stored as an integer and item description stored as a string along with 

## corresponding left and right pointers.  BinarySearchTree  class will be used as a container to handle 

## TaskItem objects.  BinarySearchTree  will also include relevant member attributes and methods. 

# Step1.  [see lab3_binary_search_tree. cpp] 

## Implement all of the methods for the class  BinarySearchTree  that are listed below. 

# class BinarySearchTree {...} [header already defined in lab3_binary_search_tree.hpp;  

#      provide your definitions in lab3_binary_search_tree.cpp] 

## // CONSTRUCTOR AND DESTRUCTOR

// PURPOSE: Default/empty constructor
BinarySearchTree();
// PURPOSE: Explicit destructor of the class BinarySearchTree
~BinarySearchTree();

## // ACCESSORS

// PURPOSE: Returns the number of nodes in the tree
unsigned int get_size() const;
// PURPOSE: Returns the maximum value of a node in the tree
// if the tree is empty, it returns (‐1, "N/A")
TaskItem max() const;
// PURPOSE: Returns the minimum value of a node in the tree
// if the tree is empty, it returns (‐1, "N/A")
TaskItem min() const;
// PURPOSE: Returns the tree height
unsigned int height() const;
// PURPOSE: Prints the contents of the tree; format not specified
void print() const;


// PURPOSE: Returns true if a node with the value val exists in the tree
// otherwise, returns false
bool exists(TaskItem val) const;

## // MUTATORS

// PURPOSE: Inserts the value val into the tree if it is unique
// returns true if successful; returns false if val already exists
bool insert(TaskItem val);
// PURPOSE: Removes the node with the value val from the tree
// returns true if successful; returns false otherwise
bool remove(TaskItem val);

# Step2.  [see lab3_tests.cpp] 

## Ensure that your code passes all of the test case methods in  BinarySearchTreeTest listed below. 

# class BinarySearchTreeTest{...} [implemented in lab3_tests.cpp] 

## // TEST CASES

// PURPOSE: Tests if the new tree is valid
bool test1();
// PURPOSE: Tests a tree with one node
bool test2();
// PURPOSE: Tests insert, remove, and size on linear list formation with three elements
bool test3();
// PURPOSE: Tests removal of a node with one child
bool test4();
// PURPOSE: Tests insert of multiple elements and remove till nothing remains
bool test5();
// PURPOSE: Tests removal of root node when both children of root have two children
bool test6();
// PURPOSE: Tests depth with many inserts and some removes
bool test7();
// PURPOSE: Tests lots of inserts and removes
bool test8();

