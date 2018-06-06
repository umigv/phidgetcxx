cmake_minimum_required(VERSION 3.1.3)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(phidgetcxx CXX)

include_directories(include/)

find_library(PHIDGET22_LIBRARIES NAMES phidget22 libphidget22.a libphidget22.so)

set(SOURCES src/channel_class.cpp src/channel_subclass.cpp src/common.cpp
            src/device_class.cpp src/device_id.cpp src/error_event_code.cpp
            src/exception.cpp src/phidget.cpp src/retained_phidget.cpp
            src/return_code.cpp src/static.cpp)

add_library(phidgetcxx ${SOURCES})
target_link_libraries(phidgetcxx ${PHIDGET22_LIBRARIES})

add_executable(test_return_code test/catch_main.cpp test/return_code.cpp)
target_link_libraries(test_return_code phidgetcxx)

add_executable(test_phidget test/catch_main.cpp test/phidget.cpp)
target_link_libraries(test_phidget phidgetcxx)
