#include "Functional.hpp"
#include <gtest/gtest.h>
#include <vector>

TEST(TestFunctional, IndexOf)
{
    std::vector<double> v{1, 2, 3, 4};
    auto i = IndexOf(v.begin(), v.end(), 2);
    ASSERT_EQ(1, i);
}

TEST(TestFunctional, Sum)
{
    std::vector<double> v{1, 2, 3, 4};
    double i = Sum<double>(v.begin(), v.end(), [](double x) { return x; });
    ASSERT_EQ(10, i);
}

TEST(TestFunctional, Where)
{
    std::vector<double> v{1, 2, 3, 4};
    double i = Where<double, std::vector<double>>(v.begin(), v.end(), [](double x) { return x == 2; }).at(0);
    ASSERT_EQ(2, i);
}

struct MockStruct
{
    char bar;
    int foo;
};

TEST(TestFunctional, Select)
{
    std::vector<MockStruct> v{MockStruct{'a', 0}, MockStruct{'b', 1}, MockStruct{'c', 2}};
    auto chars = Select<MockStruct, char, std::vector<char>>(v.begin(), v.end(), [](MockStruct x) { return x.bar; });
    auto ints = Select<MockStruct, char, std::vector<int>>(v.begin(), v.end(), [](MockStruct x) { return x.foo; });
    ASSERT_EQ(2, ints.at(2));
    ASSERT_EQ('c', chars.at(2));
}


TEST(TestFunctional, ConvertAll)
{
    std::vector<double> v{1, 2, 3, 4};
    int i = ConvertAll<double, int, std::vector<int>>(v.begin(), v.end()).at(0);
    ASSERT_EQ(1, i);
}

TEST(TestFunctional, Reverse)
{
    std::vector<double> v{1, 2, 3, 4};
    auto rev = Reverse<double, std::vector<double>>(v.begin(), v.end());
    for (int i = 0; i < v.size(); i++)
        ASSERT_EQ(v.at(i), rev.at(v.size() - i - 1));
}


