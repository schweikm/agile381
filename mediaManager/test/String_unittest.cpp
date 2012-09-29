/*
 * Copyright 2012 Marc Schweikert
 */


#include <cstddef>
#include <cstdio>
#include <string>
    using std::string;

#include "boost/shared_ptr.hpp"
  using boost::shared_ptr;

#include "gtest/gtest.h"

#include "manager/String.h"


// To use a test fixture, derive a class from testing::Test.
class StringUnitTest : public testing::Test {
  protected:
    // virtual void SetUp() will be called before each test is run.  You
    // should define it if you need to initialize the varaibles.
    // Otherwise, this can be skipped.
/*    virtual void SetUp() { } */

    // virtual void TearDown() will be called after each test is run.
    // You should define it if there is cleanup work to do.  Otherwise,
    // you don't have to provide it.
/*    virtual void TearDown() { } */


    //////////////////////
    // HELPER FUNCTIONS //
    //////////////////////


    // Constructor Helper
    void initHelper(const string& in_string) {
        // capture the statics before creating the String instance
        const int numStrings = String::get_number();
        const int totalAllocation = String::get_total_allocation();

        // create the String instance
        String testStr;
        ASSERT_EQ(OK, testStr.init(in_string.c_str()));

        // verify everything is correct
        verifyStrings(in_string.c_str(),
                      testStr.c_str(),
                      static_cast<int>(in_string.length()),
                      testStr.size(),
                      static_cast<int>(in_string.length()) + 1,
                      testStr.get_allocation(),
                      numStrings + 1,
                      totalAllocation + testStr.get_allocation());
    }


    /////////////////////
    // UTILITY METHODS //
    /////////////////////


    // utility method to compare the String data
    void verifyStrings(const char* const expected_cstr,
                       const char* const actual_cstr,
                       const int expected_length,
                       const int actual_length,
                       const int expected_allocation,
                       const int actual_allocation,
                       const int expected_numStrings,
                       const int expected_totalAllocation) {
        // String value is correct
        EXPECT_STREQ(expected_cstr, actual_cstr);

        // the length is correct
        EXPECT_EQ(expected_length, actual_length);

        // the allocation is correct
        EXPECT_EQ(expected_allocation, actual_allocation);

        // the global number of string is correct
        EXPECT_EQ(expected_numStrings, String::get_number());

        // the global allocation of memory is correct
        EXPECT_EQ(expected_totalAllocation, String::get_total_allocation());
    }

    // utility method to verify equality of String and string
    void compareStrings(const string& a, const String& b) {
        // String value is correct
        EXPECT_STREQ(a.c_str(), b.c_str());

        // the length is correct
        EXPECT_EQ(a.length(), b.size());

        // the allocation is correct
        EXPECT_EQ(a.length() + 1, b.get_allocation());
    }

    // utility method to verify equality of String and string with allocation
    void compareStringsWithAlloc(const string& a, const String& b,
                                 const int alloc) {
        // String value is correct
        EXPECT_STREQ(a.c_str(), b.c_str());

        // the length is correct
        EXPECT_EQ(a.length(), b.size());

        // the allocation is correct
        EXPECT_EQ(alloc, b.get_allocation());
    }
};


///////////////////////////////////////////////////////////////////////////////
//
// Init
//
///////////////////////////////////////////////////////////////////////////////
TEST_F(StringUnitTest, Init) {
    // TEST 1
    //    Simple string - one word
    initHelper("alpha");

    // TEST 2
    //    Simple string - a little more complex with punctuation
    initHelper("Hello, world!");

    // TEST 3
    //    Simple string - lots of non-word characters
    initHelper("The!quick@brown#fox$jumped^over&the*lazy.dog");

    // TEST 4
    //    Corner case - Empty string
    initHelper("");
}

