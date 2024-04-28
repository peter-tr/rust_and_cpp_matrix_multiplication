use std::env;
use std::fs::File;
use std::io::{self, BufRead, BufReader, Write};
use std::time::{Instant};
use std::os::raw::{c_int, c_void};

// Function to read a matrix from a file
fn read_matrix_from_file(filename: &str, n: usize) -> io::Result<Vec<Vec<i32>>> {
    let file = File::open(filename)?;
    let reader = BufReader::new(file);

    let mut matrix = vec![vec![0; n]; n];
    for (i, line) in reader.lines().enumerate() {
        for (j, val) in line?.split_whitespace().enumerate() {
            matrix[i][j] = val.parse().expect("Not an integer!");
        }
    }

    Ok(matrix)
}

// External declaration for the C++ function
extern "C" {
    fn multiply_matrices(
        matrix_a: *const c_int,
        matrix_b: *const c_int,
        result_matrix: *mut c_int,
        n: usize,
    );
}

fn main() -> io::Result<()> {
    let start_time = Instant::now();

    let args: Vec<String> = env::args().collect();
    let matrix_size = if args.len() > 1 {
        args[1].parse::<usize>().expect("Please provide a valid number")
    } else {
        let mut input = String::new();
        println!("Enter the size of the matrices: ");
        io::stdin().read_line(&mut input).expect("Failed to read line");
        input.trim().parse::<usize>().expect("Please type a number!")
    };

    let matrix_a = read_matrix_from_file(&format!("matrix_{}_a.txt", matrix_size), matrix_size)?;
    let matrix_b = read_matrix_from_file(&format!("matrix_{}_b.txt", matrix_size), matrix_size)?;

    let flat_matrix_a: Vec<c_int> = matrix_a.iter().flatten().copied().collect();
    let flat_matrix_b: Vec<c_int> = matrix_b.iter().flatten().copied().collect();
    let mut result_matrix: Vec<c_int> = vec![0; matrix_size * matrix_size];

    let start_mult_time = Instant::now();
    
    unsafe {
        multiply_matrices(
            flat_matrix_a.as_ptr(),
            flat_matrix_b.as_ptr(),
            result_matrix.as_mut_ptr(),
            matrix_size
        );
    }

    let duration_mult = start_mult_time.elapsed();
    println!("Matrix multiplication completion time (ms): {:.2}", duration_mult.as_secs_f64() * 1000.0);

    let mut result_matrix_2d = vec![vec![0; matrix_size]; matrix_size];
    for i in 0..matrix_size {
        for j in 0..matrix_size {
            result_matrix_2d[i][j] = result_matrix[i * matrix_size + j];
        }
    }

    let mut file = File::create(format!("matrix_{}_result.txt", matrix_size))?;
    for row in result_matrix_2d {
        for val in row {
            write!(file, "{} ", val)?;
        }
        writeln!(file)?;
    }

    let total_duration = start_time.elapsed();
    println!("Total execution time (ms): {:.2}", total_duration.as_secs_f64() * 1000.0);
    println!("Result matrix stored in matrix_{}_result.txt", matrix_size);

    Ok(())
}

//rustc -L . -l matrix_functions_ffi -O matrix_multiply_rust.rs