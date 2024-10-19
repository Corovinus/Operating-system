# CMake generated Testfile for 
# Source directory: D:/Progs/Project/Lab2_OS/Lab2_OS
# Build directory: D:/Progs/Project/Lab2_OS/build/Lab2_OS
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
if(CTEST_CONFIGURATION_TYPE MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
  add_test(Lab2_Test "D:/Progs/Project/Lab2_OS/build/Lab2_OS/Debug/Lab2_Tests.exe")
  set_tests_properties(Lab2_Test PROPERTIES  _BACKTRACE_TRIPLES "D:/Progs/Project/Lab2_OS/Lab2_OS/CMakeLists.txt;30;add_test;D:/Progs/Project/Lab2_OS/Lab2_OS/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
  add_test(Lab2_Test "D:/Progs/Project/Lab2_OS/build/Lab2_OS/Release/Lab2_Tests.exe")
  set_tests_properties(Lab2_Test PROPERTIES  _BACKTRACE_TRIPLES "D:/Progs/Project/Lab2_OS/Lab2_OS/CMakeLists.txt;30;add_test;D:/Progs/Project/Lab2_OS/Lab2_OS/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
  add_test(Lab2_Test "D:/Progs/Project/Lab2_OS/build/Lab2_OS/MinSizeRel/Lab2_Tests.exe")
  set_tests_properties(Lab2_Test PROPERTIES  _BACKTRACE_TRIPLES "D:/Progs/Project/Lab2_OS/Lab2_OS/CMakeLists.txt;30;add_test;D:/Progs/Project/Lab2_OS/Lab2_OS/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
  add_test(Lab2_Test "D:/Progs/Project/Lab2_OS/build/Lab2_OS/RelWithDebInfo/Lab2_Tests.exe")
  set_tests_properties(Lab2_Test PROPERTIES  _BACKTRACE_TRIPLES "D:/Progs/Project/Lab2_OS/Lab2_OS/CMakeLists.txt;30;add_test;D:/Progs/Project/Lab2_OS/Lab2_OS/CMakeLists.txt;0;")
else()
  add_test(Lab2_Test NOT_AVAILABLE)
endif()
subdirs("../_deps/googletest-build")
