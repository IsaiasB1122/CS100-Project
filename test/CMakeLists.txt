cmake_minimum_required(VERSION 3.16)


add_subdirectory(googletest)

add_executable(run_tests
	test_fileio.cpp

	../src/_command_index.cpp
	test_commands.cpp
)

TARGET_LINK_LIBRARIES(run_tests gmock gtest gtest_main cataboard_lib libstdc++fs.a)
TARGET_COMPILE_DEFINITIONS(run_tests PRIVATE gtest_disable_pthreads=ON)