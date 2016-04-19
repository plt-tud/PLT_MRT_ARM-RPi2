cmake_minimum_required(VERSION 2.8)
project(ualights)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")
set(CMAKE_CXX_FLAGS "-std=c++11")
set(CMAKE_C_FLAGS   "-std=c99")
set(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} -Wl,-rpath -Wl,$ORIGIN")

add_definitions(-fpermissive) 

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

set(otherSources  ${CMAKE_SOURCE_DIR}/src/Automaton/AutomatonElement.cpp
                  ${CMAKE_SOURCE_DIR}/src/Automaton/Automaton.cpp
                  ${CMAKE_SOURCE_DIR}/src/Automaton/State.cpp
                  ${CMAKE_SOURCE_DIR}/src/Automaton/Transition.cpp
                  ${CMAKE_SOURCE_DIR}/src/Automaton/Behavior.cpp
                  ${CMAKE_SOURCE_DIR}/src/ua_mapped_class/ua_proxies.cpp
                  ${CMAKE_SOURCE_DIR}/src/ua_mapped_class/ua_mapped_class.cpp
                  ${CMAKE_SOURCE_DIR}/src/TrafficLight/TrafficLightBehavior.cpp
                  ${CMAKE_SOURCE_DIR}/src/TrafficLight/TrafficLight.cpp
                  ${CMAKE_SOURCE_DIR}/src/TrafficLight/BinarySensor.cpp
                  ${CMAKE_SOURCE_DIR}/src/TrafficLight/TrafficLightOutputFacility.cpp
)

link_directories(${PROJECT_BINARY_DIR})

# Options
option(ENABLE_STATICBUILD     "Enable compilation of static binaries." OFF)
option(ENABLE_BUILDMODEL      "Enable ad-hoc building of the OPC UA information model." OFF)
option(ENABLE_COVERAGE        "Enable coverage stats for server build" OFF)
option(ENABLE_VERBOSE_BUILD   "Run verbose make commands (make VERBOSE=1)." OFF)
option(BUILD_STATIC_ANALYSIS  "Instead of building a binary, perform a static code analysis using clangs analyzer." OFF)
option(ENABLE_LINTING         "Enables running the cppcheck static analyzer prior to compilation." OFF)
option(BUILD_RPI              "Compile lights server for Raspberry Pi (target libbcm)." OFF)

# Add paths
include_directories(${CMAKE_SOURCE_DIR}/include/)
include_directories(${CMAKE_SOURCE_DIR}/include/open62541)
include_directories(${CMAKE_SOURCE_DIR}/include/Automaton/)
include_directories(${CMAKE_SOURCE_DIR}/include/TrafficLight/)
include_directories(${CMAKE_SOURCE_DIR}/include/ua_mapped_class//)

# Option: ENABLE_LINTING
if(ENABLE_LINTING)
  set(CPPCHECK_BINARY "/usr/bin/cppcheck" CACHE STRING "Binary to run for linting.")
endif()

# Option: Verbose build
if(ENABLE_VERBOSE_BUILD)
  set(CMAKE_VERBOSE_MAKEFILE on)
endif()

if(BUILD_RPI)
  add_definitions(-DBUILD_RPI)
  configure_file(${PROJECT_SOURCE_DIR}/lib/libopen62541_arm-eabi.so ${PROJECT_BINARY_DIR}/libopen62541.so COPYONLY)
  configure_file(${PROJECT_SOURCE_DIR}/lib/libopen62541_arm-eabi.a  ${PROJECT_BINARY_DIR}/libopen62541.a COPYONLY)
  configure_file(${PROJECT_SOURCE_DIR}/lib/libbcm2835_arm-eabi.so   ${PROJECT_BINARY_DIR}/libbcm2835.so   COPYONLY)
  configure_file(${PROJECT_SOURCE_DIR}/lib/libbcm2835_arm-eabi.a    ${PROJECT_BINARY_DIR}/libbcm2835.a   COPYONLY)
else()
  if(WIN32)
    configure_file(${PROJECT_SOURCE_DIR}/lib/libopen62541_w32.dll ${PROJECT_BINARY_DIR}/libopen62541.dll COPYONLY)
    configure_file(${PROJECT_SOURCE_DIR}/lib/libopen62541_w32.a  ${PROJECT_BINARY_DIR}/libopen62541.a COPYONLY)
  else()
    configure_file(${PROJECT_SOURCE_DIR}/lib/libopen62541_x86_64-eabi.so ${PROJECT_BINARY_DIR}/libopen62541.so COPYONLY)
    configure_file(${PROJECT_SOURCE_DIR}/lib/libopen62541_x86_64-eabi.a  ${PROJECT_BINARY_DIR}/libopen62541.a COPYONLY)
  endif()
endif()

if(BUILD_STATIC_ANALYSIS)
  set(CMAKE_C_COMPILER ccc-analyzer)
  set(CMAKE_CXX_COMPILER ccc-analyzer)
  add_definitions(-o ${PROJECT_BINARY_DIR}/static-analysis})
