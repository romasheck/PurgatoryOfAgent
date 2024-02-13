#include <iostream>
#include <vector>

#include "src/matrix.hpp"

int main() 
{
    ProbabilityTask::dMatrix matrix({{1, 1, 1}, {2, 2, 2}, {3, 3, 3}});  

    auto tmp = matrix;
    matrix.fill(42);
    matrix = tmp + matrix;
    matrix.print();

    std::cout << matrix[0][0] << std::endl;

    return 0;
}
