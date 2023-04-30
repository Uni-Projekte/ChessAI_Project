cmake_minimum_required(VERSION 3.14)

project(Component_Tests VERSION 1.0)



# Now simply link against gtest or gtest_main as needed. Eg
add_executable(${PROJECT_NAME} Board_Tests.cpp)
target_link_libraries(${PROJECT_NAME} components gtest_main)
add_test(NAME Board_Tests COMMAND ${PROJECT_NAME})

#add_custom_command(
#	TARGET ${PROJECT_NAME}
#	COMMENT "Run tests"
#	POST_BUILD
#	COMMAND ${PROJECT_NAME}
#)