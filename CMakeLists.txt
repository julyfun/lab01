cmake_minimum_required(VERSION 3.12)
project("lab01")

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

include_directories("include")

add_library(lib STATIC "src/lib.c")
add_executable(task5 "src/task5.c")

target_link_libraries(task5 lib)
