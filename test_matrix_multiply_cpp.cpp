#include <gtest/gtest.h>
#include "matrix_functions.h"
#include <vector>
#include <string>
#include <fstream>

using namespace std;

// Helper function to create a matrix file
void create_matrix_file(const string& filename, const vector<vector<int>>& matrix) {
    ofstream file(filename);
    for (const auto& row : matrix) {
        for (const auto& val : row) {
            file << val << " ";
        }
        file << endl;
    }
}

// Test read_matrix_from_file
TEST(MatrixMultiplicationTest, ReadMatrixFromFile) {
    vector<vector<int>> expected = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    string filename = "test_matrix_a.txt";
    create_matrix_file(filename, expected);

    vector<vector<int>> result = read_matrix_from_file(filename, 3);

    ASSERT_EQ(result, expected);
}

// Test multiply_matrices
TEST(MatrixMultiplicationTest, MultiplyMatrices) {
    vector<vector<int>> matrix_a = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    vector<vector<int>> matrix_b = {
        {9, 8, 7},
        {6, 5, 4},
        {3, 2, 1}
    };

    vector<vector<int>> expected_result = {
        {30, 24, 18},
        {84, 69, 54},
        {138, 114, 90}
    };

    vector<vector<int>> result = multiply_matrices(matrix_a, matrix_b, 3);

    ASSERT_EQ(result, expected_result);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

// run this to compile the test
//g++ -std=c++14 -fprofile-arcs -ftest-coverage -o test_matrix_multiply_cpp matrix_functions.cpp test_matrix_multiply_cpp.cpp -lgtest -lgtest_main -pthread -L/usr/local/lib -I/usr/local/include

// run this to generate the coverage report
//lcov --capture --directory . --output-file coverage.info --ignore-errors inconsistent
//genhtml coverage.info --output-directory out --ignore-errors inconsistent --ignore-errors corrupt
