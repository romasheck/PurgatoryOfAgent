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

/// @brief Small and casual class for one task
class ProbabilityExplorer final
{
public:
    /// @brief The constructor of class
    /// @param sizeN - number of Lines
    /// @param sizeM - number of Columns
    /// @param matrixR - matrix R (marks)
    /// @param probP - the probability of agent death
    /// @param probQ - the probability of equiprobable in directions step
    ProbabilityExplorer(uint32_t sizeN, uint32_t sizeM, dMatrix matrixR, double probP, double probQ);
    
    ProbabilityExplorer(ProbabilityExplorer&) = delete;
    ~ProbabilityExplorer() = default;

public:
    /// @brief Calculation the matrix of probabities
    /// @param numOfSteps - number of agent steps
    /// @return the matrix of probabilities to of an agent being in the coresponding cell after steps
    dMatrix getProbabilityMatrixAfterStep (uint32_t numOfSteps) const;

    /// @brief Slow function, that calculate matrix of probabilities and display it step by step (using SFML in realization)
    /// @param numOfSteps - number of agent steps
    void visualProbabiltyMatrixSteping (uint32_t numOfSteps) const;

private:
    void configureMatrixG ();
    void configureMatrixW ();

    static Directions calcTopDog (double left, double bottom, double right, double top);
    
    template<typename T>
    static Matrix<T> getExpandedMatrix (const Matrix<T> & matrix);

    template<typename T>
    static Matrix<T> getInternalMatrix(const Matrix<T> & expanded);

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