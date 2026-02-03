cmake_minimum_required(VERSION 3.22..4.1.2)
project(Interpreter2 CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
    src/main.cpp
    src/Writer.cpp
    src/Tokenizer.cpp
    src/Reader.cpp
    src/Parser.cpp
    src/AstPrinter.cpp
    src/Env.cpp
    src/Interpreter.cpp
    src/Call.cpp
)

add_executable(${PROJECT_NAME}  ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
