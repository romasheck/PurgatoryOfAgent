#pragma once

#include "matrix.hpp"

namespace ProbabilityTask
{

enum class Directions : unsigned char
{
    left = 1 << 0,   // 0001
    bottom = 1 << 1, // 0010
    right = 1 << 2,  // 0100
    top = 1 << 3     // 1000
};

class ProbabilityExplorer final
{
public:
    ProbabilityExplorer(uint32_t sizeN, uint32_t sizeM, dMatrix matrixR, double probP, double probQ);
    
    ProbabilityExplorer(ProbabilityExplorer&) = delete;
    ~ProbabilityExplorer() = default;

public:
    dMatrix getProbabilityMatrixAfterStep (uint32_t numOfSteps) const;

    void visualProbabiltyMatrixSteping (uint32_t numOfSteps) const;

private:
    void configureMatrixG ();
    void configureMatrixW ();

    static Directions calcTopDog (double left, double bottom, double right, double top);
    
    template<typename T>
    static Matrix<T> getExpandedMatrix (const Matrix<T> & matrix);/*
    {
        size_t N = matrix.getNumOfLines();
        size_t M = matrix.getNumOfColumns();

        Matrix<T> expanded( N+2, std::vector<T>(M + 2, 0));

        for (int i = 0; i < N; ++i)
        {
            T* dest = &expanded[i + 1][1];
            const T* src = &matrix[i][0];
            
            std::copy(src, src + M, dest);
        }

        return expanded;
    }*/

    template<typename T>
    static Matrix<T> getInternalMatrix(const Matrix<T> & expanded);/*
    {
        size_t N = expanded.getNumOfLines();
        size_t M = expanded.getNumOfColumns();
        
        Matrix<T> center(N - 2, std::vector<int>(M - 2, 0));
        
        for (int i = 1; i < n - 1; ++i) 
        {
            const T* src = &expanded[i][1];
            T* dest = &center[i - 1][0];
            
            std::copy(src, src + m - 2, dest);
        }
        
        return center;
    }*/

private:
    void updateMatrixT (dMatrix& lrefMatrixT, const dMatrix& matrixP) const;

    double calcStepProb (int lineOfCur, int colOfCur, int lineOfPrev, int colOfPrev, Directions neighbor) const;

private:
    const uint32_t N;
    const uint32_t M;

    dMatrix R;
    
    const double p;
    const double q;

    const double probOfSpawn;

    dMatrix matrixG;
    Matrix<unsigned char> matrixW;
};

}