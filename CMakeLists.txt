set(PROJECT_NAME "truck-dispatch")

set(CMAKE_BUILD_TYPE Release)

cmake_minimum_required(VERSION 4.00)

project(${PROJECT_NAME}
    VERSION 1.0
    LANGUAGES CXX
)

add_executable(${PROJECT_NAME}
    src/main.cpp
    src/service.cpp
    src/controller/controller.cpp
    src/controller/add-shipment.cpp
    src/controller/add-truck.cpp
    src/in-memory-repository.cpp
)

find_package(Drogon REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE Drogon::Drogon)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_23)
