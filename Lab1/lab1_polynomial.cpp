/*******************************
 * @author Sammy Robens-Paradise
 * @author Mary McPhee
 * @date Sunday Jan 26, 2020
 * @IDE: CLion, macOS
 * @SYDE_223: Lab 1
 ******************************/


#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "lab1_polynomial.h"
#include <stdexcept>
#include <stdlib.h>
#include <time.h>

#define ASSERT_TRUE(T) if (!(T)) return false;
#define ASSERT_FALSE(T) if ((T)) return false;

using namespace std;
// constants
const string pullingArrayFromFile = "Pulling Array from file... \n";
//globals
bool GLOBAL_NEGATIVE_VALUE_ERROR = false;

/**
 * Polynomial class constructor
 * expecting:
 * @param {int array} input
 * @param {int} size
 */
Polynomial::Polynomial(int input[], int size) {
    for (int i = 0; i < size; i++) {
        data.push_back(input[i]);
    }
    data.resize(size);
}

/**
 * Generates a random polynomial of a random degree and then passes
 * it to the polynomial constructor
 */
Polynomial::Polynomial() {
    int generatedRandomNumberOfTerms = rand() % 1001;
    vector<int> randomGeneratedCoefficients;
    const int numberOfTerms = ++generatedRandomNumberOfTerms;
    for (int i = 0; i < numberOfTerms; i++) {
        int generatedRandomNumberOfCoefficients = (rand() % 1001) - rand() % 1001;
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
    for (int i = 0; i < coefficientArrSize; i++) {
        data.push_back(coefficientArr[i]);
    }
    data.resize(coefficientArrSize);
}

/**
 * Polynomial class constructor
 * takes filename and extracts text from file.
 * @param {string} fileName
 */
Polynomial::Polynomial(string fileName) {
    string filePath = "./" + fileName;
    ifstream inFile(fileName);
    if (!inFile) {
        printf("⚠️ ERROR: Unable to read from file. Make sure it is in the build directory and is a *.txt file, at line: %d \n",
               __LINE__);
        printf("⚠️ WARNING: Falling back to un parameterized constructor , at line: %d \n", __LINE__);
        Polynomial fileFallback;
        throw invalid_argument("Unable to read from file in constructor");
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
        printf("⚠️ ERROR: cannot have more params then your power+1, at line %d \n", __LINE__);
        printf("⚠️ WARNING: Falling back to un parameterized constructor , at line: %d \n", __LINE__);
        Polynomial fallback;
        throw invalid_argument("Invalid Polynomial Configuration, reading from file");
    } else {
        for (int i = 0; i < sizeOfPoly; i++) {
            data.push_back(ArrOfCoefficients[i]);
        }
        data.resize(sizeOfPoly);
    }
}

/**
 * @destructor
 */
Polynomial::~Polynomial() {

};

/**
 * @performs *this == target
 * @param {Polynomial} target
 * @return bool
 */
bool Polynomial::operator==(const Polynomial &target) {
    bool equals = true;
    int i = 0;
    if (target.data.size() != data.size()) {
        equals = false;
    } else {
        while (equals && i < target.data.size()) {
            if (target.data[i] == this->data[i]) {
                i++;
            } else {
                equals = false;
            }
        }
    }
    return equals;
}

vector<int> Polynomial::get_data() {
    return data;
}

// prints the polynomial
void Polynomial::print() {
    string sign = " ";
    for (int i = data.size() - 1; i >= 0; i--) {
        while (data[i] == 0) {
            i--;
        }
        data[i] < 0 ? sign = " " : sign = "+ ";
        data[i] > 0 && i == data.size() - 1 ? sign = " " : sign = sign;
        switch (i) {
            case 0:
                cout << sign << data[i] << " ";
                break;
            case 1:
                cout << sign << data[i] << "x" << " ";
                break;
            default:
                cout << sign << data[i] << "x^" << i << " ";
                break;

        }
    }
    cout << endl;
};

// performs *this + target
/**
 *
 * @param target
 * @return Polynomial of addedPolys
 */
Polynomial Polynomial::operator+(const Polynomial &target) {
    Polynomial addedPolys;
    if(data.size() >= target.data.size()){
        addedPolys.data.resize(this->data.size());
    }else{
        addedPolys.data.resize(target.data.size());
    }

    for (int i = 0; i < addedPolys.data.size(); ++i) {
        if (i >= target.data.size()) {
            addedPolys.data[i] = data[i];
        } else if (i >= data.size()) {
            addedPolys.data[i] = target.data[i];
        } else {
            addedPolys.data[i] = data[i] + target.data[i];
        }
    }
    return addedPolys;
}

// performs *this - target
/**
 *
 * @param target
 * @return Polynomial of subtractedPolys
 */
Polynomial Polynomial::operator-(const Polynomial &target) {
    Polynomial subtractedPolys;
    if (target.data.size() >= this->data.size()) {
        subtractedPolys.data.resize(target.data.size());
    } else {
        subtractedPolys.data.resize(this->data.size());
    }
    for (int i = 0; i <= subtractedPolys.data.size(); i++) {
        if (i > target.data.size()) {
            subtractedPolys.data.push_back(this->data[i]);
        } else if (i > this->data.size()) {
            subtractedPolys.data.push_back(0 - target.data[i]);
        } else {
            subtractedPolys.data.push_back(this->data[i] - target.data[i]);
        }
    }
    return subtractedPolys;
};

// performs *this * target
/**
 *
 * @param target
 * @return Polynomial of multipliedPolys
 */
Polynomial Polynomial::operator*(const Polynomial &target) {
    // TODO check logic of this - math might be wrong?
    Polynomial multipliedPolys;
    if (target.data.size() >= this->data.size()) {
        multipliedPolys.data.resize(target.data.size());
    } else {
        multipliedPolys.data.resize(this->data.size());
    }

    for (int i = 0; i <= data.size(); i++) {
        for (int j = 0; j <= target.data.size(); j++) {
            multipliedPolys.data[i + j] = multipliedPolys.data[i + j] + this->data[i] * target.data[i];
        }
    }
    return multipliedPolys;
}

// computes the derivative d/dx of *this
/**
 * @computes derivative of poly
 * @return new Polynomial of derivedPoly
 */
Polynomial Polynomial::derivative() {
    int derivedPoly[data.size() - 1];
    for (int i = 0; i < data.size() - 1; i++) {
        derivedPoly[i] = data[i + 1] * (i + 1);
    }
    return Polynomial(derivedPoly, data.size() - 1);
};


void PolynomialTest::setup() {
    int polyArray1[] = {1, 2, 3, 4, 5};
    PolynomialInstance1 = Polynomial(polyArray1, 5);
    int polyArray2[] = {1, 2, 3, 4, 5};
    PolynomialInstance2 = Polynomial(polyArray2, 5);
    int polyArray3[] = {5, 4, 3, 2, 1};
    PolynomialInstance3 = Polynomial(polyArray3, 5);
    int polyArray4[] = {7, 6, 5, 4, 3, 2, 1};
    PolynomialInstance4 = Polynomial(polyArray4, 7);
    int polyArray5[] = {1, 2, 3, 4, 5, 6, 7};
    PolynomialInstance5 = Polynomial(polyArray5, 7);
    // Instances 2 and 3 added together
    int polyArray7[] = {6, 6, 6, 6, 6, 6};
    PolynomialInstance7 = Polynomial(polyArray7, 5);
    // Instances 3 and 4 added together
    int polyArray8[] = {12, 10, 8, 6, 4, 2, 1};
    PolynomialInstance8 = Polynomial(polyArray8, 7);
};

void PolynomialTest::cleanup() {

};

/**
 * Test function looking at file read-in
 * in class constructor
 * @return {bool}
 */
bool PolynomialTest::testPolynomialFileReadIn() {
    string fileThatExists = "test.txt";
    string fileThatDoesNotExist = "error.txt";
    string invalidFile = "text-invalid.txt";
    string negativeValFile = "negative-invalid.txt";
    bool pass1 = true;
    bool pass2 = true;
    bool pass3 = true;
    bool pass4 = true;
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
    Polynomial testPolynomial4(negativeValFile);

    GLOBAL_NEGATIVE_VALUE_ERROR ? printf(
            "✅ TEST PASS: testPolynomialReadIn with invalid negative value, at line:  %d \n", __LINE__)
                                : printf(
            "❌ TEST FAIL: testPolynomialReadIn with invalid negative value, at line:  %d \n", __LINE__);
    // reset error code
    GLOBAL_NEGATIVE_VALUE_ERROR ? GLOBAL_NEGATIVE_VALUE_ERROR = false : GLOBAL_NEGATIVE_VALUE_ERROR = true;

    Polynomial testPolynomial5(fileThatExists);
    const int arrayFromTestTextSize = 5;
    const int arrayFromTestText[arrayFromTestTextSize] = {4, 7, 5, 6, 7};
    testPolynomial5.get_data().size() == arrayFromTestTextSize ? printf(
            "✅ TEST PASS: testPolynomialReadIn with correct vector size, at line:  %d \n", __LINE__)
                                                               : printf(
            "❌ TEST FAIL: testPolynomialReadIn with correct vector size, at line:  %d \n", __LINE__);
    for (int i = 0; i < testPolynomial5.get_data().size(); i++) {
        arrayFromTestText[i] != testPolynomial5.get_data()[i] ? pass4 = false : pass4 = true;
    }
    pass4 ? printf(
            "✅ TEST PASS: testPolynomialReadIn with correct vector elements, at line:  %d \n", __LINE__)
          : printf(
            "❌ TEST FAIL: testPolynomialReadIn with correct vector elements, at line:  %d \n", __LINE__);
    return true;
}

/**
 * test function testing the creation of a
 * polynomial object
 * @return {bool}
 */
bool PolynomialTest::testPolynomialCreation() {
    const int size = 10;
    bool pass4 = true;
    int testArr1[size] = {1, 2, 4, 5, 6, 7, 7, 8, 8, 9};
    vector<int> testVec1 = {1, 2, 4, 5, 6, 7, 7, 8, 8, 9};
    Polynomial testPolynomialCreation(testArr1, size);
    vector<int> retrievedData = testPolynomialCreation.get_data();
    retrievedData.resize(size);
    testVec1.resize(size);
    try {
        for (int i = 0; i < retrievedData.size(); i++) {
            if (!(retrievedData[i] == testVec1[i])) {
                throw bad_function_call();
            }
        }
    }
    catch (bad_function_call &e) {
        cerr << e.what() << endl;
        pass4 = false;
    }
    pass4 ? printf(
            "✅ TEST PASS: testPolynomialCreation Polynomial constructor with valid comparison, at line:  %d \n",
            __LINE__)
          : printf(
            "❌ TEST FAIL: testPolynomialReadIn Polynomial constructor with invalid comparison, at line:  %d \n",
            __LINE__);
    return true;
}

/**
 * tests the default constructor generation of random output
 * polynomial
 * @return {bool}
 */
bool PolynomialTest::testPolynomialRandomOutput() {
    cout << "running testPolynomialRandomOutput constructor... \n";
    const int MAX_RANGE = 1000;
    const int MIN_RANGE = -1000;
    bool pass1 = true;
    bool pass2;
    PolynomialInstance6 = Polynomial();
    PolynomialInstance6.get_data().size() > 0 ? pass2 = true : pass2 = false;
    for (int i = 0; i < PolynomialInstance6.get_data().size(); i++) {
        int el = PolynomialInstance6.get_data()[i];
        !(el > MAX_RANGE || el < MIN_RANGE) ? pass1 = true : pass1 = false;
    }
    pass1 ? printf(
            "✅ TEST PASS: testPolynomialRandomOutput Polynomial constructor , at line:  %d \n", __LINE__)
          : printf(
            "❌ TEST FAIL: testPolynomialRandomOutput Polynomial constructor , at line  %d \n", __LINE__);
    pass2 ? printf(
            "✅ TEST PASS: testPolynomialRandomOutput Polynomial constructor size greater than 0, at line:  %d \n",
            __LINE__)
          : printf(
            "❌ TEST FAIL: testPolynomialRandomOutput Polynomial constructor size greater than 0 , at line  %d \n",
            __LINE__);
    cout << endl;
    return true;
}

/**
 * test the overloaded equivalence operatior
 * @return {bool}
 */
bool PolynomialTest::testEquivalence() {
    cout << "Running testEquivalence... \n";
    ASSERT_TRUE(PolynomialInstance1 == PolynomialInstance2);
    printf("Passed comparison of equal objects\n");
    ASSERT_FALSE(PolynomialInstance1 == PolynomialInstance3);
    printf("Passed comparison of unequal objects of the same size\n");
    ASSERT_FALSE(PolynomialInstance1 == PolynomialInstance5);
    printf("Passed comparison of unequal objects of different sizes\n");
    return true;
}

bool PolynomialTest::testPrint() {
    cout << "Running test print... \n";
    cout
            << "This section of the test running requires manual inspection. Please complete the following instructions... \n";
    const string msg = "❗ Does the following output match the expected output? (y/n)❗ \n = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =y \n";
    const string o = " >>> Expected:  \n";
    const string r = "\n >>> Received:  \n";
    const int size1 = 5;
    int testArr1[size1] = {3, 4, 0, -4, 9};
    const string expectedOutput1 = " 9x^4  -4x^3 + 4x + 3";
    Polynomial testPrintPoly1(testArr1, size1);
    cout << msg;
    cout << o;
    cout << expectedOutput1;
    cout << r;
    testPrintPoly1.print();
    string decision;
    cin >> decision;
    (decision == "y") ? printf("✅ TEST PASS: correct print output, at line:  %d \n", __LINE__) :
    printf("❌ TEST FAIL: incorrect print output,  at line:  %d \n", __LINE__);
}

bool PolynomialTest::testAddition(){
    if(PolynomialInstance2 + PolynomialInstance3 == PolynomialInstance7){
        cout << "✅ TEST PASS: testAddition adds two polynomials of the same size correctly \n";
    } else {
        cout << "❌ TEST FAIL: testAddition does not add two polynomials of the same size correctly\n";
    }

    if(PolynomialInstance1 + PolynomialInstance2 == PolynomialInstance3){
        cout << "TEST FAIL: testAddition should return false\n";
    } else {
        cout << "✅ TEST PASS: testAddition returns false when false\n";
    }

    if(PolynomialInstance3 + PolynomialInstance4 == PolynomialInstance8){
        cout << "✅ TEST PASS: testAddition adds two polynomials of different sizes correctly \n";
    } else {
        cout << "❌ TEST FAIL: testAddition adds two polynomials of different sizes incorrectly \n";
    }
    return true;
}

/**
 * @driver run
 * @void
 *
 */
void PolynomialTest::run() {
    cout << "Starting Test Runner... \n";
    setup();
    cout << "\n ------------------------------------\n";
    testPolynomialFileReadIn();
    cout << "\n ------------------------------------\n";
    testPolynomialCreation();
    cout << "\n ------------------------------------\n";
    testPolynomialRandomOutput();
    cout << "\n ------------------------------------\n";
    testEquivalence() ? printf("✅ TEST PASS: testEquivalence, at line:  %d \n", __LINE__) : printf(
            "❌ TEST FAIL: testEquivalence, at line:  %d \n", __LINE__);
    cout << "\n ------------------------------------\n";
    testPrint();
    cout << "\n ------------------------------------\n";
    testAddition();
    cout << "\n ------------------------------------\n";
    cleanup();
    cout<<"Test Runner Complete ♥️️ \n";
}

/**
 * Main function
 * @return int
 */
int main() {
    // seed random time...
    srand(time(0));
    // create test object
    PolynomialTest my_test;
    my_test.run();


    return 0;
}
