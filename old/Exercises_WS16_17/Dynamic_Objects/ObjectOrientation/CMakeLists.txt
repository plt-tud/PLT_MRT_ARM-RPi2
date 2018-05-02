cmake_minimum_required (VERSION 2.8.11)
project (ObjectOrientation)

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

add_library(ObjectOrientation-object OBJECT ${sourceFiles})

add_executable (test_linlist tests/test_linlist.c  $<TARGET_OBJECTS:ObjectOrientation-object>)
target_link_libraries(test_linlist check)

add_executable (example_00 examples/example_00.c  $<TARGET_OBJECTS:ObjectOrientation-object>)
