project(Hypatia)

option(USE_GL "Use_GL" OFF)
option(USE_VULKAN "USE_VULKAN" ON)


if (USE_GL)
  MESSAGE(STATUS "USE_GL")
  add_definitions(-DUSE_GL)
endif()

if (USE_VULKAN)
  MESSAGE(STATUS "USE_VULKAN")
  add_definitions(-DUSE_VULKAN)
endif()


find_package(Vulkan REQUIRED)

cmake_minimum_required (VERSION 3.8)
set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(HEADERS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include/headers")
set(VENDOR_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include/vendor")
set(LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib")

#Add the given directories to those the compiler uses to search for include files.

include_directories( ${HEADERS_DIR} ${VENDOR_DIR})
FILE(GLOB_RECURSE SOURCES  "${SRC_DIR}/*.cpp")
FILE(GLOB_RECURSE INCLUDES "${HEADERS_DIR}/*.h")


add_library(Hypatia STATIC ${SOURCES} ${INCLUDES})
target_precompile_headers(Hypatia PUBLIC "${HEADERS_DIR}/pch.h")

if(MSVC)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")
endif(MSVC)

target_link_libraries(${PROJECT_NAME} Vulkan::Vulkan)	
