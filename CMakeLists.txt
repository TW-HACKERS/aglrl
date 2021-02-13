cmake_minimum_required(VERSION 3.10)
project(aglrl)

add_subdirectory(deps/glfw)

include_directories(src
					deps/glfw/include
					deps/glad/include
					deps/glm)

file(GLOB_RECURSE SOURCE_FILES
	 src/*.c
	 src/*.cpp)

file(GLOB_RECURSE HEADER_FILES
	 src/*.h
	 src/*.hpp
	 include/*.h
	 include/*.hpp)

add_executable(aglrl
			   deps/glad/src/glad.c 
			   ${SOURCE_FILES} ${HEADER_FILES})

target_link_libraries(aglrl glfw)