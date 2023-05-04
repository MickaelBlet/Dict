#include <gtest/gtest.h>

#include "blet/dict.h"

GTEST_TEST(dict_string, isString) {
    {
        blet::Dict dict;
        EXPECT_EQ(dict.isString(), false);
        dict = "foo";
        EXPECT_EQ(dict.isString(), true);
    }
    {
        blet::Dict dict(std::string("foo"));
        EXPECT_EQ(dict.isString(), true);
    }
    {
        char str[] = "foo";
        blet::Dict dict(str);
        EXPECT_EQ(dict.isString(), true);
    }
}

GTEST_TEST(dict_string, getString) {
    // is not String
    {
        EXPECT_THROW(
        {
            try {
                blet::Dict dict;
                dict = false;
                dict.getString();
            }
            catch (const blet::Dict::AccessException& e) {
                EXPECT_STREQ(e.what(), "is not a string (is boolean).");
                throw;
            }
        },
        blet::Dict::AccessException);
    }
    // create new String type
    {
        blet::Dict dict;
        dict.getString() = "foo";
        EXPECT_EQ(dict, "foo");
    }
}

GTEST_TEST(dict_string, getStringConst) {
    // is not String
    {
        EXPECT_THROW(
        {
            try {
                blet::Dict dict;
                dict = false;
                const blet::Dict& cdict = dict;
                cdict.getString();
            }
            catch (const blet::Dict::AccessException& e) {
                EXPECT_STREQ(e.what(), "is not a string (is boolean).");
                throw;
            }
        },
        blet::Dict::AccessException);
    }
    // create new String type
    {
        const blet::Dict dict("foo");
        EXPECT_EQ(dict.getString(), "foo");
    }
}

GTEST_TEST(dict_string, operatorEQ) {
    {
        blet::Dict dict;
        dict = std::string("foo");
        EXPECT_EQ(dict.getString(), "foo");
    }
    {
        blet::Dict dict;
        dict = "foo";
        EXPECT_EQ(dict.getString(), "foo");
    }
    {
        blet::Dict dict;
        char foo[] = "foo";
        dict = foo;
        EXPECT_EQ(dict.getString(), "foo");
    }
}

GTEST_TEST(dict_string, castOperator) {
    blet::Dict dict;
    dict = "foo";
    {
        std::string result;
        result = static_cast<const std::string&>(dict);
        EXPECT_EQ(result, "foo");
    }
    {
        const std::string& result = dict;
        EXPECT_EQ(result, "foo");
    }
    {
        const char* result = dict;
        EXPECT_STREQ(result, "foo");
    }
}

GTEST_TEST(dict_string, newString) {
    {
        EXPECT_THROW(
        {
            try {
                blet::Dict dict;
                dict = false;
                dict.newString(std::string("foo"));
            }
            catch (const blet::Dict::AccessException& e) {
                EXPECT_STREQ(e.what(), "is not a string (is boolean).");
                throw;
            }
        },
        blet::Dict::AccessException);
    }
    {
        EXPECT_THROW(
        {
            try {
                blet::Dict dict;
                dict = false;
                dict.newString(42);
            }
            catch (const blet::Dict::AccessException& e) {
                EXPECT_STREQ(e.what(), "is not a string (is boolean).");
                throw;
            }
        },
        blet::Dict::AccessException);
    }
    {
        blet::Dict dict;
        dict.newString(std::string("foo"));
        const std::string& result = dict.getString();
        EXPECT_EQ(result, "foo");
        dict.newString(std::string("bar"));
        EXPECT_EQ(result, "bar");
    }
    {
        blet::Dict dict;
        dict.newString(42);
        const std::string& result = dict.getString();
        EXPECT_EQ(result, "42");
        dict.newString(24);
        EXPECT_EQ(result, "24");
    }
}

GTEST_TEST(dict_string, append1) {
    {
        EXPECT_THROW(
        {
            try {
                blet::Dict dict;
                dict = false;
                dict.append(std::string("foo"));
            }
            catch (const blet::Dict::AccessException& e) {
                EXPECT_STREQ(e.what(), "is not a string (is boolean).");
                throw;
            }
        },
        blet::Dict::AccessException);
    }
    {
        blet::Dict dict;
        dict.append(std::string("foo"));
        EXPECT_EQ(dict, "foo");
    }
    {
        blet::Dict dict("foo");
        dict.append(std::string("bar"));
        EXPECT_EQ(dict, "foobar");
    }
}

