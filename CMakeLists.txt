# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
# enable C and C++ language
project (VulkanRenderer)

cmake_minimum_required (VERSION 3.8)

enable_testing()

# Include sub-projects.
add_subdirectory(googletest)
add_subdirectory (Sandbox)
add_subdirectory (VulkanRenderer)
add_subdirectory(VulkanRendererTest)