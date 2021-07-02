from string import ascii_lowercase
from itertools import product
import hashlib
import timeit

# every ascii character
def get_list():
  alph = list(map(chr, range(1, 255)))
  return alph

# alphabet from a-z, to A-Z
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

def product1(*args, repeat=1):
    pools = [tuple(pool) for pool in args] * repeat
    result = [[]]
    for pool in pools:
        result = [x+[y] for x in result for y in pool]
    for prod in result:
        yield tuple(prod)

def solve_password1(password, maxrange):
  for i in range(maxrange+1):
    for attempt in product1(charset, repeat=i):
      if ''.join(attempt) == password:
        return ''.join(attempt)

def product2(*args, **kwds):
    def cycle(values, uplevel):
        for prefix in uplevel:
            for current in values:
                yield prefix + (current,)
    stack = iter(((),))
    for level in tuple(map(tuple, args)) * kwds.get('repeat', 1):
        stack = cycle(level, stack) 
    return stack

def solve_password2(password, maxrange):
  for i in range(maxrange+1):
    for attempt in product2(charset, repeat=i):
      if ''.join(attempt) == password:
        return ''.join(attempt)

def solve_hash2(h):
  for i in range(maxrange+1):
    for attempt in product2(charset, repeat=i):
      if hashlib.sha256(''.join(attempt).encode('utf-8')).hexdigest() == h:
        print("SOLVED!")
        return ''.join(attempt)

solved = solve_password('solve', maxrange)
print("Bruteforcing password:", solved)
print("Which has a SHA256 hash:", hashlib.sha256('solve'.encode('utf-8')).hexdigest())
print("Will try to solve that hash:",solve_hash("c14cdb19563cb1644772f5c3e7709845fb82e5be43348cd6d529d50c6050763e")) # the hash for 'solve

start = timeit.default_timer()
solved = solve_password('solve', maxrange)
print("Bruteforcing password:", solved)
stop = timeit.default_timer()
execution_time = stop - start
print("Program Executed in"+str(execution_time))

print("####################################")

start2 = timeit.default_timer()
solved = solve_password2('solve', maxrange)
print("Bruteforcing password:", solved)
print("Which has a SHA256 hash:", hashlib.sha256('solve'.encode('utf-8')).hexdigest())
print("Will try to solve that hash:",solve_hash2("c14cdb19563cb1644772f5c3e7709845fb82e5be43348cd6d529d50c6050763e")) # the hash for 'solv
stop2 = timeit.default_timer()
execution_time2 = stop2 - start2
print("Program Executed in"+str(execution_time))
