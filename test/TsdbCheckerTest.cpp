//
// Created by ran on 7/6/16.
//

#include <gtest/gtest.h>
#include "../src/tsdb/TsdbChecker.h"


using std::vector;

/*TEST(tsdb_checker_test, test_presence) {

    TsdbChecker checker("http://localhost:3001");
    checker.check_presence("asdf", "asdf", 123);

}*/

TEST(tsdb_checker_test, test_validate) {

    //TsdbChecker checker("http://localhost:3001");

    vector<vector<double>> actuals;
    actuals.push_back(vector<double>());
    actuals[0].push_back(3);

}