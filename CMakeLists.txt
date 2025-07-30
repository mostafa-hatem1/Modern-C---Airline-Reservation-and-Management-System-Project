(cmake_)
project(AirlineReservationSystem)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add include directories
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/src)

# Collect all source files
file(GLOB SOURCES 
    "src/*.cpp"
)

# Create the executable
add_executable(airline ${SOURCES})

# Link filesystem library (required for GCC 8/9, optional for newer versions)
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS 9.0)
    target_link_libraries(airline stdc++fs)
endif()

# Compiler-specific options
if(MSVC)
    target_compile_options(airline PRIVATE /W4)
else()
    target_compile_options(airline PRIVATE -Wall -Wextra -Wpedantic)
endif()
