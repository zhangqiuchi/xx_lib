# CMake generated Testfile for 
# Source directory: C:/xx/xx_lib/xx_lib/rapidjson/test/perftest
# Build directory: C:/xx/xx_lib/xx_lib/build/rapidjson/test/perftest
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
if("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
  add_test(perftest "C:/xx/xx_lib/xx_lib/build/bin/perftest")
  set_tests_properties(perftest PROPERTIES  WORKING_DIRECTORY "C:/xx/xx_lib/xx_lib/bin" _BACKTRACE_TRIPLES "C:/xx/xx_lib/xx_lib/rapidjson/test/perftest/CMakeLists.txt;25;add_test;C:/xx/xx_lib/xx_lib/rapidjson/test/perftest/CMakeLists.txt;0;")
elseif("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
  add_test(perftest "C:/xx/xx_lib/xx_lib/build/bin/perftest")
  set_tests_properties(perftest PROPERTIES  WORKING_DIRECTORY "C:/xx/xx_lib/xx_lib/bin" _BACKTRACE_TRIPLES "C:/xx/xx_lib/xx_lib/rapidjson/test/perftest/CMakeLists.txt;25;add_test;C:/xx/xx_lib/xx_lib/rapidjson/test/perftest/CMakeLists.txt;0;")
elseif("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
  add_test(perftest "C:/xx/xx_lib/xx_lib/build/bin/perftest")
  set_tests_properties(perftest PROPERTIES  WORKING_DIRECTORY "C:/xx/xx_lib/xx_lib/bin" _BACKTRACE_TRIPLES "C:/xx/xx_lib/xx_lib/rapidjson/test/perftest/CMakeLists.txt;25;add_test;C:/xx/xx_lib/xx_lib/rapidjson/test/perftest/CMakeLists.txt;0;")
elseif("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
  add_test(perftest "C:/xx/xx_lib/xx_lib/build/bin/perftest")
  set_tests_properties(perftest PROPERTIES  WORKING_DIRECTORY "C:/xx/xx_lib/xx_lib/bin" _BACKTRACE_TRIPLES "C:/xx/xx_lib/xx_lib/rapidjson/test/perftest/CMakeLists.txt;25;add_test;C:/xx/xx_lib/xx_lib/rapidjson/test/perftest/CMakeLists.txt;0;")
else()
  add_test(perftest NOT_AVAILABLE)
endif()
