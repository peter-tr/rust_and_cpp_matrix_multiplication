#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

// Function to generate a random matrix and store it in a file
void generateRandomMatrix(const std::string& identifier, int n) {
    std::string filename = "matrix_" + std::to_string(n) + "_" + identifier + ".txt";

    std::ofstream file(filename);
    if (!file) {
        std::cerr << "Cannot open the file: " << filename << std::endl;
        return;
    }

    srand(static_cast<unsigned int>(time(nullptr) + identifier[0])); // Seed the random number generator

    // Generate the matrix
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            // Generate random value and write it to file
            file << rand() % 100 << " "; // Random numbers between 0 and 99
        }
        file << "\n";
    }

    file.close(); // Close the file
    std::cout << "Matrix stored in " << filename << std::endl;
}

int main(int argc, char* argv[]) {

    size_t matrixSize;
    if (argc > 1) {
        matrixSize = atoi(argv[1]);
    } else {
        cout << "Enter the size of the matrices: " << endl; // New line for prompt
        cin >> matrixSize;
    }

    // Generate two matrices and store them in files with the size and identifier in the name
    generateRandomMatrix("a", matrixSize);
    generateRandomMatrix("b", matrixSize);

    return 0;
}
