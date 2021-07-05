use itertools::Itertools;
use std::iter::FromIterator;
use std::process;
use std::time::Instant;

// 97-123 & 65-91
fn main() {
  println!("Hello, world!");

  let mut multi_prod = (0..3).map(|i| (i * 2)..(i * 2 + 2)).multi_cartesian_product();
  let multi_chr = ('0'..'6').map(|_| ('A')..('Z')).multi_cartesian_product();

  assert_eq!(multi_prod.next(), Some(vec![0, 2, 4]));
  assert_eq!(multi_prod.next(), Some(vec![0, 2, 5]));
  assert_eq!(multi_prod.next(), Some(vec![0, 3, 4]));
  assert_eq!(multi_prod.next(), Some(vec![0, 3, 5]));
  assert_eq!(multi_prod.next(), Some(vec![1, 2, 4]));
  assert_eq!(multi_prod.next(), Some(vec![1, 2, 5]));
  assert_eq!(multi_prod.next(), Some(vec![1, 3, 4]));
  assert_eq!(multi_prod.next(), Some(vec![1, 3, 5]));
  assert_eq!(multi_prod.next(), None);

  let now = Instant::now();
  for i in multi_chr {
    let s = String::from_iter(&i);
//    println!("{:?} - {}", &i, s);
    if s == "ABCDEF" {
      let elapsed = now.elapsed();
      println!("Elapsed: {:.2?}", elapsed);
      process::exit(0x0);
    }
  }
}