///////////////////////////////////////////////////////////////////////////////
//
// Destructor
//
///////////////////////////////////////////////////////////////////////////////
TEST_F(StringUnitTest, Destructor) {
    // capture the statics before creating the String instance
    const int numStrings = String::get_number();
    const int totalAllocation = String::get_total_allocation();
    const string test1Val = "alpha";

    {
        String test1;
        ASSERT_EQ(OK, test1.init(test1Val.c_str()));
        EXPECT_EQ(numStrings + 1, String::get_number());
        EXPECT_EQ(test1Val.length() + 1, totalAllocation +
                                           String::get_total_allocation());
    }  // test1 goes out of scope - destructor called

    // number of strings is decremented
    EXPECT_EQ(numStrings, String::get_number());

    // allocation is decreased
    EXPECT_EQ(totalAllocation, String::get_total_allocation());
}

///////////////////////////////////////////////////////////////////////////////
//
// get
//
///////////////////////////////////////////////////////////////////////////////
TEST_F(StringUnitTest, Get) {
    const string a("all your base are belong to us");
    String b;
    ASSERT_EQ(OK, b.init(a.c_str()));
    char val;

    // normal case
    for (int i = 0; i < static_cast<int>(a.length()); i++) {
        EXPECT_EQ(OK, b.get(i, &val));
        EXPECT_EQ(a[static_cast<size_t>(i)], val);
    }

    // less than zero
    EXPECT_EQ(ERROR, b.get(-1, &val));

    // greater than length
    EXPECT_EQ(ERROR, b.get(static_cast<int>(a.length()) + 1, &val));
}

///////////////////////////////////////////////////////////////////////////////
//
// substring
//
///////////////////////////////////////////////////////////////////////////////
TEST_F(StringUnitTest, Substring) {
    const string fullString = "All your base are belong to us";
    const string subString = "your base are belong";
    const int subStringLen = 20;

    // normal case
    String test;
    String test2;

    ASSERT_EQ(OK, test.init(fullString.c_str()));
    EXPECT_EQ(OK, test.substring(4, subStringLen, &test2));
    compareStrings(subString, test2);

    // corner case, both zero
    String test4;
    EXPECT_EQ(OK, test.substring(0, 0, &test4));
    compareStrings("", test4);

    //
    // index
    //

    String test5;

    // index less than zero
    EXPECT_EQ(ERROR, test2.substring(-1, 1, &test5));

    // index greater than size
    EXPECT_EQ(ERROR, test2.substring(test.size() + 1, 1, &test5));

    //
    // length
    //

    // length less than zero
    EXPECT_EQ(ERROR, test2.substring(0, -1, &test5));

    // length greater than size
    EXPECT_EQ(ERROR, test2.substring(0, test.size() + 1, &test5));

    // index + length greater than size
    EXPECT_EQ(ERROR, test2.substring(subStringLen, test.size() + 1, &test5));
}

///////////////////////////////////////////////////////////////////////////////
//
// clear()
//
///////////////////////////////////////////////////////////////////////////////
TEST_F(StringUnitTest, Clear) {
    String test;
    ASSERT_EQ(OK, test.init("trololololololo"));
    test.clear();
    compareStrings("", test);
}

