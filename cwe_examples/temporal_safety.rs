struct Bob {
    n: Vec<i32>,
}
impl Bob {
    fn new() -> Bob {
        Bob { n: Vec::new() }
    }

    fn get_n(&self) -> &Vec<i32> {
        &self.n
    }
}
fn main() {
    let b = Bob::new();
    let xs = b.get_n();
    drop(b);
    println!("{:?}", xs[0]);
}
