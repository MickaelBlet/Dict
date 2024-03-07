#include <gtest/gtest.h>

#include "blet/dict.h"

GTEST_TEST(dict_array, isArray) {
    {
        std::deque<int> a;
        blet::Dict dict(a);
        EXPECT_EQ(dict.isArray(), true);
    }
    {
        std::list<int> a;
        blet::Dict dict(a);
        EXPECT_EQ(dict.isArray(), true);
    }
    {
        std::map<int, int> a;
        blet::Dict dict(a);
        EXPECT_EQ(dict.isArray(), true);
    }
    {
        std::queue<int> a;
        blet::Dict dict(a);
        EXPECT_EQ(dict.isArray(), true);
    }
    {
        std::set<int> a;
        blet::Dict dict(a);
        EXPECT_EQ(dict.isArray(), true);
    }
    {
        std::stack<int> a;
        blet::Dict dict(a);
        EXPECT_EQ(dict.isArray(), true);
    }
    {
        std::vector<int> a;
        blet::Dict dict(a);
        EXPECT_EQ(dict.isArray(), true);
    }
    {
        blet::Dict dict(false);
        EXPECT_EQ(dict.isArray(), false);
    }
}

GTEST_TEST(dict_array, getArray) {
    {
        std::vector<int> a;
        blet::Dict dict(a);
        EXPECT_EQ(&(dict.getArray()), &(dict.getValue().getArray()));
    }
    {
        EXPECT_THROW(
            {
                try {
                    blet::Dict dict(false);
                    dict.getArray();
                }
                catch (const blet::Dict::AccessException& e) {
                    EXPECT_STREQ(e.what(), "is not a array (is boolean).");
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
                    dict.getArray();
                }
                catch (const blet::Dict::AccessException& e) {
                    EXPECT_STREQ(e.what(), "is not a array (is boolean).");
                    throw;
                }
            },
            blet::Dict::AccessException);
    }
    {
        std::vector<int> a;
        const blet::Dict dict(a);
        EXPECT_EQ(&(dict.getArray()), &(dict.getValue().getArray()));
    }
}

GTEST_TEST(dict_array, operatorEqual) {
    {
        std::deque<int> a;
        blet::Dict dict;
        dict = a;
        EXPECT_EQ(dict.isArray(), true);
    }
    {
        std::list<int> a;
        blet::Dict dict;
        dict = a;
        EXPECT_EQ(dict.isArray(), true);
    }
    {
        std::map<int, int> a;
        blet::Dict dict;
        dict = a;
        EXPECT_EQ(dict.isArray(), true);
    }
    {
        std::queue<int> a;
        blet::Dict dict;
        dict = a;
        EXPECT_EQ(dict.isArray(), true);
    }
    {
        std::set<int> a;
        blet::Dict dict;
        dict = a;
        EXPECT_EQ(dict.isArray(), true);
    }
    {
        std::stack<int> a;
        blet::Dict dict;
        dict = a;
        EXPECT_EQ(dict.isArray(), true);
    }
    {
        std::vector<int> a;
        blet::Dict dict;
        dict = a;
        EXPECT_EQ(dict.isArray(), true);
    }
}

GTEST_TEST(dict_array, operatorAddEqual) {
    {
        std::deque<int> a;
        blet::Dict dict;
        dict += a;
        EXPECT_EQ(dict.isArray(), true);
    }
    {
        std::list<int> a;
        blet::Dict dict;
        dict += a;
        EXPECT_EQ(dict.isArray(), true);
    }
    {
        std::map<int, int> a;
        blet::Dict dict;
        dict += a;
        EXPECT_EQ(dict.isArray(), true);
    }
    {
        std::queue<int> a;
        blet::Dict dict;
        dict += a;
        EXPECT_EQ(dict.isArray(), true);
    }
    {
        std::set<int> a;
        blet::Dict dict;
        dict += a;
        EXPECT_EQ(dict.isArray(), true);
    }
    {
        std::stack<int> a;
        blet::Dict dict;
        dict += a;
        EXPECT_EQ(dict.isArray(), true);
    }
    {
        std::vector<int> a;
        blet::Dict dict;
        dict += a;
        EXPECT_EQ(dict.isArray(), true);
    }
}

GTEST_TEST(dict_array, newArray) {
    {
        blet::Dict dict;
        dict.newArray();
        EXPECT_EQ(dict.isArray(), true);
    }
    {
        blet::Dict dict;
        dict.newArray();
        EXPECT_EQ(dict.isArray(), true);
        dict.getArray().push_back(42);
        EXPECT_EQ(dict.getArray().size(), 1);
        dict.newArray();
        EXPECT_EQ(dict.isArray(), true);
        EXPECT_EQ(dict.getArray().size(), 0);
    }
    {
        EXPECT_THROW(
            {
                try {
                    blet::Dict dict(false);
                    dict.newArray();
                }
                catch (const blet::Dict::AccessException& e) {
                    EXPECT_STREQ(e.what(), "is not a array (is boolean).");
                    throw;
                }
            },
            blet::Dict::AccessException);
    }
    {
        std::vector<int> a;
        blet::Dict dict;
        dict.newArray(a);
        EXPECT_EQ(dict.isArray(), true);
    }
}

