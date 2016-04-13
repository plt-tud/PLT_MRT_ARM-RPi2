cmake_minimum_required(VERSION 2.8)
project(ualights)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")

set(CMAKE_C_COMPILER gcc)
set(CMAKE_CXX_COMPILER g++)
add_definitions(-std=c++11 )

if(CMAKE_COMPILER_IS_GNUCC OR "x${CMAKE_C_COMPILER_ID}" STREQUAL "xClang")
    # Changed for Ubuntu-12.04 (does not support add_compile_options)
    # add_definitions(-Wno-write-strings)
    add_definitions(-g)
    
    # Needed for liburcu... needed by open62541
    add_definitions(-fpermissive) 
endif()

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

set(otherSources  ${CMAKE_SOURCE_DIR}/src/Opc_ua.cpp
                  ${CMAKE_SOURCE_DIR}/src/setLight.cpp
                  ${CMAKE_SOURCE_DIR}/src/Light.cpp
                  ${CMAKE_SOURCE_DIR}/src/PedestrianLight.cpp
                  ${CMAKE_SOURCE_DIR}/src/ThreadedSensor.cpp
                  ${CMAKE_SOURCE_DIR}/src/TrafficLight.cpp
)

# Options
option(ENABLE_STATICBUILD     "Enable compilation of static binaries." OFF)
option(ENABLE_BUILDMODEL      "Enable ad-hoc building of the OPC UA information model." OFF)
option(ENABLE_COVERAGE        "Enable coverage stats for server build" ON)
option(ENABLE_VERBOSE_BUILD   "Run verbose make commands (make VERBOSE=1)." OFF)
option(BUILD_STATIC_ANALYSIS  "Instead of building a binary, perform a static code analysis using clangs analyzer." OFF)
option(ENABLE_LINTING         "Enables running the cppcheck static analyzer prior to compilation." OFF)
option(BUILD_RPI              "Compile lights server for Raspberry Pi (target libbcm)." OFF)

# Add paths
include_directories(${CMAKE_SOURCE_DIR}/include/)
include_directories(${CMAKE_SOURCE_DIR}/include/open62541)

# Option: ENABLE_LINTIN
if(ENABLE_LINTING)
  set(CPPCHECK_BINARY "/usr/bin/cppcheck" CACHE STRING "Binary to run for linting.")
endif()

# Option: Verbose build
if(ENABLE_VERBOSE_BUILD)
  set(CMAKE_VERBOSE_MAKEFILE on)
endif()

if(BUILD_RPI)
  add_definitions(-DPI)
else()
  add_definitions(-DX86)
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
# else()
#   include_directories(${CMAKE_SOURCE_DIR}/include/model_prebuilt/)
#   list(APPEND otherSources ${CMAKE_SOURCE_DIR}/include/model_prebuilt/ua_light_namespaceinit_generated.c)
#   
#   include_directories(${PROJECT_SOURCE_DIR}/include/open62541/src/)
#   include_directories(${PROJECT_SOURCE_DIR}/include/open62541/deps/)
#   add_definitions(-DUA_NO_AMALGAMATION)
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

# Build: Aggregating Server Executable
add_executable(ua_lights ${PROJECT_SOURCE_DIR}/src/main.cpp $<TARGET_OBJECTS:ua_lights-object>)
target_link_libraries(ua_lights pthread)
if(ENABLE_COVERAGE)
  target_link_libraries(ua_lights gcov )
endif()
if(ENABLE_MULTITHREADING)
  target_link_libraries(ua_lights urcu-cds urcu urcu-common)
endif()
#target_link_libraries(ua_lights open62541)
if(ENABLE_LINTING)
  add_custom_command( TARGET ua_lights
                      PRE_BUILD
                      COMMAND ${CPPCHECK_BINARY} --std=c++11 --inline-suppr --enable=all ${otherSources}
                      WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
                      COMMENT "Running CppCheck on all CPP Sources" VERBATIM)
endif()

# Build: static executable
if(ENABLE_STATICBUILD)
  add_executable(ua_lights_static ${PROJECT_SOURCE_DIR}/src/main.cpp $<TARGET_OBJECTS:ua_lights-object>)
  set_target_properties(ua_lights_static PROPERTIES COMPILE_FLAGS "-static-libstdc++ -static" )
  target_link_libraries(ua_lights_static pthread)
  if(ENABLE_COVERAGE)
    target_link_libraries(ua_lights_static gcov )
  endif()
  if(ENABLE_MULTITHREADING)
    target_link_libraries(ua_lights_static urcu-cds urcu urcu-common)
  endif()
  #target_link_libraries(ua_lights_static open62541)
  if(ENABLE_LINTING)
    add_custom_command( TARGET ua_lights
                        PRE_BUILD
                        COMMAND /usr/bin/cppcheck --std=c++11 --inline-suppr --enable=all ${otherSources}
                        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
                        COMMENT "Running CppCheck on all CPP Sources" VERBATIM)
  endif()
endif()