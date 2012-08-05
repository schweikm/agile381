/*
 * Copyright 2012 Marc Schweikert
 */

#include <cstddef>
#include <cstdio>
#include <string>
    using std::string;

#include "gtest/gtest.h"

#include "manager/String.h"



// class that captures stdout and stores it in a file
class StreamDup {
  public:
    StreamDup()
      :myNewFd(0) {
        // make the tmp file unique
        const int kBufSize = 50;
        char buffer[kBufSize];
        snprintf(buffer, kBufSize, "/tmp/gtest-%d.txt", getpid());
        myTmpFile = buffer;
    }

    void startCapture() {
        // save position of current standard output
        fgetpos(stdout, &stdoutPos);
        myNewFd = dup(fileno(stdout));
        freopen(myTmpFile.c_str(), "w", stdout);
    }

    void stopCapture() {
        // flush stdout so any buffered messages are delivered
        fflush(stdout);

        // close file and restore standard output to stdout
        dup2(myNewFd, fileno(stdout));
        close(myNewFd);
        clearerr(stdout);
        fsetpos(stdout, &stdoutPos);
    }

    const string getCapture() const {
        FILE* file = fopen(myTmpFile.c_str(), "r");
        if (0 == file) {
            return "";
        }

        // obtain file size:
        fseek(file, 0, SEEK_END);
        const int size = ftell(file);
        rewind(file);

        // return value
        string val;

        // allocate memory to contain the whole file
        char* buffer = new char[sizeof(buffer) * size];
        if (0 != buffer) {
            // copy the file into the buffer:
            const int result = fread(buffer, 1, size, file);
            if (result == size) {
                val = buffer;
            }
        }

        // clean up
        fclose(file);
        delete [] buffer;

        return val;
    }

  private:
    fpos_t stdoutPos;
    int    myNewFd;
    string myTmpFile;
};


// To use a test fixture, derive a class from testing::Test.
class StringMemberTest : public testing::Test {
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
    void ConstructorHelper(const string& in_string) {
        // capture the ouput to stdout
        StreamDup dup;

        // expected output
        const string result = "Ctor: \"" + in_string + "\"\n";

        // capture the statics before creating the String instance
        const int numStrings = String::get_number();
        const int totalAllocation = String::get_total_allocation();

        // create the String instance
        String::set_messages_wanted(true);
        dup.startCapture();
        const String testStr(in_string.c_str());
        dup.stopCapture();
        String::set_messages_wanted(false);

        // verify everything is correct
        verifyStrings(result.c_str()        , dup.getCapture().c_str(),
                      in_string.c_str()     , testStr.c_str(),
                      in_string.length()    , testStr.size(),
                      in_string.length() + 1, testStr.get_allocation(),
                      numStrings + 1        , totalAllocation +
                                                testStr.get_allocation());
    }

    // Copy Constructor Helper
    void CopyConstructorHelper(const string& in_string) {
        // capture the ouput to stdout
        StreamDup dup;

        // expected output
        const string result = "Copy ctor: \"" + in_string + "\"\n";

        // create the String to copy from
        String::set_messages_wanted(false);
        const String fromString(in_string.c_str());

        // capture the statics before creating the String instance
        const int numStrings = String::get_number();
        const int totalAllocation = String::get_total_allocation();

        // create the String instance
        String::set_messages_wanted(true);
        dup.startCapture();
        const String testStr(fromString);
        dup.stopCapture();
        String::set_messages_wanted(false);

        // verify everything is correct
        verifyStrings(result.c_str()        , dup.getCapture().c_str(),
                      in_string.c_str()     , testStr.c_str(),
                      in_string.length()    , testStr.size(),
                      in_string.length() + 1, testStr.get_allocation(),
                      numStrings + 1        , totalAllocation +
                                                testStr.get_allocation());
    }


    /////////////////////
    // UTILITY METHODS //
    /////////////////////


