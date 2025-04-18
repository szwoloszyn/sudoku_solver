# your_project/src/CMakeLists.txt


# Or if it's an executable
add_executable(sudokuSolver
    main.cpp)


add_library(sourceCode
    field.h field.cpp
    sudoku.h sudoku.cpp)

target_link_libraries(sudokuSolver PRIVATE sourceCode)
target_include_directories(sourceCode PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
