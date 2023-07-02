#include "blet/dict.h"

#include <gtest/gtest.h>

GTEST_TEST(dict, typeToStr) {
    {
        blet::Dict dict;
        dict.newNull();
        EXPECT_STREQ(dict.typeToStr(dict.getType()), "null");
    }
    {
        blet::Dict dict;
        dict.newBoolean();
        EXPECT_STREQ(dict.typeToStr(dict.getType()), "boolean");
    }
    {
        blet::Dict dict;
        dict.newNumber();
        EXPECT_STREQ(dict.typeToStr(dict.getType()), "number");
    }
    {
        blet::Dict dict;
        dict.newString();
        EXPECT_STREQ(dict.typeToStr(dict.getType()), "string");
    }
    {
        blet::Dict dict;
        dict.newArray();
        EXPECT_STREQ(dict.typeToStr(dict.getType()), "array");
    }
    {
        blet::Dict dict;
        dict.newObject();
        EXPECT_STREQ(dict.typeToStr(dict.getType()), "object");
    }
}

GTEST_TEST(dict, operatorLeftLeft) {
    {
        blet::Dict dict;
        dict.newNull();
        std::ostringstream oss("");
        oss << dict;
        EXPECT_EQ(oss.str(), "null");
    }
    {
        blet::Dict dict;
        dict.newBoolean();
        std::ostringstream oss("");
        oss << dict;
        EXPECT_EQ(oss.str(), "0");
    }
    {
        blet::Dict dict;
        dict.newNumber();
        std::ostringstream oss("");
        oss << dict;
        EXPECT_EQ(oss.str(), "0");
    }
    {
        blet::Dict dict;
        dict.newString();
        std::ostringstream oss("");
        oss << dict;
        EXPECT_EQ(oss.str(), "");
    }
    {
        blet::Dict dict;
        dict.newArray();
        std::ostringstream oss("");
        oss << dict;
        std::string str = oss.str();
        EXPECT_EQ(str.find_first_of("<array "), 0);
        EXPECT_EQ(str.find_last_of(">"), str.size() - 1);
    }
    {
        blet::Dict dict;
        dict.newObject();
        std::ostringstream oss;
        oss << dict;
        std::string str = oss.str();
        EXPECT_EQ(str.find_first_of("<object "), 0);
        EXPECT_EQ(str.find_last_of(">"), str.size() - 1);
    }
}

