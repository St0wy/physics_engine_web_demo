cmake_minimum_required(VERSION 3.26)

project(physics_engine_web_demo)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if(NOT CMAKE_BUILD_TYPE)
	message("Build Type not set, defaulting to Debug...")
	set(CMAKE_BUILD_TYPE Debug)
endif()

include(cmake/SystemLink.cmake)
include(cmake/DownloadCpm.cmake)

cpmaddpackage(
	NAME
	raylib
	GIT_TAG
	4.5.0
	GITHUB_REPOSITORY
	raysan5/raylib
	OPTIONS
	"BUILD_SHARED_LIBS OFF"
	EXCLUDE_FROM_ALL
	SYSTEM
)

cpmaddpackage(
	NAME
	StowyPhysicsEngine
	GIT_TAG
	main
	GITHUB_REPOSITORY
	St0wy/StowyPhysicsEngine
	OPTIONS
	"BUILD_SHARED_LIBS OFF"
	EXCLUDE_FROM_ALL
	SYSTEM
)

add_executable(
	physics_engine_web_demo
	include/circle.hpp
	include/physics_engine_demo.hpp
	include/rectangle.hpp
	src/circle.cpp
	src/main.cpp
	src/physics_engine_demo.cpp
	src/rectangle.cpp
)
target_include_directories(physics_engine_web_demo PRIVATE include/)
target_link_system_libraries(physics_engine_web_demo PRIVATE raylib StowyPhysicsEngine)

if(APPLE)
	target_link_libraries(${PROJECT_NAME} "-framework IOKit")
	target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
	target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()

if(EMSCRIPTEN)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s USE_GLFW=3 -s ASSERTIONS=1 -s WASM=1 -s ASYNCIFY")
	set(CMAKE_EXECUTABLE_SUFFIX ".html") # This line is used to set your executable to build with the emscripten html
	# template so that you can directly open it.
endif()
