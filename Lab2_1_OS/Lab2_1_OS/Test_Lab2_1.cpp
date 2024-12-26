#include <gtest/gtest.h>
#include <thread>
#include <vector>
#include <mutex>
#include "Lab2_1_OS.h"

using namespace std;
TEST(ThreadTest, MinMaxTest) {
    vector<int> array = { 5, 3, 8, 1, 9 };
    ThreadParams params = { array, 0, 0, 0.0 };

    thread tMinMax(Min_max, ref(params));
    tMinMax.join();

    EXPECT_EQ(params.minValue, 1);
    EXPECT_EQ(params.maxValue, 9);
}

TEST(ThreadTest, AverageTest) {
    vector<int> array = { 5, 3, 8, 1, 9 };
    ThreadParams params = { array, 0, 0, 0.0 };

    thread tAverage(Average, ref(params));
    tAverage.join();

    EXPECT_DOUBLE_EQ(params.averageValue, 5.2);
}

TEST(ThreadTest, ReplaceMinMaxWithAverageTest) {
    vector<int> array = { 5, 3, 8, 1, 9 };
    ThreadParams params = { array, 1, 9, 5.2 };

    for (int& value : params.array) {
        if (value == params.minValue || value == params.maxValue) {
            value = static_cast<int>(params.averageValue);
        }
    }

    vector<int> expectedArray = { 5, 3, 8, 5, 5 };
    EXPECT_EQ(params.array, expectedArray);
}

TEST(ThreadTest, ConcurrentExecutionTest) {
    vector<int> array = { 10, 20, 30, 40, 50 };
    ThreadParams params = { array, 0, 0, 0.0 };

    thread tMinMax(Min_max, ref(params));
    thread tAverage(Average, ref(params));

    tMinMax.join();
    tAverage.join();

    EXPECT_EQ(params.minValue, 10);
    EXPECT_EQ(params.maxValue, 50);
    EXPECT_DOUBLE_EQ(params.averageValue, 30.0);
}

TEST(ThreadTest, EmptyArrayTest) {
    vector<int> array;
    ThreadParams params = { array, 0, 0, 0.0 };

    thread tMinMax(Min_max, ref(params));
    thread tAverage(Average, ref(params));

    tMinMax.join();
    tAverage.join();

    EXPECT_EQ(params.minValue, 0);  
    EXPECT_EQ(params.maxValue, 0);
    EXPECT_DOUBLE_EQ(params.averageValue, 0.0);
}

TEST(ThreadTest, IdenticalElementsTest) {
    vector<int> array = { 7, 7, 7, 7, 7 };
    ThreadParams params = { array, 0, 0, 0.0 };

    thread tMinMax(Min_max, ref(params));
    thread tAverage(Average, ref(params));

    tMinMax.join();
    tAverage.join();

    EXPECT_EQ(params.minValue, 7);
    EXPECT_EQ(params.maxValue, 7);
    EXPECT_DOUBLE_EQ(params.averageValue, 7.0);

    for (int& value : params.array) {
        if (value == params.minValue || value == params.maxValue) {
            value = static_cast<int>(params.averageValue);
        }
    }

    EXPECT_EQ(params.array, array); 
}

int main(int argc, char** argv) {
    setlocale(LC_ALL, "RUS");
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
