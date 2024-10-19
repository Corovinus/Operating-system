#include <gtest/gtest.h>
#include "Lab2_OS.h"
#include "Windows.h"

TEST(ThreadTest, MinMaxTest) {
    
    int array[] = { 5, 3, 8, 1, 9 };
    ThreadParams params = { array, 5, 0, 0, 0.0 };

    HANDLE hMin_max = CreateThread(NULL, 0, Min_max, (void*)&params, 0, NULL);
    WaitForSingleObject(hMin_max, INFINITE);
    CloseHandle(hMin_max);

    EXPECT_EQ(params.minValue, 1);
    EXPECT_EQ(params.maxValue, 9);
}

TEST(ThreadTest, AverageTest) {
    int array[] = { 5, 3, 8, 1, 9 };
    ThreadParams params = { array, 5, 0, 0, 0.0 };

    HANDLE hAverage = CreateThread(NULL, 0, Average, (void*)&params, 0, NULL);
    WaitForSingleObject(hAverage, INFINITE);
    CloseHandle(hAverage);

    EXPECT_DOUBLE_EQ(params.averageValue, 5.2);
}

TEST(ThreadTest, ReplaceMinMaxWithAverageTest) {
    int array[] = { 5, 3, 8, 1, 9 };
    ThreadParams params = { array, 5, 1, 9, 5.2 };

    for (int i = 0; i < params.size; i++) {
        if (params.array[i] == params.minValue || params.array[i] == params.maxValue) {
            params.array[i] = static_cast<int>(params.averageValue);
        }
    }

    int expectedArray[] = { 5, 3, 8, 5, 5 };
    for (int i = 0; i < params.size; i++) {
        EXPECT_EQ(params.array[i], expectedArray[i]);
    }
}

int main(int argc, char** argv) {
    setlocale(LC_ALL, "RUS");
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
