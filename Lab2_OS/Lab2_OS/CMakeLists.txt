cmake_minimum_required(VERSION 3.12)
project(Lab2_OS)

# Создание основной программы
add_executable(Lab2_OS "Lab2_OS.cpp" "Lab2_OS.h" "Func_Lab2_OS.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Lab2_OS PROPERTY CXX_STANDARD 20)
endif()

# Настройка для тестов
if (NOT TARGET gtest)
  include(FetchContent)
  FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/heads/master.zip
  )
  set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
  FetchContent_MakeAvailable(googletest)
endif()

# Создание отдельного исполняемого файла для тестов
add_executable(Lab2_Tests "Test_Lab2.cpp" "Lab2_OS.h" "Func_Lab2_OS.cpp")

# Линковка тестов с gtest и gtest_main
target_link_libraries(Lab2_Tests gtest gtest_main)

# Настройка для тестирования
enable_testing()
add_test(NAME Lab2_Test COMMAND Lab2_Tests)
