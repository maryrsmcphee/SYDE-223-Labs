/*******************************
 * @author Sammy Robens-Paradise, 20709541
 * @author Mary McPhee, 20717047
 * @date Sunday Jan 26, 2020
 * @IDE: CLion, macOS
 * @SYDE_223: Lab 1
 ******************************/

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
    /**
     *
     * @param {Polynomial} target
     * @return
     */
    bool operator==(const Polynomial &target);
    /**
     * @void
     */
    void print();
    /**
     *
     * @param {Polynomial} target
     * @return
     */
    Polynomial operator+(const Polynomial &target);
    /**
     *
     * @param {Polynomial} target
     * @return
     */
    Polynomial operator-(const Polynomial &target);
    /**
     *
     * @param {Polynomial} target
     * @return
     */
    Polynomial operator*(const Polynomial &target);
    /**
     *
     * @return
     */
    Polynomial derivative();
};
/**
 * @class PolynomialTest
 * @driver {test}
 */
class PolynomialTest{
    Polynomial PolynomialInstance1;
    Polynomial PolynomialInstance2;
    Polynomial PolynomialInstance3;
    Polynomial PolynomialInstance4;
    Polynomial PolynomialInstance5;
    Polynomial PolynomialInstance6;
    Polynomial PolynomialInstance7;
    Polynomial PolynomialInstance8;
    Polynomial PolynomialInstance9;
    Polynomial PolynomialInstance10;
    Polynomial PolynomialInstance11;
    Polynomial PolynomialInstance12;
    Polynomial PolynomialInstance13;
    Polynomial PolynomialInstance14;
    Polynomial PolynomialInstance15;
    Polynomial PolynomialInstance16;
public:
    friend class Polynomial;

    void setup();
    void cleanup();
    bool testPolynomialFileReadIn();
    bool testPolynomialCreation();
    bool testPolynomialRandomOutput();
    bool testEquivalence();
    bool testPrint();
    bool testAddition();
    bool testSubtraction();
    bool testMultiplication();
    bool testDerivative();
    void run();
};
