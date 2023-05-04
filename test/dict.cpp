#include "blet/dict.h"

#include <gtest/gtest.h>

GTEST_TEST(dict, array) {
    blet::Dict dict;
    dict.newString("foo");
    blet::Dict dict2;
    dict2.newNumber(42);

    EXPECT_EQ(dict, "foo");
    EXPECT_EQ(dict2, 42);

    // if (dict2 != 24) {
    //     EXPECT_EQ(true, false);
    // }

    dict.swap(dict2);

    EXPECT_EQ(dict2, "foo");
    EXPECT_EQ(dict, 42);
}