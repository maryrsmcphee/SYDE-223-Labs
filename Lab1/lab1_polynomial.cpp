/*******************************
 * @author Sammy Robens-Paradise
 * @author Mary McPhee
 * @date Sunday Jan 20, 2020
 * @IDE: CLion, macOS
 * @SYDE_223: Lab 1
 ******************************/


#include <iostream>
#include <cassert>
#include <vector>
#include <string>
#include <fstream>
#include "lab1_polynomial.h"
#include <random>
#include <cmath>
#include <stdexcept>
#include <limits>

#define ASSERT_TRUE(T) if (!(T)) return false;
#define ASSERT_FALSE(T) if ((T)) return false;

using namespace std;
// constants
const string creatingPolynomialVector = "Creating polynomial vector... \n";
const string pullingArrayFromFile = "Pulling Array from file... \n";
//globals
bool GLOBAL_NEGATIVE_VALUE_ERROR = false;
// constants / error messages

// sorting helpers
/**
 * void
 * @param arrToSort
 * @param size
 */
void insertSortLeastToGreatest(int *arrToSort, int size) {
    int j, k;
    // for each el in array...
    for (int i = 0; i < size; i++) {
        // get the value at the i'th el...
        k = arrToSort[i];
        // store the i'th -1 index > 0...
        j = i - 1;
        /*
         * while the i'th -1 element is greater then  0
         * and the i'th -1 element is greater then k
         * */
        while (j >= 0 && arrToSort[j] > k) {
            arrToSort[j + 1] = arrToSort[j];
            j--;
        }
        arrToSort[j + 1] = k;
    }

}

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
        insertSortLeastToGreatest(input, size);
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
        Polynomial randomPolynomial(coefficientArr, coefficientArrSize);
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
            printf("❌ ERROR: Unable to read from file. Make sure it is in the build directory and is a *.txt file, at line: %d \n",
                   __LINE__);
            printf("⚠️ WARNING: Falling back to un parameterized constructor , at line: %d \n", __LINE__);
            Polynomial fileFallback;
            throw invalid_argument("Unable to read from file");
        }
        cout << pullingArrayFromFile << "\n";
        string lineReading;
        vector<int> valuesFromFile;
        int noc = -1;
        while (getline(inFile, lineReading)) {
            valuesFromFile.push_back(stoi(lineReading));
            noc++;
        }
        // store the first element of the vector as size
        if (valuesFromFile[0] < 0) {
            printf("⚠️ WARNING: Your power is less then 0. This is not allowed. The absolute value of the power will be used, at line:  %d \n",
                   __LINE__);
            GLOBAL_NEGATIVE_VALUE_ERROR = true;
        }

        int sizeOfPoly = abs(valuesFromFile[0]);

        // set array to the rest of the vector, which are the coefficients
        int *ArrOfCoefficients = &valuesFromFile[1];
        // check for errors before passing to constructor
        bool isInvalidSize = noc > sizeOfPoly + 1;
        bool hasSizeLessThanOrZero = sizeOfPoly <= 0;
        if (isInvalidSize || hasSizeLessThanOrZero) {
            printf("❌ ERROR: cannot have more params then your power+1, at line %d \n", __LINE__);
            printf("⚠️ WARNING: Falling back to un parameterized constructor , at line: %d \n", __LINE__);
            Polynomial fallback;
            throw invalid_argument("Invalid Polynomial Configuration");
        } else {
            Polynomial readFromFilePoly(ArrOfCoefficients, sizeOfPoly);
        }
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
    bool operator==(const Polynomial &target) {
        bool equals = true;
        int i = 0;
        while (equals == true && i <= target.data.size()) {
            if (target.data[i] == this->data[i]) {
                i++;
            } else {
                equals = false;
            }
        }
        return equals;
    };

    // prints the polynomial
    void print() {
        for (int i = 0; i <= data.size(); i++) {
            cout << data[i] << " x ^" << i;
        }
    };

    // performs *this + target
    /**
     *
     * @param target
     * @return Polynomial of addedPolys
     */
    Polynomial operator+(const Polynomial &target) {
        int addedPolys[target.data.size()];
        for (int i = 0; i <= target.data.size(); i++) {
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
    Polynomial operator-(const Polynomial &target) {
        int subtractedPolys[target.data.size()];
        for (int i = 0; i <= target.data.size(); i++) {
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
    Polynomial operator*(const Polynomial &target) {
        int multipliedPolys[target.data.size()];
        for (int i = 0; i <= target.data.size(); i++) {
            multipliedPolys[i] = this->data[i] * target.data[i];
        }
        return Polynomial(multipliedPolys, target.data.size());
    };

    // computes the derivative d/dx of *this
    /**
     * computes derivative of poly
     * returns new Polynomial of derivedPoly
     */
    Polynomial derivative() {
        int derivedPoly[data.size() - 1];
        for (int i = 0; i < data.size() - 1; i++) {
            // TODO take another look at this? -- should be ok, was a syntax error fixed in deleted PR
            derivedPoly[i] = data[i + 1] * (i + 1);
        }
        return Polynomial(derivedPoly, data.size() - 1);
    };
};

class PolynomialTest {
    friend class Polynomial;

public:

    void setup() {

    };

    void cleanup() {

    };

    bool testInsertionSort() {
        // 1
        const int size = 10;
        int simpleArray[size] = {1, 6, 7, 9, 4, 7, 5, 1, 8, 4};
        int simpleArrayControl[size] = {1, 1, 4, 4, 5, 6, 7, 7, 8, 9};
        insertSortLeastToGreatest(simpleArray, size);
        bool detector = true;
        for (int i = 0; i < size; i++) {
            simpleArray[i] == simpleArrayControl[i] ? detector = true : detector = false;
        }
        if (!detector) {
            printf("❌ FAIL: insertSortLeastToGreatest  with simple array, at line:  %d \n", __LINE__);
        }
        ASSERT_TRUE(detector);
        printf("✅ PASS: insertSortLeastToGreatest  with simple array, at line:  %d \n", __LINE__);
        // 2
        int simpleNegativeArray[size] = {1, 6, 7, 9, 4, 7, 5, 1, 8, -4};
        int simpleNegativeArrayControl[size] = {-4, 1, 1, 4, 5, 6, 7, 7, 8, 9};
        insertSortLeastToGreatest(simpleNegativeArray, size);
        bool detector2 = true;
        for (int i = 0; i < size; i++) {
            simpleNegativeArray[i] == simpleNegativeArrayControl[i] ? detector2 = true : detector2 = false;
        }
        if (!detector2) {
            printf("❌ TEST FAIL: insertSortLeastToGreatest  with simple array with negative value, at line:  %d \n",
                   __LINE__);
        }
        ASSERT_TRUE(detector2);
        printf("✅ TEST PASS: insertSortLeastToGreatest  with simple array with negative value, at line:  %d \n",
               __LINE__);
        // 3
        const int zeroSize = 1;
        int zeroArray[zeroSize] = {0};
        int zeroArrayControl[zeroSize] = {0};
        insertSortLeastToGreatest(zeroArray, zeroSize);
        bool detector3;
        zeroArray[0] == zeroArrayControl[0] ? detector3 = true : detector3 = false;
        if (!detector3) {
            printf("❌ TEST FAIL: insertSortLeastToGreatest 0 array, at line:  %d \n", __LINE__);
        }
        ASSERT_TRUE(detector3);
        printf("✅ TEST PASS: insertSortLeastToGreatest 0 array, at line:  %d \n", __LINE__);
        return true;
    }

    void testPolynomialFileReadIn() {
        string fileThatExists = "test.txt";
        string fileThatDoesNotExist = "error.txt";
        string invalidFile = "text-invalid.txt";
        bool pass1 = true;
        bool pass2 = true;
        bool pass3 = true;
        try {
            Polynomial testPolynomial(fileThatExists);
        }
        catch (invalid_argument &e) {
            cerr << e.what() << endl;
            pass1 = false;
        }
        pass1 ? printf("✅ TEST PASS: testPolynomialReadIn with expected file, at line:  %d \n", __LINE__)
              : printf("❌ TEST FAIL: testPolynomialReadIn with expected file, at line:  %d \n", __LINE__);

        try {
            Polynomial testPolynomial2(fileThatDoesNotExist);
        }
        catch (invalid_argument &e) {
            cerr << e.what() << endl;
            pass2 = false;
        }
        !pass2 ? printf("✅ TEST PASS: testPolynomialReadIn with unexpected file, at line:  %d \n", __LINE__)
               : printf("❌ TEST FAIL: testPolynomialReadIn with unexpected file, at line:  %d \n", __LINE__);

        try {
            Polynomial testPolynomial3(invalidFile);
        }
        catch (invalid_argument &e) {
            cerr << e.what() << endl;
            pass3 = false;
        }
        !pass3 ? printf("✅ TEST PASS: testPolynomialReadIn with invalid file, at line:  %d \n", __LINE__)
               : printf("❌ TEST FAIL: testPolynomialReadIn with invalid file, at line:  %d \n", __LINE__);
    }

    void run() {
        cout << "Starting Test Runner... \n";
        setup();
        cout << "\n ------------------------------------\n";
        testInsertionSort();
        cout << "\n ------------------------------------\n";
        testPolynomialFileReadIn();
        cleanup();
    }
};

/**
 * Main function
 * @return int
 */
int main() {
    PolynomialTest my_test;
    my_test.run();
    cout << __LINE__ << endl;
    return 0;
}
