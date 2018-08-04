#include <gtest/gtest.h>
#include <iostream>

#include "file_tests.cpp"
#include "metaparser_tests.cpp"
#include "utility_tests.cpp"
#include "list_tests.cpp"

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


