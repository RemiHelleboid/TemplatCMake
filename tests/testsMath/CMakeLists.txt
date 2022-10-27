file(GLOB TESTS_MATH *.cpp)

message("TESTS MATH: ")

foreach(TEST ${TESTS_MATH})
    get_filename_component(TEST_NAME ${TEST} NAME_WE)
    message("   --- Test: ${TEST_NAME}")
    add_executable(${TEST_NAME} ${TEST})
    target_link_libraries(${TEST_NAME} doctest::doctest libMath)
    add_test(${TEST_NAME} ${TEST_NAME})
endforeach()