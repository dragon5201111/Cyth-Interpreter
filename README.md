# Cyth Interpreter Version 0.1.1
# Contents
- [Build Instructions](#build-instructions)
- [Documentation](#documentation)
- [Usage](#usage)
# Build Instructions
Before building, make sure you have the following installed on your native machine:

- CMake (i.e., Version 3.22-4.1.2)
- C/C++ Compiler (e.g., gcc, clang, etc.)
- make package (i.e., if you are on a Unix based system)

Navigate to the project root directory (e.g., where src lives) and run the following based on your
OS.
### Building On Linux:
```
mkdir build
cd build
cmake ..
make
```
### Building On Windows:
```
mkdir build
cd build
cmake ..
cmake --build .
```
This will install as `Cyth`.

### Build Notes:
- The build process above was tested on two machines. One Windows (i.e., 11 Home) 
    and Linux (i.e., Version 5.15.0-164-generic, Ubuntu 22.04.5) machine.
# Usage
# Documentation
Documentation on Cyth is found at this [<u>**link**</u>](doc/cyth-documentation.md), and is updated regularly.

