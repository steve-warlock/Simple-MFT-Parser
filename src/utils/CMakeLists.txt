add_library(utils STATIC logger.cpp)

# Include path for other targets that link this library
target_include_directories(utils PUBLIC ${PROJECT_SOURCE_DIR}/include)