GTEST_TEST(dict_string, append2) {
    {
        EXPECT_THROW(
        {
            try {
                blet::Dict dict;
                dict = false;
                dict.append(std::string("foo"), 1, 1);
            }
            catch (const blet::Dict::AccessException& e) {
                EXPECT_STREQ(e.what(), "is not a string (is boolean).");
                throw;
            }
        },
        blet::Dict::AccessException);
    }
    {
        blet::Dict dict;
        dict.append(std::string("foo"), 1, 1);
        EXPECT_EQ(dict, "o");
    }
    {
        blet::Dict dict("foo");
        dict.append(std::string("bar"), 1, 1);
        EXPECT_EQ(dict, "fooa");
    }
}

GTEST_TEST(dict_string, append3) {
    {
        EXPECT_THROW(
        {
            try {
                blet::Dict dict;
                dict = false;
                dict.append("foo", 1);
            }
            catch (const blet::Dict::AccessException& e) {
                EXPECT_STREQ(e.what(), "is not a string (is boolean).");
                throw;
            }
        },
        blet::Dict::AccessException);
    }
    {
        blet::Dict dict;
        dict.append("foo", 2);
        EXPECT_EQ(dict, "fo");
    }
    {
        blet::Dict dict("foo");
        dict.append("bar", 2);
        EXPECT_EQ(dict, "fooba");
    }
}

GTEST_TEST(dict_string, append4) {
    {
        EXPECT_THROW(
        {
            try {
                blet::Dict dict;
                dict = false;
                dict.append("foo");
            }
            catch (const blet::Dict::AccessException& e) {
                EXPECT_STREQ(e.what(), "is not a string (is boolean).");
                throw;
            }
        },
        blet::Dict::AccessException);
    }
    {
        blet::Dict dict;
        dict.append("foo");
        EXPECT_EQ(dict, "foo");
    }
    {
        blet::Dict dict("foo");
        dict.append("bar");
        EXPECT_EQ(dict, "foobar");
    }
}

GTEST_TEST(dict_string, append5) {
    {
        EXPECT_THROW(
        {
            try {
                blet::Dict dict;
                dict = false;
                dict.append(3, 'o');
            }
            catch (const blet::Dict::AccessException& e) {
                EXPECT_STREQ(e.what(), "is not a string (is boolean).");
                throw;
            }
        },
        blet::Dict::AccessException);
    }
    {
        blet::Dict dict;
        dict.append(3, 'o');
        EXPECT_EQ(dict, "ooo");
    }
    {
        blet::Dict dict("foo");
        dict.append(3, 'a');
        EXPECT_EQ(dict, "fooaaa");
    }
}

GTEST_TEST(dict_string, append6) {
    {
        EXPECT_THROW(
        {
            try {
                blet::Dict dict;
                dict = false;
                std::string str("foo");
                dict.string_append(str.begin(), str.end());
            }
            catch (const blet::Dict::AccessException& e) {
                EXPECT_STREQ(e.what(), "is not a string (is boolean).");
                throw;
            }
        },
        blet::Dict::AccessException);
    }
    {
        blet::Dict dict;
        std::string str("foo");
        dict.string_append(str.begin(), str.end());
        EXPECT_EQ(dict, "foo");
    }
    {
        blet::Dict dict("foo");
        std::string str("bar");
        dict.string_append(str.begin(), str.end());
        EXPECT_EQ(dict, "foobar");
    }
}

GTEST_TEST(dict_string, assign1) {
    {
        EXPECT_THROW(
        {
            try {
                blet::Dict dict;
                dict = false;
                dict.assign(std::string("foo"));
            }
            catch (const blet::Dict::AccessException& e) {
                EXPECT_STREQ(e.what(), "is not a string (is boolean).");
                throw;
            }
        },
        blet::Dict::AccessException);
    }
    {
        blet::Dict dict;
        dict.assign(std::string("foo"));
        EXPECT_EQ(dict, "foo");
    }
    {
        blet::Dict dict("foo");
        dict.assign(std::string("bar"));
        EXPECT_EQ(dict, "bar");
    }
}

