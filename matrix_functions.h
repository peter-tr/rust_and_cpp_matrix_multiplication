#ifndef MATRIX_FUNCTIONS_H
#define MATRIX_FUNCTIONS_H

#include <vector>
#include <string>

std::vector<std::vector<int>> read_matrix_from_file(const std::string& filename, size_t n);
std::vector<std::vector<int>> multiply_matrices(const std::vector<std::vector<int>>& matrix_a, const std::vector<std::vector<int>>& matrix_b, size_t n);

#endif // MATRIX_FUNCTIONS_H
