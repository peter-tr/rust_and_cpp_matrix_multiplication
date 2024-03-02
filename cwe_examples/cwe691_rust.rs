// CWE691: Insufficient Control Flow Management

fun get_rand() -> i32 { }

fn main() {
    println!("rand: {}", get_rand());
}