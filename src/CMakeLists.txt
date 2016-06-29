project(wvtools_lib)
add_definitions(-std=gnu++11 -Wall -Wextra -pedantic -O3)

set(SOURCE_FILES WvToolsFacade.cpp WvToolsFacade.h io/InfoReader.cpp io/InfoReader.h io/IOException.cpp io/IOException.h util/ChecksumCalculator.cpp util/ChecksumCalculator.h io/WvReader.cpp io/WvReader.h io/DataWriter.cpp io/DataWriter.h io/PhysionetWriter.cpp io/PhysionetWriter.h util/SvmParams.cpp util/SvmParams.h io/QrsOnsetReader.cpp io/QrsOnsetReader.h util/FeatureCalculator.cpp util/FeatureCalculator.h util/QualityChecker.cpp util/QualityChecker.h tsdb/TsdbUploader.cpp tsdb/TsdbUploader.h io/TimestampReader.cpp io/TimestampReader.h util/TimestampCalculator.cpp util/TimestampCalculator.h tsdb/TsdbQueryConverter.cpp tsdb/TsdbQueryConverter.h)

add_library(wvtools_lib STATIC ${SOURCE_FILES})
target_link_libraries(wvtools_lib boost_regex boost_program_options restclient-cpp pthread curl)