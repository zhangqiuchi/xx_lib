# CMake generated Testfile for 
# Source directory: C:/xx/xx_lib/xx_lib/rapidjson/test/unittest
# Build directory: C:/xx/xx_lib/xx_lib/build/rapidjson/test/unittest
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
if("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
  add_test(unittest "C:/xx/xx_lib/xx_lib/build/bin/unittest")
  set_tests_properties(unittest PROPERTIES  WORKING_DIRECTORY "C:/xx/xx_lib/xx_lib/bin" _BACKTRACE_TRIPLES "C:/xx/xx_lib/xx_lib/rapidjson/test/unittest/CMakeLists.txt;79;add_test;C:/xx/xx_lib/xx_lib/rapidjson/test/unittest/CMakeLists.txt;0;")
elseif("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
  add_test(unittest "C:/xx/xx_lib/xx_lib/build/bin/unittest")
  set_tests_properties(unittest PROPERTIES  WORKING_DIRECTORY "C:/xx/xx_lib/xx_lib/bin" _BACKTRACE_TRIPLES "C:/xx/xx_lib/xx_lib/rapidjson/test/unittest/CMakeLists.txt;79;add_test;C:/xx/xx_lib/xx_lib/rapidjson/test/unittest/CMakeLists.txt;0;")
elseif("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
  add_test(unittest "C:/xx/xx_lib/xx_lib/build/bin/unittest")
  set_tests_properties(unittest PROPERTIES  WORKING_DIRECTORY "C:/xx/xx_lib/xx_lib/bin" _BACKTRACE_TRIPLES "C:/xx/xx_lib/xx_lib/rapidjson/test/unittest/CMakeLists.txt;79;add_test;C:/xx/xx_lib/xx_lib/rapidjson/test/unittest/CMakeLists.txt;0;")
elseif("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
  add_test(unittest "C:/xx/xx_lib/xx_lib/build/bin/unittest")
  set_tests_properties(unittest PROPERTIES  WORKING_DIRECTORY "C:/xx/xx_lib/xx_lib/bin" _BACKTRACE_TRIPLES "C:/xx/xx_lib/xx_lib/rapidjson/test/unittest/CMakeLists.txt;79;add_test;C:/xx/xx_lib/xx_lib/rapidjson/test/unittest/CMakeLists.txt;0;")
else()
  add_test(unittest NOT_AVAILABLE)
endif()
