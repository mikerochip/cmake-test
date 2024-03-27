cmake_minimum_required(VERSION 3.28.1)

# Mac as of Sonoma macOS 14.3.1 is causing CMake to faile to compile a simple test program.
# This works around it. See https://stackoverflow.com/a/53635241/720021
set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")

project(ErgonomicCpp)

set(CMAKE_CXX_STANDARD 17)

find_package(CLI11 REQUIRED)
find_package(fmt REQUIRED)
find_package(Poco REQUIRED)

include_directories(
  src/Libraries
)
add_subdirectory(
  src/Libraries/MyLibrary
)
add_executable(${PROJECT_NAME}
  src/App/main.cpp
  src/App/MyApp/Foo.cpp
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

target_link_libraries(${PROJECT_NAME} MyLibrary CLI11::CLI11 fmt::fmt Poco::Poco)
