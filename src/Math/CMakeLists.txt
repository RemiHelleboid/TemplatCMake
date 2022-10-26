set(HEADER_FILES_LIBEPP
    vector.hpp)

set(SOURCE_FILES_LIBEPP
    vector.cpp)

add_library(libMath STATIC ${SOURCE_FILES_LIBEPP} ${HEADER_FILES_LIBEPP})

target_include_directories(libMath PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Link with reuired libraries
target_link_libraries(libMath PUBLIC Eigen3::Eigen)

if(USE_OPENMP_ACCELERATION)
    target_link_libraries(libMath PUBLIC OpenMP::OpenMP_CXX)
endif(USE_OPENMP_ACCELERATION)

# All users of this library will need at least C++20
target_compile_features(libMath PRIVATE cxx_std_20)
