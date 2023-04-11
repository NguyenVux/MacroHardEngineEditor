cmake_minimum_required(VERSION 3.24)
project(glad)
set(CMAKE_CXX_STANDARD 17)

add_library(${PROJECT_NAME} STATIC 
	"src/gl.c" 
	"src/wgl.c" 
	"include/glad/wgl.h"
	"include/glad/gl.h"
	"include/KHR/khrplatform.h"
)

target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_link_libraries(${PROJECT_NAME} "opengl32.lib")