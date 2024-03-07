#include <gtest/gtest.h>

#include "blet/dict.h"

GTEST_TEST(dict_common, at) {
    {
        blet::Dict dict;
        dict["foo"][3] = 42;
        EXPECT_EQ(dict.at(blet::Dict::Path()["foo"][3]), 42);
    }
    {
        blet::Dict dict;
        dict["foo"][3] = 42;
        const blet::Dict& cdict = dict;
        EXPECT_EQ(cdict.at(blet::Dict::Path()["foo"][3]), 42);
    }
    {
        EXPECT_THROW(
            {
                try {
                    blet::Dict dict;
                    dict["foo"][3] = 42;
                    dict.at(blet::Dict::Path()["bar"][3]);
                }
                catch (const blet::Dict::ChildException& e) {
                    EXPECT_STREQ(e.what(), "bar has not a key.");
                    throw;
                }
            },
            blet::Dict::ChildException);
        EXPECT_THROW(
            {
                try {
                    blet::Dict dict;
                    dict[3] = 42;
                    dict.at(blet::Dict::Path()[4]);
                }
                catch (const blet::Dict::ChildException& e) {
                    EXPECT_STREQ(e.what(), "4 has out of range.");
                    throw;
                }
            },
            blet::Dict::ChildException);
        EXPECT_THROW(
            {
                try {
                    blet::Dict dict;
                    dict["foo"][3] = 42;
                    dict.at(blet::Dict::Path()[3]);
                }
                catch (const blet::Dict::AccessException& e) {
                    EXPECT_STREQ(e.what(), "wrong type of child (is object).");
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
                    dict["foo"][3] = 42;
                    const blet::Dict& cdict = dict;
                    cdict.at(blet::Dict::Path()["bar"]);
                }
                catch (const blet::Dict::ChildException& e) {
                    EXPECT_STREQ(e.what(), "bar has not a key.");
                    throw;
                }
            },
            blet::Dict::ChildException);
        EXPECT_THROW(
            {
                try {
                    blet::Dict dict;
                    dict[3] = 42;
                    const blet::Dict& cdict = dict;
                    cdict.at(blet::Dict::Path()[4]);
                }
                catch (const blet::Dict::ChildException& e) {
                    EXPECT_STREQ(e.what(), "4 has out of range.");
                    throw;
                }
            },
            blet::Dict::ChildException);
        EXPECT_THROW(
            {
                try {
                    blet::Dict dict;
                    dict["foo"][3] = 42;
                    const blet::Dict& cdict = dict;
                    cdict.at(blet::Dict::Path()[3]);
                }
                catch (const blet::Dict::AccessException& e) {
                    EXPECT_STREQ(e.what(), "wrong type of child (is object).");
                    throw;
                }
            },
            blet::Dict::AccessException);
    }
}

GTEST_TEST(dict_common, capacity) {
    {
        EXPECT_THROW(
            {
                try {
                    blet::Dict dict(false);
                    dict.capacity();
                }
                catch (const blet::Dict::MethodException& e) {
                    EXPECT_STREQ(e.what(), "has not a method capacity.");
                    throw;
                }
            },
            blet::Dict::MethodException);
    }
    {
        blet::Dict dict;
        dict.newString();
        EXPECT_GE(dict.capacity(), 0);
    }
    {
        blet::Dict dict;
        dict.newArray();
        EXPECT_GE(dict.capacity(), 0);
    }
}

GTEST_TEST(dict_common, contains) {
    {
        blet::Dict dict;
        dict["foo"][3] = 42;
        EXPECT_EQ(dict.contains(blet::Dict::Path()["foo"][3]), true);
        EXPECT_EQ(dict.contains(blet::Dict::Path()["bar"][3]), false);
        EXPECT_EQ(dict.contains(blet::Dict::Path()["foo"][4]), false);
        EXPECT_EQ(dict.contains(blet::Dict::Path()["foo"][3][false]), false);
    }
    {
        blet::Dict dict;
        dict["foo"][3] = 42;
        EXPECT_EQ(dict.contains(blet::Dict::Path()["foo"][3], dict.NUMBER_TYPE), true);
        EXPECT_EQ(dict.contains(blet::Dict::Path()["foo"][3], dict.STRING_TYPE), false);
        EXPECT_EQ(dict.contains(blet::Dict::Path()["bar"][3], dict.NUMBER_TYPE), false);
        EXPECT_EQ(dict.contains(blet::Dict::Path()["foo"][4], dict.NUMBER_TYPE), false);
        EXPECT_EQ(dict.contains(blet::Dict::Path()["foo"][3][false], dict.NUMBER_TYPE), false);
    }
}

