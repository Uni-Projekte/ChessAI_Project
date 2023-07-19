cmake_minimum_required(VERSION 3.14)

project(tests VERSION 1.0)

#SET(GCC_COVERAGE_COMPILE_FLAGS "-O2 -g")
#SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")

# Now simply link against gtest or gtest_main as needed. Eg
add_executable(${PROJECT_NAME} Helper_Tests.cpp Board_Tests.cpp Pieces_Tests.cpp )
target_link_libraries(${PROJECT_NAME} src gtest_main gmock)
add_test(NAME Board_Tests COMMAND ${PROJECT_NAME})

#add_custom_command(
#	TARGET ${PROJECT_NAME}
#	COMMENT "Run tests"
#	POST_BUILD
#	COMMAND ${PROJECT_NAME}
#)