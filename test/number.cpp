#include <gtest/gtest.h>

#include "blet/dict.h"

GTEST_TEST(dict_number, isNumber) {
    blet::Dict dict;
    EXPECT_EQ(dict.isNumber(), false);
    dict = 42;
    EXPECT_EQ(dict.isNumber(), true);
}

GTEST_TEST(dict_number, getNumber) {
    // is not Number
    {
        EXPECT_THROW(
        {
            try {
                blet::Dict dict;
                dict = false;
                dict.getNumber();
            }
            catch (const blet::Dict::AccessException& e) {
                EXPECT_STREQ(e.what(), "is not a number (is boolean).");
                throw;
            }
        },
        blet::Dict::AccessException);
    }
    // create new Number type
    {
        blet::Dict dict;
        dict.getNumber() = 42;
        EXPECT_EQ(dict, 42);
    }
}

GTEST_TEST(dict_number, getNumberConst) {
    // is not Number
    {
        EXPECT_THROW(
        {
            try {
                blet::Dict dict;
                dict = false;
                const blet::Dict& cdict = dict;
                cdict.getNumber();
            }
            catch (const blet::Dict::AccessException& e) {
                EXPECT_STREQ(e.what(), "is not a number (is boolean).");
                throw;
            }
        },
        blet::Dict::AccessException);
    }
    // create new Number type
    {
        const blet::Dict dict(42);
        EXPECT_EQ(dict.getNumber(), 42);
    }
}

GTEST_TEST(dict_number, operatorEQ) {
    blet::Dict dict;
    dict = 42;
    EXPECT_EQ(dict.getNumber(), 42);
}

GTEST_TEST(dict_number, castOperator) {
    blet::Dict dict;
    dict = 42;
    double result;
    result = dict;
    EXPECT_EQ(result, 42);
}

GTEST_TEST(dict_number, newNumber) {
    {
        EXPECT_THROW(
        {
            try {
                blet::Dict dict;
                dict = false;
                dict.newNumber(42);
            }
            catch (const blet::Dict::AccessException& e) {
                EXPECT_STREQ(e.what(), "is not a number (is boolean).");
                throw;
            }
        },
        blet::Dict::AccessException);
    }
    {
        blet::Dict dict;
        dict.newNumber(42);
        int result;
        result = dict;
        EXPECT_EQ(result, 42);
    }
}

GTEST_TEST(dict_number, operatorEQEQ) {
    blet::Dict dict(true);
    EXPECT_EQ(dict == 42, false);
    dict.clear();
    dict = 42;
    EXPECT_EQ(dict == 42, true);
    EXPECT_EQ(dict == 24, false);
    dict = 24;
    EXPECT_EQ(dict == 42, false);
    EXPECT_EQ(dict == 24, true);
}

GTEST_TEST(dict_number, operatorNEQ) {
    blet::Dict dict(true);
    EXPECT_EQ(dict != 42, true);
    dict.clear();
    dict = 42;
    EXPECT_EQ(dict != 42, false);
    EXPECT_EQ(dict != 24, true);
    dict = 24;
    EXPECT_EQ(dict != 42, true);
    EXPECT_EQ(dict != 24, false);
}

GTEST_TEST(dict_number, operatorGR) {
    blet::Dict dict(true);
    EXPECT_EQ(dict > 42, false);
    dict.clear();
    dict = 42;
    EXPECT_EQ(dict > 42, false);
    EXPECT_EQ(dict > 24, true);
    dict = 24;
    EXPECT_EQ(dict > 42, false);
    EXPECT_EQ(dict > 24, false);
}

GTEST_TEST(dict_number, operatorLE) {
    blet::Dict dict(true);
    EXPECT_EQ(dict < 42, false);
    dict.clear();
    dict = 42;
    EXPECT_EQ(dict < 42, false);
    EXPECT_EQ(dict < 24, false);
    dict = 24;
    EXPECT_EQ(dict < 42, true);
    EXPECT_EQ(dict < 24, false);
}

GTEST_TEST(dict_number, operatorGREQ) {
    blet::Dict dict(true);
    EXPECT_EQ(dict >= 42, false);
    dict.clear();
    dict = 42;
    EXPECT_EQ(dict >= 42, true);
    EXPECT_EQ(dict >= 24, true);
    dict = 24;
    EXPECT_EQ(dict >= 42, false);
    EXPECT_EQ(dict >= 24, true);
}

GTEST_TEST(dict_number, operatorLEEQ) {
    blet::Dict dict(true);
    EXPECT_EQ(dict <= 42, false);
    dict.clear();
    dict = 42;
    EXPECT_EQ(dict <= 42, true);
    EXPECT_EQ(dict <= 24, false);
    dict = 24;
    EXPECT_EQ(dict <= 42, true);
    EXPECT_EQ(dict <= 24, true);
}