include_directories(${CMAKE_CURRENT_LIST_DIR}/include)

#遍历添加文件
FILE(GLOB_RECURSE SRC_LIST ${CMAKE_CURRENT_LIST_DIR}/*.c)
FILE(GLOB_RECURSE HEADER_LIST ${CMAKE_CURRENT_LIST_DIR}/*.h)

foreach(_file ${SRC_LIST})
	list(APPEND SRC_FILE_LIST ${_file})
endforeach()

foreach(_file ${HEADER_LIST})
	list(APPEND HEADER_FILE_LIST ${_file})
endforeach()

foreach(file_name ${SRC_FILE_LIST})
	make_source_group(${file_name})
endforeach()

foreach(file_name ${HEADER_FILE_LIST})
	make_source_group(${file_name})
	auto_include_dir(${file_name})
endforeach()