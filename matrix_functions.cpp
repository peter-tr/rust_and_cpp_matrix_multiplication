#include "matrix_functions.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

std::vector<std::vector<int>> read_matrix_from_file(const std::string& filename, size_t n) {
    std::ifstream file(filename.c_str());
    std::vector<std::vector<int>> matrix(n, std::vector<int>(n, 0));
    std::string line;
    for (size_t i = 0; i < n && std::getline(file, line); ++i) {
        std::istringstream iss(line);
        for (size_t j = 0; j < n; ++j) {
            iss >> matrix[i][j];
        }
    }
    return matrix;
}

std::vector<std::vector<int>> multiply_matrices(const std::vector<std::vector<int>>& matrix_a, const std::vector<std::vector<int>>& matrix_b, size_t n) {
    std::vector<std::vector<int>> result(n, std::vector<int>(n, 0));
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            for (size_t k = 0; k < n; ++k) {
                result[i][j] += matrix_a[i][k] * matrix_b[k][j];
            }
        }
    }
    return result;
}