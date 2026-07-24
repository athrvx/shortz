cmake_minimum_required(VERSION 3.20)

project(Shortz VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Drogon CONFIG REQUIRED)

add_executable(shortz
    src/main.cpp
    controllers/HealthController.cpp
)

target_link_libraries(shortz PRIVATE Drogon::Drogon)