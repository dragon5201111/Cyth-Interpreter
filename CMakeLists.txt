cmake_minimum_required(VERSION 4.1)
project(Interpreter2 CXX)   # <- use CXX for C++ projects

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

# Only list source files (cpp)
add_executable(Interpreter2
        src/main.cpp
        include/TokenType.h
        include/Token.h
        src/Writer.cpp
        include/Writer.h
        include/Tokenizer.h
        src/Tokenizer.cpp
        include/Reader.h
        src/Reader.cpp
)
