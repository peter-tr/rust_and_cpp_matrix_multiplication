//CWE-704: Incorrect Type Conversion or Cast

fn main() {
    let x = vec!["a", "b"];
    println!("{}", x[0]);
    let y = vec!["c", "d"].iter().collect();
    println!("{}", y[0]);
}