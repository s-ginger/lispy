cmake_minimum_required(VERSION 3.10)
project(lispy C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# Флаги компиляции для MSVC
if(MSVC)
    set(CMAKE_C_FLAGS_DEBUG "/Zi /Od")
    set(CMAKE_C_FLAGS_RELEASE "/O2")
endif()


# Исходники
file(GLOB_RECURSE SOURCES src/*.c include/mpc/*.c)



# Исполняемый файл
add_executable(lispy ${SOURCES})

# Include директории
target_include_directories(lispy PRIVATE include/mpc)

target_compile_definitions(lispy PRIVATE _CRT_SECURE_NO_WARNINGS)