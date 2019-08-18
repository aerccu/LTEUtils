
cmake_minimum_required(VERSION 3.10.0)

project(lteutils VERSION 0.1.1)

# Testing
include(CTest)
enable_testing()

# Required Libs
find_package(PkgConfig)
find_package(OpenMP)
find_package(BLAS REQUIRED)
find_package(LAPACK REQUIRED)
find_package(FFTW REQUIRED)
find_package(Boost REQUIRED COMPOMENTS thread system)