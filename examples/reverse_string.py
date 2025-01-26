# Compile from outer directory with command "python3 main.py examples/fib.py" and then compile the produced c++ file using std version 17++

def reverse_string(string):
    if string == "":
        return ""
    if len(string) == 1:
        return string
    new_string = ""
    for _char in string:
        new_string = _char + new_string
    
    return new_string
