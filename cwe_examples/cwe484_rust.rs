//CWE484: Omitted Break Statement in Switch
fn main() {
    let value = 1;
    let result;
    result = match value {
        1 => 1,
        2 => 2,
        3 => 3,
        _ => 4,
    };
    println!("{}", result);
}