GTEST_TEST(dict_array, operatorBracket) {
    {
        blet::Dict dict;
        dict.newArray();
        dict[42];
        dict[41];
        EXPECT_EQ(dict.getArray().size(), 43);
    }
    {
        EXPECT_THROW(
            {
                try {
                    const blet::Dict dict(false);
                    dict[42];
                }
                catch (const blet::Dict::AccessException& e) {
                    EXPECT_STREQ(e.what(), "is not a array (is boolean).");
                    throw;
                }
            },
            blet::Dict::AccessException);
    }
    {
        EXPECT_THROW(
            {
                try {
                    std::vector<int> a;
                    const blet::Dict dict(a);
                    dict[42];
                }
                catch (const blet::Dict::ChildException& e) {
                    EXPECT_STREQ(e.what(), "42 has out of range.");
                    throw;
                }
            },
            blet::Dict::ChildException);
    }
    {
        std::vector<int> a;
        a.push_back(42);
        const blet::Dict dict(a);
        EXPECT_EQ(dict[0], 42);
    }
}

GTEST_TEST(dict_array, contains) {
    {
        EXPECT_THROW(
            {
                try {
                    const blet::Dict dict(false);
                    dict.contains(42);
                }
                catch (const blet::Dict::AccessException& e) {
                    EXPECT_STREQ(e.what(), "is not a array (is boolean).");
                    throw;
                }
            },
            blet::Dict::AccessException);
    }
    {
        std::vector<int> a;
        a.push_back(42);
        const blet::Dict dict(a);
        EXPECT_EQ(dict.contains(0), true);
        EXPECT_EQ(dict.contains(1), false);
    }
    {
        EXPECT_THROW(
            {
                try {
                    const blet::Dict dict(false);
                    dict.contains(42, blet::Dict::ARRAY_TYPE);
                }
                catch (const blet::Dict::AccessException& e) {
                    EXPECT_STREQ(e.what(), "is not a array (is boolean).");
                    throw;
                }
            },
            blet::Dict::AccessException);
    }
    {
        std::vector<int> a;
        a.push_back(42);
        const blet::Dict dict(a);
        EXPECT_EQ(dict.contains(0, blet::Dict::NUMBER_TYPE), true);
        EXPECT_EQ(dict.contains(0, blet::Dict::OBJECT_TYPE), false);
    }
}

GTEST_TEST(dict_array, assign) {
    {
        blet::Dict dict;
        dict.assign(42, blet::Dict(42));
        EXPECT_EQ(dict.getArray().size(), 42);
        EXPECT_EQ(dict.getArray()[0], 42);
        EXPECT_EQ(dict.getArray()[41], 42);
    }
}

GTEST_TEST(dict_array, array_assign) {
    {
        std::vector<int> v;
        v.push_back(0);
        v.push_back(1);
        v.push_back(2);
        v.push_back(3);
        blet::Dict dict;
        dict.array_assign(v.begin(), v.end());
        EXPECT_EQ(dict.getArray().size(), 4);
        EXPECT_EQ(dict.getArray()[0], 0);
        EXPECT_EQ(dict.getArray()[3], 3);
    }
}

GTEST_TEST(dict_array, at) {
    std::vector<int> v;
    v.push_back(42);
    v.push_back(4);
    v.push_back(2);
    v.push_back(24);
    {
        blet::Dict dict(v);
        blet::Dict& r = dict.at(0);
        EXPECT_EQ(r, 42);
    }
    {
        const blet::Dict dict(v);
        const blet::Dict& r = dict.at(1);
        EXPECT_EQ(r, 4);
    }
}

GTEST_TEST(dict_array, back) {
    std::vector<int> v;
    v.push_back(42);
    v.push_back(4);
    v.push_back(2);
    v.push_back(24);
    {
        blet::Dict dict(v);
        blet::Dict& r = dict.back();
        EXPECT_EQ(r, 24);
    }
    {
        const blet::Dict dict(v);
        const blet::Dict& r = dict.back();
        EXPECT_EQ(r, 24);
    }
}

GTEST_TEST(dict_array, array_begin) {
    std::vector<int> v;
    v.push_back(42);
    v.push_back(4);
    v.push_back(2);
    v.push_back(24);
    {
        blet::Dict dict(v);
        EXPECT_EQ(*(dict.array_begin()), 42);
        EXPECT_EQ(*(dict.array_begin() + 1), 4);
        EXPECT_EQ(*(dict.array_begin() + 2), 2);
    }
    {
        const blet::Dict dict(v);
        EXPECT_EQ(*(dict.array_begin()), 42);
        EXPECT_EQ(*(dict.array_begin() + 1), 4);
        EXPECT_EQ(*(dict.array_begin() + 2), 2);
    }
}

