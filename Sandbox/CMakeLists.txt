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



# GLFW
set(GLFW_DIR "${LIB_DIR}/glfw")
set(GLFW_BUILD_EXAMPLES OFF CACHE INTERNAL "Build the GLFW example programs")
set(GLFW_BUILD_TESTS OFF CACHE INTERNAL "Build the GLFW test programs")
set(GLFW_BUILD_DOCS OFF CACHE INTERNAL "Build the GLFW documentation")
set(GLFW_INSTALL OFF CACHE INTERNAL "Generate installation target")
add_subdirectory("${GLFW_DIR}")
#target_include_directories(${PROJECT_NAME} PUBLIC "${GLFW_DIR}/include")	
target_link_libraries(${PROJECT_NAME} "glfw" "${GLFW_LIBRARIES}")
target_compile_definitions(${PROJECT_NAME} PUBLIC "GLFW_INCLUDE_NONE")

#GLAD
set(GLAD_DIR "${LIB_DIR}/glad")
add_library("glad" "${GLAD_DIR}/src/glad.c")
target_include_directories("glad" PRIVATE "${GLAD_DIR}/include")
target_include_directories(${PROJECT_NAME} PUBLIC "${GLAD_DIR}/include")
target_link_libraries(${PROJECT_NAME} "glad" )

if(MSVC)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")
endif(MSVC)

target_link_libraries (Sandbox Hypatia d3d11.lib)