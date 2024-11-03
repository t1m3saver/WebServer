# /src/LogSystem/CMakeLists.txt

# 声明一个头文件库
add_library(LogSystem INTERFACE)

# 指定头文件路径
target_include_directories(LogSystem INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
