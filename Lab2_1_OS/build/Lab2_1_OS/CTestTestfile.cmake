# CMake generated Testfile for 
# Source directory: D:/Progs/Operating system/Lab2_1_OS/Lab2_1_OS
# Build directory: D:/Progs/Operating system/Lab2_1_OS/build/Lab2_1_OS
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
if(CTEST_CONFIGURATION_TYPE MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
  add_test(Lab2_Test "D:/Progs/Operating system/Lab2_1_OS/build/Lab2_1_OS/Debug/Lab2_Tests.exe")
  set_tests_properties(Lab2_Test PROPERTIES  _BACKTRACE_TRIPLES "D:/Progs/Operating system/Lab2_1_OS/Lab2_1_OS/CMakeLists.txt;32;add_test;D:/Progs/Operating system/Lab2_1_OS/Lab2_1_OS/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
  add_test(Lab2_Test "D:/Progs/Operating system/Lab2_1_OS/build/Lab2_1_OS/Release/Lab2_Tests.exe")
  set_tests_properties(Lab2_Test PROPERTIES  _BACKTRACE_TRIPLES "D:/Progs/Operating system/Lab2_1_OS/Lab2_1_OS/CMakeLists.txt;32;add_test;D:/Progs/Operating system/Lab2_1_OS/Lab2_1_OS/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
  add_test(Lab2_Test "D:/Progs/Operating system/Lab2_1_OS/build/Lab2_1_OS/MinSizeRel/Lab2_Tests.exe")
  set_tests_properties(Lab2_Test PROPERTIES  _BACKTRACE_TRIPLES "D:/Progs/Operating system/Lab2_1_OS/Lab2_1_OS/CMakeLists.txt;32;add_test;D:/Progs/Operating system/Lab2_1_OS/Lab2_1_OS/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
  add_test(Lab2_Test "D:/Progs/Operating system/Lab2_1_OS/build/Lab2_1_OS/RelWithDebInfo/Lab2_Tests.exe")
  set_tests_properties(Lab2_Test PROPERTIES  _BACKTRACE_TRIPLES "D:/Progs/Operating system/Lab2_1_OS/Lab2_1_OS/CMakeLists.txt;32;add_test;D:/Progs/Operating system/Lab2_1_OS/Lab2_1_OS/CMakeLists.txt;0;")
else()
  add_test(Lab2_Test NOT_AVAILABLE)
endif()
subdirs("../_deps/googletest-build")
