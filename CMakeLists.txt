cmake_minimum_required(VERSION 3.30.1)


project(monitoring LANGUAGES CXX)

find_package(ftxui 5 REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(JSONCPP REQUIRED jsoncpp)

include_directories(${JSONCPP_INCLUDE_DIRS})

#set(CMAKE_BUILD_TYPE Debug)
#set(CMAKE_BUILD_TYPE Release)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++23")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

file(GLOB
          CPPS "*.cpp")

add_executable(${PROJECT_NAME} ${CPPS})
target_link_libraries(${PROJECT_NAME}
PRIVATE ftxui::screen
PRIVATE ftxui::dom
PRIVATE ${JSONCPP_LIBRARIES} 
)
