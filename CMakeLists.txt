cmake_minimum_required (VERSION 3.10.2)

project(crossword_puzzle)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Wextra -pedantic")

set(CMAKE_MODULE_PATH /home/chris/Programming/new_ai_crossword/others)
find_package(SDL2 REQUIRED)
find_package(SDL_image REQUIRED)
find_package(SDL2TTF)


set(CW_PUZZLE_LIB_HEADERS
    ${CMAKE_CURRENT_LIST_DIR}/inc/dictionary.hpp
    ${CMAKE_CURRENT_LIST_DIR}/inc/constraint.hpp
    ${CMAKE_CURRENT_LIST_DIR}/inc/board.hpp
    ${CMAKE_CURRENT_LIST_DIR}/inc/word_footprint.hpp
    ${CMAKE_CURRENT_LIST_DIR}/inc/utils.hpp
    ${CMAKE_CURRENT_LIST_DIR}/inc/crossword.hpp
    )

set(CW_PUZZLE_LIB_SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/src/dictionary.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/constraint.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/board.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/word_footprint.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/utils.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/crossword.cpp
    )


set(CW_PUZZLE_LIB "cw_puzzle_lib")
add_library(${CW_PUZZLE_LIB} ${CW_PUZZLE_LIB_SOURCES} ${CW_PUZZLE_LIB_HEADERS})
#target_link_libraries(${CW_PUZZLE_LIB} ${SDL2_LIBRARIES})
#target_include_directories(${CW_PUZZLE_LIB} PRIVATE ${SDL2_INCLUDE_DIRS})
target_include_directories(${CW_PUZZLE_LIB} PRIVATE inc)
#target_link_libraries(${CW_PUZZLE_LIB} ${SDL2TTF_LIBRARY})


set(CW_PUZZLE_SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/src/main.cpp)

add_executable(${PROJECT_NAME} ${CW_PUZZLE_SOURCES})
#target_include_directories(${PROJECT_NAME} PRIVATE ${SDL2_INCLUDE_DIRS})
target_include_directories(${PROJECT_NAME} PRIVATE inc)
#target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${CW_PUZZLE_LIB})
#target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} ${CW_PUZZLE_LIB})


add_subdirectory(tests)