GTEST_TEST(dict_array, array_end) {
    std::vector<int> v;
    v.push_back(42);
    v.push_back(4);
    v.push_back(2);
    v.push_back(24);
    {
        blet::Dict dict(v);
        EXPECT_EQ(*(dict.array_end() - 1), 24);
        EXPECT_EQ(*(dict.array_end() - 2), 2);
        EXPECT_EQ(*(dict.array_end() - 3), 4);
    }
    {
        const blet::Dict dict(v);
        EXPECT_EQ(*(dict.array_end() - 1), 24);
        EXPECT_EQ(*(dict.array_end() - 2), 2);
        EXPECT_EQ(*(dict.array_end() - 3), 4);
    }
}

GTEST_TEST(dict_array, erase) {
    std::vector<int> v;
    v.push_back(42);
    v.push_back(4);
    v.push_back(2);
    v.push_back(24);
    {
        blet::Dict dict(v);
        dict.erase(dict.array_begin());
        EXPECT_EQ(dict[0], 4);
        EXPECT_EQ(dict[1], 2);
        EXPECT_EQ(dict[2], 24);
    }
    {
        blet::Dict dict(v);
        dict.erase(dict.array_begin() + 1, dict.array_end());
        EXPECT_EQ(dict.size(), 1);
        EXPECT_EQ(dict[0], 42);
    }
}

GTEST_TEST(dict_array, front) {
    std::vector<int> v;
    v.push_back(42);
    v.push_back(4);
    v.push_back(2);
    v.push_back(24);
    {
        blet::Dict dict(v);
        EXPECT_EQ(dict.front(), 42);
        dict.erase(dict.array_begin());
        EXPECT_EQ(dict.front(), 4);
    }
    {
        const blet::Dict dict(v);
        EXPECT_EQ(dict.front(), 42);
    }
}

GTEST_TEST(dict_array, array_get_allocator) {
    std::vector<int> v;
    v.push_back(42);
    v.push_back(4);
    v.push_back(2);
    v.push_back(24);
    {
        blet::Dict dict(v);
        blet::Dict::array_t::allocator_type type = dict.array_get_allocator();
        (void)type;
    }
}

GTEST_TEST(dict_array, insert) {
    std::vector<int> v;
    v.push_back(42);
    v.push_back(4);
    v.push_back(2);
    v.push_back(24);
    {
        blet::Dict dict(v);
        blet::Dict::array_t::iterator it = dict.insert(dict.array_begin() + 1, 42);
        EXPECT_EQ(dict.size(), 5);
        EXPECT_EQ(it, dict.array_begin() + 1);
    }
    {
        blet::Dict dict(v);
        dict.insert(dict.array_begin() + 1, 5, 42);
        EXPECT_EQ(dict.size(), 9);
    }
    {
        blet::Dict dict(v);
        std::vector<int> n;
        n.push_back(24);
        n.push_back(42);
        dict.insert(dict.array_begin() + 1, n.begin(), n.end());
        EXPECT_EQ(dict.size(), 6);
    }
}

GTEST_TEST(dict_array, pop_back) {
    std::vector<int> v;
    v.push_back(42);
    v.push_back(4);
    v.push_back(2);
    v.push_back(24);
    {
        blet::Dict dict(v);
        dict.pop_back();
        EXPECT_EQ(dict.size(), 3);
    }
}

GTEST_TEST(dict_array, push_back) {
    std::vector<int> v;
    v.push_back(42);
    v.push_back(4);
    v.push_back(2);
    v.push_back(24);
    {
        blet::Dict dict(v);
        dict.push_back(42);
        EXPECT_EQ(dict.size(), 5);
    }
}

GTEST_TEST(dict_array, array_rbegin) {
    std::vector<int> v;
    v.push_back(42);
    v.push_back(4);
    v.push_back(2);
    v.push_back(24);
    {
        blet::Dict dict(v);
        EXPECT_EQ(*dict.array_rbegin(), 24);
    }
    {
        const blet::Dict dict(v);
        EXPECT_EQ(*dict.array_rbegin(), 24);
    }
}

GTEST_TEST(dict_array, array_rend) {
    std::vector<int> v;
    v.push_back(42);
    v.push_back(4);
    v.push_back(2);
    v.push_back(24);
    {
        blet::Dict dict(v);
        EXPECT_EQ(*(dict.array_rend() - 1), 42);
    }
    {
        const blet::Dict dict(v);
        EXPECT_EQ(*(dict.array_rend() - 1), 42);
    }
}

GTEST_TEST(dict_array, resize) {
    std::vector<int> v;
    v.push_back(42);
    v.push_back(4);
    v.push_back(2);
    v.push_back(24);
    {
        blet::Dict dict(v);
        dict.resize(42, dict);
        EXPECT_EQ(dict.size(), 42);
    }
}
