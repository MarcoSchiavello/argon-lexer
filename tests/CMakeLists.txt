include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.15.2
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

include(GoogleTest)

add_executable(argon-tests
        commentState/commentStateTest.cpp
        lexer/commentRecognitionTest.cpp
        lexer/tokenizationTest.cpp
)

target_include_directories(argon-tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(argon-tests PRIVATE argon GTest::gtest_main)

gtest_discover_tests(argon-tests DISCOVERY_MODE PRE_TEST)