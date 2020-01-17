#include <iostream>
#include <cassert>
#include <vector>
#include <string>
using namespace std;
// constants
const string creatingPolynomialVector = "Creating polynomial vector... \n";

class Polynomial {
private:
    vector<int> data;
public:
    /**
     * Polynomial class constructor
     * expecting:
     * @param {int array} input
     * @param {int} size
     */
    Polynomial(int input[], int size){
        data.resize(size);
        cout<<creatingPolynomialVector;
        for(int i = 0; i < size; i++){
            data.push_back(input[i]);
        }

    }
    /**
     * default {empty} constructor
     */
    Polynomial() = default;

    Polynomial(string fileName){

    }
    /**
     * default class destructor
     */
    ~Polynomial() {
    }

    // performs *this == target
    bool operator==(const Polynomial& target);

    // prints the polynomial
    void print();

    // performs *this + target
    Polynomial operator+(const Polynomial& target);

    // performs *this - target
    Polynomial operator-(const Polynomial& target);

    // performs *this * target
    Polynomial operator*(const Polynomial& target);

    // computes the derivative d/dx of *this
    Polynomial derivative();
};

class PolynomialTest{
public:
    bool test_constructors1() {
        return true;
    }

    void run() {
        if (test_constructors1 ()) {
            cout << "Test Constructors1 Passed" << endl;
        } else {
            cout << "Test Constructors1 Failed" << endl;
        }
    }
};

int main() {
    PolynomialTest my_test;
    my_test.run();

    return 0;
}
