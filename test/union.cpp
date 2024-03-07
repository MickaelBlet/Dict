#include <gtest/gtest.h>

#include "blet/dict.h"

GTEST_TEST(dict_union, contructor) {
    {
        blet::Dict::UValue value;
        EXPECT_EQ(value.getBoolean(), false);
    }
    {
        blet::Dict::UValue value(true);
        EXPECT_EQ(value.getBoolean(), true);
    }
    {
        blet::Dict::UValue value(42);
        EXPECT_EQ(value.getNumber(), 42);
    }
    {
        blet::Dict::UValue value(std::string("foo"));
        EXPECT_EQ(value.getString(), "foo");
        value.delString();
    }
    {
        blet::Dict::UValue value("foo");
        EXPECT_EQ(value.getString(), "foo");
        value.delString();
    }
    {
        char str[] = "foo";
        blet::Dict::UValue value(str);
        EXPECT_EQ(value.getString(), "foo");
        value.delString();
    }
    {
        std::deque<int> d;
        d.push_back(42);
        blet::Dict::UValue value(d);
        EXPECT_EQ(value.getArray()[0], 42);
        value.delArray();
    }
    {
        std::list<int> d;
        d.push_back(42);
        blet::Dict::UValue value(d);
        EXPECT_EQ(value.getArray()[0], 42);
        value.delArray();
    }
    {
        std::map<double, int> d;
        d.insert(std::pair<double, int>(10, 42));
        d.insert(std::pair<double, int>(10.42, 42));
        d.insert(std::pair<double, int>(0, 42));
        blet::Dict::UValue value(d);
        EXPECT_EQ(value.getArray()[0], 42);
        value.delArray();
    }
    {
        std::queue<int> d;
        d.push(42);
        blet::Dict::UValue value(d);
        EXPECT_EQ(value.getArray()[0], 42);
        value.delArray();
    }
    {
        std::set<int> d;
        d.insert(42);
        blet::Dict::UValue value(d);
        EXPECT_EQ(value.getArray()[0], 42);
        value.delArray();
    }
    {
        std::stack<int> d;
        d.push(42);
        blet::Dict::UValue value(d);
        EXPECT_EQ(value.getArray()[0], 42);
        value.delArray();
    }
    {
        std::vector<int> d;
        d.push_back(42);
        blet::Dict::UValue value(d);
        EXPECT_EQ(value.getArray()[0], 42);
        value.delArray();
    }
    {
        std::map<std::string, int> d;
        d.insert(std::pair<std::string, int>("foo", 42));
        blet::Dict::UValue value(d);
        EXPECT_EQ(value.getObject()["foo"], 42);
        value.delObject();
    }
}

GTEST_TEST(dict_union, new) {
    {
        blet::Dict::UValue value;
        value.newString();
        EXPECT_EQ(value.getString(), "");
        value.delString();
    }
    {
        blet::Dict::UValue value;
        value.newArray();
        EXPECT_EQ(value.getArray().size(), 0);
        value.delArray();
    }
    {
        blet::Dict::UValue value;
        value.newObject();
        EXPECT_EQ(value.getObject().size(), 0);
        value.delObject();
    }
}

GTEST_TEST(dict_union, extend) {
    {
        blet::Dict::UValue value;
        value.newArray();
        std::deque<int> d;
        d.push_back(42);
        value.extendToArray(d);
        EXPECT_EQ(value.getArray()[0], 42);
        value.delArray();
    }
    {
        blet::Dict::UValue value;
        value.newArray();
        std::list<int> d;
        d.push_back(42);
        value.extendToArray(d);
        EXPECT_EQ(value.getArray()[0], 42);
        value.delArray();
    }
    {
        blet::Dict::UValue value;
        value.newArray();
        std::map<double, int> d;
        d.insert(std::pair<double, int>(10, 42));
        d.insert(std::pair<double, int>(10.42, 42));
        d.insert(std::pair<double, int>(0, 42));
        value.extendToArray(d);
        EXPECT_EQ(value.getArray()[0], 42);
        value.delArray();
    }
    {
        blet::Dict::UValue value;
        value.newArray();
        std::queue<int> d;
        d.push(42);
        value.extendToArray(d);
        EXPECT_EQ(value.getArray()[0], 42);
        value.delArray();
    }
    {
        blet::Dict::UValue value;
        value.newArray();
        std::set<int> d;
        d.insert(42);
        value.extendToArray(d);
        EXPECT_EQ(value.getArray()[0], 42);
        value.delArray();
    }
    {
        blet::Dict::UValue value;
        value.newArray();
        std::stack<int> d;
        d.push(42);
        value.extendToArray(d);
        EXPECT_EQ(value.getArray()[0], 42);
        value.delArray();
    }
    {
        blet::Dict::UValue value;
        value.newArray();
        std::vector<int> d;
        d.push_back(42);
        value.extendToArray(d);
        EXPECT_EQ(value.getArray()[0], 42);
        value.delArray();
    }
    {
        blet::Dict::UValue value;
        value.newObject();
        std::map<std::string, int> d;
        d.insert(std::pair<std::string, int>("foo", 42));
        value.extendToObject(d);
        EXPECT_EQ(value.getObject()["foo"], 42);
        value.delObject();
    }
}

GTEST_TEST(dict_union, get) {
    {
        blet::Dict::UValue value;
        value.getBoolean() = true;
        const blet::Dict::UValue& cvalue = value;
        EXPECT_EQ(value.getBoolean(), true);
        EXPECT_EQ(cvalue.getBoolean(), true);
    }
    {
        blet::Dict::UValue value;
        value.getNumber() = 42;
        const blet::Dict::UValue& cvalue = value;
        EXPECT_EQ(value.getNumber(), 42);
        EXPECT_EQ(cvalue.getNumber(), 42);
    }
    {
        blet::Dict::UValue value;
        value.newString();
        const blet::Dict::UValue& cvalue = value;
        EXPECT_EQ(value.getString(), "");
        EXPECT_EQ(cvalue.getString(), "");
        value.delString();
    }
    {
        blet::Dict::UValue value;
        value.newArray();
        const blet::Dict::UValue& cvalue = value;
        EXPECT_EQ(value.getArray().size(), 0);
        EXPECT_EQ(cvalue.getArray().size(), 0);
        value.delArray();
    }
    {
        blet::Dict::UValue value;
        value.newObject();
        const blet::Dict::UValue& cvalue = value;
        EXPECT_EQ(value.getObject().size(), 0);
        EXPECT_EQ(cvalue.getObject().size(), 0);
        value.delObject();
    }
}
