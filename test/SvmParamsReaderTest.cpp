//
// Created by rliu14 on 6/27/16.
//

#include "gtest/gtest.h"
#include "../src/util/SvmParams.h"

using std::cerr;
using std::endl;

using std::vector;

TEST(svm_params_reader_test, tokenize_test) {

    vector<double> result = SvmParams::tokenize("3 -5 2.535");
    EXPECT_EQ(3, result.size());
    EXPECT_EQ(3, result[0]);
    EXPECT_EQ(-5, result[1]);
    EXPECT_EQ(2.535, result[2]);

}

TEST(svm_params_reader_test, read_file) {

    try {
        SvmParams reader("data/svm.txt");
        EXPECT_EQ(reader.coefficients.size(), 9);
        EXPECT_EQ(reader.means.size(), 9);
        EXPECT_EQ(reader.sigmas.size(), 9);
        EXPECT_EQ(reader.bias, 2.8);

    } catch (IOException& e) {
        cerr << e.get_message() << endl;
        FAIL();
    }

}