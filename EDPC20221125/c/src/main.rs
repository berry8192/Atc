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
        n: usize,
        v: [[i32;3];n],
    }

    let mut dp=vec![[0i32;3];n];
    for i in 0..3 {
        dp[0][i]=v[0][i];
    }

    for i in 1..n {
        for j in 0..3 {
            let mut ma=0i32;
            for k in 0..3 {
                if j==k {continue};
                ma=ma.max(dp[i-1][k]+v[i][j]);
            }
            dp[i][j]=ma;
        }
    }

    // println!("n: {}, k: {}", n, k);
    // println!("{:?}", v);
    // for i in 0..n {
    //     println!("{:?}", dp[i]);
    // }
    println!("{:?}", dp[n-1].iter().max().unwrap());
}   
