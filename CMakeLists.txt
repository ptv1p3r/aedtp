cmake_minimum_required(VERSION 3.6)
project(aedtp)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c tree.c tree.h treeType.h item.c item.h)
add_executable(aedtp ${SOURCE_FILES})