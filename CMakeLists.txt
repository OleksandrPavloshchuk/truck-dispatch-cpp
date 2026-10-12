set(PROJECT_NAME "truck-dispatch")
set(TEST_NAME "truck-dispatch-tests")

cmake_minimum_required(VERSION 4.00)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_BUILD_TYPE Release)

project(${PROJECT_NAME}
	VERSION 1.0
    	LANGUAGES CXX
)

add_executable(${PROJECT_NAME}
	src/main.cpp
	src/config.cpp
	src/service.cpp
	src/controller/controller.cpp
	src/controller/add-shipment.cpp
	src/controller/add-truck.cpp
	src/repository/postgresql.cpp
)

find_package(Drogon REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE Drogon::Drogon)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_23)

target_compile_options(${PROJECT_NAME} PRIVATE
	-Wall
	-Wextra
	-Wpedantic
	-Wshadow
)

include(CTest)

if(BUILD_TESTING)

	find_package(Catch2 3 REQUIRED)
	
	add_executable(${TEST_NAME}
		tests/service/cant-add-shipment.cpp
		src/service.cpp
	)
	
    	target_link_libraries(${TEST_NAME}
        	PRIVATE Catch2::Catch2WithMain
    	)	

	target_compile_features(${TEST_NAME} PRIVATE cxx_std_23)

    	include(Catch)
    	catch_discover_tests(${TEST_NAME})
	
	
endif()
