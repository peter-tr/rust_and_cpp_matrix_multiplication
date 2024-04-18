import os
import subprocess
import numpy as np
import matplotlib.pyplot as plt
import psutil
import time

# Matrix sizes to test
#matrix_sizes = [10, 20, 40, 80]
matrix_sizes = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150, 160, 200, 220, 250, 300, 320, 350, 380, 400, 430, 460, 500, 520, 550, 570, 600, 640, 700, 750, 800, 850, 900, 950,1000]

# Paths to the executables
generate_matrices_exec = './generate_matrices'
matrix_multiply_cpp_exec = './matrix_multiply_cpp'
matrix_multiply_rust_exec = './matrix_multiply_rust'

# Number of runs for each size to account for random errors
num_runs = 1

# Function to run a command and get the output
def run_command(command):
    result = subprocess.run(command, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
    return result.stdout

# Function to measure memory usage using psutil
def measure_memory_usage(command):
    process = subprocess.Popen(command, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
    peak_memory_usage = 0
    while process.poll() is None:
        memory_info = psutil.Process(process.pid).memory_info()
        peak_memory_usage = max(peak_memory_usage, memory_info.rss)
        time.sleep(0.01)  # Sleep briefly to reduce CPU usage
    process.wait()
    return peak_memory_usage / 1024  # Convert to KB

# Lists to store the results
cpp_total_times = []
cpp_mult_times = []
cpp_memory_usages = []
rust_total_times = []
rust_mult_times = []
rust_memory_usages = []

# Run the benchmarks
for size in matrix_sizes:
    cpp_total_run_times = []
    cpp_mult_run_times = []
    cpp_memory_run_usages = []
    rust_total_run_times = []
    rust_mult_run_times = []
    rust_memory_run_usages = []

    for _ in range(num_runs):
        # Generate matrices
        run_command([generate_matrices_exec, str(size)])
        
        # Measure memory usage for C++ matrix multiplication
        cpp_memory_usage = measure_memory_usage([matrix_multiply_cpp_exec, str(size)])
        cpp_memory_run_usages.append(cpp_memory_usage)
        
        # Run C++ matrix multiplication
        cpp_output = run_command([matrix_multiply_cpp_exec, str(size)])
        for line in cpp_output.split('\n'):
            if 'Total execution time' in line:
                cpp_total_time = float(line.split()[-1])
                cpp_total_run_times.append(cpp_total_time)
            if 'Matrix multiplication completion time' in line:
                cpp_mult_time = float(line.split()[-1])
                cpp_mult_run_times.append(cpp_mult_time)

        # Measure memory usage for Rust matrix multiplication
        rust_memory_usage = measure_memory_usage([matrix_multiply_rust_exec, str(size)])
        rust_memory_run_usages.append(rust_memory_usage)
        
        # Run Rust matrix multiplication
        rust_output = run_command([matrix_multiply_rust_exec, str(size)])
        for line in rust_output.split('\n'):
            if 'Total execution time' in line:
                rust_total_time = float(line.split()[-1])
                rust_total_run_times.append(rust_total_time)
            if 'Matrix multiplication completion time' in line:
                rust_mult_time = float(line.split()[-1])
                rust_mult_run_times.append(rust_mult_time)

    # Compute average and standard deviation
    cpp_total_times.append((np.mean(cpp_total_run_times), np.std(cpp_total_run_times)))
    cpp_mult_times.append((np.mean(cpp_mult_run_times), np.std(cpp_mult_run_times)))
    cpp_memory_usages.append((np.mean(cpp_memory_run_usages), np.std(cpp_memory_run_usages)))
    rust_total_times.append((np.mean(rust_total_run_times), np.std(rust_total_run_times)))
    rust_mult_times.append((np.mean(rust_mult_run_times), np.std(rust_mult_run_times)))
    rust_memory_usages.append((np.mean(rust_memory_run_usages), np.std(rust_memory_run_usages)))

# Save the results to a text file
with open('benchmark_results.txt', 'w') as f:
    f.write("Matrix Size,CPP Total Mean,CPP Total Std,CPP Mult Mean,CPP Mult Std,CPP Mem Mean,CPP Mem Std,Rust Total Mean,Rust Total Std,Rust Mult Mean,Rust Mult Std,Rust Mem Mean,Rust Mem Std\n")
    for size, cpp_total, cpp_mult, cpp_mem, rust_total, rust_mult, rust_mem in zip(matrix_sizes, cpp_total_times, cpp_mult_times, cpp_memory_usages, rust_total_times, rust_mult_times, rust_memory_usages):
        f.write(f"{size},{cpp_total[0]},{cpp_total[1]},{cpp_mult[0]},{cpp_mult[1]},{cpp_mem[0]},{cpp_mem[1]},{rust_total[0]},{rust_total[1]},{rust_mult[0]},{rust_mult[1]},{rust_mem[0]},{rust_mem[1]}\n")

# Plotting the results
matrix_sizes = np.array(matrix_sizes)
cpp_total_means = np.array([x[0] for x in cpp_total_times])
cpp_total_stds = np.array([x[1] for x in cpp_total_times])
cpp_mult_means = np.array([x[0] for x in cpp_mult_times])
cpp_mult_stds = np.array([x[1] for x in cpp_mult_times])
cpp_memory_means = np.array([x[0] for x in cpp_memory_usages])
cpp_memory_stds = np.array([x[1] for x in cpp_memory_usages])
rust_total_means = np.array([x[0] for x in rust_total_times])
rust_total_stds = np.array([x[1] for x in rust_total_times])
rust_mult_means = np.array([x[0] for x in rust_mult_times])
rust_mult_stds = np.array([x[1] for x in rust_mult_times])
rust_memory_means = np.array([x[0] for x in rust_memory_usages])
rust_memory_stds = np.array([x[1] for x in rust_memory_usages])

plt.figure(figsize=(14, 8))

plt.errorbar(matrix_sizes, cpp_total_means, yerr=cpp_total_stds, label='C++ Total Time', marker='o', capsize=5)
plt.errorbar(matrix_sizes, rust_total_means, yerr=rust_total_stds, label='Rust Total Time', marker='s', capsize=5)
plt.errorbar(matrix_sizes, cpp_mult_means, yerr=cpp_mult_stds, label='C++ Multiplication Time', marker='^', capsize=5)
plt.errorbar(matrix_sizes, rust_mult_means, yerr=rust_mult_stds, label='Rust Multiplication Time', marker='d', capsize=5)

plt.xlabel('Matrix Size (n x n)')
plt.ylabel('Execution Time (ms)')
plt.title('Matrix Multiplication Execution Time: C++ vs Rust')
plt.legend()
plt.grid(True)
plt.show()

plt.figure(figsize=(14, 8))

plt.errorbar(matrix_sizes, cpp_memory_means, yerr=cpp_memory_stds, label='C++ Memory Usage', marker='o', capsize=5)
plt.errorbar(matrix_sizes, rust_memory_means, yerr=rust_memory_stds, label='Rust Memory Usage', marker='s', capsize=5)

plt.xlabel('Matrix Size (n x n)')
plt.ylabel('Memory Usage (KB)')
plt.title('Matrix Multiplication Memory Usage: C++ vs Rust')
plt.legend()
plt.grid(True)
plt.show()
