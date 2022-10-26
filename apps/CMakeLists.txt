# Create the main executables
add_executable(my_app my_app.cpp)
target_link_libraries(my_app PUBLIC libMath)
target_compile_features(my_app PRIVATE cxx_std_20)