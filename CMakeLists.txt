# 1.cmake version，指定cmake版本
cmake_minimum_required(VERSION 3.19)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -fexec-charset=GBK")    #中文输出不乱码
set(CMAKE_CXX_STANDARD 14)

# 2.project name，指定项目的名称，一般和项目的文件夹名称对应
project(TeleBook)

# 3.head file path，头文件目录
INCLUDE_DIRECTORIES(lib/. include)

# 添加 src 子目录
# add_subdirectory(src)

# set environment variable，设置环境变量，编译用到的源文件全部都要放到这里，否则编译能够通过，但是执行的时候会出现各种问题，比如"symbol lookup error xxxxx , undefined symbol"
# SET(library ${DIR_SRCS})

# 4.设置源文件
SET(sources
        src/Bucket.cpp
        src/Dire_Page.cpp
        Src/IOFile.cpp
        src/People.cpp
        src/Key.cpp)
# 5.设置头文件
SET(headers
        lib/Bucket.h
        lib/Dire_Page.h
        lib/IOFile.h
        lib/People.h
        lib/Key.h
        "G:/mingw64/include"
        )
AUX_SOURCE_DIRECTORY(. SRC)

# 6.创建静态库
add_library(AllFunctions ${sources} ${headers})
set_target_properties(AllFunctions PROPERTIES LINKER_LANGUAGE CXX)

# 7.add executable file，添加要编译的可执行文件
# link_libraries(libraryFunctions AllFunctions)
add_executable(TeleBook main.cpp)
target_link_libraries(TeleBook AllFunctions)


# 7.add link library，添加可执行文件所需要的库，比如我们用到了libm.so（命名规则：lib+name+.so），就添加该库的名称
add_executable(Test Test.cpp)
add_executable(ClionTest ClionTest.cpp)