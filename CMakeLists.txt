cmake_minimum_required(VERSION 3.10)

project(CoroutineScheduler VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(CoroutineScheduler 
	src/main.cpp
	src/task.cpp
)

target_include_directories(CoroutineScheduler PUBLIC include)