set(PROJECT_NAME "truck-dispatch")
set(TEST_NAME "truck-dispatch-tests")

cmake_minimum_required(VERSION 4.00)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_BUILD_TYPE Release)

set(SRC_MAIN "src/main/c++")
set(SRC_TEST "src/test/c++")

project(${PROJECT_NAME}
	VERSION 1.0
    	LANGUAGES CXX
)

add_executable(${PROJECT_NAME}
	${SRC_MAIN}/main.cpp
	${SRC_MAIN}/config.cpp
	${SRC_MAIN}/service.cpp
	${SRC_MAIN}/controller/controller.cpp
	${SRC_MAIN}/controller/add-shipment.cpp
	${SRC_MAIN}/controller/add-truck.cpp
	${SRC_MAIN}/repository/postgresql.cpp
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
		${SRC_TEST}/service/cant-add-shipment.cpp
		${SRC_TEST}/service/no-truck.cpp
		${SRC_TEST}/service/truck-found.cpp
		${SRC_TEST}/controller/add-truck/truck-waits.cpp
		${SRC_MAIN}/service.cpp
		${SRC_MAIN}/controller/controller.cpp
		${SRC_MAIN}/controller/add-truck.cpp		
	)
	
    	target_link_libraries(${TEST_NAME}
        	PRIVATE Catch2::Catch2WithMain
        	PRIVATE Drogon::Drogon
    	)	

	target_compile_features(${TEST_NAME} PRIVATE cxx_std_23)

    	include(Catch)
    	catch_discover_tests(${TEST_NAME})
	
	
endif()
