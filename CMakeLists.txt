#CAMKE 最低版本号要求
cmake_minimum_required(VERSION 2.8)

#将文件归组
function(make_source_group file_name)
	#判断是否是绝对路径
	if(IS_ABSOLUTE ${file_name})
		#提取相对路劲
		file(RELATIVE_PATH rel_path ${CMAKE_CURRENT_SOURCE_DIR} ${file_name})
	else()
		set(rel_path ${file_name})
	endif()
	
	#得到文件的路劲部分
	get_filename_component(_path ${rel_path} PATH)
	#替换“/” - "\\"
	string(REPLACE "/" "\\" group_path ${_path})
	
	#分组
	source_group(${group_path} FILES ${file_name})
endfunction(make_source_group)

#项目名字
project(Aurora)


include(./3rdparty/glfw3/CMakeLists.txt)

#遍历添加文件
FILE(GLOB_RECURSE SRC_LIST "src/*.cpp")

#list(APPEND SRC_LIST 
#	src/main.cpp
#	src/test/test.cpp
#)

foreach(file_name ${SRC_LIST})
	make_source_group(${file_name})
endforeach()



#find_library(glfw3)
LINK_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/glfw3)
#include_directories(${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/glfw3/include)

#指定生成目标
add_executable(Aurora ${SRC_LIST})

#添加子目录
target_link_libraries(Aurora "glfw3")
