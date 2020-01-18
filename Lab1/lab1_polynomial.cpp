#include <iostream>
#include <cassert>
#include <vector>
#include <string>
#include <fstream>
#include "lab1_polynomial.h"
#include <random>

using namespace std;
// constants
const string creatingPolynomialVector = "Creating polynomial vector... \n";
// constants / error messages
const string unableToReadFileERROR = "ERROR: Unable to read from file. Check that the file is in the root directory and that it has the correct file extension (.*txt). \n";

/**
 * Class Polynomial
 */
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
    Polynomial(int input[], int size) {
        data.resize(size);
        cout << creatingPolynomialVector;
        for (int i = 0; i < size; i++) {
            data.push_back(input[i]);
        }
    }

    /**
     * Generates a random polynomial of a random degree and then passes
     * it to the polynomial constructor
     */
    Polynomial() {
        default_random_engine generator;
        uniform_int_distribution<int> distribution(0, 1000);
        int generatedRandomNumberOfTerms = distribution(generator);
        vector<int> randomGeneratedCoefficients;
        const int numberOfTerms = ++generatedRandomNumberOfTerms;
        for (int i = 0; i < numberOfTerms; i++) {
            default_random_engine generatorCoefficients;
            uniform_int_distribution<int> distributionCoefficients(-1000, 1000);
            int generatedRandomNumberOfCoefficients = distributionCoefficients(generatorCoefficients);
            randomGeneratedCoefficients.push_back(generatedRandomNumberOfCoefficients);
        }
        /*
         * Setting vector to  array
         * we can do this by pointing an array to the location in memory
         * of the first element of the vector since both arrays and vectors
         * store their elements sequentially in memory
         * */
        int *coefficientArr = &randomGeneratedCoefficients[0];
        int coefficientArrSize = randomGeneratedCoefficients.size();
        Polynomial randomPolynomial(coefficientArr,coefficientArrSize);
    }

    /**
     * Polynomial class constructor
     * takes filename and extracts text from file.
     * @param {string} fileName
     */
    Polynomial(string fileName) {
        string filePath = "./" + fileName;
        ifstream inFile(fileName);
        if (!inFile) {
            cout << unableToReadFileERROR;;
        }
        string lineReading;
        vector<string> valuesFromFile;
        while (getline(inFile, lineReading)) {
            valuesFromFile.push_back(lineReading);
            for (unsigned i = 0; i < valuesFromFile.size(); i++) {
                cout << valuesFromFile[i];

            }
            cout << "\n";
        }
        // TODO cast to ints form string and pass to second constructor
    }

    /**
     * default class destructor
     */
    ~Polynomial() {
    }

    // performs *this == target
    /**
     * @param {Polynomial} target
     * @return bool
     */
    bool operator==(const Polynomial &target){
        bool equals = true;
        int i = 0;
        while(equals == true && i <= target.data.size()) {
            if (target.data[i] == this->data[i]) {
                i++;
            } else {
                equals = false;
            }
        }
        return equals;
    };

    // prints the polynomial
    void print(){
        for(int i = 0; i <= data.size(); i++){
            cout << data[i] << " x ^" << i ;
        }
    };

    // performs *this + target
    /**
     *
     * @param target
     * @return Polynomial of addedPolys
     */
    Polynomial operator+(const Polynomial &target){
        int addedPolys[target.data.size()];
        for(int i = 0; i <= target.data.size(); i++){
            addedPolys[i] = target.data[i] + this->data[i];
        }
        return Polynomial(addedPolys, target.data.size());
    };

    // performs *this - target
    /**
     *
     * @param target
     * @return Polynomial of subtractedPolys
     */
    Polynomial operator-(const Polynomial& target){
        int subtractedPolys[target.data.size()];
        for(int i = 0; i <= target.data.size(); i++){
            subtractedPolys[i] = this->data[i] - target.data[i];
        }
        return Polynomial(subtractedPolys, target.data.size());
    };

    // performs *this * target
    /**
     *
     * @param target
     * @return Polynomial of multipliedPolys
     */
    Polynomial operator*(const Polynomial& target){
        int multipliedPolys[target.data.size()];
        for(int i = 0; i <= target.data.size(); i++){
            multipliedPolys[i] = this->data[i] * target.data[i];
        }
        return Polynomial(multipliedPolys, target.data.size());
    };

    // computes the derivative d/dx of *this
    /**
     * computes derivative of poly
     * returns new Polynomial of derivedPoly
     */
    Polynomial derivative(){
        int derivedPoly[data.size() - 1];
        for(int i = 0; i < data.size() - 1; i++){
            derivedPoly[i] = data[i+1] * [i+1];
        }
        return Polynomial(derivedPoly, data.size() - 1);
    };
};

class PolynomialTest {
public:
    bool test_constructors1() {
        return true;
    }

    void run() {
        if (test_constructors1()) {
            cout << "Test Constructors1 Passed" << endl;
        } else {
            cout << "Test Constructors1 Failed" << endl;
        }
    }
};

int main() {
    PolynomialTest my_test;
    my_test.run();
    Polynomial test("test.txt");

    return 0;
}
