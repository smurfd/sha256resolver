# sha256resolver
Can you resolve a sha256 hash back to text?

# SHA256
========

I set out for an interesting goal for the summer. To be able to reverse a SHA256 hash.

It was not that hard to find a solution for this in Python
```python
from string import ascii_lowercase
from itertools import product
import hashlib
import timeit

# Get the whole ascii set
def get_list():
  alph = list(map(chr, range(1, 255)))
  return alph

# Get a-z and A-Z
def get_alph():
  alph = list(map(chr, range(97, 123)))
  alph = alph + list(map(chr, range(65, 91)))
  return alph

maxrange = 10
charset = get_alph()

def solve_hash(h):
  for i in range(maxrange+1):
    for attempt in product(charset, repeat=i):
      if hashlib.sha256(''.join(attempt).encode('utf-8')).hexdigest() == h:
        print("SOLVED!")
        return ''.join(attempt)

def solve_password(password, maxrange):
  for i in range(maxrange+1):
    for attempt in product(charset, repeat=i):
      if ''.join(attempt) == password:
        return ''.join(attempt)

solved = solve_password('solve', maxrange)
print("Bruteforcing password:", solved)
print("Which has a SHA256 hash:", hashlib.sha256('solve'.encode('utf-8')).hexdigest())
print("Will try to solve that hash:",solve_hash("c14cdb19563cb1644772f5c3e7709845fb82e5be43348cd6d529d50c6050763e")) # the hash for 'solve'
```
This used the [Itertools](https://docs.python.org/3/library/itertools.html) and worked like a charm.
The output would be like:

```
Bruteforcing password: solve
Which has a SHA256 hash: c14cdb19563cb1644772f5c3e7709845fb82e5be43348cd6d529d50c6050763e
SOLVED!
Will try to solve that hash: solve
Bruteforcing password: solve
```

The maxrange variable is the number of characters the potential password would be, and the charset is in this case the alphabet from a-Z ie both small and large characters. no numbers no special characters.
So it is very limited. If you either change the maxrange or use the whole ascii set, this will take fooooreverrrr.

Was prepared for that speed would be a issue. Python is great for alot of things, but can be "slow".
Did some trivial benchmarking on loop and like additions/multiplications in python, rust and C.

Ofcourse C was the fastest.
How you compile the C code made a huge difference, if you add the -03 [option](https://gcc.gnu.org/onlinedocs/gcc/Optimize-Options.html) compared to a general compilation.

My thought was then to create a library that i could call from python.
Something like:
```c
#include <stdio.h>
int myFunction(int num) {
  if (num == 0)
    return 0;
  else
    printf("hi from C\n");
    return ((num & (num - 1)) == 0 ? 1 : 0);
}
```
which you'd compile with : `gcc -fPIC -shared -o libmyfunc.so myfunc.c`

```python
import ctypes
NUM = 16
fun = ctypes.CDLL("libmyfunc.so")

fun.myFunction.argtypes = [ctypes.c_int]

returnValue = fun.myFunction(NUM)
print(returnValue)
```
you'd call that with : `python3 call.py`

I did the same for Rust just to be sure, if i needed it. It was a similar process.
Create a cargo project. Edit your Cargo.toml to be this :
```
[package]
name = "rust2py"
version = "0.1.0"
edition = "2018"

[lib]
name = "rust2py"
crate-type = ["cdylib"]

[dependencies.pyo3]
version = "0.13.2"
features = ["extension-module"]
```

in your src/lib.rs you do something like:
```rust
use pyo3::prelude::*;
use std::process::exit;

#[pymodule]
fn rust2py(py: Python, m: &PyModule) -> PyResult<()> {
  #[pyfn(m, "sum_as_string")]
  fn sum_as_string_py(_py: Python, a: i64, b: i64) -> PyResult<String> {
      let out = sum_as_string(a, b);
      Ok(out)
  }

  Ok(())
}

fn sum_as_string(a: i64, b: i64) -> String {
  format!("{}", a + b)
}
```

After that you need to build your rust code. and create a symlink for the library
```
cargo build --release
ln -s rust2py.so target/release/librust2py.dylib
```

Then from python you do:
```python
import rust2py
print(rust2py.__doc__)
print(rust2py.sum_as_string(12,234))
```

If you remeber the Python code it used that Itertools, which ofcourse is not availalbe for C.
For [Rust](https://docs.rs/itertools/0.10.1/itertools/) though it exists
So played around with that for a while, and i think i got that to work.

But knowing that C is vastly faster for the things i wanted, it felt like a waste of time.
The plan then was to pick a part the itertools functionallities that i used in python, to be able to call C functions to speed things up.
This led to a rabbit hole that Alice never would get back from.

This loop from the python code : `for attempt in product(charset, repeat=i):`
Wanted to take that product part and make my own, found this after some time.
```python
def product2(*args, **kwds):
    def cycle(values, uplevel):
        for prefix in uplevel:
            for current in values:
                yield prefix + (current,)
    stack = iter(((),))
    for level in tuple(map(tuple, args)) * kwds.get('repeat', 1):
        stack = cycle(level, stack)
    return stack
```
Nice, no real speed difference to the itertools product().
wtf is [yield](https://docs.python.org/3/reference/expressions.html#yieldexpr)? ofcourse not available in C either...

Mean while. I was also thinking about if it was possible to distribute the load to atleast some processes or threads in the C code. Quickly realized i was confused about what was what.
Read about [fork](https://www.man7.org/linux/man-pages/man2/fork.2.html)
then read about [pthreads](https://man7.org/linux/man-pages/man7/pthreads.7.html)

Also mean while that, i was still thinking about ways to solve the brute forcing thing in C.
How fudging hard should it be, right, go over a string for each character and cycle through the charset.
Sounds so easy.

After giving up a few times i Finally found a [Gist](https://gist.github.com/lvidakovic/5859203) what led to this code
```c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LENGTH 4
int clength = 1, co, i;
char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
char pw[] = "qXaY";
char *charsetptr = charset;
char **base = NULL;

void expandArray(char **baseArray, char* symbols, int length) {
  baseArray = (char**) realloc(baseArray, sizeof(char*)*(length+1));
  for(int i=0; i<=length; i++) {
    baseArray[i] = symbols;
  }
}

int checkArray(char **baseArray, int len) {
  static char str[LENGTH];
  for(int i=0; i<len; i++)
    str[i] = *baseArray[i];

  // printf("%s\n", str); // enable for debugging output
  return strcmp(str, pw);
}

int main() {
  base = (char**) malloc(sizeof(char*));
  const char *charsetend = charsetptr + strlen(charset);

  while (clength <= LENGTH) {
    while (charsetptr < charsetend) {
      base[clength - 1] = charsetptr++;
      if (checkArray(base, clength) == 0)
        printf("FOUND ... exiting\n");
    }

    co = 0;
    for (long i=clength - 1; i >=0; i--) {
      if (*base[i] == *(charsetend - 1))
        co++;
      else
        break;
    }

    if (co == clength) {
      expandArray(base, charset, clength);
      clength++;
    } else {
      base[clength - co - 1]++;
      for (long i=clength - 1; i >= clength - co; i--)
        base[i] = charset;
    }
    charsetptr = charset;
  }

  if (base)
    free(base);
  return 0;
}
```

... this is the state where im at now i think.
Just have to find a way to generate a sha256 hash and reverse that... Oh ofcourse, Hashlib does not exist in C.

Seems like OpenSSL is the way to go, it uses C not god awful C++ with cout << blah << blah and other shit.
It would have been nice finding something smaller than OpenSSL that maby you could pick some parts of and rework to do what you want. Also reading the openssl code gave me a headache with a vengance. Might not be the code is badly written, just the vast size of it and how entangled everything is...

It has been really really fun doing this, and i have relearned a shit ton of C stuff like forking and threading that i knew decades ago but have forgotten.

Why do this though?
I have a painting on my wall saying : "Whatever i will do it anyway"
That is how i feel. These days, there are to few people doing things just 'cus
Exceptions do exist, and those are the real heroes. Have found some of those on twitch.

Throughout all this i have for the longest time tried to stay away from searching for the answers, but in the end usually ended up there anyway.
That would be a good social experiment on coding companies. Turn off external internet access for a month, to see how it would affect things getting done ;)

Will clean out the code and put it up here later, it is not PG-13 right now.
