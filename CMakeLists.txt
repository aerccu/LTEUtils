
cmake_minimum_required(VERSION 3.10.0)

project(lteutils VERSION 0.1.1)

#set(CMAKE_C_COMPILER "/usr/local/bin/gcc-9")
#set(CMAKE_CXX_COMPILER "/usr/local/bin/g++-9")

# Testing
include(CTest)
enable_testing()

# Required Libs
find_package(PkgConfig)
find_package(OpenMP)
find_package(BLAS REQUIRED)
find_package(LAPACK REQUIRED)
#find_package(FFTW REQUIRED)
find_package(Boost REQUIRED COMPONENTS thread system)

include_directories( ${Boost_INCLUDE_DIR})   

if(OPENMP_FOUND)
    set(CMAKE_C_FLAGS ${OpenMP_C_FLAGS})
    set(CMAKE_CXX_FLAGS ${OpenMP_CXX_FLAGS})
endif()

# Includes
include_directories(${PROJECT_SOURCE_DIR}/include)
