cmake_minimum_required(VERSION 3.14)

project(ChessAI_Project)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(${PROJECT_NAME} ChessAI_Project.cpp src/contest/gameclient.cpp src/contest/gameclient.h)

add_subdirectory(src)
add_subdirectory(test)

find_package(jsoncpp CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} src JsonCpp::JsonCpp)

if(NOT googletest)
	include(FetchContent)
	FetchContent_Declare(
			googletest
			# Specify the commit you depend on and update it regularly.
			URL https://github.com/google/googletest/archive/refs/heads/main.zip
	)
	# For Windows: Prevent overriding the parent project's compiler/linker settings
	set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
	FetchContent_MakeAvailable(googletest)
endif()