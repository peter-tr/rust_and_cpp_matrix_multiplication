// Description: CWE-681: Incorrect Conversion between Numeric Types
fn main() {
    let n_x: f64 = 7.0;
    let n_y: f64 = 2.0;
    let n_value: i32 = n_x / n_y as i32;

    println!("{}", n_value);
}


