#pragma once

#include <vector>
#include <string>
#include <sstream>
#include <cmath>

template <typename T>
class Matrix {
private:
    std::vector<std::vector<T>> table_;

    double determinant(const std::vector<std::vector<T>>& matrix) const;

public:
    Matrix();
    Matrix(const Matrix<T>& other);
    void setRow(const std::string& row);
    double determinant() const;
};