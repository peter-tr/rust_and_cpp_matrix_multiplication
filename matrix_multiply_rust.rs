use std::env;
use std::fs::File;
use std::io::{self, BufRead, BufReader, Write};
use std::time::{Instant};

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

// Function to multiply two matrices
fn multiply_matrices(matrix_a: &Vec<Vec<i32>>, matrix_b: &Vec<Vec<i32>>, n: usize) -> Vec<Vec<i32>> {
    let mut result = vec![vec![0; n]; n];

    for i in 0..n {
        for j in 0..n {
            let mut s = 0;
            for k in 0..n {
                unsafe {
                    s += matrix_a.get_unchecked(i).get_unchecked(k) * matrix_b.get_unchecked(k).get_unchecked(j);
                    //result[i][j] += matrix_a.get_unchecked(i).get_unchecked(k) * matrix_b.get_unchecked(k).get_unchecked(j);
                }
                result[i][j] = s;
                //result[i][j] += matrix_a[i][k] * matrix_b[k][j];
                // += matrix_a.get_unchecked(i).get_unchecked(k) * matrix_b.get_unchecked(k).get_unchecked(j);
            }
        }
    }

    result
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

    let start_mult_time = Instant::now();
    let result_matrix = multiply_matrices(&matrix_a, &matrix_b, matrix_size);
    let duration_mult = start_mult_time.elapsed();

    println!("Matrix multiplication completion time (ms): {:.2}", duration_mult.as_secs_f64() * 1000.0);

    let mut file = File::create(format!("matrix_{}_result.txt", matrix_size))?;
    for row in result_matrix {
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

//rustc -O matrix_multiply_rust.rs