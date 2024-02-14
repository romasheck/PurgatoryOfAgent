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

private:
    void configureMatrixG ();
    void configureMatrixW ();

    static Directions calcTopDog (double left, double bottom, double right, double top);
    
    template<typename T>
    static Matrix<T> getExpandedMatrix (const Matrix<T> & matrix);

    template<typename T>
    static Matrix<T> getInternalMatrix (const Matrix<T> & expanded);

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