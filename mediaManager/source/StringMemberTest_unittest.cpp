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
//: MAINTENANCE
//    This should be moved to a Google Test Utility file at some point
//
class StreamSwapper { 
public: 
    StreamSwapper(ostream& orig, ostream& replacement) 
      : buf_(orig.rdbuf()), str_(orig) {
        orig.rdbuf(replacement.rdbuf());
    } 
    
    ~StreamSwapper() {
        str_.rdbuf(buf_);
    } 

private: 
    streambuf* buf_; 
    ostream& str_; 
};


// To use a test fixture, derive a class from testing::Test.
class StringMemberTest : public testing::Test {
protected:

    // virtual void SetUp() will be called before each test is run.  You
    // should define it if you need to initialize the varaibles.
    // Otherwise, this can be skipped.
    virtual void SetUp() { }

    // virtual void TearDown() will be called after each test is run.
    // You should define it if there is cleanup work to do.  Otherwise,
    // you don't have to provide it.
    virtual void TearDown() { }

    // Constructor Helper
    void ConstructorHelper(string in_string) {
        // capture the ouput to stdout
        ostringstream output;
        StreamSwapper swapper(cout, output);

        //: MAINTENANCE
        //    I'm not sure how to convert std::endl to a character,
        //    so I'll do this hack instead
        char newline = '\n';
        string result = "Ctor: \"" + in_string + "\"" + newline;

        // turn on diagnostic messages
        String::set_messages_wanted(true);

        // create the String instance
        String testStr(in_string.c_str());

        // message to cout is correct
        ASSERT_STREQ(result.c_str(), output.str().c_str());

        // String value is correct
        ASSERT_STREQ(in_string.c_str(), testStr.c_str());

        // the length is correct
        ASSERT_EQ(in_string.length(), testStr.size());

        // the allocation is correct
        ASSERT_EQ(in_string.length() + 1, testStr.get_allocation());

        // turn off diagnostic messages
        String::set_messages_wanted(false);
    }

    // Copy Constructor Helper
    void CopyConstructorHelper(string in_string) {
        // capture the ouput to stdout
        ostringstream output;
        StreamSwapper swapper(cout, output);

        //: MAINTENANCE
        //    I'm not sure how to convert std::endl to a character,
        //    so I'll do this hack instead
        char newline = '\n';
        string result = "Copy ctor: \"" + in_string + "\"" + newline;

        // create the String to copy from
        String::set_messages_wanted(false);
        String fromString(in_string.c_str());
        
        // turn on diagnostic messages
        String::set_messages_wanted(true);

        // create the String instance
        String testStr(fromString);

        // message to cout is correct
        ASSERT_STREQ(result.c_str(), output.str().c_str());

        // String value is correct
        ASSERT_STREQ(in_string.c_str(), testStr.c_str());

        // the length is correct
        ASSERT_EQ(in_string.length(), testStr.size());

        // the allocation is correct
        ASSERT_EQ(in_string.length() + 1, testStr.get_allocation());

        // turn off diagnostic messages
        String::set_messages_wanted(false);
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

// copy constructor
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
            ASSERT_EQ(1, String::get_number());
            ASSERT_EQ(test1Val.length() + 1, String::get_total_allocation());

            // turn on diagnostic messages
            String::set_messages_wanted(true);
        } // test1 goes out of scope - destructor called

        //: MAINTENANCE
        //    I'm not sure how to convert std::endl to a character,
        //    so I'll do this hack instead
        char newline = '\n';
        string result = "Dtor: \"" + test1Val + "\"" + newline;

        // message to cout is correct
        ASSERT_STREQ(result.c_str(), output.str().c_str());

        // number of strings is decremented
        ASSERT_EQ(0, String::get_number());

        // allocation is decreased
        ASSERT_EQ(0, String::get_total_allocation());
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

