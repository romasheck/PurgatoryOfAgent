#include "ProbabilityExplorer.hpp"

namespace ProbabilityTask
{

template class Matrix<double>;

ProbabilityExplorer::ProbabilityExplorer (uint32_t sizeN, uint32_t sizeM, dMatrix matrixR, double probP, double probQ):
    N(sizeN),
    M(sizeM),
    R(matrixR),
    p(probP),
    q(probQ),
    probOfSpawn(1 / (double)(N * M)),
    matrixG(N + 2, M + 2),
    matrixW(N + 2, M + 2)
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

    R = getExpandedMatrix<double> (R);
    
    configureMatrixG();
    configureMatrixW();
}

void
ProbabilityExplorer::configureMatrixG ()
{
    matrixG.fill(0);

    dMatrix matrixFilledOne(N, M);

    matrixFilledOne.fill(1);
    matrixFilledOne = getExpandedMatrix (matrixFilledOne);

    for (int i = 1; i < N + 1; i++)
    {
        for (int j = 1; j < M + 1; j++)
        {
            matrixG[i][j] += matrixFilledOne[i-1][j];
            matrixG[i][j] += matrixFilledOne[i+1][j];

            matrixG[i][j] += matrixFilledOne[i][j-1];
            matrixG[i][j] += matrixFilledOne[i][j+1];

            matrixG[i][j] = 1 / matrixG[i][j];
        }
    }
}

void
ProbabilityExplorer::configureMatrixW ()
{
    for (int i = 1; i < N + 1; i++)
    {
        for (int j = 1; j < M + 1; j++)
        {
            auto topDog = calcTopDog(R[i][j-1], R[i-1][j], R[i][j+1], R[i+1][j]);

            switch (topDog)
            {
            case Directions::left:
            {
                matrixW[i][j-1] = matrixW[i][j-1] | static_cast<unsigned char>(Directions::right);
                break;
            }
            case Directions::bottom:
            {
                matrixW[i-1][j] = matrixW[i-1][j] | static_cast<unsigned char>(Directions::top);
                break;
            }
            case Directions::right:
            {
                matrixW[i][j+1] = matrixW[i][j+1] | static_cast<unsigned char>(Directions::left);
                break;
            }
            case Directions::top:
            {
                matrixW[i+1][j] = matrixW[i+1][j] | static_cast<unsigned char>(Directions::bottom);
                break;
            }
            default:
                std::cerr << "wrong direction" << std::endl;
                break;
            }
        }
    }
}

Directions
ProbabilityExplorer::calcTopDog (double left, double bottom, double right, double top)
{
    if (left >= bottom && left >= right && left >= top) {
        return Directions::left;
    } else if (bottom >= left && bottom >= right && bottom >= top) {
        return Directions::bottom;
    } else if (right >= left && right >= bottom && right >= top) {
        return Directions::right;
    } else {
        return Directions::top;
    }
}


template <typename T>
Matrix<T>
ProbabilityExplorer::getExpandedMatrix (const Matrix<T> & matrix)
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
}

template<typename T>
Matrix<T>
ProbabilityExplorer::getInternalMatrix(const Matrix<T> & expanded)
{
    size_t N = expanded.getNumOfLines();
    size_t M = expanded.getNumOfColumns();
    
    Matrix<T> center(N - 2, std::vector<T>(M - 2, 0));
    
    for (int i = 1; i < N - 1; ++i) 
    {
        const T* src = &expanded[i][1];
        T* dest = &center[i - 1][0];
        
        std::copy(src, src + M - 2, dest);
    }
    
    return center;
}


dMatrix
ProbabilityExplorer::getProbabilityMatrixAfterStep (uint32_t numOfSteps) const
{
    dMatrix matrixP(N, M), matrixFilledOne(N, M);

    matrixP.fill(probOfSpawn);
    matrixFilledOne.fill(1);

    matrixP = getExpandedMatrix<double> (matrixP);
    matrixFilledOne = getExpandedMatrix<double> (matrixFilledOne);


    dMatrix matrixT(N + 2, M + 2);
    matrixT.fill(0);

    for (int step = 1; step <= numOfSteps; step++)
    {
        updateMatrixT (matrixT, matrixP);

        matrixP = matrixFilledOne * (p*probOfSpawn) + matrixT * (1-p); 
    }

    return getInternalMatrix<double>(matrixP);
}

void
ProbabilityExplorer::updateMatrixT (dMatrix& lrefMatrixT, const dMatrix& matrixP) const
{
    for (int i = 1; i < N +1; i++)
    {
        for (int j = 1; j < M +1; j++)
        {
            lrefMatrixT[i][j] = 0;

            lrefMatrixT[i][j] += matrixP[i][j-1] * calcStepProb(i, j, i, j - 1, Directions::left);
            lrefMatrixT[i][j] += matrixP[i-1][j] * calcStepProb(i, j, i - 1, j, Directions::bottom);
            lrefMatrixT[i][j] += matrixP[i][j+1] * calcStepProb(i, j, i, j + 1, Directions::right);
            lrefMatrixT[i][j] += matrixP[i+1][j] * calcStepProb(i, j, i + 1, j, Directions::top);
        }
    }
}

double
ProbabilityExplorer::calcStepProb (int lineOfCur, int colOfCur, int lineOfPrev, int colOfPrev, Directions neighbor) const
{
    auto result = matrixG[lineOfPrev][colOfPrev] * q;
 
    result += ((double) (( matrixW[lineOfCur][colOfCur] & static_cast<unsigned char>(neighbor)) != 0)) * (1-q);

    return result;
}

}