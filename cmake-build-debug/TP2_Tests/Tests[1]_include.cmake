if(EXISTS "/Users/jacquesboisclair/CLionProjects/TP2/TP2/cmake-build-debug/TP2_Tests/Tests[1]_tests.cmake")
  include("/Users/jacquesboisclair/CLionProjects/TP2/TP2/cmake-build-debug/TP2_Tests/Tests[1]_tests.cmake")
else()
  add_test(Tests_NOT_BUILT Tests_NOT_BUILT)
endif()
