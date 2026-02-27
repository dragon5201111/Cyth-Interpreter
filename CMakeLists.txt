cmake_minimum_required(VERSION 3.22..4.1.2)
project(Cyth CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
    src/main.cpp
    src/io/Writer.cpp
    src/token/Tokenizer.cpp
    src/io/Reader.cpp
    src/ast/Parser.cpp
    src/ast/AstPrinter.cpp
    src/interpreter/Env.cpp
    src/interpreter/Interpreter.cpp
    src/interpreter/Call.cpp
    src/value/Value.cpp
    src/value/Num.cpp
    src/io/Preproc.cpp
)

add_executable(${PROJECT_NAME}  ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
