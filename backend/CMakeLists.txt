cmake_minimum_required(VERSION 3.20)

project(Shortz VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Drogon CONFIG REQUIRED)
find_package(unofficial-sqlite3 CONFIG REQUIRED)

file(GLOB_RECURSE SOURCES
    src/*.cpp
    controllers/*.cpp
    services/*.cpp
    repositories/*.cpp
    database/*.cpp
    utils/*.cpp
)

add_executable(shortz ${SOURCES})

target_link_libraries(shortz PRIVATE
    Drogon::Drogon
    unofficial::sqlite3::sqlite3
)

target_include_directories(shortz PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/utils
    ${CMAKE_CURRENT_SOURCE_DIR}/controllers
    ${CMAKE_CURRENT_SOURCE_DIR}/services
    ${CMAKE_CURRENT_SOURCE_DIR}/repositories
    ${CMAKE_CURRENT_SOURCE_DIR}/database
    ${CMAKE_CURRENT_SOURCE_DIR}/models
)