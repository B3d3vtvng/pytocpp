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
- Basic I/O operations (read, print)
- Basic built-in functions (len(), type casting, ...)
- 64-bit integers and 128-bit floats

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
- Custom Runtime errors in the compiled executable to enforce full type safety
- No OOP features
- Limited built-in function support

Please let me know if you notice any other limitations.


## Build process

I am proud to say that the python part of this project has close to no dependencies. The only extern libraries used are itertools, sys and the c++ headers 'iostream', 'variant' and 'vector'. For the C++ part of the project, a basic C++ compiler should do the job and in general, just cloning the project and running the main file with the file to compile being the first commandline argument should be enough. C++ Version 17+ is required.
