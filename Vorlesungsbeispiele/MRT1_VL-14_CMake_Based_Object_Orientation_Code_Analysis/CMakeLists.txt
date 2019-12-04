# Neuer Kommentar

cmake_minimum_required (VERSION 2.8.11)
project (ObjectOrientation)

option(ENABLE_COVERAGE          "Enable GCov/LCov based coverage" OFF)
option(ENABLE_STATIC_ANALYSIS   "Enable CCAnalyze/Scanbuild instead of binary target" OFF)

include_directories(${CMAKE_SOURCE_DIR}/include
                    ${CMAKE_SOURCE_DIR}/src
                    ${CMAKE_BINARY_DIR}/src_generated
)

set(sourceFiles ${CMAKE_SOURCE_DIR}/src/dog.c
                ${CMAKE_SOURCE_DIR}/src/human.c
                ${CMAKE_SOURCE_DIR}/src/linlist_elem.c
                ${CMAKE_SOURCE_DIR}/src/linlist.c
                ${CMAKE_SOURCE_DIR}/src/mamal.c
)


set(libs check m rt pthread subunit)

if (ENABLE_COVERAGE)
    add_definitions(-O0 --coverage)
    add_definitions(-ftest-coverage -fprofile-arcs)
    set(libs ${libs} gcov)
endif()

if (ENABLE_STATIC_ANALYSIS)
    set(CMAKE_C_COMPILER   ccc-analyzer)
    set(CMAKE_CXX_COMPILER ccc-analyzer)
endif()

add_definitions(-g)
add_library(ObjectOrientation-object OBJECT ${sourceFiles})

add_executable (example_00 examples/example_00.c $<TARGET_OBJECTS:ObjectOrientation-object>)
if (ENABLE_COVERAGE)
    target_link_libraries(example_00 ${libs})
endif()

add_executable (test_linlist tests/test_linlist.c  $<TARGET_OBJECTS:ObjectOrientation-object>)
target_link_libraries(test_linlist ${libs})
