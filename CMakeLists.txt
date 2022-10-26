cmake_minimum_required(VERSION 3.15...3.25)

include(CMakePrintHelpers)

project(
    MyProject
    VERSION "0.0.0"
    DESCRIPTION "An amazing description."
    LANGUAGES C CXX)

add_compile_definitions(CMAKE_SOURCE_DIR="${CMAKE_SOURCE_DIR}")

# -----------------------------------------------------------------------------
# Set the project options.
option(ENABLE_OPEN_MP "Build programs with suppot of OpenMP." OFF)
option(ENABLE_MPI_BUILD "Build some programs with MPI parralelization." OFF)
option(ENABLE_CLANG_TIDY "Enable clang tidy at compilation" OFF)
option(ENABLE_BUILD_DOC "Enable the documentation build (doxygen)" OFF)
option(ENABLE_BUILD_TEST "Enable the documentation build (doxygen)" OFF)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Handling build type nicely Set a default build type if none was specified
set(default_build_type "Release")

if(EXISTS "${CMAKE_SOURCE_DIR}/.git")
    set(default_build_type "RelWithDebInfo")
endif()

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(
        STATUS
        "Setting build type to '${default_build_type}' as none was specified.")
    set(CMAKE_BUILD_TYPE
        "${default_build_type}"
        CACHE STRING "Choose the type of build." FORCE)

    # Set the possible values of build type for cmake-gui
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release"
        "MinSizeRel" "RelWithDebInfo")
endif()

if(ENABLE_CLANG_TIDY)
    message("Clang tidy at compilation is enabled")
    set(CMAKE_CXX_CLANG_TIDY clang-tidy -checks=-*,readability-*)
endif()

# Flags for the compiler
if(MSVC)
    add_compile_options("/W4" "$<$<CONFIG:RELEASE>:/O2>")
else()
    add_compile_options("-Wall" "-Wextra" "-pedantic")

    # add_compile_options("-Werror")
    if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
        add_compile_options("-stdlib=libc++")
    else()
        # nothing special for gcc at the moment
    endif()
endif()

# -----------------------------------------------------------------------------
# FIND / GET RELEVANT LIBRARIES
include(FetchContent)

# Find Eigen library Find Eigen library
FetchContent_Declare(
    Eigen
    GIT_REPOSITORY "https://gitlab.com/libeigen/eigen.git"
    GIT_TAG "3.4.0"
    GIT_SHALLOW TRUE
    GIT_PROGRESS TRUE)

find_package(Eigen3 NO_MODULE)

if(NOT Eigen3_FOUND)
    set(EIGEN_BUILD_DOC OFF)
    set(BUILD_TESTING OFF)
    set(EIGEN_BUILD_PKGCONFIG OFF)
    message("Fetching Eigen3 lib ...")
    add_compile_definitions(EIGEN_USE_LAPACK=0)
    FetchContent_MakeAvailable(Eigen)
endif()

# Find OpenMP
if(ENABLE_OPEN_MP)
    message("OpenMP optimization activated.")
    find_package(OpenMP)

    if(OpenMP_FOUND)
        set(USE_OPENMP_ACCELERATION 1)
        add_compile_definitions(USE_OPEN_MP=1)
    endif()
else()
    set(USE_OPENMP_ACCELERATION 0)
    add_compile_definitions(USE_OPEN_MP=0)
endif(ENABLE_OPEN_MP)

FetchContent_Declare(
    DocTest
    GIT_REPOSITORY "https://github.com/onqtam/doctest"
    GIT_TAG "4d8716f1efc1d14aa736ef52ee727bd4204f4c40")

# check if Doxygen is installed
find_package(Doxygen)

if(DOXYGEN_FOUND AND ENABLE_BUILD_DOC)
    # set input and output files
    set(DOXYGEN_IN ${PROJECT_SOURCE_DIR}/doc/Doxyfile)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)
    set(MAINPAGE_IN ${PROJECT_SOURCE_DIR}/doc/mainpage.md)
    set(MAINPAGE_OUT ${CMAKE_CURRENT_BINARY_DIR}/mainpage.md)

    # request to configure the file
    configure_file(${MAINPAGE_IN} ${MAINPAGE_OUT} @ONLY)
    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
    message("Doxygen build started")

    # note the option ALL which allows to build the docs together with the
    # application
    add_custom_target(
        doc_doxygen ALL
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM)
else(DOXYGEN_FOUND)
    message("Doxygen need to be installed to generate the doxygen documentation")
endif()

# MPI SUPPORT
if(ENABLE_MPI_BUILD)
    message("MPI support activated.")
    find_package(MPI)

    if(MPI_FOUND)
        set(USE_MPI_ACCELERATION 1)
        add_compile_definitions(USE_MPI=1)
        add_definitions(-DOMPI_SKIP_MPICXX)
        include_directories(SYSTEM ${MPI_INCLUDE_PATH})
        message("MPI ACCELERATION ENABLED.")
    endif()
else()
    set(USE_MPI_ACCELERATION 0) 
    add_compile_definitions(USE_MPI=0)
    message("MPI support deactivated. Not found.")
endif(ENABLE_MPI_BUILD)

# The tests are here
if(ENABLE_BUILD_TEST)
    message("Fetching DocTest lib ...")
    FetchContent_MakeAvailable(DocTest)
    add_subdirectory(tests/)
endif(ENABLE_BUILD_TEST)

# -----------------------------------------------------------------------------
# The compiled library code is here
add_subdirectory(src/Math)
add_subdirectory(apps/)
