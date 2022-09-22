#pragma once

#include <iostream>

using std::cout;
using std::endl;

class Matrix{

public:

    Matrix(const int numRows, const int numCols);
    Matrix(const int numRows, const int numCols, double** initialisingArray);
    Matrix(const Matrix& matrix);
    ~Matrix();

    Matrix operator*(const Matrix& secondMatrix);
    void operator=(const Matrix& secondMatrix);

    double getElm(int numRow, int numCol);
    void setElm(int numRow, int numCol, double value);

    void print();

protected:

    int numRows = 0;
    int numCols = 0;
    double** matrix = nullptr;
};
