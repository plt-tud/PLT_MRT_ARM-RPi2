cmake_minimum_required(VERSION 2.6)
project(ampel)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")
set(CMAKE_CXX_FLAGS "-std=c++11")
set(CMAKE_C_FLAGS   "-std=c99")

option(BUILD_RPI "Compile lights server for Raspberry Pi (target libbcm)." OFF)

link_directories(${PROJECT_BINARY_DIR})
if(BUILD_RPI)
  add_definitions(-DBUILD_RPI)
  configure_file(${PROJECT_SOURCE_DIR}/lib/libbcm2835_arm-eabi.so   ${PROJECT_BINARY_DIR}/libbcm2835.so   COPYONLY)
  configure_file(${PROJECT_SOURCE_DIR}/lib/libbcm2835_arm-eabi.a    ${PROJECT_BINARY_DIR}/libbcm2835.a   COPYONLY)
else()
  if(WIN32)
  else()
  endif()
endif()


include_directories(${CMAKE_SOURCE_DIR}/include/)
include_directories(${CMAKE_SOURCE_DIR}/include/Automaton/)
include_directories(${CMAKE_SOURCE_DIR}/include/Peripheral/)

set(SOURCES ${CMAKE_SOURCE_DIR}/src/Automaton.cpp  
            ${CMAKE_SOURCE_DIR}/src/AutomatonElement.cpp  
            ${CMAKE_SOURCE_DIR}/src/Behavior.cpp  
            ${CMAKE_SOURCE_DIR}/src/State.cpp  
            ${CMAKE_SOURCE_DIR}/src/Transition.cpp
            ${CMAKE_SOURCE_DIR}/src/Ampel.cpp
            ${CMAKE_SOURCE_DIR}/src/Ampel_Behaviors.cpp
            ${CMAKE_SOURCE_DIR}/src/ampel_capabilities.cpp
            ${CMAKE_SOURCE_DIR}/src/ampel_peripheral_x86.cpp
            ${CMAKE_SOURCE_DIR}/src/rPi_accessor.cpp
            ${CMAKE_SOURCE_DIR}/src/ampel_peripheral_rPi.cpp
            ${CMAKE_SOURCE_DIR}/src/task.cpp
            )

add_executable(ampel ${CMAKE_SOURCE_DIR}/src/main.cpp ${SOURCES})

install(TARGETS ampel RUNTIME DESTINATION bin)
target_link_libraries(ampel pthread )
if(BUILD_RPI)
    target_link_libraries(ampel bcm2835 )
endif()