GTEST_TEST(dict, constructor) {
    // default
    {
        blet::Dict dict;
        EXPECT_TRUE(dict.isNull());
    }
    // copy
    {
        blet::Dict dict;
        blet::Dict dict2(dict);
        EXPECT_TRUE(dict2.isNull());
    }
    {
        blet::Dict dict;
        dict.newBoolean();
        blet::Dict dict2(dict);
        EXPECT_TRUE(dict2.isBoolean());
    }
    {
        blet::Dict dict;
        dict.newNumber();
        blet::Dict dict2(dict);
        EXPECT_TRUE(dict2.isNumber());
    }
    {
        blet::Dict dict;
        dict.newString();
        blet::Dict dict2(dict);
        EXPECT_TRUE(dict2.isString());
    }
    {
        blet::Dict dict;
        dict.newArray();
        blet::Dict dict2(dict);
        EXPECT_TRUE(dict2.isArray());
    }
    {
        blet::Dict dict;
        dict.newObject();
        blet::Dict dict2(dict);
        EXPECT_TRUE(dict2.isObject());
    }
    // boolean
    {
        blet::Dict dict(true);
        EXPECT_TRUE(dict.isBoolean());
        EXPECT_TRUE(dict.getBoolean());
    }
    // number
    {
        blet::Dict dict(42);
        EXPECT_TRUE(dict.isNumber());
        EXPECT_EQ(dict.getNumber(), 42);
    }
    // string
    {
        blet::Dict dict(std::string("foo"));
        EXPECT_TRUE(dict.isString());
        EXPECT_EQ(dict.getString(), "foo");
    }
    {
        blet::Dict dict("foo");
        EXPECT_TRUE(dict.isString());
        EXPECT_EQ(dict.getString(), "foo");
    }
    {
        char str[] = "foo";
        blet::Dict dict(str);
        EXPECT_TRUE(dict.isString());
        EXPECT_EQ(dict.getString(), "foo");
    }
    // array
    {
        std::deque<int> d;
        d.push_back(42);
        blet::Dict dict(d);
        EXPECT_TRUE(dict.isArray());
        EXPECT_EQ(dict.getArray()[0], 42);
    }
    {
        std::list<int> d;
        d.push_back(42);
        blet::Dict dict(d);
        EXPECT_TRUE(dict.isArray());
        EXPECT_EQ(dict.getArray()[0], 42);
    }
    {
        std::map<double, int> d;
        d.insert(std::pair<double, int>(10, 42));
        d.insert(std::pair<double, int>(10.42, 42));
        d.insert(std::pair<double, int>(0, 42));
        blet::Dict dict(d);
        EXPECT_TRUE(dict.isArray());
        EXPECT_EQ(dict.getArray()[0], 42);
    }
    {
        std::queue<int> d;
        d.push(42);
        blet::Dict dict(d);
        EXPECT_TRUE(dict.isArray());
        EXPECT_EQ(dict.getArray()[0], 42);
    }
    {
        std::set<int> d;
        d.insert(42);
        blet::Dict dict(d);
        EXPECT_TRUE(dict.isArray());
        EXPECT_EQ(dict.getArray()[0], 42);
    }
    {
        std::stack<int> d;
        d.push(42);
        blet::Dict dict(d);
        EXPECT_TRUE(dict.isArray());
        EXPECT_EQ(dict.getArray()[0], 42);
    }
    {
        std::vector<int> d;
        d.push_back(42);
        blet::Dict dict(d);
        EXPECT_TRUE(dict.isArray());
        EXPECT_EQ(dict.getArray()[0], 42);
    }
    // object
    {
        std::map<std::string, int> d;
        d.insert(std::pair<std::string, int>("foo", 42));
        blet::Dict dict(d);
        EXPECT_TRUE(dict.isObject());
        EXPECT_EQ(dict.getObject()["foo"], 42);
    }
}

GTEST_TEST(dict, destructor) {
    {
        blet::Dict dict;
        dict.newNull();
    }
    {
        blet::Dict dict;
        dict.newBoolean();
    }
    {
        blet::Dict dict;
        dict.newNumber();
    }
    {
        blet::Dict dict;
        dict.newString();
    }
    {
        blet::Dict dict;
        dict.newArray();
    }
    {
        blet::Dict dict;
        dict.newObject();
    }
}

GTEST_TEST(dict, operatorEqual) {
    {
        blet::Dict dict;
        dict.newNull();
        blet::Dict dict2;
        dict2 = dict;
        dict2 = dict2;
        EXPECT_TRUE(dict2.isNull());
    }
    {
        blet::Dict dict;
        dict.newBoolean();
        blet::Dict dict2;
        dict2 = dict;
        EXPECT_TRUE(dict2.isBoolean());
    }
    {
        blet::Dict dict;
        dict.newNumber();
        blet::Dict dict2;
        dict2 = dict;
        EXPECT_TRUE(dict2.isNumber());
    }
    {
        blet::Dict dict;
        dict.newString();
        blet::Dict dict2;
        dict2 = dict;
        EXPECT_TRUE(dict2.isString());
    }
    {
        blet::Dict dict;
        dict.newArray();
        blet::Dict dict2;
        dict2 = dict;
        EXPECT_TRUE(dict2.isArray());
    }
    {
        blet::Dict dict;
        dict.newObject();
        blet::Dict dict2;
        dict2 = dict;
        EXPECT_TRUE(dict2.isObject());
    }
}

