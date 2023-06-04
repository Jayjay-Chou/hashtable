cmake_minimum_required(VERSION 3.25)
project(hashtable C)

set(CMAKE_C_STANDARD 11)

add_executable(hashtable main.c list.h hashtable.h hashfunc.h)
