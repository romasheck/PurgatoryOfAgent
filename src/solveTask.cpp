#include "ProbabilityExplorer.hpp"

#include <fstream>
#include <string>
#include <sstream>

/*

Dirtty main. I can write a parser and etc.
It should be done, but not today))

*/

using namespace ProbabilityTask;

int main( int argc, char* argv[]) 
{
//// Initialization begin
    if (argc < 5) {
        std::cerr << "Usage: " << argv[0] << " <N> <M> <num of steps> <p> <q>" << std::endl;
        return 1;
    }

    const auto N = std::atoi(argv[1]);
    const auto M = std::atoi(argv[2]);

    const auto stepsNum = std::atoi(argv[3]);

    const auto p = std::atof(argv[4]);
    const auto q = std::atof(argv[5]);

    std::ifstream file("assets/matrixR.txt");
    if (!file.is_open()) {
        std::cerr << "Failed to open file." << std::endl;
        return 1;
    }

    dMatrix matrixR(N, M);

    double num;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            if (!(file >> num)) {
                std::cerr << "Failed to read element at (" << i << "," << j << ")" << std::endl;
                return 1;
            }
            matrixR[i][j] = num;
        }
    }

    file.close();
//// Initialization end

    // Create main class 
    ProbabilityExplorer solver(N, M, matrixR, p ,q);

    // Use it to calculate the matrix of probabilities
    auto matrix = solver.getProbabilityMatrixAfterStep(stepsNum);
    
    // Print the matrix of probabilties stdout
    matrix.print();


    return 0;
}
