# CMakeList.txt: проект CMake для Lab2_1_OS; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Добавьте источник в исполняемый файл этого проекта.
add_executable (Lab2_1_OS "Lab2_1_OS.cpp" "Func_Lab2_1_OS.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Lab2_1_OS PROPERTY CXX_STANDARD 20)
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
add_executable(Lab2_Tests "Test_Lab2_1.cpp" "Lab2_1_OS.h" "Func_Lab2_1_OS.cpp")

# Линковка тестов с gtest и gtest_main
target_link_libraries(Lab2_Tests gtest gtest_main)

# Настройка для тестирования
enable_testing()
add_test(NAME Lab2_Test COMMAND Lab2_Tests)

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
