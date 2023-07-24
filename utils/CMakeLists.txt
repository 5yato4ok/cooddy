project(Utils)
set(CMAKE_CXX_STANDARD 17)

include_directories(../include)
include_directories(../include/utils)
include_directories(../include/locale)
include_directories(../include/deps)

file(GLOB UTILS_SOURCES CONFIGURE_DEPENDS
    *.cpp
    *.h
)

add_library(Utils ${COODDY_LINKING_TYPE} ${UTILS_SOURCES})

target_link_libraries(Utils Deps)