GTEST_TEST(dict_string, assign2) {
    {
        EXPECT_THROW(
        {
            try {
                blet::Dict dict;
                dict = false;
                dict.assign(std::string("foo"), 1, 1);
            }
            catch (const blet::Dict::AccessException& e) {
                EXPECT_STREQ(e.what(), "is not a string (is boolean).");
                throw;
            }
        },
        blet::Dict::AccessException);
    }
    {
        blet::Dict dict;
        dict.assign(std::string("foo"), 1, 1);
        EXPECT_EQ(dict, "o");
    }
    {
        blet::Dict dict("foo");
        dict.assign(std::string("bar"), 1, 1);
        EXPECT_EQ(dict, "a");
    }
}

GTEST_TEST(dict_string, assign3) {
    {
        EXPECT_THROW(
        {
            try {
                blet::Dict dict;
                dict = false;
                dict.assign("foo", 1);
            }
            catch (const blet::Dict::AccessException& e) {
                EXPECT_STREQ(e.what(), "is not a string (is boolean).");
                throw;
            }
        },
        blet::Dict::AccessException);
    }
    {
        blet::Dict dict;
        dict.assign("foo", 2);
        EXPECT_EQ(dict, "fo");
    }
    {
        blet::Dict dict("foo");
        dict.assign("bar", 2);
        EXPECT_EQ(dict, "ba");
    }
}

GTEST_TEST(dict_string, assign4) {
    {
        EXPECT_THROW(
        {
            try {
                blet::Dict dict;
                dict = false;
                dict.assign("foo");
            }
            catch (const blet::Dict::AccessException& e) {
                EXPECT_STREQ(e.what(), "is not a string (is boolean).");
                throw;
            }
        },
        blet::Dict::AccessException);
    }
    {
        blet::Dict dict;
        dict.assign("foo");
        EXPECT_EQ(dict, "foo");
    }
    {
        blet::Dict dict("foo");
        dict.assign("bar");
        EXPECT_EQ(dict, "bar");
    }
}

GTEST_TEST(dict_string, assign5) {
    {
        EXPECT_THROW(
        {
            try {
                blet::Dict dict;
                dict = false;
                dict.assign(3, 'o');
            }
            catch (const blet::Dict::AccessException& e) {
                EXPECT_STREQ(e.what(), "is not a string (is boolean).");
                throw;
            }
        },
        blet::Dict::AccessException);
    }
    {
        blet::Dict dict;
        dict.assign(3, 'o');
        EXPECT_EQ(dict, "ooo");
    }
    {
        blet::Dict dict("foo");
        dict.assign(3, 'a');
        EXPECT_EQ(dict, "aaa");
    }
}

GTEST_TEST(dict_string, assign6) {
    {
        EXPECT_THROW(
        {
            try {
                blet::Dict dict;
                dict = false;
                std::string str("foo");
                dict.string_assign(str.begin(), str.end());
            }
            catch (const blet::Dict::AccessException& e) {
                EXPECT_STREQ(e.what(), "is not a string (is boolean).");
                throw;
            }
        },
        blet::Dict::AccessException);
    }
    {
        blet::Dict dict;
        std::string str("foo");
        dict.string_assign(str.begin(), str.end());
        EXPECT_EQ(dict, "foo");
    }
    {
        blet::Dict dict("foo");
        std::string str("bar");
        dict.string_assign(str.begin(), str.end());
        EXPECT_EQ(dict, "bar");
    }
}

GTEST_TEST(dict_string, begin) {
    {
        EXPECT_THROW(
        {
            try {
                blet::Dict dict;
                dict = false;
                dict.string_begin();
            }
            catch (const blet::Dict::AccessException& e) {
                EXPECT_STREQ(e.what(), "is not a string (is boolean).");
                throw;
            }
        },
        blet::Dict::AccessException);
    }
    {
        blet::Dict dict("foo");
        EXPECT_EQ(*(dict.string_begin()),     'f');
        EXPECT_EQ(*(dict.string_begin() + 1), 'o');
        EXPECT_EQ(*(dict.string_begin() + 2), 'o');
    }
    {
        const blet::Dict dict("foo");
        EXPECT_EQ(*(dict.string_begin()),     'f');
        EXPECT_EQ(*(dict.string_begin() + 1), 'o');
        EXPECT_EQ(*(dict.string_begin() + 2), 'o');
    }
}

