# Transpiler from Python to C++

## Content

- Introduction
- Features
- Limitations
- Build process


## Introduction

This Project has been a dream of mine for about half a year now. Do not take this project and especially the code too serious as this is nothing but a toy project. I would be happy about tipps for absolutely everything because this is my first real big project and I am the complete opposite of experienced.


## Features

Supported features include:

- Variables with basic data types (int, str, bool, float, lists)
- Basic arithmetic operations (addition, subtraction, multiplication, division, modulo)
- Basic logical operations (and, or, ==, <, ...)
- Basic control flow structures (if, elif, else, while, for, ...)
- Functions
- Basic I/O operations (read, print, file IO)
- Basic built-in functions (len(), type casting, ...)
- 64-bit integers and 128-bit floats
- Import statements
- Continue statements
- Shell support on UNIX systems

Possible features in the future could be:

- More advanced data types (tuple, dict, ...)

I am not planning on implementing OOP features.


## Limitations

The limitations of this projects are mostly set by the time in would require to implement them. Beforehand, I have decided not to implement OOP features as I think it would be a pain in the butt, and because I only have limited time, there can only be so many built-in functions. Another limitation would be custom runtime errors in the compiled executable which are neccessary to enforce full type safety.

Please let me know if you notice any other limitations.


## Build process

I am proud to say that the python part of this project has close to no dependencies. The very little dependencies are part of the standart library of their respective language. For the C++ part of the project, a basic C++ compiler should do the job and in general, just cloning the project and running the main file with the file to compile being the first commandline argument should be enough. C++ Version 17+ is required.

## Shell interface

There are multiple ways of running a script with pytocpp:

- Manually compiling the script:
    - Running "python3 main.py [-args] filename" in the shell to invoke the compiler, producing a .cpp file
    - Compiling the produced executable using a c++ compiler supporting c++ standart 17+
    - Running the produced executable

- Invoking the script using the pytocpp command (after running install.sh):
    - Using the shell command "pytocpp [-args] filename" to automatically compile and run the script in the tmp folder

- Invoking the script using a shebang:
    - Putting "#!/usr/local/bin/pytocpp" at the top of your script
    - Running the script through the terminal with ./filename
