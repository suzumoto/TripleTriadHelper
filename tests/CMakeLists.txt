include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.13.0.zip
)
FetchContent_MakeAvailable(googletest)
enable_testing()
include(GoogleTest)

add_executable(test.exe test.cpp)
add_executable(playtest.exe play-test.cpp)
target_link_libraries(test.exe TripleTriad)
target_link_libraries(playtest.exe TripleTriad gtest_main)

add_test(NAME PlayTest COMMAND playtest.exe)
