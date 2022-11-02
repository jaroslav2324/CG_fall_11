#include "Matrix.h"

Matrix::Matrix(const int numRows, const int numCols){

    Matrix::numRows = numRows;
    Matrix::numCols = numCols;

	matrix = new double*[numRows];

    for (int i = 0; i < numRows; i++){
        matrix[i] = new double[numCols];
        for (int j = 0; j < numCols; j++)
            matrix[i][j] = 0;
    }
}

Matrix::Matrix(const int numRows, const int numCols, double** initialisingArray){

    Matrix::numRows = numRows;
    Matrix::numCols = numCols;

    Matrix::matrix = new double*[numRows];

    for (int i = 0; i < numRows; i++){
        Matrix::matrix[i] = new double[numCols];
        for (int j = 0; j < numCols; j++)
            Matrix::matrix[i][j] = initialisingArray[i][j];
    }
}


Matrix::Matrix(const Matrix& matrix){

    numRows = matrix.numRows;
    numCols = matrix.numCols;

    Matrix::matrix = new double*[numRows];

    for (int i = 0; i < numRows; i++){
        Matrix::matrix[i] = new double[numCols];
        for (int j = 0; j < numCols; j++)
            Matrix::matrix[i][j] = matrix.matrix[i][j];
    }
}

Matrix::~Matrix(){

    for (int i = 0; i < numCols; i++)
        delete matrix[i];

    delete matrix;
}

Matrix Matrix::operator*(const Matrix& secondMatrix){

    if (numCols != secondMatrix.numRows)
        ;
        //TODO throw

    Matrix newMatrix(numRows, secondMatrix.numCols);

	/*muliply matrixes*/
    for (int i = 0; i < numRows; i++){
        for (int j = 0; j < secondMatrix.numCols; j++){
            double result = 0;

            for (int k = 0; k < numCols; k++){
                result += matrix[i][k] * secondMatrix.matrix[k][j];
            }

            newMatrix.matrix[i][j] = result;
        }
    }

	return newMatrix;
}

void Matrix::operator=(const Matrix& secondMatrix){

    if (numRows != secondMatrix.numRows || numCols != secondMatrix.numCols)
        ;
        //TODO throw

    for (int i = 0; i < numRows; i++)
        for (int j = 0; j < numCols; j++)
            Matrix::matrix[i][j] = secondMatrix.matrix[i][j];
    
}

void Matrix::print(){

    for (int i = 0; i < numRows; i++){
        for (int j = 0; j < numCols; j++)
            cout << matrix[i][j] << " ";
        cout << endl;
    }       
}

double Matrix::getElm(int numRow, int numCol){

    if (numRow < 0 || numRows <= numRow)
        ;
        //TODO throw
    if (numCol < 0 || numCols <= numCol)
        ;
        //TODO throw

    return matrix[numRow][numCol];
}

void Matrix::setElm(int numRow, int numCol, double value){

    if (numRow < 0 || numRows <= numRow)
        ;
        //TODO throw
    if (numCol < 0 || numCols <= numCol)
        ;
        //TODO throw

    matrix[numRow][numCol] = value;
}