GTEST_TEST(dict_string, beginConst) {
    {
        EXPECT_THROW(
        {
            try {
                blet::Dict dict;
                dict = false;
                const blet::Dict& cdict = dict;
                cdict.string_begin();
            }
            catch (const blet::Dict::AccessException& e) {
                EXPECT_STREQ(e.what(), "is not a string (is boolean).");
                throw;
            }
        },
        blet::Dict::AccessException);
    }
    {
        const blet::Dict dict("foo");
        EXPECT_EQ(*(dict.string_begin()),     'f');
        EXPECT_EQ(*(dict.string_begin() + 1), 'o');
        EXPECT_EQ(*(dict.string_begin() + 2), 'o');
    }
}

GTEST_TEST(dict_string, c_str) {
    {
        EXPECT_THROW(
        {
            try {
                blet::Dict dict;
                dict = false;
                dict.c_str();
            }
            catch (const blet::Dict::AccessException& e) {
                EXPECT_STREQ(e.what(), "is not a string (is boolean).");
                throw;
            }
        },
        blet::Dict::AccessException);
    }
    {
        const blet::Dict dict("foo");
        EXPECT_STREQ(dict.c_str(), "foo");
    }
}

GTEST_TEST(dict_string, compare1) {
    {
        EXPECT_THROW(
        {
            try {
                blet::Dict dict;
                dict = false;
                dict.compare(std::string("foo"));
            }
            catch (const blet::Dict::AccessException& e) {
                EXPECT_STREQ(e.what(), "is not a string (is boolean).");
                throw;
            }
        },
        blet::Dict::AccessException);
    }
    {
        blet::Dict dict("foo");
        EXPECT_EQ(dict.compare(std::string("foo")), 0);
    }
    {
        blet::Dict dict("foo");
        EXPECT_GT(dict.compare(std::string("bar")), 0);
    }
    {
        blet::Dict dict("bar");
        EXPECT_LT(dict.compare(std::string("foo")), 0);
    }
}

GTEST_TEST(dict_string, compare2) {
    {
        EXPECT_THROW(
        {
            try {
                blet::Dict dict;
                dict = false;
                dict.compare(1, 0, std::string("foo"));
            }
            catch (const blet::Dict::AccessException& e) {
                EXPECT_STREQ(e.what(), "is not a string (is boolean).");
                throw;
            }
        },
        blet::Dict::AccessException);
    }
    {
        blet::Dict dict("fooabc");
        EXPECT_EQ(dict.compare(1, 5, std::string("ooabc")), 0);
    }
    {
        blet::Dict dict("foo");
        EXPECT_GT(dict.compare(1, 3, std::string("bar")), 0);
    }
    {
        blet::Dict dict("bar");
        EXPECT_LT(dict.compare(1, 3, std::string("foo")), 0);
    }
}

GTEST_TEST(dict_string, compare3) {
    {
        EXPECT_THROW(
        {
            try {
                blet::Dict dict;
                dict = false;
                dict.compare(1, 0, std::string("foo"), 0, 2);
            }
            catch (const blet::Dict::AccessException& e) {
                EXPECT_STREQ(e.what(), "is not a string (is boolean).");
                throw;
            }
        },
        blet::Dict::AccessException);
    }
    {
        blet::Dict dict("foab");
        EXPECT_EQ(dict.compare(1, 3, std::string("ooabc"), 1, 3), 0);
    }
    {
        blet::Dict dict("foo");
        EXPECT_GT(dict.compare(1, 2, std::string("bar"), 1), 0);
    }
    {
        blet::Dict dict("bar");
        EXPECT_LT(dict.compare(1, 2, std::string("foo"), 1), 0);
    }
}

GTEST_TEST(dict_string, compare4) {
    {
        EXPECT_THROW(
        {
            try {
                blet::Dict dict;
                dict = false;
                dict.compare("foo");
            }
            catch (const blet::Dict::AccessException& e) {
                EXPECT_STREQ(e.what(), "is not a string (is boolean).");
                throw;
            }
        },
        blet::Dict::AccessException);
    }
    {
        blet::Dict dict("foo");
        EXPECT_EQ(dict.compare("foo"), 0);
    }
    {
        blet::Dict dict("foo");
        EXPECT_GT(dict.compare("bar"), 0);
    }
    {
        blet::Dict dict("bar");
        EXPECT_LT(dict.compare("foo"), 0);
    }
}