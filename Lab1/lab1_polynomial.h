//
// Created by Mary McPhee on 2020-01-16.
//

#ifndef LAB1_LAB1_POLYNOMIAL_H
#define LAB1_LAB1_POLYNOMIAL_H

#endif //LAB1_LAB1_POLYNOMIAL_H

using namespace std;

class Polynomial{
private:
    vector<int> data;

public:
    Polynomial(int input[], int size);
    Polynomial();
    Polynomial(string fileName);
    ~Polynomial();
    vector<int> get_data();
    bool operator==(const Polynomial &target);
    void print();

    Polynomial operator+(const Polynomial &target);
    Polynomial operator-(const Polynomial &target);
    Polynomial operator*(const Polynomial &target);
    Polynomial derivative();
};

class PolynomialTest{
public:
    friend class Polynomial;

    void setup();
    void cleanup();
    bool testPolynomialFileReadIn();
    bool testPolynomialCreation();
    bool testPolynomialRandomOutput();
    void run();
};