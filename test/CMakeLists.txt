project(wvtools_test)

add_definitions(-std=gnu++0x)

set(SOURCE_FILES InfoReaderTest.cpp)
add_executable(wvtools_test ${SOURCE_FILES})

target_link_libraries(wvtools_test gtest gtest_main pthread)