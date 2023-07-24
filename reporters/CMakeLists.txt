project(Reporters)
set(CMAKE_CXX_STANDARD 17)

include_directories(../include)

file(GLOB REPORTERS_SOURCES CONFIGURE_DEPENDS
        *.cpp
        *.h
        )

add_subdirectory(SampleReporter/src)
add_subdirectory(SarifReporter/src)

add_library(Reporters STATIC ${REPORTERS_SOURCES})
