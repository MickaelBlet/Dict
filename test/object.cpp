#include <gtest/gtest.h>

#include "blet/dict.h"

GTEST_TEST(dict_object, isObject) {
    {
        blet::Dict::object_t obj;
        obj.insert(blet::Dict::object_t::value_type("foo", "bar"));
        blet::Dict dict(obj);
        EXPECT_EQ(dict.isObject(), true);
    }
    {
        blet::Dict dict(false);
        EXPECT_EQ(dict.isObject(), false);
    }
}

GTEST_TEST(dict_object, getObject) {
    {
        std::map<std::string, int> a;
        blet::Dict dict(a);
        EXPECT_EQ(&(dict.getObject()), &(dict.getValue().getObject()));
    }
    {
        EXPECT_THROW(
            {
                try {
                    blet::Dict dict(false);
                    dict.getObject();
                }
                catch (const blet::Dict::AccessException& e) {
                    EXPECT_STREQ(e.what(), "is not a object (is boolean).");
                    throw;
                }
            },
            blet::Dict::AccessException);
    }
    {
        EXPECT_THROW(
            {
                try {
                    const blet::Dict dict(false);
                    dict.getObject();
                }
                catch (const blet::Dict::AccessException& e) {
                    EXPECT_STREQ(e.what(), "is not a object (is boolean).");
                    throw;
                }
            },
            blet::Dict::AccessException);
    }
    {
        std::map<std::string, int> a;
        const blet::Dict dict(a);
        EXPECT_EQ(&(dict.getObject()), &(dict.getValue().getObject()));
    }
}

GTEST_TEST(dict_object, operatorEqual) {
    {
        std::map<std::string, int> a;
        blet::Dict dict;
        dict = a;
        EXPECT_EQ(dict.isObject(), true);
    }
}

GTEST_TEST(dict_object, operatorAddEqual) {
    {
        std::map<std::string, int> a;
        blet::Dict dict;
        dict += a;
        EXPECT_EQ(dict.isObject(), true);
    }
}

GTEST_TEST(dict_object, newObject) {
    {
        blet::Dict dict;
        dict.newObject();
        EXPECT_EQ(dict.isObject(), true);
    }
    {
        blet::Dict dict;
        dict.newObject();
        EXPECT_EQ(dict.isObject(), true);
        dict.getObject().insert(blet::Dict::object_t::value_type("foo", 42));
        EXPECT_EQ(dict.getObject().size(), 1);
        dict.newObject();
        EXPECT_EQ(dict.isObject(), true);
        EXPECT_EQ(dict.getObject().size(), 0);
    }
    {
        EXPECT_THROW(
            {
                try {
                    blet::Dict dict(false);
                    dict.newObject();
                }
                catch (const blet::Dict::AccessException& e) {
                    EXPECT_STREQ(e.what(), "is not a object (is boolean).");
                    throw;
                }
            },
            blet::Dict::AccessException);
    }
    {
        std::map<std::string, int> a;
        blet::Dict dict;
        dict.newObject(a);
        EXPECT_EQ(dict.isObject(), true);
    }
}

