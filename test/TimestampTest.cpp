//
// Created by rliu14 on 6/28/16.
//

#include <gtest/gtest.h>

#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time.hpp>
#include "../src/io/TimestampReader.h"
#include "../src/util/TimestampCalculator.h"

using namespace boost::gregorian;
using namespace boost::posix_time;

using std::cout;
using std::endl;
using std::cerr;
using std::locale;
using std::stringstream;

TEST(timestamp_test, format_test) {

    ptime time(date(2002, Jan, 10), hours(13) + minutes(5) + seconds(2) + milliseconds(23));

    time_facet* t = new time_facet("%A"); // Not a memory leak; the locale takes ownership. The more you know.
    locale loc(locale("en_US.utf8"), t);

    stringstream stream;
    stream.imbue(loc);
    stream << time;

    EXPECT_EQ(stream.str(), "Thursday");

}

TEST(timestamp_test, timestamp_reader_test) {

    try {
        TimestampReader reader("data/test");
        EXPECT_EQ(reader.start_time.date().year(), 2014);
        EXPECT_EQ(reader.start_time.date().day().as_number(), 24);
        EXPECT_EQ(reader.start_time.date().month().as_number(), 12);

        EXPECT_EQ(reader.start_time.time_of_day().hours(), 18);
        EXPECT_EQ(reader.start_time.time_of_day().minutes(), 42);
        EXPECT_EQ(reader.start_time.time_of_day().seconds(), 34);

        cout << reader.start_time << endl;

    } catch (IOException& e) {
        cerr << e.get_message() << endl;
        FAIL();
    }

}

TEST(timestamp_test, timestamp_calculator_test) {
    TimestampCalculator calculator("%Y-%m-%d %H:%M:%s:", ptime(date(2016, Feb, 1)), 125);

    cout << calculator.format_time(0) << endl;

}