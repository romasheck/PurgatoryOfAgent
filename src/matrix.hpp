#pragma once

#include <vector>
#include <iostream>

namespace ProbabilityTask
{
/// @brief Small and casual class of Matrix
/// @tparam T - the elems of the Matrix type. It should be writable by "std::cout<< ..." 
template <typename T>
class Matrix : protected std::vector<std::vector<T>> {
public:
    using std::vector<std::vector<T>>::operator=;
    using std::vector<std::vector<T>>::operator[];
    using std::vector<std::vector<T>>::vector;
    using std::vector<std::vector<T>>::size;

public:
    /// @brief The constructor of the class, use std::vector constructor
    /// @param numOfLines - number of lines
    /// @param numOfColumns - number of columns
    Matrix (size_t numOfLines, size_t numOfColumns):
    std::vector<std::vector<T>>(numOfLines, std::vector<T>(numOfColumns))
    {};

public:
    size_t getNumOfLines () const;
    size_t getNumOfColumns () const;

    /// @brief Printing matrix for debug
    void print() const;

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
    /// @brief The constructor of the class, that allow to cast Matrix<double> to dMatrix
    ///         Perhaps I should use && and std::move
    /// @param matrix - the source of the copy
    dMatrix(Matrix<double> matrix);

public:
    /// @brief Fill whole dMatrix by one double value
    /// @param value - this value
    void fill(const double value);

    /// @brief Default operator * Matrix to scalar 
    dMatrix operator*(const double scalar) const;

    /// @brief Default operator + matrix with matrix
    dMatrix operator+(const dMatrix& other) const;

public:
    /// @brief summarize all elements of the matrix. Use it for verification the probability model.
    /// @return sum of all elements 
    double getSumOfAll () const;
};


}