# CMake entry point
cmake_minimum_required (VERSION 3.0)
project (BasicOpenGLGame)

find_package(OpenGL REQUIRED)


if( CMAKE_BINARY_DIR STREQUAL CMAKE_SOURCE_DIR )
    message( FATAL_ERROR "Please select another Build Directory ! (and give it a clever name, like bin_Visual2012_64bits/)" )
endif()
if( CMAKE_SOURCE_DIR MATCHES " " )
	message( "Your Source Directory contains spaces. If you experience problems when compiling, this can be the cause." )
endif()
if( CMAKE_BINARY_DIR MATCHES " " )
	message( "Your Build Directory contains spaces. If you experience problems when compiling, this can be the cause." )
endif()

#***************** TO BE ADDED FOR C++ COMPILER *****************
cmake_minimum_required(VERSION 3.1.0)   # for CMAKE_CXX_STANDARD
set (CMAKE_CXX_STANDARD 11)


# Compile external dependencies 
add_subdirectory (external)

# On Visual 2005 and above, this module can set the debug working directory
cmake_policy(SET CMP0026 OLD)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/external/rpavlik-cmake-modules-fe2273")
include(CreateLaunchers)
include(MSVCMultipleProcessCompile) # /MP

if(INCLUDE_DISTRIB)
add_subdirectory(distrib)
endif(INCLUDE_DISTRIB)



include_directories(
	external/AntTweakBar-1.16/include/
	external/glfw-3.1.2/include/GLFW/
	external/glm-0.9.7.1/
	external/glew-1.13.0/include/
	external/assimp-3.0.1270/include/
	external/bullet-2.81-rev2613/src/
	.
)

set(ALL_LIBS
	${OPENGL_LIBRARY}
	glfw
	GLEW_1130
)

add_definitions(
	-DTW_STATIC
	-DTW_NO_LIB_PRAGMA
	-DTW_NO_DIRECT3D
	-DGLEW_STATIC
	-D_CRT_SECURE_NO_WARNINGS
)
FILE(GLOB SRC_FILES "basicgame/*.hlsl")
set_source_files_properties(${SRC_FILES} PROPERTIES VS_TOOL_OVERRIDE "None")

add_executable(basicgame
	basicgame/View.cpp
	basicgame/View.hpp
	basicgame/Model.cpp
	basicgame/Model.hpp
	basicgame/Controller.cpp
	basicgame/Controller.hpp
	basicgame/GameObject.cpp
	basicgame/GameObject.hpp
	basicgame/global.hpp
	basicgame/playground.cpp
	common/shader.cpp
	common/shader.hpp
	common/texture.cpp
	common/texture.hpp
	common/controls.cpp
	common/controls.hpp
	common/objloader.cpp
	common/objloader.hpp	
	common/vboindexer.cpp
	common/vboindexer.hpp
	common/text2D.cpp
	common/text2D.hpp
	${SRC_FILES}

		
)
# Xcode and Visual working directories
set_target_properties(basicgame PROPERTIES COMPILE_DEFINITIONS "USE_ASSIMP")
set_target_properties(basicgame PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/basicgame/")
create_target_launcher(basicgame WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/basicgame/")
target_link_libraries(basicgame
	${ALL_LIBS}
	assimp
)
SOURCE_GROUP(shaders REGULAR_EXPRESSION ".*hlsl*" )
SOURCE_GROUP(common REGULAR_EXPRESSION ".*/common/.*" )

#add_custom_command(
#   TARGET playground POST_BUILD
#   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/playground${CMAKE_EXECUTABLE_SUFFIX}" "${CMAKE_CURRENT_SOURCE_DIR}/playground/"
#)

