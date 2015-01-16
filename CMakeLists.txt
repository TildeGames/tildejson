cmake_minimum_required(VERSION 3.0)

# Project name
project(GameEngine)

# Output path
set(LIBRARY_OUTPUT_PATH lib)

# Include directory
include_directories(include)

# Source files
file(
        GLOB_RECURSE
        source_files
        src/TildeJSON/*
        include/TildeJSON/*
)

# Library
add_library(
        tildejson
        SHARED
        ${source_files}
)

# Linker options
target_link_libraries(tildejson)


add_custom_target(
	tests
	WORKING_DIRECTORY ./src/tests
    COMMAND "./build.sh") 

# Install target
install(TARGETS tildejson
        LIBRARY DESTINATION lib)
install(DIRECTORY include/TildeJSON DESTINATION include)