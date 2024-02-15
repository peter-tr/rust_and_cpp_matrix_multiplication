fn foo(mut value: i32) -> i32 {
    if value = 0 {  
        return 1;
    } else {
        return value;
    }
}
fn main() {
    println!("{}", foo(0));  
    println!("{}", foo(1));  
}