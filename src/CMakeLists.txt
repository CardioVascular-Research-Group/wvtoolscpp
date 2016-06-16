project(wvtools_lib)
add_definitions(-std=c++11 -Wall -Wextra -pedantic)

set(SOURCE_FILES WvToolsFacade.cpp WvToolsFacade.h io/InfoReader.cpp io/InfoReader.h)

add_library(wvtools_lib STATIC ${SOURCE_FILES})