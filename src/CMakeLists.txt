cmake_minimum_required(VERSION 3.4)

project(squirrel_holocast_protocol)
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

set(COMMON_SRC
    "main.c"
    )

include_directories(
    "."
    )

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_STANDARD 11)


add_executable(${CMAKE_PROJECT_NAME} ${COMMON_SRC})

target_link_libraries(${CMAKE_PROJECT_NAME}
    dl
    )

add_library(fun1 SHARED lib1.c )
add_library(fun2 SHARED lib2.c )


install(TARGETS ${CMAKE_PROJECT_NAME} RUNTIME DESTINATION bin)
