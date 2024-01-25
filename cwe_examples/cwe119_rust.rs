//CWE-119: Improper Restriction of Operations within the Bounds of a Memory Buffer

fn main() {
    let v = vec![1,2,3,4,5];
    println!("The value of v[0] is: {}", v[-1]);
    println!("The value of v[1] is: {}", v[5]);
}