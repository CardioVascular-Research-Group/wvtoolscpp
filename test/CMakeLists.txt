project(wvtools_test)

add_definitions(-std=gnu++0x)

set(SOURCE_FILES InfoReaderTest.cpp WvReaderTest.cpp ChecksumCalculatorTest.cpp QrsOnsetReaderTest.cpp SvmParamsReaderTest.cpp FeatureCalculatorTest.cpp RestApiTest.cpp TimestampTest.cpp TsdbUploaderTest.cpp TsdbQueryConverterTest.cpp ConfigFileReadTest.cpp TsuidCacheTest.cpp)
add_executable(wvtools_test ${SOURCE_FILES})

target_link_libraries(wvtools_test wvtools_lib gtest gtest_main)
file(COPY "data/" DESTINATION "data")

