#include <gtest/gtest.h>

#include "blet/dict.h"

GTEST_TEST(dict_null, new) {
    {
        EXPECT_THROW(
            {
                try {
                    blet::Dict dict;
                    dict = true;
                    dict.newNull();
                }
                catch (const blet::Dict::AccessException& e) {
                    EXPECT_STREQ(e.what(), "is not a null (is boolean).");
                    throw;
                }
            },
            blet::Dict::AccessException);
    }
    {
        blet::Dict dict;
        dict.newNull();
        EXPECT_EQ(dict.isNull(), true);
    }
}
