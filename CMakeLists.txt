cmake_minimum_required(VERSION 3.12)
project(widevineproxy C)

set(CMAKE_C_STANDARD 11)

add_library(widevineproxy SHARED core.c core.h loader.c)