    // utility method to compare the String data
    void verifyStrings(const char* const expected_stdout_cstr,
                       const char* const actual_stdout_cstr,
                       const char* const expected_cstr,
                       const char* const actual_cstr,
                       const int expected_length,
                       const int actual_length,
                       const int expected_allocation,
                       const int actual_allocation,
                       const int expected_numStrings,
                       const int expected_totalAllocation) {
        // message to cout is correct
        EXPECT_STREQ(expected_stdout_cstr, actual_stdout_cstr);

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


    // Declares the variables your tests want to use.
};


///////////////////////////////////////////////////////////////////////////////
//
// Constructor
//
///////////////////////////////////////////////////////////////////////////////
TEST_F(StringMemberTest, Contructor) {
    // TEST 1
    //    Simple string - one word
    ConstructorHelper("alpha");

    // TEST 2
    //    Simple string - a little more complex with punctuation
    ConstructorHelper("Hello, world!");

    // TEST 3
    //    Simple string - lots of non-word characters
    ConstructorHelper("The!quick@brown#fox$jumped^over&the*lazy.dog");

    // TEST 4
    //    Corner case - Empty string
    ConstructorHelper("");
}

///////////////////////////////////////////////////////////////////////////////
//
// Copy Constructor
//
///////////////////////////////////////////////////////////////////////////////
TEST_F(StringMemberTest, CopyContructor) {
    // TEST 1
    //    Simple string - one word
    CopyConstructorHelper("alpha");

    // TEST 2
    //    Simple string - a little more complex with punctuation
    CopyConstructorHelper("Hello, world!");

    // TEST 3
    //    Simple string - lots of non-word characters
    CopyConstructorHelper("The!quick@brown#fox$jumped^over&the*lazy.dog");

    // TEST 4
    //    Corner case - Empty string
    CopyConstructorHelper("");
}

///////////////////////////////////////////////////////////////////////////////
//
// operator= (String)
//
///////////////////////////////////////////////////////////////////////////////
TEST_F(StringMemberTest, AssignmentOperatorString) {
    const string test = "operator= - from String";
    const string expectedStdout = "Assign from String:  \"" + test + "\"\n" +
                                  "Copy ctor: \"" + test + "\"\n" +
                                  "Dtor: \"\"\n";
    StreamDup dup;

    const String test1(test.c_str());
    String test2;

    // turn on diagnostic messages
    String::set_messages_wanted(true);

    dup.startCapture();
    test2 = test1;
    dup.stopCapture();

    // turn off diagnostic messages
    String::set_messages_wanted(false);

    // message to stdout is correct
    EXPECT_STREQ(expectedStdout.c_str(), dup.getCapture().c_str());

    // strings are equivalent
    compareStrings(test, test2);
}

///////////////////////////////////////////////////////////////////////////////
//
// operator= (char)
//
///////////////////////////////////////////////////////////////////////////////
TEST_F(StringMemberTest, AssignmentOperatorChar) {
    const char* const test = "operator= - from C-string";
    const string expectedStdout = "Assign from C-string:  \"" + string(test) +
                                    "\"\n" +
                                  "Ctor: \"" + string(test) + "\"\n" +
                                  "Dtor: \"\"\n";
    StreamDup dup;
    String test1;

    // turn on diagnostic messages
    String::set_messages_wanted(true);

    dup.startCapture();
    test1 = test;
    dup.stopCapture();

    // turn off diagnostic messages
    String::set_messages_wanted(false);

    // message to stdout is correct
    EXPECT_STREQ(expectedStdout.c_str(), dup.getCapture().c_str());

    // strings are equivalent
    compareStrings(string(test), test1);
}

///////////////////////////////////////////////////////////////////////////////
//
// Destructor
//
///////////////////////////////////////////////////////////////////////////////
TEST_F(StringMemberTest, Destructor) {
    // turn off diagnostic messages
    String::set_messages_wanted(false);

    // capture the statics before creating the String instance
    const int numStrings = String::get_number();
    const int totalAllocation = String::get_total_allocation();

    // capture the ouput to stdout
    StreamDup dup;
    const string test1Val = "alpha";

    {
        const String test1(test1Val.c_str());
        EXPECT_EQ(numStrings + 1, String::get_number());
        EXPECT_EQ(test1Val.length() + 1, totalAllocation +
                                           String::get_total_allocation());

        // turn on diagnostic messages
        String::set_messages_wanted(true);
        dup.startCapture();
    }  // test1 goes out of scope - destructor called

    dup.stopCapture();
    const string result = "Dtor: \"" + test1Val + "\"\n";

    // turn off diagnostic messages
    String::set_messages_wanted(false);

    // message to cout is correct
    EXPECT_STREQ(result.c_str(), dup.getCapture().c_str());

    // number of strings is decremented
    EXPECT_EQ(numStrings, String::get_number());

    // allocation is decreased
    EXPECT_EQ(totalAllocation, String::get_total_allocation());
}

///////////////////////////////////////////////////////////////////////////////
//
// operator[] and operator[] const
//
///////////////////////////////////////////////////////////////////////////////
TEST_F(StringMemberTest, OperatorAccessor) {
    const string a("all your base are belong to us");
    String b(a.c_str());
    const String c(a.c_str());

    // normal case
    for (size_t i = 0; i < a.length(); i++) {
        EXPECT_EQ(a[i], b[i]);
        EXPECT_EQ(a[i], c[i]);
    }

    // non-const less than zero
    try {
        b[-1];
        ASSERT_EQ(1, 0);
    } catch(const String_exception&) { }

    // const less than zero
    try {
        c[-1];
        ASSERT_EQ(1, 0);
    } catch(const String_exception&) { }

    // non-const greater than size
    try {
        b[a.length() + 1];
        ASSERT_EQ(1, 0);
    } catch(const String_exception&) { }

    // const greater than size
    try {
        c[a.length() + 1];
        ASSERT_EQ(1, 0);
    } catch(const String_exception&) { }
}

///////////////////////////////////////////////////////////////////////////////
//
// substring()
//
///////////////////////////////////////////////////////////////////////////////
TEST_F(StringMemberTest, substring) {
    const string fullString = "All your base are belong to us";
    const string subString = "your base are belong";
    const int subStringLen = 20;

    // normal case
    const String test(fullString.c_str());
    String test2 = test.substring(4, subStringLen);
    const String test3 = test.substring(4, subStringLen);
    compareStrings(subString, test2);
    compareStrings(subString, test3);

    // corner case, both zero
    String test4 = test.substring(0, 0);
    compareStrings("", test4);

    //
    // index
    //

    // non-const index less than zero
    try {
        test2.substring(-1, 1);
        ASSERT_EQ(1, 0);
    } catch(const String_exception&) { }

    // const index less than zero
    try {
        test3.substring(-1, 1);
        ASSERT_EQ(1, 0);
    } catch(const String_exception&) { }

    // non-const index greater than size
    try {
        test2.substring(test.size() + 1, 1);
        ASSERT_EQ(1, 0);
    } catch(const String_exception&) { }

    // const index greater than size
    try {
        test3.substring(test.size() + 1, 1);
        ASSERT_EQ(1, 0);
    } catch(const String_exception&) { }

    //
    // length
    //

    // non-const length less than zero
    try {
        test2.substring(0, -1);
        ASSERT_EQ(1, 0);
    } catch(const String_exception&) { }

    // const length less than zero
    try {
        test3.substring(0, -1);
        ASSERT_EQ(1, 0);
    } catch(const String_exception&) { }

    // non-const length greater than size
    try {
        test2.substring(0, test.size() + 1);
        ASSERT_EQ(1, 0);
    } catch(const String_exception&) { }

    // const length greater than size
    try {
        test3.substring(0, test.size() + 1);
        ASSERT_EQ(1, 0);
    } catch(const String_exception&) { }

    // non-const index + length greater than size
    try {
        test2.substring(subStringLen, test.size() + 1);
        ASSERT_EQ(1, 0);
    } catch(const String_exception&) { }

    // const length greater than size
    try {
        test3.substring(subStringLen, test.size() + 1);
        ASSERT_EQ(1, 0);
    } catch(const String_exception&) { }
}

///////////////////////////////////////////////////////////////////////////////
//
// clear()
//
///////////////////////////////////////////////////////////////////////////////
TEST_F(StringMemberTest, clear) {
    String test("trololololololo");
    test.clear();
    compareStrings("", test);
}

///////////////////////////////////////////////////////////////////////////////
//
// remove()
//
///////////////////////////////////////////////////////////////////////////////
TEST_F(StringMemberTest, remove) {
    // normal case
    const string fullString = "All your base are belong to us";
    const string subString = "All your belong to us";
    String test(fullString.c_str());
    test.remove(9, 9);
    compareStringsWithAlloc(subString, test, fullString.length() + 1);

    // normal case 2
    const string subString1 = "All your o us";
    String test1(fullString.c_str());
    test1.remove(9, 17);
    compareStringsWithAlloc(subString1, test1, fullString.length() + 1);

    // corner case, both zero
    String test2(fullString.c_str());
    test2.remove(0, 0);
    compareStringsWithAlloc(fullString, test2, fullString.length() + 1);

    //
    // index
    //

    // non-const index less than zero
    try {
        test2.remove(-1, 1);
        ASSERT_EQ(1, 0);
    } catch(const String_exception&) { }

    // non-const index greater than size
    try {
        test2.remove(test2.size() + 1, 1);
        ASSERT_EQ(1, 0);
    } catch(const String_exception&) { }

    //
    // length
    //

    // non-const length less than zero
    try {
        test2.remove(0, -1);
        ASSERT_EQ(1, 0);
    } catch(const String_exception&) { }

    // non-const length greater than size
    try {
        test2.remove(0, test2.size() + 1);
        ASSERT_EQ(1, 0);
    } catch(const String_exception&) { }

    // non-const index + length greater than size
    try {
        test2.remove(8, test2.size() + 1);
        ASSERT_EQ(1, 0);
    } catch(const String_exception&) { }
}

///////////////////////////////////////////////////////////////////////////////
//
// insert_before()
//
///////////////////////////////////////////////////////////////////////////////
TEST_F(StringMemberTest, insertBefore) {
    ASSERT_EQ(1, 1);
}

///////////////////////////////////////////////////////////////////////////////
//
// operator+= (char)
//
///////////////////////////////////////////////////////////////////////////////
TEST_F(StringMemberTest, operatorConcatenationChar) {
    ASSERT_EQ(1, 1);
}

///////////////////////////////////////////////////////////////////////////////
//
// operator+= (char const)
//
///////////////////////////////////////////////////////////////////////////////
TEST_F(StringMemberTest, operatorConcatenationCharConst) {
    ASSERT_EQ(1, 1);
}

///////////////////////////////////////////////////////////////////////////////
//
// operator+= (String)
//
///////////////////////////////////////////////////////////////////////////////
TEST_F(StringMemberTest, operatorConcatenationString) {
    ASSERT_EQ(1, 1);
}

///////////////////////////////////////////////////////////////////////////////
//
// swap()
//
///////////////////////////////////////////////////////////////////////////////
TEST_F(StringMemberTest, swap) {
    // turn off messages
    String::set_messages_wanted(false);

    // make two different Strings
    String a("alpha beta");
    String b("charlie delta");

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

