#include <gtest/gtest.h>

#include "blet/dict.h"

GTEST_TEST(dict_array, exception) {
    EXPECT_THROW(
        {
            try {
                blet::Dict dict;
                dict = true;
                dict.newArray();
            }
            catch (const blet::Dict::AccessException& e) {
                EXPECT_STREQ(e.what(), "is not a array (is boolean).");
                throw;
            }
        },
        blet::Dict::AccessException);
    EXPECT_THROW(
        {
            try {
                blet::Dict dict;
                dict = true;
                dict.getArray();
            }
            catch (const blet::Dict::AccessException& e) {
                EXPECT_STREQ(e.what(), "is not a array (is boolean).");
                throw;
            }
        },
        blet::Dict::AccessException);
}

GTEST_TEST(dict_array, assign) {
    blet::Dict dict;
    dict.assign(42, blet::Dict(42));

    EXPECT_EQ(dict.size(), 42);

    for (std::size_t i = 0; i < dict.size(); ++i) {
        EXPECT_EQ(dict[i], 42);
    }
}

GTEST_TEST(dict_array, array) {
    blet::Dict dict;
    dict.newArray();
    EXPECT_EQ(dict.getArray().size(), 0);
    EXPECT_EQ(dict.getArray().size(), 0);

    blet::Dict::array_t::iterator it = dict.array_begin();

    dict.array_assign(it, it);

    dict[1]["test"].push_back("test");

    EXPECT_EQ(dict[1].at("test")[0], "test");
}