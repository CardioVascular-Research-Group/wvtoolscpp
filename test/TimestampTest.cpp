//
// Created by rliu14 on 6/28/16.
//

#include <gtest/gtest.h>

#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include "../src/io/TimestampReader.h"

using namespace boost::gregorian;
using namespace boost::posix_time;

using std::cout;
using std::endl;
using std::cerr;

TEST(timestamp_test, basic_arithmetic_test) {

    ptime time(date(2002, Jan, 10), hours(13) + minutes(5) + seconds(2) + milliseconds(23));

    cout << endl;
    cout << time << endl;
    cout << time + hours(2) << endl;

    cout << "timestamp " << (time - ptime(date(1970, 1, 1))).total_seconds() << endl;
}

TEST(timestamp_test, timestamp_reader_test) {

    try {
        TimestampReader reader("data/test");
        cout << reader.start_time << endl;

    } catch (IOException& e) {
        cerr << e.get_message() << endl;
        FAIL();
    }

}