GTEST_TEST(dict_common, empty) {
    {
        EXPECT_THROW(
            {
                try {
                    blet::Dict dict(false);
                    dict.empty();
                }
                catch (const blet::Dict::MethodException& e) {
                    EXPECT_STREQ(e.what(), "has not a method empty.");
                    throw;
                }
            },
            blet::Dict::MethodException);
    }
    {
        blet::Dict dict;
        dict.newString();
        EXPECT_EQ(dict.empty(), true);
    }
    {
        blet::Dict dict;
        dict.newArray();
        EXPECT_EQ(dict.empty(), true);
    }
    {
        blet::Dict dict;
        dict.newObject();
        EXPECT_EQ(dict.empty(), true);
    }
}

GTEST_TEST(dict_common, max_size) {
    {
        EXPECT_THROW(
            {
                try {
                    blet::Dict dict(false);
                    dict.max_size();
                }
                catch (const blet::Dict::MethodException& e) {
                    EXPECT_STREQ(e.what(), "has not a method max_size.");
                    throw;
                }
            },
            blet::Dict::MethodException);
    }
    {
        blet::Dict dict;
        dict.newString();
        EXPECT_GE(dict.max_size(), 0);
    }
    {
        blet::Dict dict;
        dict.newArray();
        EXPECT_GE(dict.max_size(), 0);
    }
    {
        blet::Dict dict;
        dict.newObject();
        EXPECT_GE(dict.max_size(), 0);
    }
}

GTEST_TEST(dict_common, reserve) {
    {
        EXPECT_THROW(
            {
                try {
                    blet::Dict dict(false);
                    dict.reserve();
                }
                catch (const blet::Dict::MethodException& e) {
                    EXPECT_STREQ(e.what(), "has not a method reserve.");
                    throw;
                }
            },
            blet::Dict::MethodException);
    }
    {
        blet::Dict dict;
        dict.newString();
        dict.reserve(42);
    }
    {
        blet::Dict dict;
        dict.newArray();
        dict.reserve(42);
    }
}

GTEST_TEST(dict_common, resize) {
    {
        EXPECT_THROW(
            {
                try {
                    blet::Dict dict(false);
                    dict.resize(42);
                }
                catch (const blet::Dict::MethodException& e) {
                    EXPECT_STREQ(e.what(), "has not a method resize.");
                    throw;
                }
            },
            blet::Dict::MethodException);
    }
    {
        blet::Dict dict;
        dict.newString();
        dict.resize(42);
    }
    {
        blet::Dict dict;
        dict.newArray();
        dict.resize(42);
    }
}

GTEST_TEST(dict_common, size) {
    {
        EXPECT_THROW(
            {
                try {
                    blet::Dict dict(false);
                    dict.size();
                }
                catch (const blet::Dict::MethodException& e) {
                    EXPECT_STREQ(e.what(), "has not a method size.");
                    throw;
                }
            },
            blet::Dict::MethodException);
    }
    {
        blet::Dict dict;
        dict.newString();
        EXPECT_EQ(dict.size(), 0);
    }
    {
        blet::Dict dict;
        dict.newArray();
        EXPECT_EQ(dict.size(), 0);
    }
    {
        blet::Dict dict;
        dict.newObject();
        EXPECT_EQ(dict.size(), 0);
    }
}

