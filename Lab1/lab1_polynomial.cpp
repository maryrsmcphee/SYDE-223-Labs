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
#include <stdexcept>

#define ASSERT_TRUE(T) if (!(T)) return false;
#define ASSERT_FALSE(T) if ((T)) return false;

using namespace std;
// constants
const string pullingArrayFromFile = "Pulling Array from file... \n";
//globals
bool GLOBAL_NEGATIVE_VALUE_ERROR = false;
int GLOBAL_COMPARISON_ERROR = 400;
// constants / error messages


/**
 * Class Polynomial
 */

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
Polynomial::Polynomial(string fileName) {
    string filePath = "./" + fileName;
    ifstream inFile(fileName);
    if (!inFile) {
        printf("⚠️ ERROR: Unable to read from file. Make sure it is in the build directory and is a *.txt file, at line: %d \n",
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
        printf("⚠️ ERROR: cannot have more params then your power+1, at line %d \n", __LINE__);
        printf("⚠️ WARNING: Falling back to un parameterized constructor , at line: %d \n", __LINE__);
        Polynomial fallback;
        throw invalid_argument("Invalid Polynomial Configuration");
    } else {
        Polynomial readFromFilePoly(ArrOfCoefficients, sizeOfPoly);
    }
}
/**
 * @destructor
 */
Polynomial::~Polynomial(){

};

/**
 * @performs *this == target
 * @param {Polynomial} target
 * @return bool
 */
bool Polynomial::operator==(const Polynomial &target) {
    bool equals = true;
    int i = 0;
    if(target.data.size() != data.size()){
        equals = false;
    } else {
        while (equals && i <= target.data.size()) {
            if (target.data[i] == this->data[i]) {
                i++;
            } else {
                equals = false;
            }
        }
    }
    return equals;
}

vector<int> Polynomial::get_data(){
    return data;
}
    
    /**
     * default class destructor
     */
// prints the polynomial
void Polynomial::print() {
    for (int i = 0; i <= data.size(); i++) {
        cout << data[i] << " x ^" << i;
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
    if(target.data.size() >= this->data.size()){
        addedPolys.data.resize(target.data.size());
    } else {
        addedPolys.data.resize(this->data.size());
    }
    for (int i = 0; i <= addedPolys.data.size(); i++) {
        if(i >= target.data.size()){
            addedPolys.data.push_back(data[i]);
        } else if(i >= this->data.size()){
            addedPolys.data.push_back(target.data[i]);
        } else {
            addedPolys.data.push_back(data[i] + target.data[i]);
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
    if(target.data.size() >= this->data.size()){
        subtractedPolys.data.resize(target.data.size());
    } else {
        subtractedPolys.data.resize(this->data.size());
    }
    for (int i = 0; i <= subtractedPolys.data.size(); i++) {
        if(i > target.data.size()) {
            subtractedPolys.data.push_back(this->data[i]);
        } else if (i > this->data.size()){
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
    if(target.data.size() >= this->data.size()){
        multipliedPolys.data.resize(target.data.size());
    } else {
        multipliedPolys.data.resize(this->data.size());
    }

    for(int i = 0; i <= data.size(); i++){
        for(int j = 0; j <= target.data.size(); j++) {
            multipliedPolys.data[i + j] = multipliedPolys.data[i + j] + this->data[i]*target.data[i];
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
};

void PolynomialTest::cleanup() {

};


bool PolynomialTest::testPolynomialFileReadIn() {
    string fileThatExists = "test.txt";
    string fileThatDoesNotExist = "error.txt";
    string invalidFile = "text-invalid.txt";
    string negativeValFile = "negative-invalid.txt";
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
    Polynomial testPolynomial4(negativeValFile);

    GLOBAL_NEGATIVE_VALUE_ERROR ? printf(
            "✅ TEST PASS: testPolynomialReadIn with invalid negative value, at line:  %d \n", __LINE__)
                                : printf(
            "❌ TEST FAIL: testPolynomialReadIn with invalid negative value, at line:  %d \n", __LINE__);
    GLOBAL_NEGATIVE_VALUE_ERROR ? GLOBAL_NEGATIVE_VALUE_ERROR = false : GLOBAL_NEGATIVE_VALUE_ERROR = true;
    return true;
}

bool PolynomialTest::testPolynomialCreation(){
    const int size  = 10;
    bool pass4 = true;
    int testArr1[size] = {1,2,4,5,6,7,7,8,8,9};
    vector<int> testVec1 = {1,2,4,5,6,7,7,8,8,9};
     Polynomial testPolynomialCreation(testArr1,size);
     vector<int> retrievedData = testPolynomialCreation.get_data();
     retrievedData.resize(size);
     testVec1.resize(size);
     try {
         for (int i = 0; i < retrievedData.size(); i++) {
             if(!(retrievedData[i] == testVec1[i])){
                throw bad_function_call();
             }
         }
     }
     catch(bad_function_call &e){
         cerr << e.what() <<endl;
         pass4 = false;
     }
     pass4 ? printf(
             "✅ TEST PASS: testPolynomialCreation Polynomial constructor with valid comparison, at line:  %d \n", __LINE__)
            : printf(
             "❌ TEST FAIL: testPolynomialReadIn Polynomial constructor with invalid comparison, at line:  %d \n", __LINE__);

}

bool PolynomialTest::testPolynomialRandomOutput(){

    return true;
}

bool PolynomialTest::testEquivalence() {
    cout << "running testEquivalence... \n";
    ASSERT_TRUE(PolynomialInstance1 == PolynomialInstance2);
    printf("Passed comparison of equal objects\n");
    ASSERT_FALSE(PolynomialInstance1 == PolynomialInstance3);
    printf("Passed comparison of unequal objects of the same size\n");
    ASSERT_FALSE(PolynomialInstance1 == PolynomialInstance5);
    printf("Passed comparison of unequal objects of different sizes\n");
    printf("✅ TEST PASS: testEquivalence\n");
}

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
    testEquivalence();
    cout << "\n ------------------------------------\n";
    cleanup();
}

/**
 * Main function
 * @return int
 */
int main() {
    PolynomialTest my_test;
    my_test.run();
    return 0;
}
