project(Solver)

include_directories(SYSTEM ${Z3_HOME}/include)
include_directories(../include)

file(GLOB SOLVER_SOURCES CONFIGURE_DEPENDS
    *.cpp
    *.h
)

add_library(Solver ${COODDY_LINKING_TYPE} ${SOLVER_SOURCES})

if (MSVC)
    target_link_libraries(Solver z3 TUnit)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang")
    target_link_libraries(Solver PRIVATE Utils TUnit -Wl, z3 -Wl,-dynamic -Wl,-hidden-lz3)
else ()
    target_link_libraries(Solver PRIVATE Utils TUnit -Wl,-Bstatic stdc++ z3 -Wl,-Bdynamic -Wl,--exclude-libs,libz3.a)
endif ()
