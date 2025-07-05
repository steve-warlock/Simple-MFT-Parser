cmake_minimum_required(VERSION 3.24)
project(mft_to_json_parser)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Gather the files from src
file(GLOB SRC_FILES src/*.cpp)

add_executable(mft_to_json_converter ${SRC_FILES})

# include the headers folder
target_include_directories(mft_to_json_converter PRIVATE include)

# Find nlohmann_json package
find_package(nlohmann_json REQUIRED)
# Link the package
target_link_libraries(mft_to_json_converter PRIVATE nlohmann_json::nlohmann_json)

# Find CLI11 package (commandline parser similar to rust's clap)
find_package(CLI11 REQUIRED)
# Link the package
target_link_libraries(mft_to_json_converter PRIVATE CLI11::CLI11)

# Final message
message(STATUS "Finished build")
