#include <vector>
#include <iostream>

namespace ProbabilityTask
{

template <typename T>
class Matrix : public std::vector<std::vector<T>> {
public:
    using std::vector<std::vector<T>>::operator=;
    using std::vector<std::vector<T>>::operator[];
    using std::vector<std::vector<T>>::vector;
};

class dMatrix : public Matrix<double> {
public:
    using Matrix<double>::operator[];
    using Matrix<double>::Matrix; // Используем конструкторы базового класса
    using Matrix<double>::operator=;

    // Методы
    void fill(const double& value);

    dMatrix operator*(const double scalar) const;

    dMatrix operator+(const dMatrix& other) const;

    void print() const;
};


}