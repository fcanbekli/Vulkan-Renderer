cmake_minimum_required (VERSION 3.8)
set(This VulkanRendererTest)

set(CompilerFlags
        CMAKE_CXX_FLAGS
        CMAKE_CXX_FLAGS_DEBUG
        CMAKE_CXX_FLAGS_RELEASE
        CMAKE_C_FLAGS
        CMAKE_C_FLAGS_DEBUG
        CMAKE_C_FLAGS_RELEASE
        )
foreach(CompilerFlag ${CompilerFlags})
  string(REPLACE "/MD" "/MT" ${CompilerFlag} "${${CompilerFlag}}")
endforeach()

FILE(GLOB_RECURSE SOURCES "*.cpp")
SET(CMAKE_EXE_LINKER_FLAGS  "/FORCE")
add_executable(${This} ${SOURCES})
target_link_libraries(${This} PUBLIC
    gtest
    gtest_main
    VulkanRenderer
)

add_test(
    NAME ${This}
    COMMAND ${This}
)