//CWE457: Use of Uninitialized Variable
fn main() {
    let a;
    let x;
    if a {
        x = 5;
    }
    println!("{}", x);
}