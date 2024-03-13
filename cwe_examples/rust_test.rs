// CWE:787: Out-of-bounds Write
fn main() {
    
    // create array of int size 3
    let mut arr: [i32; 3] = [0; 3];

    //for loop to iterate over the array
    for i in 0..4 {
        // assign value to the array
        arr[i] = i as i32;
        println!("{}",i);
    }

}