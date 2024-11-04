# CMakeLists.txt

cmake_minimum_required(VERSION 3.10)

project(WebServer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

# 查找其他非std库
find_package(yaml-cpp REQUIRED)

# 创建可执行文件
add_executable(WebServer main.cpp)

# 添加src目录
add_subdirectory(src)

# 链接库
target_link_libraries(WebServer LogSystem Server yaml-cpp)