GTEST_TEST(dict_object, operatorBracket) {
    {
        blet::Dict dict;
        dict.newObject();
        dict["42"];
        dict["41"];
        EXPECT_EQ(dict.getObject().size(), 2);
        EXPECT_EQ(dict[std::string("41")].isNull(), true);
    }
    {
        EXPECT_THROW(
            {
                try {
                    const blet::Dict dict(false);
                    dict["42"];
                }
                catch (const blet::Dict::AccessException& e) {
                    EXPECT_STREQ(e.what(), "is not a object (is boolean).");
                    throw;
                }
            },
            blet::Dict::AccessException);
    }
    {
        std::map<std::string, int> a;
        EXPECT_THROW(
            {
                try {
                    const blet::Dict dict(a);
                    dict["42"];
                }
                catch (const blet::Dict::ChildException& e) {
                    EXPECT_STREQ(e.what(), "42 has not a key.");
                    throw;
                }
            },
            blet::Dict::ChildException);
    }
    {
        std::map<std::string, int> a;
        a.insert(std::map<std::string, int>::value_type("foo", 42));
        const blet::Dict dict(a);
        EXPECT_EQ(dict[std::string("foo")], 42);
    }
    {
        std::map<std::string, int> a;
        a.insert(std::map<std::string, int>::value_type("foo", 42));
        blet::Dict dict(a);
        EXPECT_EQ(dict["foo"], 42);
    }
    {
        std::map<std::string, int> a;
        a.insert(std::map<std::string, int>::value_type("foo", 42));
        const blet::Dict dict(a);
        EXPECT_EQ(dict["foo"], 42);
    }
    {
        std::map<std::string, int> a;
        a.insert(std::map<std::string, int>::value_type("foo", 42));
        blet::Dict dict(a);
        char str[] = "foo";
        EXPECT_EQ(dict[str], 42);
    }
    {
        std::map<std::string, int> a;
        a.insert(std::map<std::string, int>::value_type("foo", 42));
        const blet::Dict dict(a);
        char str[] = "foo";
        EXPECT_EQ(dict[str], 42);
    }
}

GTEST_TEST(dict_object, contains) {
    {
        blet::Dict dict;
        dict.newObject();
        EXPECT_EQ(dict.contains(std::string("foo")), false);
    }
    {
        EXPECT_THROW(
            {
                try {
                    blet::Dict dict(false);
                    dict.contains(std::string("foo"));
                }
                catch (const blet::Dict::AccessException& e) {
                    EXPECT_STREQ(e.what(), "is not a object (is boolean).");
                    throw;
                }
            },
            blet::Dict::AccessException);
    }
    {
        blet::Dict dict;
        dict.newObject();
        EXPECT_EQ(dict.contains("foo"), false);
    }
    {
        blet::Dict dict;
        dict.newObject();
        char str[] = "foo";
        EXPECT_EQ(dict.contains(str), false);
    }
    {
        blet::Dict dict;
        dict.newObject();
        EXPECT_EQ(dict.contains(std::string("foo"), blet::Dict::OBJECT_TYPE), false);
    }
    {
        EXPECT_THROW(
            {
                try {
                    blet::Dict dict(false);
                    dict.contains(std::string("foo"), blet::Dict::OBJECT_TYPE);
                }
                catch (const blet::Dict::AccessException& e) {
                    EXPECT_STREQ(e.what(), "is not a object (is boolean).");
                    throw;
                }
            },
            blet::Dict::AccessException);
    }
    {
        std::map<std::string, int> a;
        a.insert(std::map<std::string, int>::value_type("foo", 42));
        blet::Dict dict(a);
        EXPECT_EQ(dict.contains("foo", blet::Dict::OBJECT_TYPE), false);
        EXPECT_EQ(dict.contains("foo", blet::Dict::NUMBER_TYPE), true);
    }
    {
        std::map<std::string, int> a;
        a.insert(std::map<std::string, int>::value_type("foo", 42));
        blet::Dict dict(a);
        char str[] = "foo";
        EXPECT_EQ(dict.contains(str, blet::Dict::OBJECT_TYPE), false);
        EXPECT_EQ(dict.contains(str, blet::Dict::NUMBER_TYPE), true);
    }
}

