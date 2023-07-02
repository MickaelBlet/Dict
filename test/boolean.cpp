#include <gtest/gtest.h>

#include "blet/dict.h"

GTEST_TEST(dict_boolean, isBoolean) {
    blet::Dict dict;
    EXPECT_EQ(dict.isBoolean(), false);
    dict = false;
    EXPECT_EQ(dict.isBoolean(), true);
}

GTEST_TEST(dict_boolean, getBoolean) {
    // is not boolean
    {
        EXPECT_THROW(
            {
                try {
                    blet::Dict dict;
                    dict = 0;
                    dict.getBoolean();
                }
                catch (const blet::Dict::AccessException& e) {
                    EXPECT_STREQ(e.what(), "is not a boolean (is number).");
                    throw;
                }
            },
            blet::Dict::AccessException);
    }
    // create new boolean type
    {
        blet::Dict dict;
        dict.getBoolean() = true;
        EXPECT_EQ(dict, true);
    }
}

GTEST_TEST(dict_boolean, getBooleanConst) {
    // is not boolean
    {
        EXPECT_THROW(
            {
                try {
                    blet::Dict dict;
                    dict = 0;
                    const blet::Dict& cdict = dict;
                    cdict.getBoolean();
                }
                catch (const blet::Dict::AccessException& e) {
                    EXPECT_STREQ(e.what(), "is not a boolean (is number).");
                    throw;
                }
            },
            blet::Dict::AccessException);
    }
    // create new boolean type
    {
        const blet::Dict dict(true);
        EXPECT_EQ(dict.getBoolean(), true);
    }
}

GTEST_TEST(dict_boolean, operatorEQ) {
    blet::Dict dict;
    dict = true;
    EXPECT_EQ(dict.getBoolean(), true);
}

GTEST_TEST(dict_boolean, castOperator) {
    blet::Dict dict;
    dict = true;
    bool result;
    result = dict;
    EXPECT_EQ(result, true);
}

GTEST_TEST(dict_boolean, newBoolean) {
    {
        EXPECT_THROW(
            {
                try {
                    blet::Dict dict;
                    dict = 0;
                    dict.newBoolean();
                }
                catch (const blet::Dict::AccessException& e) {
                    EXPECT_STREQ(e.what(), "is not a boolean (is number).");
                    throw;
                }
            },
            blet::Dict::AccessException);
    }
    {
        blet::Dict dict;
        dict.newBoolean();
        bool result;
        result = dict;
        EXPECT_EQ(result, false);
    }
    {
        EXPECT_THROW(
            {
                try {
                    blet::Dict dict;
                    dict = 0;
                    dict.newBoolean(true);
                }
                catch (const blet::Dict::AccessException& e) {
                    EXPECT_STREQ(e.what(), "is not a boolean (is number).");
                    throw;
                }
            },
            blet::Dict::AccessException);
    }
    {
        blet::Dict dict;
        dict.newBoolean(true);
        bool result;
        result = dict;
        EXPECT_EQ(result, true);
    }
}

GTEST_TEST(dict_boolean, operatorEQEQ) {
    blet::Dict dict(42);
    EXPECT_EQ(dict == true, false);
    dict.clear();
    dict = false;
    EXPECT_EQ(dict == false, true);
    EXPECT_EQ(dict == true, false);
    dict = true;
    EXPECT_EQ(dict == false, false);
    EXPECT_EQ(dict == true, true);
}

GTEST_TEST(dict_boolean, operatorNEQ) {
    blet::Dict dict(42);
    EXPECT_EQ(dict != true, true);
    dict.clear();
    dict = false;
    EXPECT_EQ(dict != false, false);
    EXPECT_EQ(dict != true, true);
    dict = true;
    EXPECT_EQ(dict != false, true);
    EXPECT_EQ(dict != true, false);
}

GTEST_TEST(dict_boolean, operatorGR) {
    blet::Dict dict(42);
    EXPECT_EQ(dict > true, false);
    dict.clear();
    dict = false;
    EXPECT_EQ(dict > false, false);
    EXPECT_EQ(dict > true, false);
    dict = true;
    EXPECT_EQ(dict > false, true);
    EXPECT_EQ(dict > true, false);
}

GTEST_TEST(dict_boolean, operatorLE) {
    blet::Dict dict(42);
    EXPECT_EQ(dict < true, false);
    dict.clear();
    dict = false;
    EXPECT_EQ(dict < false, false);
    EXPECT_EQ(dict < true, true);
    dict = true;
    EXPECT_EQ(dict < false, false);
    EXPECT_EQ(dict < true, false);
}

GTEST_TEST(dict_boolean, operatorGREQ) {
    blet::Dict dict(42);
    EXPECT_EQ(dict >= true, false);
    dict.clear();
    dict = false;
    EXPECT_EQ(dict >= false, true);
    EXPECT_EQ(dict >= true, false);
    dict = true;
    EXPECT_EQ(dict >= false, true);
    EXPECT_EQ(dict >= true, true);
}

GTEST_TEST(dict_boolean, operatorLEEQ) {
    blet::Dict dict(42);
    EXPECT_EQ(dict <= true, false);
    dict.clear();
    dict = false;
    EXPECT_EQ(dict <= false, true);
    EXPECT_EQ(dict <= true, true);
    dict = true;
    EXPECT_EQ(dict <= false, false);
    EXPECT_EQ(dict <= true, true);
}