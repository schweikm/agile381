#include <String.h>
#include <gtest/gtest.h>

#include <cstddef>
#include <iostream>
#include <string>

using std::cout;
using std::ostream;
using std::ostringstream;
using std::streambuf;

using std::string;


// smart class that will swap streambufs and replace them
// when object goes out of scope.
//
// MAINTENANCE
//    This should be moved to a Google Test Utility file at some point
//
class StreamSwapper {
public:
    StreamSwapper(ostream& orig, ostream& replacement)
      : buf(orig.rdbuf()), str(orig) {
        orig.rdbuf(replacement.rdbuf());
    }

    ~StreamSwapper() {
        str.rdbuf(buf);
    }

private:
    streambuf* buf;
    ostream& str;
};


// To use a test fixture, derive a class from testing::Test.
class StringMemberTest : public testing::Test {
protected:
    // virtual void SetUp() will be called before each test is run.  You
    // should define it if you need to initialize the varaibles.
    // Otherwise, this can be skipped.
//    virtual void SetUp() { }

    // virtual void TearDown() will be called after each test is run.
    // You should define it if there is cleanup work to do.  Otherwise,
    // you don't have to provide it.
//    virtual void TearDown() { }

    // Constructor Helper
    void ConstructorHelper(string in_string) {
        // capture the ouput to stdout
        ostringstream output;
        StreamSwapper swapper(cout, output);

        // MAINTENANCE
        //    I'm not sure how to convert std::endl to a character,
        //    so I'll do this hack instead
        char newline = '\n';
        string result = "Ctor: \"" + in_string + "\"" + newline;

        // capture the statics before creating the String instance
        const int numStrings = String::get_number();
        const int totalAllocation = String::get_total_allocation();

        // create the String instance
        String::set_messages_wanted(true);
        String testStr(in_string.c_str());
        String::set_messages_wanted(false);

        // verify everything is correct
        verifyStrings(result.c_str()        , output.str().c_str(),
                      in_string.c_str()     , testStr.c_str(),
                      in_string.length()    , testStr.size(),
                      in_string.length() + 1, testStr.get_allocation(),
                      numStrings + 1        , totalAllocation +
                                                testStr.get_allocation());
    }

    // Copy Constructor Helper
    void CopyConstructorHelper(string in_string) {
        // capture the ouput to stdout
        ostringstream output;
        StreamSwapper swapper(cout, output);

        // MAINTENANCE
        //    I'm not sure how to convert std::endl to a character,
        //    so I'll do this hack instead
        char newline = '\n';
        string result = "Copy ctor: \"" + in_string + "\"" + newline;

        // create the String to copy from
        String::set_messages_wanted(false);
        String fromString(in_string.c_str());

        // capture the statics before creating the String instance
        const int numStrings = String::get_number();
        const int totalAllocation = String::get_total_allocation();

        // create the String instance
        String::set_messages_wanted(true);
        String testStr(fromString);
        String::set_messages_wanted(false);

        // verify everything is correct
        verifyStrings(result.c_str()        , output.str().c_str(),
                      in_string.c_str()     , testStr.c_str(),
                      in_string.length()    , testStr.size(),
                      in_string.length() + 1, testStr.get_allocation(),
                      numStrings + 1        , totalAllocation +
                                                testStr.get_allocation());
    }

    // utility method to compare the String data
    void verifyStrings(const char* expected_stdout_cstr,
                       const char* actual_stdout_cstr,
                       const char* expected_cstr,
                       const char* actual_cstr,
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


    // Declares the variables your tests want to use.
};


///////////////////////////////////////////////////////////////////////////////
//
// Constructor
//
//    DEPENDS ON:
//      - c_str()
//      - size()
//      - get_allocation()
//      - String::get_number()
//      - String::get_total_allocation()
//      - String::set_messages_wanted()
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
//    DEPENDS ON:
//      - String()
//      - c_str()
//      - size()
//      - get_allocation()
//      - String::get_number()
//      - String::get_total_allocation()
//      - String::set_messages_wanted()
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

// assignment operator
TEST_F(StringMemberTest, AssignmentOperator) {
    ASSERT_EQ(1, 1);
}

///////////////////////////////////////////////////////////////////////////////
//
// Destructor
//
//    DEPENDS ON:
//      - String()
//      - String::get_number()
//      - String::set_messages_wanted()
//      - String::get_total_allocation()
//
///////////////////////////////////////////////////////////////////////////////
TEST_F(StringMemberTest, Destructor) {
    // turn off diagnostic messages
    String::set_messages_wanted(false);
    {
        // capture the ouput to stdout
        ostringstream output;
        StreamSwapper swapper(cout, output);
        string test1Val = "alpha";

        {
            String test1(test1Val.c_str());
            EXPECT_EQ(1, String::get_number());
            EXPECT_EQ(test1Val.length() + 1, String::get_total_allocation());

            // turn on diagnostic messages
            String::set_messages_wanted(true);
        }  // test1 goes out of scope - destructor called

        // MAINTENANCE
        //    I'm not sure how to convert std::endl to a character,
        //    so I'll do this hack instead
        char newline = '\n';
        string result = "Dtor: \"" + test1Val + "\"" + newline;

        // message to cout is correct
        EXPECT_STREQ(result.c_str(), output.str().c_str());

        // number of strings is decremented
        EXPECT_EQ(0, String::get_number());

        // allocation is decreased
        EXPECT_EQ(0, String::get_total_allocation());
    }
}

// c_str()
TEST_F(StringMemberTest, cStr) {
    ASSERT_EQ(1, 1);
}

// size
TEST_F(StringMemberTest, size) {
    ASSERT_EQ(1, 1);
}

// operator[]
TEST_F(StringMemberTest, OperatorAccessor) {
    ASSERT_EQ(1, 1);
}

// substring
TEST_F(StringMemberTest, substring) {
    ASSERT_EQ(1, 1);
}

// clear
TEST_F(StringMemberTest, clear) {
    ASSERT_EQ(1, 1);
}

// remove
TEST_F(StringMemberTest, remove) {
    ASSERT_EQ(1, 1);
}

// insert_before
TEST_F(StringMemberTest, insertBefore) {
    ASSERT_EQ(1, 1);
}

// operator+=
TEST_F(StringMemberTest, operatorConcatenation) {
    ASSERT_EQ(1, 1);
}

// swap
TEST_F(StringMemberTest, swap) {
    ASSERT_EQ(1, 1);
}

