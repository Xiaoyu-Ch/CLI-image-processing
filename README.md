# CLI-image-processing
C++ image processing project that reads, manipulates, and writes TGA image files.  Implements blending algorithms, channel operations, and a command-line interface.hardest project of COP3503


# Image Processing Project (C++)

**Course:** COP3503C – Programming Fundamentals II  
**Institution:** University of Florida  

## Overview
This project implements an image processing system in C++ that can read, manipulate, and write **TGA binary image files**. It supports multiple manipulation algorithms and a custom command-line interface (CLI), showcasing skills in file I/O, algorithm design, memory management, and software engineering best practices.

The project was completed in two milestones:

1. **Milestone 1 – Image Manipulations**
   - Implemented 10 core image operations such as multiply, subtract, screen, overlay, channel scaling, clamping, splitting/combining channels, and flipping.
   - Designed reusable functions to operate on TGA pixel data.
   - Developed a `Makefile` for streamlined building and testing.

2. **Milestone 2 – Command-Line Interface**
   - Extended the program with a CLI to let users specify operations dynamically.
   - Supported chaining multiple operations on the fly.
   - Implemented robust error handling and validation of arguments.

##  Features
- Read/write **binary TGA files**
- Image blending algorithms: Multiply, Screen, Overlay, Subtract
- Channel manipulation: add, scale, isolate
- File operations: split channels, combine RGB layers, flip image
- CLI-based task execution with argument validation
- Portable across Unix-like systems with `make`

## Tech Stack
- **Language:** C++11  
- **Build System:** Makefile  
- **Testing:** Manual diff checks and binary file comparisons  
- **Environment:** Compatible with Linux/Unix (tested on CISE machines at UF)

## Usage
```bash
# Build the project
make

# Run CLI
./project2.out output/out.tga input/car.tga multiply input/pattern1.tga
