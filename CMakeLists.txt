cmake_minimum_required(VERSION 3.10)

project(CoroutineScheduler VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(CoroutineScheduler STATIC
	src/task.cpp
	include/task.h
)

target_include_directories(CoroutineScheduler PUBLIC include)