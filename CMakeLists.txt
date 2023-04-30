cmake_minimum_required(VERSION 3.14)

project(ChessAI_Project)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(${PROJECT_NAME} ChessAI_Project.cpp)

add_subdirectory(components)
add_subdirectory(components_tests)

target_link_libraries(${PROJECT_NAME} components)




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

file(COPY bitboards.txt DESTINATION .)
file(COPY bitboards.txt DESTINATION ./components_tests)
file(COPY bitboards.txt DESTINATION ./Debug)
file(COPY bitboards.txt DESTINATION ./Debug/components_tests)