//
// Created by rliu14 on 6/29/16.
//

#include <vector>

#include <gtest/gtest.h>
#include "../src/tsdb/TsdbUploader.h"

using nlohmann::json;

using std::cout;
using std::endl;
using std::vector;

TEST(tsdb_uploader_test, create_json_entry_test) {

    TsdbUploader uploader(1, "asdf");

    TsdbUploader::data_entry entry;
    entry.metric = "ECG";
    entry.timestamp = 42;
    entry.value = 3.14159;
    entry.tags["uid"] = "asdfasfd";

    EXPECT_EQ(TsdbUploader::create_json_entry(entry).dump(), "{\"metric\":\"ECG\",\"tags\":{\"uid\":\"asdfasfd\"},\"timestamp\":42,\"value\":3.14159}");
    cout << TsdbUploader::create_json_entry(entry) << endl;

}

TEST(tsdb_uploader_test, json_array_test) {

    vector<json> objects;

    json x1 = {
            {"asdf", 1},
            {"awooga", 35}
    };
    json x2 = {
            {"fdsa", 42},
            {"asdfasfd", true}
    };

    objects.push_back(x1);
    objects.push_back(x2);

    json array(objects);

    cout << array << endl;

    EXPECT_EQ(array.dump(), "[{\"asdf\":1,\"awooga\":35},{\"asdfasfd\":true,\"fdsa\":42}]");

}

/*TEST(tsdb_uploader_test, flush_test) {

    TsdbUploader uploader(2, "asfd");

    uploader.add_data_point("ECG", 315, 3.2, {{"uid", "awooga"}});
    uploader.add_data_point("ECG", 234, 5.22, {{"uid", "fdsa"}});

    uploader.add_data_point("ECG", 1234, 7.2, {{"uid", "asdf"}});
    uploader.add_data_point("ECG", 12, 2.2, {{"uid", "wer"}});

}*/

/*

TEST(tsdb_uploader_test, query_tsuid_test) {

    TsdbUploader uploader(25, "http://localhost:3001");
    auto result = uploader.query_tsuid("ecg", 1419446554000, {{"subject_id", "2224BN1416911131-20141224-184234"}});
    cout << result << endl;

}
*/
