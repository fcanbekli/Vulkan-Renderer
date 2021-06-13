project(Sandbox)

cmake_minimum_required (VERSION 3.8)

set(CompilerFlags
        CMAKE_CXX_FLAGS
        CMAKE_CXX_FLAGS_DEBUG
        CMAKE_CXX_FLAGS_RELEASE
        CMAKE_C_FLAGS
        CMAKE_C_FLAGS_DEBUG
        CMAKE_C_FLAGS_RELEASE
        )


set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(INC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib")

set(HEADERS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../Hypatia/include/headers")
set(VENDOR_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../Hypatia/include/vendor")
include_directories( ${INC_DIR} ${HEADERS_DIR} ${VENDOR_DIR})

#Add the given directories to those the compiler uses to search for include files.
include_directories( ${INC_DIR} )

FILE(GLOB_RECURSE SOURCES "${SRC_DIR}/*.cpp" "${INC_DIR}/*.cpp")
FILE(GLOB_RECURSE INCLUDES "${INC_DIR}/*.h" "${INC_DIR}/*.hpp")

add_executable(Sandbox ${SOURCES} ${INCLUDES})

if(MSVC)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")
endif(MSVC)

target_link_libraries (Sandbox Hypatia d3d11.lib)