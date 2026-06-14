cmake_minimum_required(VERSION 3.20)
project(argon-lexer CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(argon
        main.cpp
        src/lexer.cpp
        src/generators/additionTokenGenerator.cpp
        src/generators/IntTokenGenerator.cpp
        src/utils.cpp
)

target_include_directories(argon PRIVATE
        include
        include/tokens
        include/generators
)

target_compile_options(argon PRIVATE -Wall -Wextra)
