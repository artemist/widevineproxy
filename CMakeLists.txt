cmake_minimum_required(VERSION 3.12)
project(widevineproxy CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 11)

add_compile_options(-fvisibility=hidden)

add_library(widevineproxy SHARED base_interface.cpp loader.cpp loader.h extern/cdmapi.h globals.cpp cdmproxy.cpp cdmproxy.h printing.cpp printing.h)