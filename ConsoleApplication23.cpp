#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <stdexcept>
using namespace std;

template<typename T>
class Matrix {
private:
    T** data; 
    size_t rows;
    size_t cols;  

    void freeMemory() {
        for (size_t i = 0; i < rows; ++i) {
            delete[] data[i];
        }
        delete[] data;
    }

public:
    Matrix(size_t rows, size_t cols) : rows(rows), cols(cols) {
        data = new T * [rows];
        for (size_t i = 0; i < rows; ++i) {
            data[i] = new T[cols];
        }
    }

    ~Matrix() {
        freeMemory();
    }

    void fillRandom(T minValue, T maxValue) {
        srand(static_cast<unsigned>(time(0)));
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                data[i][j] = minValue + static_cast<T>(rand()) / (RAND_MAX / (maxValue - minValue));
            }
        }
    }

    void fillFromInput() {
        cout << "Enter the elements of the matrix (" << rows << "x" << cols << "):\n";
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                cin >> data[i][j];
            }
        }
    }

    void print() const {
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                cout << data[i][j] << " ";
            }
            cout << "\n";
        }
    }

    Matrix operator+(const Matrix& other) const {
        if (rows != other.rows || cols != other.cols) {
            throw invalid_argument("The matrix sizes do not match!");
        }
        Matrix result(rows, cols);
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                result.data[i][j] = data[i][j] + other.data[i][j];
            }
        }
        return result;
    }

    Matrix operator-(const Matrix& other) const {
        if (rows != other.rows || cols != other.cols) {
            throw invalid_argument("The matrix sizes do not match!");
        }
        Matrix result(rows, cols);
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                result.data[i][j] = data[i][j] - other.data[i][j];
            }
        }
        return result;
    }

    Matrix operator*(const Matrix& other) const {
        if (cols != other.rows) {
            throw invalid_argument("Incompatible sizes for multiplication!");
        }
        Matrix result(rows, other.cols);
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < other.cols; ++j) {
                result.data[i][j] = 0;
                for (size_t k = 0; k < cols; ++k) {
                    result.data[i][j] += data[i][k] * other.data[k][j];
                }
            }
        }
        return result;
    }

    Matrix operator/(const Matrix& other) const {
        if (rows != other.rows || cols != other.cols) {
            throw invalid_argument("The matrix sizes do not match!");
        }
        Matrix result(rows, cols);
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                if (other.data[i][j] == 0) {
                    throw invalid_argument("Division by zero!");
                }
                result.data[i][j] = data[i][j] / other.data[i][j];
            }
        }
        return result;
    }

    T findMin() const {
        T minElement = data[0][0];
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                if (data[i][j] < minElement) {
                    minElement = data[i][j];
                }
            }
        }
        return minElement;
    }

    T findMax() const {
        T maxElement = data[0][0];
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                if (data[i][j] > maxElement) {
                    maxElement = data[i][j];
                }
            }
        }
        return maxElement;
    }
};

int main() {
    size_t rows = 3, cols = 3;

    Matrix<int> mat1(rows, cols);
    Matrix<int> mat2(rows, cols);

    mat1.fillRandom(1, 10);
    mat2.fillRandom(1, 10);

    cout << "Matrix 1:\n";
    mat1.print();

    cout << "Matrix 2:\n";
    mat2.print();

    Matrix<int> sum = mat1 + mat2;
    cout << "Sum:\n";
    sum.print();

    cout << "Maximum in matrix 1: " << mat1.findMax() << "\n";
    cout << "Minimum in matrix 1: " << mat1.findMin() << "\n";
}
