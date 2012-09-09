/*
 * Copyright 2012 Marc Schweikert
 */


#include <cstring>
#include <string>
  using std::string;

#include "gtest/gtest.h"
#include "manager/String.h"


///////////////////////////////////////////////////////////////////////////////
//
// operator==
//
///////////////////////////////////////////////////////////////////////////////
TEST(StringNonMemberTest, operatorEquals) {
    const String test1("alpha");
    const String test2("alpha");
    const String test3("beta");

    // equal - pass
    EXPECT_TRUE(test1 == test2);

    // not equal - fail
    EXPECT_FALSE(test1 == test3);
}

///////////////////////////////////////////////////////////////////////////////
//
// operator!=
//
///////////////////////////////////////////////////////////////////////////////
TEST(StringNonMemberTest, operatorNotEquals) {
    const String test1("charlie");
    const String test2("charlie");
    const String test3("delta");

    // equal - fail
    EXPECT_FALSE(test1 != test2);

    // not equal - pass
    EXPECT_TRUE(test1 != test3);
}

///////////////////////////////////////////////////////////////////////////////
//
// operator<
//
///////////////////////////////////////////////////////////////////////////////
TEST(StringNonMemberTest, operatorLessThan) {
    const String test1("echo");
    const String test2("foxtrot");

    // less than - pass
    EXPECT_TRUE(test1 < test2);

    // greater than - fail
    EXPECT_FALSE(test2 < test1);
}

///////////////////////////////////////////////////////////////////////////////
//
// operator>
//
///////////////////////////////////////////////////////////////////////////////
TEST(StringNonMemberTest, operatorGreaterThan) {
    const String test1("gulf");
    const String test2("hotel");

    // greater than - pass
    EXPECT_TRUE(test2 > test1);

    // less than - fail
    EXPECT_FALSE(test1 > test2);
}

///////////////////////////////////////////////////////////////////////////////
//
// operator+
//
///////////////////////////////////////////////////////////////////////////////
TEST(StringNonMemberTest, operatorAddition) {
    const string str1 = "|ye ye ye ye ye|";
    const string str2 = "^ho ho ho ho ho^";
    const string concat = str1 + str2;

    const String test1(str1.c_str());
    const String test2(str2.c_str());
    const String test3 = test1 + test2;

    // this is just a wrapper for operator+=, so just compare the strings
    EXPECT_STREQ(concat.c_str(), test3.c_str());
}
