cmake_minimum_required(VERSION 3.19)
set(CMAKE_CXX_STANDARD 14)

project(TeleBook)


INCLUDE_DIRECTORIES(./lib include)

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
    add_compile_options("$<$<C_COMPILER_ID:MSVC>:/GBK>")
    add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/GBK>")
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -finput-charset=GBK -fexec-charset=GBK")  #中文输出不乱码
endif()

AUX_SOURCE_DIRECTORY(src/ SRC)

add_library(AllFunctions ${SRC}  )
set_target_properties(AllFunctions PROPERTIES LINKER_LANGUAGE CXX)

add_executable(TeleBook main.cpp )
target_link_libraries(TeleBook AllFunctions)

add_executable(Test Test.cpp )
add_executable(ClionTest ClionTest.cpp )