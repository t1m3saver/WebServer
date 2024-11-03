# /src/Utils/CMakeLists.txt

# 声明库
add_library(Utils fs.cpp)

# 指定头文件路径
target_include_directories(Utils PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})