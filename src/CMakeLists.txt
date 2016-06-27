project(wvtools_lib)
add_definitions(-std=c++11 -Wall -Wextra -pedantic -O3)

set(SOURCE_FILES WvToolsFacade.cpp WvToolsFacade.h io/InfoReader.cpp io/InfoReader.h io/IOException.cpp io/IOException.h util/ChecksumCalculator.cpp util/ChecksumCalculator.h io/WvReader.cpp io/WvReader.h io/DataWriter.cpp io/DataWriter.h io/PhysionetWriter.cpp io/PhysionetWriter.h io/SvmParamsReader.cpp io/SvmParamsReader.h io/QrsOnsetReader.cpp io/QrsOnsetReader.h util/FeatureCalculator.cpp util/FeatureCalculator.h)

add_library(wvtools_lib STATIC ${SOURCE_FILES})
target_link_libraries(wvtools_lib boost_regex)