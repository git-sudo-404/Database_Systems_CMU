
# Specify the minimum version required 
cmake_minimum_required(VERSION 3.10)

#define the project name
project(Task1)

#Tell the cmake to create an executable , and list the source files needed 

add_executable(t1 
                murmurhash/MurmurHash3.cpp
                Task1/hyperloglog.cpp  
                Task1/main.cpp
)

add_executable(
                t2
                murmurhash/MurmurHash3.cpp 
                Task2/hyperloglog_presto.cpp 
                Task2/main.cpp 
)

#Tell the compiler where to look for header files 

target_include_directories(t1 PRIVATE 
                            ${CMAKE_CURRENT_SOURCE_DIR}/Task1
                            ${CMAKE_CURRENT_SOURCE_DIR}/murmurhash 
)

target_include_directories(t2 PRIVATE
                            ${CMAKE_CURRENT_SOURCE_DIR}/Task2
                            ${CMAKE_CURRENT_SOURCE_DIR}/murmurhash 
)

# Specify the C++ standard to use
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
