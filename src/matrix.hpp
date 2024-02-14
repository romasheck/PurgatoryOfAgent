#pragma once

#include <vector>
#include <iostream>

namespace ProbabilityTask
{

template <typename T>
class Matrix : protected std::vector<std::vector<T>> {
public:
    using std::vector<std::vector<T>>::operator=;
    using std::vector<std::vector<T>>::operator[];
    using std::vector<std::vector<T>>::vector;
    using std::vector<std::vector<T>>::size;

public:
    Matrix (size_t numOfLines, size_t numOfColumns);

public:
    size_t getNumOfLines () const;
    size_t getNumOfColumns () const;
};

class dMatrix : public Matrix<double> {
public:
    using Matrix<double>::operator[];
    using Matrix<double>::Matrix;
    using Matrix<double>::operator=;
    using Matrix<double>::size;

    using Matrix<double>::getNumOfColumns;
    using Matrix<double>::getNumOfLines;

public:
    dMatrix(Matrix<double> matrix);

public:
    void fill(const double value);

    dMatrix operator*(const double scalar) const;

    dMatrix operator+(const dMatrix& other) const;

    void print() const;

public:
    //static dMatrix E(size_t N, size_t M);
};


}