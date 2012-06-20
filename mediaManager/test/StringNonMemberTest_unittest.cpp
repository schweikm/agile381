/*
 * Copyright 2012 Marc Schweikert
 */

#include "String.h"
#include "gtest/gtest.h"


// To use a test fixture, derive a class from testing::Test.
class StringNonMemberTest : public testing::Test {
    protected:
    // virtual void SetUp() will be called before each test is run.  You
    // should define it if you need to initialize the varaibles.
    // Otherwise, this can be skipped.
/*    virtual void SetUp() { } */

    // virtual void TearDown() will be called after each test is run.
    // You should define it if there is cleanup work to do.  Otherwise,
    // you don't have to provide it.
/*    virtual void TearDown() { } */

    // Declares the variables your tests want to use.
};


// operator==
TEST_F(StringNonMemberTest, operatorEquals) {
    ASSERT_EQ(1, 1);
}

// operator !=
TEST_F(StringNonMemberTest, operatorNotEquals) {
    ASSERT_EQ(1, 1);
}

// operator<
TEST_F(StringNonMemberTest, operatorLessThan) {
    ASSERT_EQ(1, 1);
}

// operator>
TEST_F(StringNonMemberTest, operatorGreaterThan) {
    ASSERT_EQ(1, 1);
}

// operator+
TEST_F(StringNonMemberTest, operatorAddition) {
    ASSERT_EQ(1, 1);
}

// getline
TEST_F(StringNonMemberTest, getline) {
    ASSERT_EQ(1, 1);
}

