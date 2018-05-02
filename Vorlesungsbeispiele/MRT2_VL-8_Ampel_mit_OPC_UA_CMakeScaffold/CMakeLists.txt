cmake_minimum_required(VERSION 2.6)
project(ampel)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g")
set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS} -std=c99 -g")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g")

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


include_directories(${CMAKE_SOURCE_DIR}/src/)
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
            ${CMAKE_SOURCE_DIR}/src/open62541.c
            ${CMAKE_SOURCE_DIR}/src/ampel_iot_callbacks.cpp
            ${CMAKE_SOURCE_DIR}/src/ampel_iot_opcua.cpp
            ${CMAKE_SOURCE_DIR}/src/RemoteAmpel.cpp
)

add_executable(ampel_server ${CMAKE_SOURCE_DIR}/ampel_server.cpp ${SOURCES})
target_link_libraries(ampel_server pthread )
if(BUILD_RPI)
    target_link_libraries(ampel_server bcm2835 )
endif()

add_executable(ampel_controller ${CMAKE_SOURCE_DIR}/ampel_controller.cpp ${SOURCES})
target_link_libraries(ampel_controller pthread )
if(BUILD_RPI)
    target_link_libraries(ampel_controller bcm2835 )
endif()
