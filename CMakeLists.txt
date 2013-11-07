
#Recipe Spelunker CMake Script

cmake_minimum_required(VERSION 2.8.11)

project(RESPLUNK)

#Set options
set(STATIC_BUILD TRUE CACHE BOOL "Link SFML statically")
set(JSON_ROOT ${RESPLUNK_SOURCE_DIR}/lib/json-parser/ CACHE PATH "Path to json-parser library")
set(LACEWING_ROOT ${RESPLUNK_SOURCE_DIR}/lib/lacewing/ CACHE PATH "Path to lacewing library")

#Get all source files
file(GLOB_RECURSE RESPLUNK_COMMON_SOURCES "src/common/*.cpp")
file(GLOB_RECURSE RESPLUNK_CLIENT_SOURCES "src/client/*.cpp")
file(GLOB_RECURSE RESPLUNK_SERVER_SOURCES "src/server/*.cpp")
file(GLOB_RECURSE RESPLUNK_COMMON_HEADERS "src/common/*.hpp")
file(GLOB_RECURSE RESPLUNK_CLIENT_HEADERS "src/client/*.hpp")
file(GLOB_RECURSE RESPLUNK_SERVER_HEADERS "src/server/*.hpp")
list(APPEND RESPLUNK_COMMON_SOURCES "${JSON_ROOT}/json.c")
list(APPEND RESPLUNK_COMMON_HEADERS "${JSON_ROOT}/json.h")
list(APPEND RESPLUNK_COMMON_HEADERS "${LACEWING_ROOT}/lacewing.h")

#Common - compilation flags & include directories
set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")
include_directories(${JSON_ROOT})
include_directories(${LACEWING_ROOT}/include/)
include_directories("${CMAKE_SOURCE_DIR}/src/common/")
set(LACEWING_LIBRARIES ws2_32 mswsock mpr crypt32 secur32 lacewing)

#Common - Boost
find_package(Boost 1.54.0 COMPONENTS filesystem system REQUIRED)
include_directories(${BOOST_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIR})
 
#Client-only - SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
if(STATIC_BUILD)
	set(SFML_STATIC_LIBRARIES TRUE)
else()
	set(SFML_STATIC_LIBRARIES FALSE)
endif()
find_package(SFML 2 REQUIRED graphics window system audio)
set(client_specific_include_dirs ${client_specific_include_dirs} ${SFML_INCLUDE_DIR} ${SFML_INCLUDE_DIRS})
link_directories(${SFML_LIBRARY_DIR})

#Client-only - OpenGL & GLUT
find_package(OpenGL REQUIRED)
#find_package(GLUT REQUIRED)
set(client_specific_include_dirs ${client_specific_include_dirs} ${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS})
link_directories(${OPENGL_LIBRARY_DIR} ${GLUT_LIBRARY_DIR})

#Common - resources & configuration
if(NOT ${CMAKE_CURRENT_BINARY_DIR} STREQUAL ${PROJECT_SOURCE_DIR})
	file(COPY config/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/config/)
	file(COPY res/	DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/res/)
endif()

#Common - libraries for specific OSes
if(UNIX)
	set(SFML_LIBRARIES pthread ${SFML_LIBRARIES} Xrandr Xext X11 freetype rt)
endif()

#Setup targets
#client
add_executable(resplunk-client
	${RESPLUNK_COMMON_SOURCES}
	${RESPLUNK_CLIENT_SOURCES}
)
target_link_libraries(resplunk-client
	${SFML_LIBRARIES}
	${OPENGL_LIBRARIES}
	${GLUT_LIBRARY}
	${Boost_LIBRARIES}
#	${LACEWING_LIBRARIES}
)
#server
add_executable(resplunk-server
	${RESPLUNK_COMMON_SOURCES}
	${RESPLUNK_SERVER_SOURCES}
)
target_link_libraries(resplunk-server
	${Boost_LIBRARIES}
#	${LACEWING_LIBRARIES}
)

#Setup specific settings
get_target_property(client_include_dirs resplunk-client INCLUDE_DIRECTORIES)
get_target_property(server_include_dirs resplunk-server INCLUDE_DIRECTORIES)
set(client_include_dirs ${client_include_dirs} ${client_specific_include_dirs} "${CMAKE_SOURCE_DIR}/src/client/")
set(server_include_dirs ${server_include_dirs} ${server_specific_include_dirs} "${CMAKE_SOURCE_DIR}/src/server/")
set_target_properties(resplunk-client
	PROPERTIES
	INCLUDE_DIRECTORIES "${client_include_dirs}"
)
set_target_properties(resplunk-server
	PROPERTIES
	INCLUDE_DIRECTORIES "${server_include_dirs}"
)
