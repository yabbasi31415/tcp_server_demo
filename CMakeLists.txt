cmake_minimum_required(VERSION 3.10)  # CMake version check
project(async_server)               # Create project 
set(CMAKE_CXX_STANDARD 17)            # Enable c++17 standard

# Add async_server.cpp file of project root directory as source file
set(SOURCE_FILES async_server.cpp)

# Add executable target with source files listed in SOURCE_FILES variable

set(Boost_USE_STATIC_LIBS OFF) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF) 
find_package(Boost 1.65.1 COMPONENTS filesystem regex) 

if(Boost_FOUND)
    add_executable(async_server ${SOURCE_FILES}) 
    target_link_libraries(async_server Boost::filesystem Boost::regex)
endif()
