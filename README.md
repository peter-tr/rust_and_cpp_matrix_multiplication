# Thesis Files: "Optimising Programming Language Selection in Aviation"

Due to NDA restrictions, the reports and detailed analysis cannot be revealed. However, the provided files reflect the experimental work done in matrix multiplication using both Rust and C++. The naive approach was implemented, reflecting an algorithmic time complexity of O(n^3) and space complexity of O(n^2), directly translating the mathematical matrix multiplication into code.

## Pseudo-Code

```plaintext
input A and B, both n by n matrices
initialise C to be an n by n matrix of all zeros
for i from 1 to n:
    for j from 1 to n:
        for k from 1 to n:
            C[i][j] = C[i][j] + A[i][k]*B[k][j]
output C (as A*B)
```
## Performance Evaluation Methodology

### Matrix Generation

To ensure a fair performance assessment, matrices of various sizes (10, 20, 40, 80, 100, 120, 160, 200, 280, 360, 480, 600) were randomly generated and used consistently across Rust and C++ implementations. The experiment was repeated ten times for each matrix size to minimize random fluctuations. Although the focus is on matrix multiplication, the program reads input matrices from files and writes results to an output file.

### Matrix Multiplication

The `multiply_matrix` program reads the generated matrices, multiplies them, and writes the result to an output file. Key steps include:

- **Reading Matrices**: A function `read_matrix_from_file` reads matrices into a 2D vector.
- **Multiplication**: The `multiply_matrices` function computes the product matrix using standard matrix multiplication.
- **Output**: The resulting matrix is written to a new file, and the completion time is printed to the console.

### Benchmarking

Execution time for C++ was measured using the `clock` module, and Rust used the `time` module. Memory usage was measured by running the programs in a Python subprocess and using the `psutil` profiling tool to measure peak memory usage. A Python benchmark script automates testing and recording the performance of the `multiply_matrix` programs in both C++ and Rust. It measures execution time and memory usage for different matrix sizes, visualizing results with Matplotlib.

### Comparison of C++ and Rust Implementation

The `generate_matrices` and `matrix_multiply` programs were first implemented in C++. This decision was driven by the author’s prior familiarity with C++. Following the implementation in C++, the next step was to port the programs to Rust. For this implementation, no optimization was applied to the code to ensure a fair comparison between the two languages. The same algorithm was used for both implementations.

Incorporating Rust's ownership and borrowing concepts into the matrix multiplication port initially presented a steep learning curve, given their absence in C++. The strict, compile-time enforced rules of Rust's ownership model prevent many runtime errors that can plague C++ applications. While the initial adaptation requires effort, the long-term benefits of Rust's rigorous approach to memory safety are clear, offering a reliable enhancement over traditional C++ practices.

## CWE Examples

The CWE examples folder contains specific memory safety issues in both Rust and C++. Experiments were conducted, and the errors were sorted into Common Weakness Enumerations (CWE). The following CWEs compile without errors in C++ but result in compile-time errors in Rust, demonstrating Rust's emphasis on safety and reliability.


