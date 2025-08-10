cmake_minimum_required(VERSION 3.10)
project(MyClispy C)

# Использовать clang, если он доступен
set(CMAKE_C_COMPILER clang)

# Добавить исполняемый файл
add_executable(lispy 
            src/main.c
            src/eval.c
            include/mpc/mpc.c
            )

target_include_directories(lispy PRIVATE include/mpc)

