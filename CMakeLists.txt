cmake_minimum_required(VERSION 3.14)

project(ChessAI_Project)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_TOOLCHAIN_FILE C:/Users/nikla/.clion-vcpkg/vcpkg/scripts/buildsystems)

add_executable(${PROJECT_NAME} ChessAI_Project.cpp src/contest/gameclient.cpp src/contest/gameclient.h src/jsoncpp.cpp src/json/json.h)

add_subdirectory(src)
add_subdirectory(test)

find_package(websocketpp CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} src ws2_32 websocketpp::websocketpp )

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