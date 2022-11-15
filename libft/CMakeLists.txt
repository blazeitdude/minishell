cmake_minimum_required(VERSION 3.22)
project(libft)

set(CMAKE_C_STANDARD 99)

file(GLOB SOURCES sources/*.c)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Werror -c")
add_library(${PROJECT_NAME} STATIC ${SOURCES})