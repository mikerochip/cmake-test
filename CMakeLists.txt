cmake_minimum_required(VERSION 3.13)

# Mac as of Sonoma macOS 14.3.1 is causing CMake to faile to compile a simple test program.
# This works around it. See https://stackoverflow.com/a/53635241/720021
set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")

project(ErgonomicCpp)

set(CMAKE_CXX_STANDARD 14)

# this check is needed for CLion to not generate an error
if(EXISTS ${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    conan_basic_setup()
else()
    message(WARNING "conanbuildinfo.cmake doesn't exist, you have to run conan install first")
endif()

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

target_link_libraries(${PROJECT_NAME} MyLibrary ${CONAN_LIBS})