GTEST_TEST(dict_common, operatorEQEQ) {
    {
        blet::Dict dict1;
        blet::Dict dict2;
        EXPECT_EQ(dict1, dict2);
    }
    {
        blet::Dict dict1(true);
        blet::Dict dict2(true);
        EXPECT_EQ(dict1, dict2);
    }
    {
        blet::Dict dict1(42);
        blet::Dict dict2(42);
        EXPECT_EQ(dict1, dict2);
    }
    {
        blet::Dict dict1("foo");
        blet::Dict dict2("foo");
        EXPECT_EQ(dict1, dict2);
    }
    {
        std::vector<int> v;
        v.push_back(42);
        v.push_back(24);
        blet::Dict dict1(v);
        blet::Dict dict2(v);
        EXPECT_EQ(dict1, dict2);
    }
    {
        std::map<std::string, int> m;
        m.insert(std::map<std::string, int>::value_type("foo", 42));
        m.insert(std::map<std::string, int>::value_type("bar", 24));
        blet::Dict dict1(m);
        blet::Dict dict2(m);
        EXPECT_EQ(dict1, dict2);
    }
    {
        blet::Dict dict1(42);
        blet::Dict dict2("foo");
        EXPECT_EQ(dict1 == dict2, false);
    }
}

GTEST_TEST(dict_common, operatorNE) {
    {
        blet::Dict dict1(42);
        blet::Dict dict2("foo");
        EXPECT_EQ(dict1 != dict2, true);
    }
}

GTEST_TEST(dict_common, operatorGT) {
    {
        blet::Dict dict1;
        blet::Dict dict2;
        EXPECT_EQ(dict1 > dict2, true);
    }
    {
        blet::Dict dict1(true);
        blet::Dict dict2(false);
        EXPECT_EQ(dict1 > dict2, true);
    }
    {
        blet::Dict dict1(42);
        blet::Dict dict2(24);
        EXPECT_EQ(dict1 > dict2, true);
    }
    {
        blet::Dict dict1("foobar");
        blet::Dict dict2("foo");
        EXPECT_EQ(dict1 > dict2, true);
    }
    {
        std::vector<int> v1;
        v1.push_back(42);
        v1.push_back(24);
        std::vector<int> v2;
        v2.push_back(42);
        v2.push_back(23);
        blet::Dict dict1(v1);
        blet::Dict dict2(v2);
        EXPECT_EQ(dict1 > dict2, true);
    }
    {
        std::map<std::string, int> m1;
        m1.insert(std::map<std::string, int>::value_type("foo", 42));
        m1.insert(std::map<std::string, int>::value_type("bar", 24));
        std::map<std::string, int> m2;
        m2.insert(std::map<std::string, int>::value_type("foo", 42));
        m2.insert(std::map<std::string, int>::value_type("bar", 23));
        blet::Dict dict1(m1);
        blet::Dict dict2(m2);
        EXPECT_EQ(dict1 > dict2, true);
    }
    {
        blet::Dict dict1(42);
        blet::Dict dict2("foo");
        EXPECT_EQ(dict1 > dict2, false);
    }
}

GTEST_TEST(dict_common, operatorLT) {
    {
        blet::Dict dict1;
        blet::Dict dict2;
        EXPECT_EQ(dict1 < dict2, true);
    }
    {
        blet::Dict dict1(false);
        blet::Dict dict2(true);
        EXPECT_EQ(dict1 < dict2, true);
    }
    {
        blet::Dict dict1(24);
        blet::Dict dict2(42);
        EXPECT_EQ(dict1 < dict2, true);
    }
    {
        blet::Dict dict1("foo");
        blet::Dict dict2("foobar");
        EXPECT_EQ(dict1 < dict2, true);
    }
    {
        std::vector<int> v1;
        v1.push_back(42);
        v1.push_back(24);
        std::vector<int> v2;
        v2.push_back(42);
        v2.push_back(23);
        blet::Dict dict1(v2);
        blet::Dict dict2(v1);
        EXPECT_EQ(dict1 < dict2, true);
    }
    {
        std::map<std::string, int> m1;
        m1.insert(std::map<std::string, int>::value_type("foo", 42));
        m1.insert(std::map<std::string, int>::value_type("bar", 24));
        std::map<std::string, int> m2;
        m2.insert(std::map<std::string, int>::value_type("foo", 42));
        m2.insert(std::map<std::string, int>::value_type("bar", 23));
        blet::Dict dict1(m2);
        blet::Dict dict2(m1);
        EXPECT_EQ(dict1 < dict2, true);
    }
    {
        blet::Dict dict1(42);
        blet::Dict dict2("foo");
        EXPECT_EQ(dict1 < dict2, false);
    }
}

