#include "Skip_list.h"
#include <gtest.h>
#include <climits> 

class Test_Skip_list : public ::testing::Test
{
protected:

    void SetUp() override  
    {
        container = new Skip_list(3);

        sampleData = { 23, 12, 45, 5 };

        for (int num : sampleData)
        {
            container->insert(num);
        }
    }

    void TearDown() override  
    {
        delete container;
    }

    Skip_list* container;

    std::vector<int> sampleData;
};


TEST_F(Test_Skip_list, CombinedOperationsCheck)
{
    container->insert(30);

    ASSERT_NE(container->locate(30), nullptr);

    container->erase(12);

    EXPECT_EQ(container->locate(12), nullptr);

    container->insert(12);

    EXPECT_NE(container->locate(12), nullptr);

    XNode* element = container->locate(5);

    EXPECT_EQ(element->right->data, 12);
}

TEST_F(Test_Skip_list, ConstructorValidation)
{
    Skip_list newContainer(2);

    EXPECT_EQ(newContainer.getHeight(), 2);

    EXPECT_EQ(newContainer.locate(0), nullptr);
}

TEST_F(Test_Skip_list, InsertionEffect)
{
    const size_t initialCount = sampleData.size();

    container->insert(30);

    EXPECT_NE(container->locate(30), nullptr);
}

TEST_F(Test_Skip_list, SuccessfulLocateOperations)
{
    for (int num : sampleData)
    {
        XNode* result = container->locate(num);

        ASSERT_NE(result, nullptr);

        EXPECT_EQ(result->data, num);
    }
}

TEST_F(Test_Skip_list, FailedLocateOperations)
{
    std::vector<int> nonExisting = { 99, -1, 1000 };

    for (int num : nonExisting)
    {
        EXPECT_EQ(container->locate(num), nullptr);
    }
}

TEST_F(Test_Skip_list, ValidRemoval)
{
    container->erase(23);

    EXPECT_EQ(container->locate(23), nullptr);

    container->erase(5);

    EXPECT_EQ(container->locate(5), nullptr);
}

TEST_F(Test_Skip_list, InvalidRemoval)
{
    EXPECT_THROW(container->erase(999), std::logic_error);

    EXPECT_THROW(container->erase(-5), std::logic_error);
}

TEST_F(Test_Skip_list, OrderVerification)
{
    container->insert(15);

    XNode* element = container->locate(12);

    ASSERT_NE(element, nullptr);

    EXPECT_EQ(element->right->data, 15);

    EXPECT_EQ(element->right->right->data, 23);
}

TEST_F(Test_Skip_list, BottomLayerCheck)
{
    XNode* element = container->locate(5);

    while (element)
    {
        EXPECT_EQ(element->bottom, nullptr);

        element = element->right;
    }
}

TEST_F(Test_Skip_list, DuplicateHandling)
{
    container->insert(12);

    XNode* element = container->locate(12);

    ASSERT_NE(element, nullptr);

    EXPECT_EQ(element->data, 12);
}

TEST_F(Test_Skip_list, BoundaryValues)
{
    container->insert(INT_MAX);

    container->insert(INT_MIN);

    EXPECT_EQ(container->locate(INT_MAX)->data, INT_MAX);

    EXPECT_EQ(container->locate(INT_MIN)->data, INT_MIN);
}