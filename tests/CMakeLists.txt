include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.13.0.zip
)
FetchContent_MakeAvailable(googletest)
enable_testing()
include(GoogleTest)

add_executable(playtest.exe play-test.cpp)
add_executable(evaltest.exe eval-test.cpp)
add_executable(io-test.exe io-test.cpp)
add_executable(dynamic-test.exe dynamic-programming-test.cpp)
add_executable(hash-test.exe hash-test.cpp)

target_link_libraries(playtest.exe TripleTriad gtest_main)
target_link_libraries(evaltest.exe TripleTriad gtest_main)
target_link_libraries(io-test.exe TripleTriad gtest_main)
target_link_libraries(dynamic-test.exe TripleTriad gtest_main)
target_link_libraries(hash-test.exe TripleTriad gtest_main)

add_test(NAME PlayTest COMMAND playtest.exe)
add_test(NAME LongTest COMMAND evaltest.exe)
add_test(NAME IO-Test COMMAND io-test.exe)
add_test(NAME Dynamic-Test COMMAND dynamic-test.exe)
add_test(NAME Hash-Test COMMAND hash-test.exe)
