#include "matrix_functions.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <ctime>
#include <cstdlib>

using namespace std;

int main(int argc, char* argv[]) {
    clock_t start_time = clock();

    size_t matrix_size;
    if (argc > 1) {
        matrix_size = atoi(argv[1]);
    } else {
        cout << "Enter the size of the matrices: " << endl; // New line for prompt
        cin >> matrix_size;
    }

    stringstream ss;
    ss << "matrix_" << matrix_size << "_a.txt";
    string filename_a = ss.str();
    ss.str("");
    ss << "matrix_" << matrix_size << "_b.txt";
    string filename_b = ss.str();

    vector<vector<int>> matrix_a = read_matrix_from_file(filename_a, matrix_size);
    vector<vector<int>> matrix_b = read_matrix_from_file(filename_b, matrix_size);

    clock_t start_mult_time = clock();
    vector<vector<int>> result_matrix = multiply_matrices(matrix_a, matrix_b, matrix_size);
    clock_t end_mult_time = clock();
    double duration_mult = 1000.0 * (end_mult_time - start_mult_time) / CLOCKS_PER_SEC; // Duration in milliseconds

    cout << "Matrix multiplication completion time (ms): " << duration_mult << endl;

    ss.str("");
    ss << "matrix_" << matrix_size << "_result.txt";
    string result_filename = ss.str();
    ofstream file(result_filename.c_str());
    for (size_t i = 0; i < matrix_size; ++i) {
        for (size_t j = 0; j < matrix_size; ++j) {
            file << result_matrix[i][j] << " ";
        }
        file << endl;
    }

    clock_t end_time = clock();
    double total_duration = 1000.0 * (end_time - start_time) / CLOCKS_PER_SEC; // Total duration in milliseconds
    cout << "Total execution time (ms): " << total_duration << endl;

    cout << "Result matrix stored in " << result_filename << endl;
    return 0;
}

//optimise
//g++ -std=c++14 -o matrix_multiply_cpp matrix_multiply_cpp.cpp matrix_functions.cpp


//g++ -std=c++14 -fprofile-arcs -ftest-coverage -o matrix_multiply matrix_multiply_cpp.cpp matrix_functions.cpp -lgtest -lgtest_main -pthread -L/usr/local/lib -I/usr/local/include
