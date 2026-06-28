cmake_minimum_required(VERSION 3.20)
project(argon-lexer CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(argon STATIC
        src/lexer.cpp
        src/utils.cpp
        src/generators/IntTokenGenerator.cpp
        src/generators/additionTokenGenerator.cpp
        src/generators/divisionTokenGenerator.cpp
        src/commentState/noCommentState.cpp
        src/commentState/initCommentState.cpp
        src/commentState/mlCommentState.cpp
        src/commentState/lineCommentState.cpp
        src/commentState/endMlCommentState.cpp
        src/commentState/skipCharCommentState.cpp
)

target_include_directories(argon PUBLIC
        include
        include/tokens
        include/generators
        include/commentState
)

target_compile_options(argon PRIVATE -Wall -Wextra)

enable_testing()
add_subdirectory(tests)