GTEST_TEST(dict_object, at) {
    {
        std::map<std::string, int> a;
        a.insert(std::map<std::string, int>::value_type("foo", 42));
        blet::Dict dict(a);
        EXPECT_EQ(dict.at(std::string("foo")), dict["foo"]);
    }
    {
        std::map<std::string, int> a;
        a.insert(std::map<std::string, int>::value_type("foo", 42));
        const blet::Dict dict(a);
        EXPECT_EQ(dict.at(std::string("foo")), dict["foo"]);
    }
    {
        std::map<std::string, int> a;
        a.insert(std::map<std::string, int>::value_type("foo", 42));
        blet::Dict dict(a);
        EXPECT_EQ(dict.at("foo"), dict["foo"]);
    }
    {
        std::map<std::string, int> a;
        a.insert(std::map<std::string, int>::value_type("foo", 42));
        const blet::Dict dict(a);
        EXPECT_EQ(dict.at("foo"), dict["foo"]);
    }
    {
        std::map<std::string, int> a;
        a.insert(std::map<std::string, int>::value_type("foo", 42));
        blet::Dict dict(a);
        char str[] = "foo";
        EXPECT_EQ(dict.at(str), dict["foo"]);
    }
    {
        std::map<std::string, int> a;
        a.insert(std::map<std::string, int>::value_type("foo", 42));
        const blet::Dict dict(a);
        char str[] = "foo";
        EXPECT_EQ(dict.at(str), dict["foo"]);
    }
}

GTEST_TEST(dict_object, object_begin) {
    {
        std::map<std::string, int> a;
        a.insert(std::map<std::string, int>::value_type("foo", 42));
        blet::Dict dict(a);
        EXPECT_EQ(*(dict.object_begin()), blet::Dict::object_t::value_type("foo", 42));
    }
    {
        std::map<std::string, int> a;
        a.insert(std::map<std::string, int>::value_type("foo", 42));
        const blet::Dict dict(a);
        EXPECT_EQ(*(dict.object_begin()), blet::Dict::object_t::value_type("foo", 42));
    }
}

GTEST_TEST(dict_object, object_end) {
    {
        std::map<std::string, int> a;
        a.insert(std::map<std::string, int>::value_type("foo", 42));
        blet::Dict dict(a);
        blet::Dict::object_t::iterator it = dict.object_end();
        --it;
        EXPECT_EQ(*(it), blet::Dict::object_t::value_type("foo", 42));
    }
    {
        std::map<std::string, int> a;
        a.insert(std::map<std::string, int>::value_type("foo", 42));
        const blet::Dict dict(a);
        blet::Dict::object_t::const_iterator it = dict.object_end();
        --it;
        EXPECT_EQ(*(it), blet::Dict::object_t::value_type("foo", 42));
    }
}

GTEST_TEST(dict_object, erase) {
    {
        std::map<std::string, int> a;
        a.insert(std::map<std::string, int>::value_type("foo", 42));
        blet::Dict dict(a);
        dict.erase(dict.object_begin());
        EXPECT_EQ(dict.size(), 0);
    }
    {
        std::map<std::string, int> a;
        a.insert(std::map<std::string, int>::value_type("foo", 42));
        blet::Dict dict(a);
        dict.erase("foo");
        EXPECT_EQ(dict.size(), 0);
    }
    {
        std::map<std::string, int> a;
        a.insert(std::map<std::string, int>::value_type("foo", 42));
        a.insert(std::map<std::string, int>::value_type("bar", 42));
        blet::Dict dict(a);
        dict.erase(dict.object_begin(), dict.object_end());
        EXPECT_EQ(dict.size(), 0);
    }
}

GTEST_TEST(dict_object, find) {
    {
        std::map<std::string, int> a;
        a.insert(std::map<std::string, int>::value_type("foo", 42));
        blet::Dict dict(a);
        EXPECT_EQ(dict.find("foo"), dict.object_begin());
    }
    {
        std::map<std::string, int> a;
        a.insert(std::map<std::string, int>::value_type("foo", 42));
        const blet::Dict dict(a);
        EXPECT_EQ(dict.find("foo"), dict.object_begin());
    }
}

GTEST_TEST(dict_object, object_get_allocator) {
    {
        std::map<std::string, int> a;
        a.insert(std::map<std::string, int>::value_type("foo", 42));
        blet::Dict dict(a);
        blet::Dict::object_t::allocator_type at = dict.object_get_allocator();
        (void)at;
    }
}

