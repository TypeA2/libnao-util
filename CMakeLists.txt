# CMakeList.txt : CMake project for libnao-util, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("libnao-util")

# Add source to this project's executable.
add_executable (libnao-util "libnao-util.cpp" "libnao-util.h")

# TODO: Add tests and install targets if needed.
