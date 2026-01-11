def integer_math(n):
    x = 0
    for i in range(n):
        x += i * 2 / 3

def float_math(n):
    x = 0.0
    for i in range(n):
        x += (i * 1.1) / 2.3

def string_concat(n):
    s = ""
    for i in range(n / 1000):
        s += "abc"

def list_processing(n):
    lst = range(n)
    total = 0
    for i in lst:
        total += i

def f(x): 
    return x * x

def function_calls(n):
    total = 0
    for i in range(n):
        total += f(i)

def ptime(old_time, msg):
    time_taken = time() - old_time
    print("Time taken for " + msg + ": " + str(time_taken))

cur_time = time()
start_time = cur_time
integer_math(1000000)
ptime(cur_time, "Integer Math")
cur_time = time()
float_math(1000000)
ptime(cur_time, "Float Math")
cur_time = time()
string_concat(1000000)
ptime(cur_time, "String Concatenation")
cur_time = time()
list_processing(1000000)
ptime(cur_time, "List Processing")
cur_time = time()
function_calls(1000000)
ptime(cur_time, "Function Calls")

print("Total Time taken: " + str(time() - start_time))
