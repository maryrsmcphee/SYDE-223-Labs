#include <iostream>
#include <cassert>
#include <vector>
#include <string>
#include <fstream>

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
    /**
     * Polynomial class constructor
     * takes filename and extracts text from file.
     * @param {string} fileName
     */
    Polynomial(string fileName){
        string filePath = "./"+ fileName;
        ifstream inFile(fileName);
        if(!inFile){
            cout<<unableToReadFileERROR;;
        }
        string lineReading;
        vector<string> valuesFromFile;
        while(getline(inFile,lineReading)){
            valuesFromFile.push_back(lineReading);
            for (unsigned i=0; i < valuesFromFile.size(); i++) {
                cout<<valuesFromFile[i];

            }
            cout<<"\n";
        }
        // TODO cast to ints form string and pass to second constructor
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
    Polynomial test("test.txt");
    return 0;
}
