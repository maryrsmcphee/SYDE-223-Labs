#include <iostream>
#include <cassert>
#include <vector>

using namespace std;

class Polynomial {
    vector<int> data;

    Polynomial(int A[], int size){
        data.resize(size);
    }

    Polynomial(){

    }

    Polynomial(string fileName){

    }

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