GTEST_TEST(dict, operatorLeftLeftEqual) {
    EXPECT_THROW(
        {
            blet::Dict dict;
            dict.newBoolean();
            try {
                blet::Dict dict2;
                dict <<= dict2;
            }
            catch (const blet::Dict::AccessException& e) {
                EXPECT_STREQ(e.what(), "is not null (is boolean).");
                EXPECT_EQ(&dict, &e.dict());
                throw;
            }
        },
        blet::Dict::AccessException);
    {
        blet::Dict dict;
        dict.newNull();
        blet::Dict dict2;
        dict2 <<= dict;
        dict2 <<= dict2;
        EXPECT_TRUE(dict2.isNull());
    }
    {
        blet::Dict dict;
        dict.newBoolean();
        blet::Dict dict2;
        dict2 <<= dict;
        EXPECT_TRUE(dict2.isBoolean());
    }
    {
        blet::Dict dict;
        dict.newNumber();
        blet::Dict dict2;
        dict2 <<= dict;
        EXPECT_TRUE(dict2.isNumber());
    }
    {
        blet::Dict dict;
        dict.newString();
        blet::Dict dict2;
        dict2 <<= dict;
        EXPECT_TRUE(dict2.isString());
    }
    {
        blet::Dict dict;
        dict.newArray();
        blet::Dict dict2;
        dict2 <<= dict;
        EXPECT_TRUE(dict2.isArray());
    }
    {
        blet::Dict dict;
        dict.newObject();
        blet::Dict dict2;
        dict2 <<= dict;
        EXPECT_TRUE(dict2.isObject());
    }
}

GTEST_TEST(dict, getType) {
    {
        blet::Dict dict;
        EXPECT_EQ(dict.getType(), blet::Dict::NULL_TYPE);
    }
    {
        const blet::Dict dict;
        EXPECT_EQ(dict.getType(), blet::Dict::NULL_TYPE);
    }
}

GTEST_TEST(dict, getValue) {
    {
        blet::Dict dict;
        EXPECT_EQ(dict.getValue().getBoolean(), false);
    }
    {
        const blet::Dict dict;
        EXPECT_EQ(dict.getValue().getBoolean(), false);
    }
}

GTEST_TEST(dict, swap) {
    {
        blet::Dict dict;
        dict.newBoolean();
        blet::Dict dict2;
        dict2.newNumber();
        dict.swap(dict2);
        EXPECT_TRUE(dict2.isBoolean());
        EXPECT_TRUE(dict.isNumber());
    }
}

GTEST_TEST(dict, clear) {
    {
        blet::Dict dict;
        dict.newNull();
        dict.clear();
        EXPECT_TRUE(dict.isNull());
    }
    {
        blet::Dict dict;
        dict.newBoolean();
        dict.clear();
        EXPECT_TRUE(dict.isNull());
    }
    {
        blet::Dict dict;
        dict.newNumber();
        dict.clear();
        EXPECT_TRUE(dict.isNull());
    }
    {
        blet::Dict dict;
        dict.newString();
        dict.clear();
        EXPECT_TRUE(dict.isNull());
    }
    {
        blet::Dict dict;
        dict.newArray();
        dict.clear();
        EXPECT_TRUE(dict.isNull());
    }
    {
        blet::Dict dict;
        dict.newObject();
        dict.clear();
        EXPECT_TRUE(dict.isNull());
    }
}

// GTEST_TEST(dict, array) {

//     blet::Dict dict2;
//     dict2.newNumber(42);

//     EXPECT_EQ(dict, "foo");
//     EXPECT_EQ(dict2, 42);

//     // if (dict2 != 24) {
//     //     EXPECT_EQ(true, false);
//     // }

//     dict.swap(dict2);

//     EXPECT_EQ(dict2, "foo");
//     EXPECT_EQ(dict, 42);
// }