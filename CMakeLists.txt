cmake_minimum_required(VERSION 2.8)
project(Neuron)
set(CMAKE_CXX_FALGS "-W -Wall -pedantic -std=c++11")

###### Simulation core compilation ######

add_executable (neuron 
					test_fun1.cpp 
					neuron.cpp 
					network.cpp)

###### Gtest complation ######

enable_testing()
add_subdirectory(googletest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})					

add_executable (neuron_unittest 
					neuron.cpp 
					network.cpp 
					neuron_unittest.cpp)

target_link_libraries(neuron_unittest gtest gtest_main)
add_test(neuron_unittest neuron_unittest)

###### Doxygen generation ######

# We first check if Doxygen is present.
find_package(Doxygen)
if(DOXYGEN_FOUND)

    # We then check if the Doxyconfig configuration file exists
    IF(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/Doxyconfig)
        message(FATAL_ERROR "Doxygen configuration file is needed to build the documentation:
         - ${CMAKE_CURRENT_SOURCE_DIR}/Doxyconfig not found.
         - Generate one in the project folder with doxygen -g Doxyconfig")
    ENDIF(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/Doxyconfig)

    # We configure the doxyfile for make.
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyconfig ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
    add_custom_target(doc
        ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    )
ELSE(DOXYGEN_FOUND)
    message(FATAL_ERROR "Doxygen is needed to build the documentation.")
ENDIF(DOXYGEN_FOUND)