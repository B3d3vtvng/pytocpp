# Transpiler from Python to C++

## Content

- Introduction
- Features
- Limitations
- Contributing
- Build process


## Introduction

This Project has been a dream of mine for about half a year now. Do not take this project and especially the code too serious as this is nothing but a toy project. I would be happy about tips for absolutely everything because this is my first real big project and I am the complete opposite of experienced.


## Features

Features that will be supported when I have finished the Transpiler include:

- Variables with basic data types (int, str, bool, float, lists)
- Basic arithmetic operations (addition, subtraction, multiplication, division)
- Basic logical operations (and, or, ==, <, ...)
- Basic control flow structures (if, elif, else, while, for, ...)
- Functions
- Basic I/O operations (read, print)
- Basic built-in functions (len(), type casting, ...)

Possible features in the future could be:

- A Python-like pass keyword
- A Python-like break keyword
- More advanced data types (tuple, dict, ...)

I am not planning on implementing OOP features.


## Limitations

This project has a lot of limitations as I have been very strict about keeping everything as close to the original python as possible which leads to some problems. Limitations include:

- No imports
- No left side indexing (but I am planning to change that)
- No double indexing
- Runtime errors in the compiled executable
- No declaring new variables inside of if-statements
- No changing variable types inside of if-statements
- Staticly typed function arguments and return types
- No OOP features
- Limited built-in functions

Please let me know if you notice any other limitations.


## Contributing

This Repository is currently not open for Contributing as it is a school project of mine and it will be plagiarism if I include any work that has not been done by myself. 
This is going to change in Summer 2025 when I will have submitted my school project.


## Build process

I am proud to say that the python part of this project has close to no dependencies. The only extern libraries used are itertools and the c++ headers 'iostream', 'variant' and 'vector'. For the C++ part of the project, a basic C++ compiler shoud do the job and in general, just cloning the project and running the main file with the file to compile being the first commandline argument should be enough. C++ Version 17+ is required.
