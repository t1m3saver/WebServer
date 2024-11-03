# /src/ServerSrc/CMakeLists.txt

# 声明库
add_library(Server Server.cpp)

# 指定头文件路径
target_include_directories(Server PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