GTEST_TEST(dict_common, operatorGE) {
    {
        blet::Dict dict1;
        blet::Dict dict2;
        EXPECT_EQ(dict1 >= dict2, true);
    }
    {
        blet::Dict dict1(true);
        blet::Dict dict2(false);
        EXPECT_EQ(dict1 >= dict2, true);
    }
    {
        blet::Dict dict1(42);
        blet::Dict dict2(24);
        EXPECT_EQ(dict1 >= dict2, true);
    }
    {
        blet::Dict dict1("foobar");
        blet::Dict dict2("foo");
        EXPECT_EQ(dict1 >= dict2, true);
    }
    {
        std::vector<int> v1;
        v1.push_back(42);
        v1.push_back(24);
        std::vector<int> v2;
        v2.push_back(42);
        v2.push_back(23);
        blet::Dict dict1(v1);
        blet::Dict dict2(v2);
        EXPECT_EQ(dict1 >= dict2, true);
    }
    {
        std::map<std::string, int> m1;
        m1.insert(std::map<std::string, int>::value_type("foo", 42));
        m1.insert(std::map<std::string, int>::value_type("bar", 24));
        std::map<std::string, int> m2;
        m2.insert(std::map<std::string, int>::value_type("foo", 42));
        m2.insert(std::map<std::string, int>::value_type("bar", 23));
        blet::Dict dict1(m1);
        blet::Dict dict2(m2);
        EXPECT_EQ(dict1 >= dict2, true);
    }
    {
        blet::Dict dict1(42);
        blet::Dict dict2("foo");
        EXPECT_EQ(dict1 >= dict2, false);
    }
}

GTEST_TEST(dict_common, operatorLE) {
    {
        blet::Dict dict1;
        blet::Dict dict2;
        EXPECT_EQ(dict1 <= dict2, true);
    }
    {
        blet::Dict dict1(false);
        blet::Dict dict2(true);
        EXPECT_EQ(dict1 <= dict2, true);
    }
    {
        blet::Dict dict1(24);
        blet::Dict dict2(42);
        EXPECT_EQ(dict1 <= dict2, true);
    }
    {
        blet::Dict dict1("foo");
        blet::Dict dict2("foobar");
        EXPECT_EQ(dict1 <= dict2, true);
    }
    {
        std::vector<int> v1;
        v1.push_back(42);
        v1.push_back(24);
        std::vector<int> v2;
        v2.push_back(42);
        v2.push_back(23);
        blet::Dict dict1(v2);
        blet::Dict dict2(v1);
        EXPECT_EQ(dict1 <= dict2, true);
    }
    {
        std::map<std::string, int> m1;
        m1.insert(std::map<std::string, int>::value_type("foo", 42));
        m1.insert(std::map<std::string, int>::value_type("bar", 24));
        std::map<std::string, int> m2;
        m2.insert(std::map<std::string, int>::value_type("foo", 42));
        m2.insert(std::map<std::string, int>::value_type("bar", 23));
        blet::Dict dict1(m2);
        blet::Dict dict2(m1);
        EXPECT_EQ(dict1 <= dict2, true);
    }
    {
        blet::Dict dict1(42);
        blet::Dict dict2("foo");
        EXPECT_EQ(dict1 <= dict2, false);
    }
}

GTEST_TEST(dict_common, operatorAdd) {
    {
        EXPECT_THROW(
            {
                try {
                    blet::Dict dict("foo");
                    +dict;
                }
                catch (const blet::Dict::MethodException& e) {
                    EXPECT_STREQ(e.what(), "has not a method operator+.");
                    throw;
                }
            },
            blet::Dict::MethodException);
    }
    {
        blet::Dict dict(true);
        blet::Dict dictRes = +dict;
        EXPECT_EQ(dictRes.getType(), blet::Dict::NUMBER_TYPE);
        EXPECT_EQ(dictRes, 1);
    }
    {
        blet::Dict dict(42.42);
        blet::Dict dictRes = +dict;
        EXPECT_EQ(dictRes.getType(), blet::Dict::NUMBER_TYPE);
        EXPECT_EQ(dictRes, 42.42);
    }
}

