
file(GLOB_RECURSE SOURCE_FILES_ENGINE "*.cpp")
file(GLOB_RECURSE HEADER_FILES_ENGINE "*.h")

# vulkan
find_package(Vulkan REQUIRED)

# glfw
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory("external/glfw")

# Engine library
add_library(DragonbyteEngine ${SOURCE_FILES_ENGINE} ${HEADER_FILES_ENGINE})

target_include_directories(DragonbyteEngine PUBLIC "include")

target_link_libraries(DragonbyteEngine PUBLIC Vulkan::Vulkan glfw)