///////////////////////////////////////////////////////////////////////////////
//
// remove()
//
///////////////////////////////////////////////////////////////////////////////
TEST_F(StringUnitTest, Remove) {
    // normal case
    const string fullString = "All your base are belong to us";
    const string subString = "All your belong to us";
    String test;
    ASSERT_EQ(OK, test.init(fullString.c_str()));
    EXPECT_EQ(OK, test.remove(9, 9));
    compareStringsWithAlloc(subString,
                            test,
                            static_cast<int>(fullString.length()) + 1);

    // normal case 2
    const string subString1 = "All your o us";
    String test1;
    ASSERT_EQ(OK, test1.init(fullString.c_str()));
    EXPECT_EQ(OK, test1.remove(9, 17));
    compareStringsWithAlloc(subString1,
                            test1,
                            static_cast<int>(fullString.length()) + 1);

    // corner case, both zero
    String test2;
    ASSERT_EQ(OK, test2.init(fullString.c_str()));
    EXPECT_EQ(OK, test2.remove(0, 0));
    compareStringsWithAlloc(fullString,
                            test2,
                            static_cast<int>(fullString.length()) + 1);

    //
    // index
    //

    // index less than zero
    EXPECT_EQ(ERROR, test2.remove(-1, 1));

    // index greater than size
    EXPECT_EQ(ERROR, test2.remove(test2.size() + 1, 1));

    //
    // length
    //

    // length less than zero
    EXPECT_EQ(ERROR, test2.remove(0, -1));

    // length greater than size
    EXPECT_EQ(ERROR, test2.remove(0, test2.size() + 1));

    // index + length greater than size
    EXPECT_EQ(ERROR, test2.remove(8, test2.size() + 1));
}

///////////////////////////////////////////////////////////////////////////////
//
// insert_before()
//
///////////////////////////////////////////////////////////////////////////////
TEST_F(StringUnitTest, InsertBefore) {
    const string full1 = "|the quick brown fox|";
    const string full2 = "^jumps over the lazy dog^";
    const int alloc1 = 2 * (static_cast<int>(full1.length()) +
                              static_cast<int>(full2.length()) + 1);

    // normal case - from front
    String test1;
    String test2;
    ASSERT_EQ(OK, test1.init(full1.c_str()));
    ASSERT_EQ(OK, test2.init(full2.c_str()));
    EXPECT_EQ(OK, test1.insert_before(0, test2));
    compareStringsWithAlloc(full2 + full1, test1, alloc1);

    // normal case - from end
    String test3;
    String test4;
    ASSERT_EQ(OK, test3.init(full1.c_str()));
    ASSERT_EQ(OK, test4.init(full2.c_str()));
    EXPECT_EQ(OK, test3.insert_before(test3.size(), test4));
    compareStringsWithAlloc(full1 + full2, test3, alloc1);

    // normal case - from middle
    String test5;
    String test6;
    ASSERT_EQ(OK, test5.init("alpha"));
    ASSERT_EQ(OK, test6.init("beta"));
    const int alloc2 = 2 * (test5.size() + test6.size() + 1);
    EXPECT_EQ(OK, test5.insert_before(2, test6));
    compareStringsWithAlloc("albetapha", test5, alloc2);

    // index less than zero
    EXPECT_EQ(ERROR, test1.insert_before(-1, test2));

    // index greater than size
    EXPECT_EQ(ERROR, test1.insert_before(test1.size() + 1, test2));
}

///////////////////////////////////////////////////////////////////////////////
//
// swap()
//
///////////////////////////////////////////////////////////////////////////////
TEST_F(StringUnitTest, Swap) {
    // make two different Strings
    String a;
    String b;
    ASSERT_EQ(OK, a.init("alpha beta"));
    ASSERT_EQ(OK, b.init("charlie delta"));

    // store the values of the member variables
    const char* const a_cstr = a.c_str();
    const int a_size = a.size();
    const int a_alloc = a.get_allocation();

    const char* const b_cstr = b.c_str();
    const int b_size = b.size();
    const int b_alloc = b.get_allocation();

    // now swap the string contents
    a.swap(b);

    //
    // and verify that the contents were swapped
    // and no heap allocation / deallocation occurred
    //

    // string values
    EXPECT_STREQ(a_cstr, b.c_str());
    EXPECT_STREQ(b_cstr, a.c_str());

    // pointer values (no heap move)
    EXPECT_EQ(a_cstr, b.c_str());
    EXPECT_EQ(b_cstr, a.c_str());

    // size
    EXPECT_EQ(a_size, b.size());
    EXPECT_EQ(b_size, a.size());

    // allocation
    EXPECT_EQ(a_alloc, b.get_allocation());
    EXPECT_EQ(b_alloc, a.get_allocation());
}

