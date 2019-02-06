cmake_minimum_required(VERSION 3.2)
project(WebHook)

# Configure C++ flags.
set (CMAKE_CXX_STANDARD 14)


# Set directory variables.
set(SOURCE    ${CMAKE_CURRENT_SOURCE_DIR}/source)
set(LIBRARIES ${CMAKE_CURRENT_SOURCE_DIR}/libraries)
set(TESTS     ${CMAKE_CURRENT_SOURCE_DIR}/tests)
set(INCLUDE   ${CMAKE_CURRENT_SOURCE_DIR}/include)


file(GLOB SOURCES ${SOURCE}/*.cpp)

add_executable(WebHook ${SOURCES})
target_include_directories(WebHook PRIVATE include/)

# For linux.
target_link_libraries(WebHook pthread)


# Set up google test
# https://github.com/google/googletest/blob/master/googletest/README.md
# https://stackoverflow.com/questions/12540970/how-to-make-gtest-build-mdd-instead-of-mtd-by-default-using-cmake
enable_testing()
add_subdirectory(${LIBRARIES}/googletest)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
file(GLOB TEST_SOURCES ${TESTS}/*.cpp)

add_executable(unittest ${TEST_SOURCES})
target_include_directories(unittest PRIVATE ${LIBRARIES}/googletest/googletest/include)
target_include_directories(unittest PRIVATE ${LIBRARIES}/googletest/googlemock/include)
target_include_directories(unittest PRIVATE include/)
target_link_libraries(unittest gtest)