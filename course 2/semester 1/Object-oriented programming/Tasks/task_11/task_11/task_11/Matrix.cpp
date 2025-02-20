#include "Matrix.h"

template <typename T>
Matrix<T>::Matrix() = default;

template <typename T>
Matrix<T>::Matrix(const Matrix<T>& other) : table_(other.table_) {}

template <typename T>
void Matrix<T>::setRow(const std::string& row) {
    std::stringstream str(row);
    std::vector<T> rowVec;
    T push;
    while (str >> push) {
        rowVec.push_back(push);
    }
    table_.push_back(rowVec);
}

template <typename T>
double Matrix<T>::determinant(const std::vector<std::vector<T>>& matrix) const {
    int n = matrix.size();
    double det = 0;
    if (n == 2) {
        return ((matrix[0][0] * matrix[1][1]) - (matrix[1][0] * matrix[0][1]));
    }
    else {
        for (int p = 0; p < n; p++) {
            std::vector<std::vector<T>> tempMatrix = matrix;
            tempMatrix.erase(tempMatrix.begin());
            for (int i = 0; i < n - 1; i++) {
                tempMatrix[i].erase(tempMatrix[i].begin() + p);
            }
            det += matrix[0][p] * pow(-1, p) * determinant(tempMatrix);
        }
        return det;
    }
}

template <typename T>
double Matrix<T>::determinant() const {
    return determinant(table_);
}