GTEST_TEST(dict_common, operatorSub) {
    {
        EXPECT_THROW(
            {
                try {
                    blet::Dict dict("foo");
                    -dict;
                }
                catch (const blet::Dict::MethodException& e) {
                    EXPECT_STREQ(e.what(), "has not a method operator-.");
                    throw;
                }
            },
            blet::Dict::MethodException);
    }
    {
        blet::Dict dict(true);
        blet::Dict dictRes = -dict;
        EXPECT_EQ(dictRes.getType(), blet::Dict::NUMBER_TYPE);
        EXPECT_EQ(dictRes, -1);
    }
    {
        blet::Dict dict(42.42);
        blet::Dict dictRes = -dict;
        EXPECT_EQ(dictRes.getType(), blet::Dict::NUMBER_TYPE);
        EXPECT_EQ(dictRes, -42.42);
    }
}

GTEST_TEST(dict_common, operatorAddString) {
    {
        EXPECT_THROW(
            {
                try {
                    blet::Dict dict(false);
                    dict + std::string("foo");
                }
                catch (const blet::Dict::MethodException& e) {
                    EXPECT_STREQ(e.what(), "has not a method operator+.");
                    throw;
                }
            },
            blet::Dict::MethodException);
    }
    {
        blet::Dict dict("foo");
        EXPECT_EQ(dict + std::string("bar"), "foobar");
    }
    {
        EXPECT_THROW(
            {
                try {
                    blet::Dict dict(false);
                    dict + "foo";
                }
                catch (const blet::Dict::MethodException& e) {
                    EXPECT_STREQ(e.what(), "has not a method operator+.");
                    throw;
                }
            },
            blet::Dict::MethodException);
    }
    {
        blet::Dict dict("foo");
        EXPECT_EQ(dict + "bar", "foobar");
    }
    {
        EXPECT_THROW(
            {
                try {
                    char str[] = "foo";
                    blet::Dict dict(false);
                    dict + str;
                }
                catch (const blet::Dict::MethodException& e) {
                    EXPECT_STREQ(e.what(), "has not a method operator+.");
                    throw;
                }
            },
            blet::Dict::MethodException);
    }
    {
        char str[] = "bar";
        blet::Dict dict("foo");
        EXPECT_EQ(dict + str, "foobar");
    }
}

GTEST_TEST(dict_common, operatorAddNumber) {
    {
        EXPECT_THROW(
            {
                try {
                    blet::Dict dict("foo");
                    dict + 42;
                }
                catch (const blet::Dict::MethodException& e) {
                    EXPECT_STREQ(e.what(), "has not a method operator+.");
                    throw;
                }
            },
            blet::Dict::MethodException);
    }
    {
        blet::Dict dict(true);
        EXPECT_EQ(dict + 42, 43);
    }
    {
        blet::Dict dict(42);
        EXPECT_EQ(dict + 42, 84);
    }
}

GTEST_TEST(dict_common, operatorSubNumber) {
    {
        EXPECT_THROW(
            {
                try {
                    blet::Dict dict("foo");
                    dict - 42;
                }
                catch (const blet::Dict::MethodException& e) {
                    EXPECT_STREQ(e.what(), "has not a method operator-.");
                    throw;
                }
            },
            blet::Dict::MethodException);
    }
    {
        blet::Dict dict(true);
        EXPECT_EQ(dict - 42, -41);
    }
    {
        blet::Dict dict(42);
        EXPECT_EQ(dict - 24, 18);
    }
}

GTEST_TEST(dict_common, operatorMul) {
    {
        EXPECT_THROW(
            {
                try {
                    blet::Dict dict("foo");
                    dict * 42;
                }
                catch (const blet::Dict::MethodException& e) {
                    EXPECT_STREQ(e.what(), "has not a method operator*.");
                    throw;
                }
            },
            blet::Dict::MethodException);
    }
    {
        blet::Dict dict(true);
        EXPECT_EQ(dict * 42, 42);
    }
    {
        blet::Dict dict(42);
        EXPECT_EQ(dict * 24, 1008);
    }
}

