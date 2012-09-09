/*
 * Copyright 2012 Marc Schweikert
 */


#include "glog/logging.h"
#include "gtest/gtest.h"


int main(int argc, char **argv) {
    // Initialize Google Test
    ::testing::InitGoogleTest(&argc, argv);

    // Initialize Google's logging library.
    google::InitGoogleLogging(argv[0]);

    const int ret = RUN_ALL_TESTS();

    // Shutdown google's logging library.
    google::ShutdownGoogleLogging();

    return ret;
}
