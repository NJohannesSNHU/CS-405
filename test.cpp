// Uncomment the next line to use precompiled headers
#include "pch.h"
// uncomment the next line if you do not use precompiled headers
//#include "gtest/gtest.h"
//
// the global test environment setup and tear down
// you should not need to change anything here
class Environment : public ::testing::Environment
{
public:
    ~Environment() override {}

    // Override this to define how to set up the environment.
    void SetUp() override
    {
        //  initialize random seed
        srand(time(nullptr));
    }

    // Override this to define how to tear down the environment.
    void TearDown() override {}
};

// create our test class to house shared data between tests
// you should not need to change anything here
class CollectionTest : public ::testing::Test
{
protected:
    // create a smart point to hold our collection
    std::unique_ptr<std::vector<int>> collection;

    void SetUp() override
    { // create a new collection to be used in the test
        collection.reset(new std::vector<int>);
    }

    void TearDown() override
    { //  erase all elements in the collection, if any remain
        collection->clear();
        // free the pointer
        collection.reset(nullptr);
    }

    // helper function to add random values from 0 to 99 count times to the collection
    void add_entries(int count)
    {
        assert(count > 0);
        for (auto i = 0; i < count; ++i)
            collection->push_back(rand() % 100);
    }
};

// When should you use the EXPECT_xxx or ASSERT_xxx macros?
// Use ASSERT when failure should terminate processing, such as the reason for the test case.
// Use EXPECT when failure should notify, but processing should continue

// Test that a collection is empty when created.
// Prior to calling this (and all other TEST_F defined methods),
//  CollectionTest::StartUp is called.
// Following this method (and all other TEST_F defined methods),
//  CollectionTest::TearDown is called
TEST_F(CollectionTest, CollectionSmartPointerIsNotNull)
{
    // is the collection created
    ASSERT_TRUE(collection);

    // if empty, the size must be 0
    ASSERT_NE(collection.get(), nullptr);
}

// Test that a collection is empty when created.
TEST_F(CollectionTest, IsEmptyOnCreate)
{
    // is the collection empty?
    ASSERT_TRUE(collection->empty());

    // if empty, the size must be 0
    ASSERT_EQ(collection->size(), 0);
}

/* Comment this test out to prevent the test from running
 * Uncomment this test to see a failure in the test explorer */
/*TEST_F(CollectionTest, AlwaysFail)
*{
*    FAIL();
*}*/

// Test that a single value can be added to an empty collection.
TEST_F(CollectionTest, CanAddToEmptyVector)
{
    // The collection should initially be empty.
    ASSERT_TRUE(collection->empty());
    ASSERT_EQ(collection->size(), 0);
    
    // Add one entry.
    add_entries(1);

    // The collection should no longer be empty.
    EXPECT_FALSE(collection->empty());
    
    // The collection shoud contain exactly one entry.
    EXPECT_EQ(collection->size(), 1);
}

// Test that five values can be added to the collection.
TEST_F(CollectionTest, CanAddFiveValuesToVector)
{
    // Add five entries.
    add_entries(5);

    // The collection should contain five entries.
    ASSERT_EQ(collection->size(), 5);

    // The collection should not be empty.
    EXPECT_FALSE(collection->empty());
}

// Test that capacity is greater than or equal to size
// for 0, 1, 5, and 10 entries.
TEST_F(CollectionTest, CapacityIsGreaterThanOrEqualToSize)
{
    // Test with an empty collection.
    EXPECT_GE(collection->capacity(), collection->size());

    // Test with one entry.
    add_entries(1);
    EXPECT_GE(collection->capacity(), collection->size());

    // Test with five entries.
    add_entries(4);
    EXPECT_GE(collection->capacity(), collection->size());

    // Test with ten entries.
    add_entries(5);
    EXPECT_GE(collection->capacity(), collection->size());
}

// Test that resizing increases the collection.
TEST_F(CollectionTest, ResizeIncreasesCollection)
{
    // Resize the collection to hold five elements.
    collection->resize(5);

    // The collection should now contain five elements.
    ASSERT_EQ(collection->size(), 5);

    // The collection should not be empty.
    EXPECT_FALSE(collection->empty());
}