GTEST_TEST(dict_object, insert) {
    {
        std::map<std::string, int> a;
        a.insert(std::map<std::string, int>::value_type("foo", 42));
        blet::Dict dict(a);
        dict.insert(blet::Dict::object_t::value_type("bar", 42));
        EXPECT_EQ(dict.size(), 2);
    }
    {
        std::map<std::string, int> a;
        a.insert(std::map<std::string, int>::value_type("foo", 42));
        blet::Dict dict(a);
        dict.insert(dict.object_begin(), blet::Dict::object_t::value_type("bar", 42));
        EXPECT_EQ(dict.size(), 2);
    }
    {
        std::map<std::string, int> a;
        a.insert(std::map<std::string, int>::value_type("foo", 42));
        a.insert(std::map<std::string, int>::value_type("bar", 42));
        std::map<std::string, int> b;
        b.insert(std::map<std::string, int>::value_type("foo2", 42));
        b.insert(std::map<std::string, int>::value_type("bar2", 42));
        blet::Dict dict(a);
        EXPECT_EQ(dict.size(), 2);
        dict.insert(b.begin(), b.end());
        EXPECT_EQ(dict.size(), 4);
    }
}

GTEST_TEST(dict_object, key_comp) {
    {
        std::map<std::string, int> a;
        a.insert(std::map<std::string, int>::value_type("foo", 42));
        blet::Dict dict(a);
        blet::Dict::object_t::key_compare comp = dict.key_comp();
        (void)comp;
    }
}

GTEST_TEST(dict_object, lower_bound) {
    {
        std::map<std::string, int> a;
        a.insert(std::map<std::string, int>::value_type("foo", 42));
        blet::Dict dict(a);
        EXPECT_EQ(dict.lower_bound("fo"), dict.object_begin());
    }
    {
        std::map<std::string, int> a;
        a.insert(std::map<std::string, int>::value_type("foo", 42));
        const blet::Dict dict(a);
        EXPECT_EQ(dict.lower_bound("fo"), dict.object_begin());
    }
}

GTEST_TEST(dict_object, object_rbegin) {
    {
        std::map<std::string, int> a;
        a.insert(std::map<std::string, int>::value_type("foo", 42));
        blet::Dict dict(a);
        EXPECT_EQ(*(dict.object_rbegin()), blet::Dict::object_t::value_type("foo", 42));
    }
    {
        std::map<std::string, int> a;
        a.insert(std::map<std::string, int>::value_type("foo", 42));
        const blet::Dict dict(a);
        EXPECT_EQ(*(dict.object_rbegin()), blet::Dict::object_t::value_type("foo", 42));
    }
}

GTEST_TEST(dict_object, object_rend) {
    {
        std::map<std::string, int> a;
        a.insert(std::map<std::string, int>::value_type("foo", 42));
        blet::Dict dict(a);
        blet::Dict::object_t::reverse_iterator it = dict.object_rend();
        --it;
        EXPECT_EQ(*(it), blet::Dict::object_t::value_type("foo", 42));
    }
    {
        std::map<std::string, int> a;
        a.insert(std::map<std::string, int>::value_type("foo", 42));
        const blet::Dict dict(a);
        blet::Dict::object_t::const_reverse_iterator it = dict.object_rend();
        --it;
        EXPECT_EQ(*(it), blet::Dict::object_t::value_type("foo", 42));
    }
}

GTEST_TEST(dict_object, upper_bound) {
    {
        std::map<std::string, int> a;
        a.insert(std::map<std::string, int>::value_type("foo", 42));
        blet::Dict dict(a);
        EXPECT_EQ(dict.upper_bound("e"), dict.object_begin());
    }
    {
        std::map<std::string, int> a;
        a.insert(std::map<std::string, int>::value_type("foo", 42));
        const blet::Dict dict(a);
        EXPECT_EQ(dict.upper_bound("e"), dict.object_begin());
    }
}

GTEST_TEST(dict_object, value_comp) {
    {
        std::map<std::string, int> a;
        a.insert(std::map<std::string, int>::value_type("foo", 42));
        blet::Dict dict(a);
        blet::Dict::object_t::value_compare comp = dict.value_comp();
        (void)comp;
    }
}
