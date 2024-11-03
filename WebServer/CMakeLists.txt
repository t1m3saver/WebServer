# /CMakeLists.txt

cmake_minimum_required (VERSION 3.10)

project(WebServer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 添加src目录
add_subdirectory(src)
#创建可执行文件
add_executable(WebServer main.cpp)
#链接库
target_link_libraries(WebServer LogSystem Server)
