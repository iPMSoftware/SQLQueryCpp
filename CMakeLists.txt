cmake_minimum_required(VERSION 3.14)
project(my_project)

# GoogleTest requires at least C++11
set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/ea55f1f52c489535f0d3b583c81529762c9cb5ea.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
  sql_query_test
  sql_query_test.cc
)

target_link_libraries(
  sql_query_test
  gtest_main
)

include(GoogleTest)
gtest_discover_tests(sql_query_test)

