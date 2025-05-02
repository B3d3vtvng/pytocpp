# Compile from outer directory with command "python3 main.py examples/fib.py" and then compile the produced c++ file using stdc++ version 17+

def fib(n):
    if n <= 0:
        return 0
    elif n == 1:
        return 1
    else:
        return fib(n - 1) + fib(n - 2)
    
print(fib(30))