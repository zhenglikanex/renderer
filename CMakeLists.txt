#CAMKE 最低版本号要求
cmake_minimum_required(VERSION 2.8)

#项目名字
project(Aurora)

set(SRC_LIST)
set(HEADER_LIST)

#添加camke模块
include(cmake/common.cmake)

include(./3rdparty/glfw3/CMakeLists.txt)
include(3rdparty/glad/CMakeLists.txt)
include(3rdparty/stb/CMakeLists.txt)

#添加头文件引用目录
#include_directories(./3rdparty/glad/include)

#添加h、hpp、c、cpp文件
add_dir_header_and_src(${CMAKE_CURRENT_SOURCE_DIR}/src)


#find_library(glfw3)
LINK_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/glfw3)
#include_directories(${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/glfw3/include)

#指定生成目标
add_executable(Aurora ${SRC_LIST} ${HEADER_LIST})

#设置VS工作目录
set_target_properties(Aurora PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/resources)

#添加库
target_link_libraries(Aurora "glfw3")
target_link_libraries(Aurora "opengl32")
