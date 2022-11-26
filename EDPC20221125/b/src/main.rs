macro_rules! input {
    (source = $s:expr, $($r:tt)*) => {
        let mut iter = $s.split_whitespace();
        input_inner!{iter, $($r)*}
    };
    ($($r:tt)*) => {
        let s = {
            use std::io::Read;
            let mut s = String::new();
            std::io::stdin().read_to_string(&mut s).unwrap();
            s
        };
        let mut iter = s.split_whitespace();
        input_inner!{iter, $($r)*}
    };
}
macro_rules! input_inner {
    ($iter:expr) => {};
    ($iter:expr, ) => {};

    ($iter:expr, $var:ident : $t:tt $($r:tt)*) => {
        let $var = read_value!($iter, $t);
        input_inner!{$iter $($r)*}
    };
}
macro_rules! read_value {
    ($iter:expr, ( $($t:tt),* )) => {
        ( $(read_value!($iter, $t)),* )
    };

    ($iter:expr, [ $t:tt ; $len:expr ]) => {
        (0..$len).map(|_| read_value!($iter, $t)).collect::<Vec<_>>()
    };

    ($iter:expr, chars) => {
        read_value!($iter, String).chars().collect::<Vec<char>>()
    };

    ($iter:expr, usize1) => {
        read_value!($iter, usize) - 1
    };

    ($iter:expr, $t:ty) => {
        $iter.next().unwrap().parse::<$t>().expect("Parse error")
    };
}

fn main(){
    input!{
        n: usize, k: usize,
        v: [i64; n],
    }

    let mut dp=vec![0;n];
    for i in 1..n {
        let mut mi=2000000000;
        for j in 1..k+1 {
            if i<j {continue};
            mi=std::cmp::min(mi, dp[i-j]+(v[i]-v[i-j]).abs());
        }
        // dp[i]=[max(0, )].iter().fold(0.0/0.0, |mi, vi| min(mi, ))
        dp[i]=mi;
    }

    // println!("n: {}, k: {}", n, k);
    // println!("{:?}", v);
    // println!("{:?}", dp);
    println!("{}", dp[n-1]);
}
