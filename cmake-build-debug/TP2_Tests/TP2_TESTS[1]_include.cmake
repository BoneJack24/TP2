if(EXISTS "/Users/jacquesboisclair/CLionProjects/TP2/TP2/cmake-build-debug/TP2_Tests/TP2_TESTS[1]_tests.cmake")
  include("/Users/jacquesboisclair/CLionProjects/TP2/TP2/cmake-build-debug/TP2_Tests/TP2_TESTS[1]_tests.cmake")
else()
  add_test(TP2_TESTS_NOT_BUILT TP2_TESTS_NOT_BUILT)
endif()