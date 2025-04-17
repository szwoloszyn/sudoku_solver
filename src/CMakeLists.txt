# your_project/src/CMakeLists.txt


# Or if it's an executable
add_executable(sudokuSolver
    main.cpp)


add_library(sourceCode
    field.h field.cpp
    sudoku.h sudoku.cpp)

target_include_directories(sudokuSolver PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
