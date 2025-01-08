#include "LinearAlgebra.h"

Vector::Vector(int size) : elements(size) {}

double& Vector::operator[](int index) {
    return elements[index];
}

double Vector::operator[](int index) const {
    return elements[index];
}

int Vector::size() const {
    return elements.size();
}

double Vector::dot(const Vector& other) const {
    if (size() != other.size()) {
        throw std::invalid_argument("Vectors must be of the same size");
    }
    double result = 0.0;
    for (int i = 0; i < size(); ++i) {
        result += elements[i] * other.elements[i];
    }
    return result;
}

double Vector::norm() const {
    return std::sqrt(dot(*this));
}

Vector Vector::operator+(const Vector& other) const {
    if (size() != other.size()) {
        throw std::invalid_argument("Vectors must be of the same size");
    }
    Vector result(size());
    for (int i = 0; i < size(); ++i) {
        result[i] = elements[i] + other.elements[i];
    }
    return result;
}

Vector Vector::operator-(const Vector& other) const {
    if (size() != other.size()) {
        throw std::invalid_argument("Vectors must be of the same size");
    }
    Vector result(size());
    for (int i = 0; i < size(); ++i) {
        result[i] = elements[i] - other.elements[i];
    }
    return result;
}

Vector Vector::operator*(double scalar) const {
    Vector result(size());
    for (int i = 0; i < size(); ++i) {
        result[i] = elements[i] * scalar;
    }
    return result;
}

Matrix::Matrix(int rows, int cols) : numRows(rows), numCols(cols), elements(rows, std::vector<double>(cols)) {}

double& Matrix::operator()(int row, int col) {
    return elements[row][col];
}

double Matrix::operator()(int row, int col) const {
    return elements[row][col];
}

int Matrix::rows() const {
    return numRows;
}

int Matrix::cols() const {
    return numCols;
}

Matrix Matrix::operator+(const Matrix& other) const {
    if (rows() != other.rows() || cols() != other.cols()) {
        throw std::invalid_argument("Matrices must be of the same size");
    }
    Matrix result(rows(), cols());
    for (int i = 0; i < rows(); ++i) {
        for (int j = 0; j < cols(); ++j) {
            result(i, j) = elements[i][j] + other(i, j);
        }
    }
    return result;
}

Matrix Matrix::operator-(const Matrix& other) const {
    if (rows() != other.rows() || cols() != other.cols()) {
        throw std::invalid_argument("Matrices must be of the same size");
    }
    Matrix result(rows(), cols());
    for (int i = 0; i < rows(); ++i) {
        for (int j = 0; j < cols(); ++j) {
            result(i, j) = elements[i][j] - other(i, j);
        }
    }
    return result;
}

Matrix Matrix::operator*(double scalar) const {
    Matrix result(rows(), cols());
    for (int i = 0; i < rows(); ++i) {
        for (int j = 0; j < cols(); ++j) {
            result(i, j) = elements[i][j] * scalar;
        }
    }
    return result;
}

Matrix Matrix::transpose() const {
    Matrix result(cols(), rows());
    for (int i = 0; i < rows(); ++i) {
        for (int j = 0; j < cols(); ++j) {
            result(j, i) = elements[i][j];
        }
    }
    return result;
}

Matrix multiply(const Matrix& a, const Matrix& b) {
    if (a.cols() != b.rows()) {
        throw std::invalid_argument("Matrix dimensions must agree for multiplication");
    }
    Matrix result(a.rows(), b.cols());
    for (int i = 0; i < a.rows(); ++i) {
        for (int j = 0; j < b.cols(); ++j) {
            for (int k = 0; k < a.cols(); ++k) {
                result(i, j) += a(i, k) * b(k, j);
            }
        }
    }
    return result;
}

double determinant(const Matrix& matrix) {
    if (matrix.rows() != matrix.cols()) {
        throw std::invalid_argument("Matrix must be square to compute determinant");
    }
    // Colocar algoritmo para calcular a determinante de uma matriz
    throw std::runtime_error("Determinant calculation not implemented");
}

double cofat(const Matrix& matrix) {
    if (matrix.rows() != matrix.cols()) {
        throw std::invalid_argument("Matrix must be square to compute determinant");
    }
    // Colocar algoritmo para calcular o cofator da matriz
    throw std::runtime_error("Determinant calculation not implemented");
}

Matrix cofat_Matrix(const Matrix& matrix) {
    if (matrix.rows() != matrix.cols()) {
        throw std::invalid_argument("Matrix must be square to compute determinant");
    }
    // Colocar algoritmo para calcular a matriz dos cofatores
    throw std::runtime_error("Determinant calculation not implemented");
}

Matrix inverse(const Matrix& matrix) {
    if (matrix.rows() != matrix.cols()) {
        throw std::invalid_argument("Matrix must be square to compute inverse");
    }
    // Colocar algoritmo para calcular a inversa de uma matriz
    throw std::runtime_error("Matrix inversion not implemented");
}