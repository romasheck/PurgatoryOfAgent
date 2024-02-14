#include "matrix.hpp"

namespace ProbabilityTask
{

template <typename T>
Matrix<T>::Matrix (size_t numOfLines, size_t numOfColumns):
    std::vector<std::vector<T>>(numOfLines, std::vector<T>(numOfColumns))
    {};

template <typename T>
size_t
Matrix<T>::getNumOfLines() const
{
    size();
}

template <typename T>
size_t
Matrix<T>::getNumOfLines() const
{
    at(0).size();
}

dMatrix::dMatrix(Matrix<double> matrix):
    Matrix<double>(matrix)
    {};

dMatrix
dMatrix:: operator * (const double scalar) const
{
    dMatrix result = *this;
    
    for (auto& row : result)
    {
        for (auto& elem : row)
        {    
            elem *= scalar;
        }
    }

    return result;
}

void 
dMatrix::fill(const double value)
{
    for (auto& row : *this)
    {
        for (auto& elem : row)
        {
            elem = value;
        }
    }
}

dMatrix 
dMatrix:: operator + (const dMatrix& other) const 
{
    if (this->size() != other.size() || (*this)[0].size() != other[0].size())
    {
        std::cerr << "Matrices must have the same size for addition" << std::endl;

        return *this;
    }

    dMatrix result = *this;
    
    for (size_t i = 0; i < result.size(); ++i)
    {
        for (size_t j = 0; j < result[0].size(); ++j)
        {
            result[i][j] += other[i][j];
        }
    }

    return result;
}

void
dMatrix::print() const 
{
    for (const auto& row : *this)
    {
        for (const auto& elem : row)
        {
            std::cout << elem << " ";
        }
        
        std::cout << std::endl;
    }
}



}