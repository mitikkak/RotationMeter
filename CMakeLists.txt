project(RotationMeter)

find_package(GTest REQUIRED)
set(PROJECT_ROOT ${CMAKE_CURRENT_SOURCE_DIR})
set(SRC_DIR ${PROJECT_ROOT}/src)
set(TST_DIR ${PROJECT_ROOT}/tst)
include_directories(${GTEST_INCLUDE_DIRS})
include_directories(${SRC_DIR})

set( CMAKE_BUILD_TYPE Debug)
aux_source_directory(${TST_DIR} TESTS)
add_executable(${PROJECT_NAME} ${TESTS})
target_link_libraries(${PROJECT_NAME} ${GTEST_LIBRARIES} pthread)