endif()

if(ENABLE_COVERAGE)
  set(COVERAGE_DIR ${PROJECT_BINARY_DIR}/coverage/ CACHE STRING "Coverage scoring directory for lcov")
  add_definitions(-O0 --coverage)
  add_definitions(-fprofile-arcs -ftest-coverage)
endif()

# Option: Generate Namespace model
if(ENABLE_BUILDMODEL)
  set(COSIM_MODEL_XML "ua_lights.xml" CACHE STRING "Namespace definition XML file for CoSim Model")
  
  include_directories(${PROJECT_BINARY_DIR}/src_generated/)
  include_directories(${PROJECT_SOURCE_DIR}/include/open62541/src/)
  include_directories(${PROJECT_SOURCE_DIR}/include/open62541/deps/)
  
  list(APPEND otherSources ${PROJECT_BINARY_DIR}/src_generated/ua_light_namespaceinit_generated.c)
  add_definitions(-DUA_NO_AMALGAMATION)
  file(MAKE_DIRECTORY "${PROJECT_BINARY_DIR}/src_generated")
else()
  include_directories(${CMAKE_SOURCE_DIR}/include/model_pregenerated/)
  list(APPEND otherSources ${CMAKE_SOURCE_DIR}/include/model_pregenerated/ua_light_namespaceinit_generated.c)
  
  include_directories(${PROJECT_SOURCE_DIR}/include/open62541/src/)
  include_directories(${PROJECT_SOURCE_DIR}/include/open62541/deps/)
  add_definitions(-DUA_NO_AMALGAMATION)
endif()

add_custom_command(OUTPUT ${PROJECT_BINARY_DIR}/src_generated/ua_light_namespaceinit_generated.c
                          ${PROJECT_BINARY_DIR}/src_generated/ua_light_namespaceinit_generated.h
                   PRE_BUILD
                   COMMAND ${PYTHON_EXECUTABLE} ${PROJECT_SOURCE_DIR}/tools/pyUANamespace/generate_open62541CCode.py
                                                -i ${PROJECT_SOURCE_DIR}/model/NodeID_Blacklist_FullNS0.txt
                                                -b ${PROJECT_SOURCE_DIR}/model/NodeID_Blacklist.txt
                                                ${PROJECT_SOURCE_DIR}/model/Opc.Ua.NodeSet2.xml
                                                ${PROJECT_SOURCE_DIR}/model/${COSIM_MODEL_XML}
                                                ${PROJECT_BINARY_DIR}/src_generated/ua_light_namespaceinit_generated
                   DEPENDS ${PROJECT_SOURCE_DIR}/model/Opc.Ua.NodeSet2.xml
                           ${PROJECT_SOURCE_DIR}/model/${COSIM_MODEL_XML}
			   ${PROJECT_SOURCE_DIR}/model/NodeID_Blacklist_FullNS0.txt
                           ${PROJECT_SOURCE_DIR}/model/NodeID_Blacklist.txt
                           ${PROJECT_SOURCE_DIR}/tools/pyUANamespace/generate_open62541CCode.py
                           ${PROJECT_SOURCE_DIR}/tools/pyUANamespace/logger.py
                           ${PROJECT_SOURCE_DIR}/tools/pyUANamespace/open62541_MacroHelper.py
                           ${PROJECT_SOURCE_DIR}/tools/pyUANamespace/ua_builtin_types.py
                           ${PROJECT_SOURCE_DIR}/tools/pyUANamespace/ua_constants.py
                           ${PROJECT_SOURCE_DIR}/tools/pyUANamespace/ua_namespace.py
                           ${PROJECT_SOURCE_DIR}/tools/pyUANamespace/ua_node_types.py)

