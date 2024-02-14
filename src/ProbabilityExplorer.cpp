#include "PrabilityExplorer.hpp"

namespace ProbabilityTask
{

ProbabilityExplorer::ProbabilityExplorer (uint32_t sizeN, uint32_t sizeM, dMatrix matrixR, double probP, double probQ):
    M(sizeM),
    N(sizeN),
    R(matrixR),
    p(probP),
    q(probQ),
    probOfSpawn(1 / (N * M)),
    matrixG(N, M),
    matrixW(N, M)
{
    if (!(p >= 0 && p <= 1))
    {
        std::cerr << "incorrect prob. of death\n";
        exit(-1);
    }
    if (!(q >= 0 && q <= 1))
    {
        std::cerr << "incorrect prob. of eq-prob choise\n";
        exit(-1);
    }

    if (N != R.getNumOfLines() || M != R.getNumOfColumns())
    {
        std::cerr << "incorrect size of matrix R\n";
        exit(-1);
    }

    matrixG.fill(0);

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j ++)
        {
            if ( i != 0 && i != N-1 && j != 0 && j != M -1)
            {
                
            }
        }
    }    
}

dMatrix
ProbabilityExplorer::getProbabilityMatrixAfterStep (uint32_t numOfSteps) const
{
    dMatrix matrixP(N, M), matrixFilledOne(N, M);

    matrixP.fill(probOfSpawn);
    matrixFilledOne.fill(1);

    dMatrix matrixT(N, M);
    matrixT.fill(0);

    for (int step = 1; step <= numOfSteps; step++)
    {
        updateMatrixT (matrixT, matrixP);

        matrixP = matrixFilledOne * (p*probOfSpawn) + matrixP * (1-p); 
    }

    return matrixP;
}

void
ProbabilityExplorer::updateMatrixT (dMatrix& lrefMatrixT, const dMatrix& matrixP) const
{
    updateMatrixTInternal (lrefMatrixT, matrixP);
    
    ////// necessary cringe and copypaste

    updateMatrixTBoundLeft (lrefMatrixT, matrixP);
    updateMatrixTBoundBottom (lrefMatrixT, matrixP);
    updateMatrixTBoundRight (lrefMatrixT, matrixP);
    updateMatrixTBoundTop (lrefMatrixT, matrixP);

    updateMatrixTCornerLB (lrefMatrixT, matrixP);
    updateMatrixTCornerRB (lrefMatrixT, matrixP);
    updateMatrixTCornerRT (lrefMatrixT, matrixP);
    updateMatrixTCornerLT (lrefMatrixT, matrixP);
    //////
}

void
ProbabilityExplorer::updateMatrixTInternal (dMatrix& lrefMatrixT, const dMatrix& matrixP) const
{
    for (int i = 1; i < N-1; i++)
    {
        for (int j = 1; j < M-1; j++)
        {
            lrefMatrixT[i][j] += matrixP[i][j-1] * calcStepProb (i, j, i, j-1, Directions::left);//left
            lrefMatrixT[i][j] += matrixP[i-1][j] * calcStepProb (i, j, i-1, j, Directions::bottom);//bottom
            lrefMatrixT[i][j] += matrixP[i][j+1] * calcStepProb (i, j, i, j+1, Directions::right);//right
            lrefMatrixT[i][j] += matrixP[i+1][j] * calcStepProb (i, j, i+1, j, Directions::top);//top
        }
    }
}

////// necessary cringe and copypaste

void
ProbabilityExplorer::updateMatrixTBoundLeft (dMatrix& lrefMatrixT, const dMatrix& matrixP) const
{
    const auto j = 0;

    for (int i = 1; i < N-1; i++)
    {
        lrefMatrixT[i][0] += matrixP[i-1][0] * calcStepProb (i, j, i-1, j, Directions::bottom);
        lrefMatrixT[i][0] += matrixP[i][1] * calcStepProb (i, j, i, j+1, Directions::right);
        lrefMatrixT[i][0] += matrixP[i+1][0] * calcStepProb (i, j, i+1, j, Directions::top);
    }
}

