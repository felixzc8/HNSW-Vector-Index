cmake_minimum_required(VERSION 3.16)
project(hnsw_cpp CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -march=native -funroll-loops")

# Export compile_commands.json so the IDE/clangd resolves include paths.
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(hnsw_core
  src/dataset.cpp
  src/brute_force.cpp
  src/nsw.cpp
  src/hnsw.cpp
)
target_include_directories(hnsw_core PUBLIC include)

add_executable(hnsw src/main.cpp)
target_link_libraries(hnsw PRIVATE hnsw_core)

enable_testing()
add_executable(test_brute_force tests/test_brute_force.cpp)
target_link_libraries(test_brute_force PRIVATE hnsw_core)
add_test(NAME brute_force COMMAND test_brute_force)
