use proconio::input;

fn main() {
    input! {
        n: i32,
        m: i32,
        p: [(i32, i32); m],
    }

    println!("{} {}", n, m);
    println!("{}", p.len());

    // for &p in p.iter(){
    //     print!("{} {} ", p.0, p.1);
    // }
}
