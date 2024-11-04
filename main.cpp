#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const int SIZE = 4;         //Matrix size, 4x4, but will end with two of them.
const string FILE_PATH = "matrix-data.txt";

class Matrix {
private:
    int data[SIZE][SIZE];

public:
    Matrix() {        //Initializing matrix with zeros to begin with
        for (int i = 0; i < SIZE; ++i)
            for (int j = 0; j < SIZE; ++j)
                data[i][j] = 0;
    }

    void loadFromStream(std::ifstream &file) {        //Function to load matrix
        for (int i = 0; i < SIZE; ++i)
            for (int j = 0; j < SIZE; ++j)
                file >> data[i][j];
    }

    void display() const {          //Displaying matrix
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j)
                cout << data[i][j] << " ";
            cout << endl;
        }
    }

    Matrix operator+(const Matrix &other) const {     //Operator overloading for addition.
        Matrix result;
        for (int i = 0; i < SIZE; ++i)
            for (int j = 0; j < SIZE; ++j)
                result.data[i][j] = data[i][j] + other.data[i][j];
        return result;
    }

    Matrix operator*(const Matrix &other) const {         //Operator overloading for multiplication.
        Matrix result;
        for (int i = 0; i < SIZE; ++i)
            for (int j = 0; j < SIZE; ++j) {
                result.data[i][j] = 0;
                for (int k = 0; k < SIZE; ++k)
                    result.data[i][j] += data[i][k] * other.data[k][j];
            }
        return result;
    }

    int diagonalSum() const {           //Sum of diagonal.
        int first_diag = 0, second_diag = 0;
        for (int i = 0; i < SIZE; ++i) {
            first_diag += data[i][i];
            second_diag += data[i][SIZE - i - 1];
        }
        return first_diag + second_diag;
    }

    void swapRows(int r1, int r2) {             //Swapping two rows
        if (r1 >= 0 && r1 < SIZE && r2 >= 0 && r2 < SIZE) {
            for (int j = 0; j < SIZE; ++j)
                swap(data[r1][j], data[r2][j]);
        } else {
            cerr << "Invalid row indices!" << endl;
        }
    }
};

int main() {
    Matrix mat1, mat2;

    std::ifstream file(FILE_PATH);
    if (!file) {
        cerr << "Error opening file!" << endl;
        return 1;
    }

    mat1.loadFromStream(file);        //mat1 = 4 rows.
    mat2.loadFromStream(file);           //mat2 = next 4 rows.
    file.close();

    cout << "Matrix 1:" << endl;           //Displaying matrices.
    mat1.display();

    cout << "\nMatrix 2:" << endl;
    mat2.display();

    Matrix sumMatrix = mat1 + mat2;       //Adding.
    cout << "\nSum of Matrix 1 and Matrix 2:" << endl;
    sumMatrix.display();

    Matrix productMatrix = mat1 * mat2;      //Multiplying.
    cout << "\nProduct of Matrix 1 and Matrix 2:" << endl;
    productMatrix.display();

    int diagSum = mat1.diagonalSum();          //Getting sum of diagonal
    cout << "\nSum of diagonals of Matrix 1: " << diagSum << endl;

    int r1, r2;        //User chooses two rows to swap.
    cout << "\nPlease enter desired rows (space in between) to swap in Matrix 1 (0 to " << SIZE - 1 << "): ";
    cin >> r1 >> r2;

    mat1.swapRows(r1, r2);        //Performing swap.
    cout << "\nMatrix 1 after swapping rows " << r1 << " and " << r2 << ":" << endl;
    mat1.display();

    return 0;
}
