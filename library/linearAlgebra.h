#ifndef LINEAR_ALGEBRA_H
#define LINEAR_ALGEBRA_H

#include <vector>
#include <iostream>
#include <cmath>
#include <stdexcept>
using namespace std;

class Vector {
    public:
        Vector(int size);
        double& operator[](int index);
        double operator[](int index) const;
        int size() const;
        double dot(const Vector& other) const;
        double norm() const;
        Vector operator+(const Vector& other) const;
        Vector operator-(const Vector& other) const;
        Vector operator*(double scalar) const;
    private:
        vector<double> elements;
};

class Matrix {
    public:
        Matrix(int rows, int cols);
        double& operator()(int row, int col);
        double operator()(int row, int col) const;
        int rows() const;
        int cols() const;
        Matrix operator+(const Matrix& other) const;
        Matrix operator-(const Matrix& other) const;
        Matrix operator*(double scalar) const;
        Matrix transpose() const;
        double cofat(const Matrix& matrix);
        Matrix cofat_Matrix(const Matrix& matrix);

    private:
        vector<vector<double>> elements;
        int numRows, numCols;
};

Matrix multiply(const Matrix& a, const Matrix& b);
double determinant(const Matrix& matrix);
Matrix inverse(const Matrix& matrix);

#endif 