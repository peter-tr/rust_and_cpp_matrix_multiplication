//CWE197: Numeric Truncation Error
fn process(val: f64) -> f64 {
    let temp = val as f32;
    temp
}

fn main() {
    const PI: f64 = std::f64::consts::PI;
    println!("{} ?= {}", PI, process(PI));
}