# OPTION: Coverage
if(ENABLE_COVERAGE)
  set(CMAKE_BUILD_TYPE DEBUG)
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fprofile-arcs -ftest-coverage")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fprofile-arcs -ftest-coverage")
  set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -fprofile-arcs -ftest-coverage")
endif()

# OPTION: Unit tests 
if(ENABLE_UNIT_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

# Prepare: Place all object files into the same directory and reuse
add_library(ua_lights-object OBJECT ${otherSources})

# Build: Server Executable
add_executable(ua_lights ${PROJECT_SOURCE_DIR}/src/ua_lights.cpp $<TARGET_OBJECTS:ua_lights-object>)
target_link_libraries(ua_lights open62541 pthread rt)
if(ENABLE_COVERAGE)
  target_link_libraries(ua_lights gcov )
endif()
if(ENABLE_MULTITHREADING)
  target_link_libraries(ua_lights urcu-cds urcu urcu-common)
endif()
if(BUILD_RPI)
  target_link_libraries(ua_lights bcm2835)
endif()
if(ENABLE_LINTING)
  add_custom_command( TARGET ua_lights
                      PRE_BUILD
                      COMMAND ${CPPCHECK_BINARY} --std=c++11 --inline-suppr --enable=all ${otherSources}
                      WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
                      COMMENT "Running CppCheck on all CPP Sources" VERBATIM)
endif()

# Build: Dummy Client Executable
add_executable(ua_lights_controller ${PROJECT_SOURCE_DIR}/src/ua_lights_controller.cpp $<TARGET_OBJECTS:ua_lights-object>)
target_link_libraries(ua_lights_controller open62541 pthread rt)
if(ENABLE_COVERAGE)
  target_link_libraries(ua_lights_controller gcov )
endif()
if(ENABLE_MULTITHREADING)
  target_link_libraries(ua_lights_controller urcu-cds urcu urcu-common)
endif()
if(BUILD_RPI)
  target_link_libraries(ua_lights_controller bcm2835)
endif()
if(ENABLE_LINTING)
  add_custom_command( TARGET ua_lights_controller
                      PRE_BUILD
                      COMMAND ${CPPCHECK_BINARY} --std=c++11 --inline-suppr --enable=all ${otherSources}
                      WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
                      COMMENT "Running CppCheck on all CPP Sources" VERBATIM)
endif()

# Build: static executable
if(ENABLE_STATICBUILD)
  add_executable(ua_lights_static ${PROJECT_SOURCE_DIR}/src/ua_lights.cpp $<TARGET_OBJECTS:ua_lights-object>)
  set_target_properties(ua_lights_static PROPERTIES COMPILE_FLAGS "-static-libstdc++ -static" )
  target_link_libraries(ua_lights_static pthread)
  if(ENABLE_COVERAGE)
    target_link_libraries(ua_lights_static gcov )
  endif()
  if(ENABLE_MULTITHREADING)
    target_link_libraries(ua_lights_static urcu-cds urcu urcu-common)
  endif()
    target_link_libraries(ua_lights_static open62541  rt)
  if(BUILD_RPI)
    target_link_libraries(ua_lights bcm2835)
  endif()
  if(ENABLE_LINTING)
    add_custom_command( TARGET ua_lights
                        PRE_BUILD
                        COMMAND /usr/bin/cppcheck --std=c++11 --inline-suppr --enable=all ${otherSources}
                        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
                        COMMENT "Running CppCheck on all CPP Sources" VERBATIM)
  endif()
endif()