void
ProbabilityExplorer::updateMatrixTBoundBottom (dMatrix& lrefMatrixT, const dMatrix& matrixP) const
{
    const auto i = 0;

    for (int j = 1; j < N-1; j++)
    {
        lrefMatrixT[i][j] += matrixP[i][j-1] * calcStepProb (i, j, i, j-1, Directions::left);//left
        lrefMatrixT[i][j] += matrixP[i][j+1] * calcStepProb (i, j, i, j+1, Directions::right);//right
        lrefMatrixT[i][j] += matrixP[i+1][j] * calcStepProb (i, j, i+1, j, Directions::top);//top
    }
}

void
ProbabilityExplorer::updateMatrixTBoundRight (dMatrix& lrefMatrixT, const dMatrix& matrixP) const
{
    const auto j = M-1;

    for (int i = 1; i < N-1; i++)
    {
        lrefMatrixT[i][j] += matrixP[i][j-1] * calcStepProb (i, j, i, j-1, Directions::left);//left
        lrefMatrixT[i][j] += matrixP[i-1][j] * calcStepProb (i, j, i-1, j, Directions::bottom);//bottom
        lrefMatrixT[i][j] += matrixP[i+1][j] * calcStepProb (i, j, i+1, j, Directions::top);//top
    }
}

void
ProbabilityExplorer::updateMatrixTBoundTop (dMatrix& lrefMatrixT, const dMatrix& matrixP) const
{
    const auto i = N -1;

    for (int j = 1; j < M-1; j++)
    {
        lrefMatrixT[i][j] += matrixP[i][j-1] * calcStepProb (i, j, i, j-1, Directions::left);//left
        lrefMatrixT[i][j] += matrixP[i-1][j] * calcStepProb (i, j, i-1, j, Directions::bottom);//bottom
        lrefMatrixT[i][j] += matrixP[i][j+1] * calcStepProb (i, j, i, j+1, Directions::right);//right
    }
}

void
ProbabilityExplorer::updateMatrixTCornerLB (dMatrix& lrefMatrixT, const dMatrix& matrixP) const
{
    const auto i = 0;
    const auto j = 0;

    lrefMatrixT[i][j] += matrixP[i][j+1] * calcStepProb (i, j, i, j+1, Directions::right);//right
    lrefMatrixT[i][j] += matrixP[i+1][j] * calcStepProb (i, j, i+1, j, Directions::top);//top
}

void
ProbabilityExplorer::updateMatrixTCornerRB (dMatrix& lrefMatrixT, const dMatrix& matrixP) const
{
    const auto i = 0;
    const auto j = M-1;

    lrefMatrixT[i][j] += matrixP[i][j-1] * calcStepProb (i, j, i, j-1, Directions::left);//left
    lrefMatrixT[i][j] += matrixP[i+1][j] * calcStepProb (i, j, i+1, j, Directions::top);//top
}

void
ProbabilityExplorer::updateMatrixTCornerRT (dMatrix& lrefMatrixT, const dMatrix& matrixP) const
{
    const auto i = N - 1;
    const auto j = M - 1;
    
    lrefMatrixT[i][j] += matrixP[i][j-1] * calcStepProb (i, j, i, j-1, Directions::left);//left
    lrefMatrixT[i][j] += matrixP[i-1][j] * calcStepProb (i, j, i-1, j, Directions::bottom);//bottom
}

void
ProbabilityExplorer::updateMatrixTCornerLT (dMatrix& lrefMatrixT, const dMatrix& matrixP) const
{
    const auto i = N - 1;
    const auto j = 0;

    lrefMatrixT[i][j] += matrixP[i-1][j] * calcStepProb (i, j, i-1, j, Directions::bottom);//bottom
    lrefMatrixT[i][j] += matrixP[i][j+1] * calcStepProb (i, j, i, j+1, Directions::right);//right
}

///////

double
ProbabilityExplorer::calcStepProb (int lineOfCur, int colOfCur, int lineOfPrev, int colOfPrev, Directions neighbor) const
{
    auto result = matrixG[lineOfCur][lineOfPrev] * q;

    result += (double) (( matrixW[lineOfCur][colOfCur] & static_cast<unsigned char>(neighbor)) != 0) * (1-q);
}

}