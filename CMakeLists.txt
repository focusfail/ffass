cmake_minimum_required(VERSION 3.20)
project(ffass VERSION 0.0.1 LANGUAGES CXX C)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(DEPS "${CMAKE_CURRENT_SOURCE_DIR}/dependencies")

file(GLOB_RECURSE SRC "${CMAKE_CURRENT_SOURCE_DIR}/app/source/*.cpp")

add_subdirectory("${DEPS}/raylib")

add_executable(ffass)
target_sources(ffass PRIVATE ${SRC})
target_include_directories(ffass PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/app/include")
target_link_libraries(ffass PRIVATE raylib)
set_target_properties(ffass PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_CURRENT_SOURCE_DIR}/build/app"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/build/app"
)

# Copy the assets directory to the output
add_custom_command(TARGET ffass POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/app/assets"
        "$<TARGET_FILE_DIR:ffass>/assets"
)