// Test that resizing decreases the collection.
TEST_F(CollectionTest, ResizeDecreasesCollection)
{
    // Add ten entries to the collection.
    add_entries(10);

    // Verify that ten entries were added.
    ASSERT_EQ(collection->size(), 10);

    // Resize the collection to five elements.
    collection->resize(5);

    // The collection should now contain five elements.
    EXPECT_EQ(collection->size(), 5);

    // The collection should not be empty.
    EXPECT_FALSE(collection->empty());
}

// Test that resizing the collection to zero removes all elements.
TEST_F(CollectionTest, ResizeToZeroEmptiesCollection)
{
    // Add five entries.
    add_entries(5);

    // Verify that the collection contains five entries.
    ASSERT_EQ(collection->size(), 5);

    // Resize the collection to zero.
    collection->resize(0);

    // The collection should now be empty.
    EXPECT_TRUE(collection->empty());

    // The collection size should be zero.
    EXPECT_EQ(collection->size(), 0);
}

// Test that clear erases the collection.
TEST_F(CollectionTest, ClearErasesCollection)
{
    // Add five entries.
    add_entries(5);

    // Verify that the collection contains five entries.
    ASSERT_EQ(collection->size(), 5);

    // Clear the collection.
    collection->clear();

    // The collection should be empty.
    EXPECT_TRUE(collection->empty());

    // The collection size should be zero.
    EXPECT_EQ(collection->size(), 0);
}

// Test that erase(begin, end) erases the collection.
TEST_F(CollectionTest, EraseBeginEndErasesCollection)
{
    // Add five entries.
    add_entries(5);

    // Verify that the collection contains five entries.
    ASSERT_EQ(collection->size(), 5);

    // Erase all elements using the beginning and ending iterators.
    collection->erase(collection->begin(), collection->end());

    // The collection should now be empty.
    EXPECT_TRUE(collection->empty());

    // The collection size should be zero.
    EXPECT_EQ(collection->size(), 0);
}

// Test that reserve increases capacity without changing size.
TEST_F(CollectionTest, ReserveIncreasesCapacityWithoutChangingSize)
{
    // Add five entries to the collection.
    add_entries(5);

    // Record the original size and capacity.
    const auto originalSize = collection->size();
    const auto originalCapacity = collection->capacity();

    // Reserve enough space for 100 elements.
    collection->reserve(100);

    // The size should not change when reserve is called.
    EXPECT_EQ(collection->size(), originalSize);

    // The capacity should be at least 100.
    EXPECT_GE(collection->capacity(), 100);

    // The capacity should not have decreased.
    EXPECT_GE(collection->capacity(), originalCapacity);
}

// Negative test: verify that accessing an invalid index
// throws the expected std::out_of_range exception.
TEST_F(CollectionTest, ThrowsOutOfRangeWhenAccessingInvalidIndex)
{
    // Add five entries to the collection.
    add_entries(5);

    // Accessing index 5 is invalid because valid indexes are 0 through 4.
    EXPECT_THROW(collection->at(5), std::out_of_range);
}

// Custom positive test: verify that the first element can be
// accessed using front().
TEST_F(CollectionTest, CanAccessFirstElement)
{
    // Add a known value to the collection.
    collection->push_back(42);

    // Add another value so that the collection has more than one element.
    collection->push_back(100);

    // The first element should be 42.
    ASSERT_FALSE(collection->empty());
    EXPECT_EQ(collection->front(), 42);
}

// Custom negative test: verify that accessing an empty collection
// with at() throws std::out_of_range.
TEST_F(CollectionTest, ThrowsOutOfRangeWhenAccessingEmptyVector)
{
    // The collection should initially be empty.
    ASSERT_TRUE(collection->empty());

    // Calling at(0) on an empty vector should throw std::out_of_range.
    EXPECT_THROW(collection->at(0), std::out_of_range);
}