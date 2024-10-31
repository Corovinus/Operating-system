# CMakeList.txt: проект CMake для Lab4_OS; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#

# Добавьте источник в исполняемый файл этого проекта.
add_executable (Lab4_OS "Lab4_OS.cpp" "Lab4_OS.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Lab4_OS PROPERTY CXX_STANDARD 20)
endif()

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
