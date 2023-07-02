#include <gtest/gtest.h>

#include "blet/dict.h"

GTEST_TEST(dict_exception, Exception) {
    EXPECT_THROW(
        {
            try {
                throw blet::Dict::Exception("foo");
            }
            catch (const blet::Dict::Exception& e) {
                EXPECT_STREQ(e.what(), "foo");
                throw;
            }
        },
        blet::Dict::Exception);
}

GTEST_TEST(dict_exception, AccessException) {
    EXPECT_THROW(
        {
            blet::Dict dict;
            try {
                throw blet::Dict::AccessException(dict, "foo");
            }
            catch (const blet::Dict::AccessException& e) {
                EXPECT_STREQ(e.what(), "foo (is null).");
                EXPECT_EQ(&dict, &e.dict());
                throw;
            }
        },
        blet::Dict::AccessException);
}

GTEST_TEST(dict_exception, ChildException) {
    EXPECT_THROW(
        {
            blet::Dict dict;
            try {
                throw blet::Dict::ChildException(dict, 42);
            }
            catch (const blet::Dict::ChildException& e) {
                EXPECT_STREQ(e.what(), "42 has out of range.");
                EXPECT_EQ(&dict, &e.dict());
                EXPECT_EQ(e.index(), 42);
                throw;
            }
        },
        blet::Dict::ChildException);
    EXPECT_THROW(
        {
            blet::Dict dict;
            try {
                throw blet::Dict::ChildException(dict, "foo");
            }
            catch (const blet::Dict::ChildException& e) {
                EXPECT_STREQ(e.what(), "foo has not a key.");
                EXPECT_EQ(&dict, &e.dict());
                EXPECT_EQ(e.key(), "foo");
                throw;
            }
        },
        blet::Dict::ChildException);
}

GTEST_TEST(dict_exception, MethodException) {
    EXPECT_THROW(
        {
            blet::Dict dict;
            try {
                throw blet::Dict::MethodException(dict, "foo");
            }
            catch (const blet::Dict::MethodException& e) {
                EXPECT_STREQ(e.what(), "has not a method foo.");
                EXPECT_EQ(&dict, &e.dict());
                EXPECT_EQ(e.methodName(), "foo");
                throw;
            }
        },
        blet::Dict::MethodException);
}