// anksilae@gmail.com


#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "include/doctest.h"

#include "MyContainer.hpp"

using namespace containers;

TEST_CASE("Add and Size")
{
    MyContainer<int> c;
    c.add(1);
    c.add(2);
    c.add(3);
    CHECK(c.size() == 3);
}

TEST_CASE("Remove element once and all its occurrences")
{
    MyContainer<int> c;
    c.add(5);
    c.add(3);
    c.add(5);
    c.add(5);
    c.remove(5);
    CHECK(c.size() == 1);
    CHECK_THROWS(c.remove(5)); // כבר לא קיים
}
TEST_CASE("Remove throws when element not found")
{
    MyContainer<int> c;
    c.add(1);
    c.add(2);
    c.add(3);

    CHECK_THROWS_AS(c.remove(999), std::runtime_error);
}


TEST_CASE("AscendingOrder")
{
    MyContainer<int> c;
    c.add(7);
    c.add(15);
    c.add(6);
    c.add(1);
    c.add(2);
    std::vector<int> expected = {1, 2, 6, 7, 15};
    size_t i = 0;
    for (int x : c.Ascending())
    {
        CHECK(x == expected[i++]);
    }
}

TEST_CASE("DescendingOrder")
{
    MyContainer<int> c;
    c.add(7);
    c.add(15);
    c.add(6);
    c.add(1);
    c.add(2);
    std::vector<int> expected = {15, 7, 6, 2, 1};
    size_t i = 0;
    for (int x : c.Descending())
    {
        CHECK(x == expected[i++]);
    }
}

TEST_CASE("ReverseOrder")
{
    MyContainer<int> c;
    c.add(7);
    c.add(15);
    c.add(6);
    c.add(1);
    c.add(2);
    std::vector<int> expected = {2, 1, 6, 15, 7};
    size_t i = 0;
    for (int x : c.Reverse())
    {
        CHECK(x == expected[i++]);
    }
}

TEST_CASE("Order - original insertion")
{
    MyContainer<int> c;
    c.add(7);
    c.add(15);
    c.add(6);
    c.add(1);
    c.add(2);
    std::vector<int> expected = {7, 15, 6, 1, 2};
    size_t i = 0;
    for (int x : c.Normal())
    {
        CHECK(x == expected[i++]);
    }
}

TEST_CASE("MiddleOutOrder with odd number of elements")
{
    MyContainer<int> c;
    c.add(7);
    c.add(15);
    c.add(6);
    c.add(1);
    c.add(2);
    std::vector<int> expected = {6, 15, 1, 7, 2};
    size_t i = 0;
    for (int x : c.MiddleOut())
    {
        CHECK(x == expected[i++]);
    }
}
TEST_CASE("MiddleOut with even number of elements")
{
    MyContainer<int> c;
    c.add(7);
    c.add(15);
    c.add(6);
    c.add(1);
    c.add(2);
    c.add(8);
    // עיגול כלפי מטה -> אמצע באינדקס 2 (הערך 6)
    std::vector<int> expected = {1, 6, 2, 15, 8, 7};
    size_t i = 0;
    for (int x : c.MiddleOut())
    {
        CHECK(x == expected[i++]);
    }
}

TEST_CASE("SideCrossOrder")
{
    MyContainer<int> c;
    c.add(7);
    c.add(15);
    c.add(6);
    c.add(1);
    c.add(2);
    std::vector<int> expected = {1, 15, 2, 7, 6};
    size_t i = 0;
    for (int x : c.SideCross())
    {
        CHECK(x == expected[i++]);
    }
}

TEST_CASE("Edge case: remove from empty container throws")
{
    MyContainer<int> c;
    CHECK_THROWS(c.remove(42));
}
TEST_CASE("Remove non-existent int value throws")
{
    MyContainer<int> c;
    c.add(10);
    c.add(20);
    c.add(30);
    CHECK_THROWS(c.remove(999)); // אין כזה ערך => שגיאה צריכה להיזרק
}
TEST_CASE("Remove throws on non-existent string")
{
    MyContainer<std::string> c;
    c.add("a");
    CHECK_THROWS_AS(c.remove("b"), std::runtime_error);
}



TEST_CASE("Using container with std::string")
{
    MyContainer<std::string> c;
    c.add("hello");
    c.add("world");
    CHECK(c.size() == 2);
    c.remove("hello");
    CHECK(c.size() == 1);
}

TEST_CASE("Iterators on empty container do not crash")
{
    MyContainer<int> c;
    CHECK(c.Ascending().begin() == c.Ascending().end());
    CHECK(c.Descending().begin() == c.Descending().end());
    CHECK(c.SideCross().begin() == c.SideCross().end());
    CHECK(c.Reverse().begin() == c.Reverse().end());
    CHECK(c.Normal().begin() == c.Normal().end());
    CHECK(c.MiddleOut().begin() == c.MiddleOut().end());
}
TEST_CASE("Single element container behaves correctly in all iterators")
{
    MyContainer<int> c;
    c.add(99);
    std::vector<int> expected = {99};

    size_t i = 0;
    for (int x : c.Ascending())
        CHECK(x == expected[i++]);
    i = 0;
    for (int x : c.Descending())
        CHECK(x == expected[i++]);
    i = 0;
    for (int x : c.SideCross())
        CHECK(x == expected[i++]);
    i = 0;
    for (int x : c.Reverse())
        CHECK(x == expected[i++]);
    i = 0;
    for (int x : c.Normal())
        CHECK(x == expected[i++]);
    i = 0;
    for (int x : c.MiddleOut())
        CHECK(x == expected[i++]);
}
TEST_CASE("Iterator equality and inequality works")
{
    MyContainer<int> c;
    c.add(1);
    c.add(2);
    c.add(3);

    auto asc = c.Ascending();
    auto it = asc.begin();
    auto end = asc.end();

    CHECK(it != end);
    while (it != end)
        ++it;
    CHECK(it == end);
}
TEST_CASE("Iterator invalidation behavior ")
{
    MyContainer<int> c;
    c.add(1);
    c.add(2);
    c.add(3);
    auto it = c.Ascending().begin();

    c.add(4); // שינוי במבנה

    // אפשר לצפות לשגיאה:
    CHECK_THROWS(*it);
    CHECK_THROWS(++it); 
}
TEST_CASE("Iterator throws on out of bounds access") {
    MyContainer<int> c;
    c.add(1);
    auto it = c.Ascending().end();
    CHECK_THROWS_AS(*it, std::out_of_range);
}
TEST_CASE("Iterator throws when incrementing past end") {
    MyContainer<int> c;
    c.add(1);
    auto it = c.Ascending().begin();
    ++it;  // now at end
    CHECK_THROWS_AS(++it, std::out_of_range);
}
