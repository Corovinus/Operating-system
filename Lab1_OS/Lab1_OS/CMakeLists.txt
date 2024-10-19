
add_executable(Main "Main.cpp")

add_executable(Creator "Creator.cpp")

add_executable(Reporter "Reporter.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Main PROPERTY CXX_STANDARD 20)
  set_property(TARGET Creator PROPERTY CXX_STANDARD 20)
  set_property(TARGET Reporter PROPERTY CXX_STANDARD 20)
endif()