cmake_minimum_required(VERSION 3.10)
project(nonlinear_solver VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(nonlinear_solver
    src/solver.cpp
    src/utils.cpp
)

target_include_directories(nonlinear_solver
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

# Installation
include(GNUInstallDirs)
install(TARGETS nonlinear_solver
    EXPORT nonlinear_solver-targets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

install(DIRECTORY include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

add_executable(nonlinear_solver_example demo.cpp)
target_link_libraries(nonlinear_solver_example PRIVATE nonlinear_solver)
