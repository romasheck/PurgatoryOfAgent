#include "matrix.hpp"

#include <bitset>

namespace ProbabilityTask
{

template class Matrix<double>;
template class Matrix<unsigned char>;

template <typename T>
size_t
Matrix<T>::getNumOfLines() const
{
    return size();
}

template <typename T>
size_t
Matrix<T>::getNumOfColumns() const
{
    return ((std::vector<std::vector<T>>*)(this))->at(0).size();
}

template <typename T>
void
Matrix<T>::print () const
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

template<>
void
Matrix<unsigned char>::print () const
{
    for (const auto& row : *this)
    {
        for (const auto& elem : row)
        {
            std::cout << std::bitset<4>(elem) << " ";
        }
        
        std::cout << std::endl;
    }
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

double
dMatrix::getSumOfAll () const
{
    double result = 0;

    for (auto row : *this)
    {
        for (auto elem : row)
        {
            result += elem;
        }
    }

    return result;
}

}