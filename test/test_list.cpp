#include "list.h"

#include <gtest/gtest.h>


class TestList : public ::testing::Test
{
};

TEST_F(TestList, createEmptyList)
{
    const pa::List<int> l;
    ASSERT_EQ(l.size(), 0);
    ASSERT_TRUE(l.empty());
}

TEST_F(TestList, createListUsingInitializerList)
{
    const pa::List l{ 1, 2, 3, 4, 5 };
    ASSERT_TRUE(l.size() == 5);
    ASSERT_TRUE(!l.empty());
}

TEST_F(TestList, pushBack)
{
	pa::List<int> l;
	for (const auto i : { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 })
	{
		l.pushBack(i);
	}

	ASSERT_EQ(l.size(), 10);
    // Todo add comparing using operator ==
}

TEST_F(TestList, pushFront)
{
    pa::List<int> l;
    for (const auto i : { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 })
    {
        l.pushFront(i);
    }
    ASSERT_EQ(l.size(), 10);
}

TEST_F(TestList, popFront)
{
    pa::List l { 1, 2, 3 };
    ASSERT_EQ(l.size(), 3);
	ASSERT_FALSE(l.empty());

    ASSERT_EQ(1, l.popFront());
    ASSERT_EQ(l.size(), 2);

    ASSERT_EQ(2, l.popFront());
    ASSERT_EQ(l.size(), 1);

    ASSERT_EQ(3, l.popFront());
    ASSERT_TRUE(l.empty());
}

TEST_F(TestList, popBack)
{
    pa::List l{ 1, 2, 3 };
    ASSERT_EQ(l.size(), 3);
    ASSERT_FALSE(l.empty());

    ASSERT_EQ(3, l.popBack());
    ASSERT_EQ(l.size(), 2);

    ASSERT_EQ(2, l.popBack());
    ASSERT_EQ(l.size(), 1);

    ASSERT_EQ(1, l.popBack());
    ASSERT_TRUE(l.empty());
}

TEST_F(TestList, remove)
{
    using namespace pa;
    {
        List l{ 1, 2, 3 };
        ASSERT_TRUE(l.remove(3));
        ASSERT_EQ(l.size(), 2);
    }
    {
        List l{ 1, 2, 3 };
        ASSERT_TRUE(l.remove(1) == true);
        ASSERT_EQ(l.size(), 2);

        ASSERT_FALSE(l.remove(10));
        ASSERT_EQ(l.size(), 2);
    }
    {
        List l{ 1, 2, 3 };
        ASSERT_TRUE(l.remove(2));
        ASSERT_EQ(l.size(), 2);
        ASSERT_EQ(l.front(), 1);
        ASSERT_EQ(l.back(), 3);
    }
    {
        List<int> l;
        l.pushBack(1);
        ASSERT_TRUE(l.remove(1) == true);
        ASSERT_EQ(l.size(), 0);
    }
    {
        List<int> l;
        ASSERT_FALSE(l.remove(1));
        ASSERT_EQ(l.size(), 0);
        ASSERT_TRUE(l.empty());
    }
}

TEST_F(TestList, insert)
{
    using namespace pa;
    List<int> l;
    for (const auto i : { 1, 2, 3 })
    {
        l.insert(3);
    }
    ASSERT_EQ(3, l.size());
}
