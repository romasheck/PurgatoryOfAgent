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

enum class Corners
{
    lb, 
    rb, 
    rt, 
    lt
};

//enum PartsOfMatrix
//{
//    Internal,
//    cornorLB,
//    cornorRB,
//    cornorRT,
//    cornorLT,
//    boundL,
//    boundB,
//    boundR,
//    boundT
//};

class ProbabilityExplorer final
{
public:
    ProbabilityExplorer(uint32_t sizeN, uint32_t sizeM, dMatrix matrixR, double probP, double probQ);
    
    ProbabilityExplorer(ProbabilityExplorer&) = delete;
    ~ProbabilityExplorer() = default;

public:
    dMatrix getProbabilityMatrixAfterStep (uint32_t numOfSteps) const;

private:
    void updateMatrixT (dMatrix& lrefMatrixT, const dMatrix& matrixP) const;
    //void updateMatrixTPart (PartsOfMatrix part, dMatrix& lrefMatrixT, dMatrix matrixP, std::fun) const;
    void updateMatrixTInternal (dMatrix& lrefMatrixT, const dMatrix& matrixP) const;
    
////// necessary cringe and copypaste
////// I dont use switch construction to avoid branching 
////// If matrix is realy big, it can help to vectorization
////// But ! If matrix is realy big, the programm have trouble with locality of usable data

    void updateMatrixTBoundLeft (dMatrix& lrefMatrixT, const dMatrix& matrixP) const;
    void updateMatrixTBoundBottom (dMatrix& lrefMatrixT, const dMatrix& matrixP) const;
    void updateMatrixTBoundRight (dMatrix& lrefMatrixT, const dMatrix& matrixP) const;
    void updateMatrixTBoundTop (dMatrix& lrefMatrixT, const dMatrix& matrixP) const;
    
    void updateMatrixTCornerLB (dMatrix& lrefMatrixT, const dMatrix& matrixP) const;
    void updateMatrixTCornerRB (dMatrix& lrefMatrixT, const dMatrix& matrixP) const;
    void updateMatrixTCornerRT (dMatrix& lrefMatrixT, const dMatrix& matrixP) const;
    void updateMatrixTCornerLT (dMatrix& lrefMatrixT, const dMatrix& matrixP) const;
//////

    double calcStepProb (int lineOfCur, int colOfCur, int lineOfPrev, int colOfPrev, Directions neighbor) const;

private:
    const uint32_t N;
    const uint32_t M;

    const dMatrix R;
    
    const double p;
    const double q;

    const double probOfSpawn;

    dMatrix matrixG;
    Matrix<unsigned char> matrixW;
};

}