GTEST_TEST(dict_common, operatorDiv) {
    {
        EXPECT_THROW(
            {
                try {
                    blet::Dict dict("foo");
                    dict / 42;
                }
                catch (const blet::Dict::MethodException& e) {
                    EXPECT_STREQ(e.what(), "has not a method operator/.");
                    throw;
                }
            },
            blet::Dict::MethodException);
    }
    {
        blet::Dict dict(true);
        EXPECT_EQ(dict / 42, 0);
    }
    {
        blet::Dict dict(42);
        EXPECT_EQ(dict / 24, 1.75);
    }
}

GTEST_TEST(dict_common, operatorMod) {
    {
        EXPECT_THROW(
            {
                try {
                    blet::Dict dict("foo");
                    dict % 42;
                }
                catch (const blet::Dict::MethodException& e) {
                    EXPECT_STREQ(e.what(), "has not a method operator%.");
                    throw;
                }
            },
            blet::Dict::MethodException);
    }
    {
        blet::Dict dict(true);
        EXPECT_EQ(dict % 42, 1);
    }
    {
        blet::Dict dict(42);
        EXPECT_EQ(dict % 24, 18);
    }
}

GTEST_TEST(dict_common, operatorNot) {
    {
        EXPECT_THROW(
            {
                try {
                    blet::Dict dict("foo");
                    ~dict;
                }
                catch (const blet::Dict::MethodException& e) {
                    EXPECT_STREQ(e.what(), "has not a method operator~.");
                    throw;
                }
            },
            blet::Dict::MethodException);
    }
    {
        blet::Dict dict(42);
        EXPECT_EQ(~dict, -43);
    }
}

GTEST_TEST(dict_common, operatorAnd) {
    {
        EXPECT_THROW(
            {
                try {
                    blet::Dict dict("foo");
                    dict & 42;
                }
                catch (const blet::Dict::MethodException& e) {
                    EXPECT_STREQ(e.what(), "has not a method operator&.");
                    throw;
                }
            },
            blet::Dict::MethodException);
    }
    {
        blet::Dict dict(true);
        EXPECT_EQ(dict & 42, 0);
    }
    {
        blet::Dict dict(42);
        EXPECT_EQ(dict & 24, 8);
    }
}

GTEST_TEST(dict_common, operatorOr) {
    {
        EXPECT_THROW(
            {
                try {
                    blet::Dict dict("foo");
                    dict | 42;
                }
                catch (const blet::Dict::MethodException& e) {
                    EXPECT_STREQ(e.what(), "has not a method operator|.");
                    throw;
                }
            },
            blet::Dict::MethodException);
    }
    {
        blet::Dict dict(true);
        EXPECT_EQ(dict | 42, 43);
    }
    {
        blet::Dict dict(42);
        EXPECT_EQ(dict | 24, 58);
    }
}

GTEST_TEST(dict_common, operatorXor) {
    {
        EXPECT_THROW(
            {
                try {
                    blet::Dict dict("foo");
                    dict ^ 42;
                }
                catch (const blet::Dict::MethodException& e) {
                    EXPECT_STREQ(e.what(), "has not a method operator^.");
                    throw;
                }
            },
            blet::Dict::MethodException);
    }
    {
        blet::Dict dict(true);
        EXPECT_EQ(dict ^ 42, 43);
    }
    {
        blet::Dict dict(42);
        EXPECT_EQ(dict ^ 24, 50);
    }
}

GTEST_TEST(dict_common, get) {
    {
        blet::Dict dict(42);
        int i = dict.get<int>();
        EXPECT_EQ(i, 42);
        double d;
        dict.get(d);
        EXPECT_EQ(d, 42);
    }
}

