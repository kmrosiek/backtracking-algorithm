project(tests)

find_package(GTest REQUIRED)

add_executable(${PROJECT_NAME} tests.cpp)
target_include_directories(${PROJECT_NAME} PRIVATE ../inc)
target_link_libraries(${PROJECT_NAME}
    ${CW_PUZZLE_LIB}
    ${GTEST_LIBRARIES}
    gtest_main
    Threads::Threads
    )