GTEST_TEST(dict_common, containerCast) {
    std::vector<int> v;
    v.push_back(42);
    v.push_back(24);
    v.push_back(1337);
    std::map<std::string, int> m;
    m.insert(std::map<std::string, int>::value_type("foo", 42));
    m.insert(std::map<std::string, int>::value_type("bar", 24));
    m.insert(std::map<std::string, int>::value_type("toto", 1337));
    {
        blet::Dict dict(v);
        std::deque<double> dq = dict;
        EXPECT_EQ(dq.front(), 42);
        dq.pop_front();
        EXPECT_EQ(dq.front(), 24);
        dq.pop_front();
        EXPECT_EQ(dq.front(), 1337);
    }
    {
        blet::Dict dict(m);
        std::deque<double> dq = dict;
        EXPECT_EQ(dq.front(), 24);
        dq.pop_front();
        EXPECT_EQ(dq.front(), 42);
        dq.pop_front();
        EXPECT_EQ(dq.front(), 1337);
    }
    {
        blet::Dict dict(false);
        std::deque<double> dq = dict;
        EXPECT_EQ(dq.empty(), true);
    }
    {
        blet::Dict dict(v);
        std::list<double> l = dict;
        EXPECT_EQ(l.front(), 42);
        l.pop_front();
        EXPECT_EQ(l.front(), 24);
        l.pop_front();
        EXPECT_EQ(l.front(), 1337);
    }
    {
        blet::Dict dict(m);
        std::list<double> l = dict;
        EXPECT_EQ(l.front(), 24);
        l.pop_front();
        EXPECT_EQ(l.front(), 42);
        l.pop_front();
        EXPECT_EQ(l.front(), 1337);
    }
    {
        blet::Dict dict(false);
        std::list<double> l = dict;
        EXPECT_EQ(l.empty(), true);
    }
    {
        blet::Dict dict(v);
        std::map<double, double> mp = dict;
        EXPECT_EQ(mp.at(0), 42);
        EXPECT_EQ(mp.at(1), 24);
        EXPECT_EQ(mp.at(2), 1337);
    }
    {
        blet::Dict dict(m);
        std::map<std::string, double> mp = dict;
        EXPECT_EQ(mp.at("foo"), 42);
        EXPECT_EQ(mp.at("bar"), 24);
        EXPECT_EQ(mp.at("toto"), 1337);
    }
    {
        blet::Dict dict(v);
        std::queue<double> q = dict;
        EXPECT_EQ(q.front(), 42);
        q.pop();
        EXPECT_EQ(q.front(), 24);
        q.pop();
        EXPECT_EQ(q.front(), 1337);
    }
    {
        blet::Dict dict(m);
        std::queue<double> q = dict;
        EXPECT_EQ(q.front(), 24);
        q.pop();
        EXPECT_EQ(q.front(), 42);
        q.pop();
        EXPECT_EQ(q.front(), 1337);
    }
    {
        blet::Dict dict(false);
        std::queue<double> q = dict;
        EXPECT_EQ(q.empty(), true);
    }
    {
        blet::Dict dict(v);
        std::set<double> s = dict;
        EXPECT_NE(s.find(42), s.end());
        EXPECT_NE(s.find(24), s.end());
        EXPECT_NE(s.find(1337), s.end());
    }
    {
        blet::Dict dict(m);
        std::set<double> s = dict;
        EXPECT_NE(s.find(42), s.end());
        EXPECT_NE(s.find(24), s.end());
        EXPECT_NE(s.find(1337), s.end());
    }
    {
        blet::Dict dict(false);
        std::set<double> s = dict;
        EXPECT_EQ(s.empty(), true);
    }
    {
        blet::Dict dict(v);
        std::stack<double> s = dict;
        EXPECT_EQ(s.top(), 1337);
        s.pop();
        EXPECT_EQ(s.top(), 24);
        s.pop();
        EXPECT_EQ(s.top(), 42);
    }
    {
        blet::Dict dict(m);
        std::stack<double> s = dict;
        EXPECT_EQ(s.top(), 1337);
        s.pop();
        EXPECT_EQ(s.top(), 42);
        s.pop();
        EXPECT_EQ(s.top(), 24);
    }
    {
        blet::Dict dict(false);
        std::stack<double> s = dict;
        EXPECT_EQ(s.empty(), true);
    }
    {
        blet::Dict dict(v);
        std::vector<double> vc = dict;
        EXPECT_EQ(vc[0], 42);
        EXPECT_EQ(vc[1], 24);
        EXPECT_EQ(vc[2], 1337);
    }
    {
        blet::Dict dict(m);
        std::vector<double> vc = dict;
        EXPECT_EQ(vc[0], 24);
        EXPECT_EQ(vc[1], 42);
        EXPECT_EQ(vc[2], 1337);
    }
    {
        blet::Dict dict(false);
        std::vector<double> vc = dict;
        EXPECT_EQ(vc.empty(), true);
    }
}
