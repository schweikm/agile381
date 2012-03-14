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
    virtual void SetUp() {
    }

    // virtual void TearDown() will be called after each test is run.
    // You should define it if there is cleanup work to do.  Otherwise,
    // you don't have to provide it.
    virtual void TearDown() {
    }

    // Constructor Helper
    void ConstructorHelper(string in_string) {
        // capture the ouput to stdout
        ostringstream output;
        StreamSwapper swapper(cout, output);

        //: MAINTENANCE
        //    I'm not sure how to convert std::endl to a character,
        //    so I'll do this hack instead
        char newline = '\n';
        string result = "Ctor: \"" + in_string +  "\"" + newline;

        // create the String instance
        String test(in_string.c_str());

        // Google Test assertions
        ASSERT_STREQ(result.c_str(), output.str().c_str());
        ASSERT_EQ(in_string.length(), test.size());
        ASSERT_EQ(in_string.length() + 1, test.get_allocation());
    }

    // Declares the variables your tests want to use.
};


///////////////////////////////////////////////////////////////////////////////
//
// Constructor
//
//    DEPENDS ON:  c_str()
//                 size()
//                 get_allocation()
//
///////////////////////////////////////////////////////////////////////////////
TEST_F(StringMemberTest, Contructor) {
    // turn on diagnostic messages
    String::set_messages_wanted(true);


    // ************ //
    // Normal Cases //
    // ************ //


    // TEST 1
    ConstructorHelper("alpha");


    // TEST 2
    ConstructorHelper("Hello, world!");


    // TEST 3
    ConstructorHelper("The!quick@brown#fox$jumped^over&the*lazy.dog");


    // ************ //
    // Corner Cases //
    // ************ //


    // TEST 4
    ConstructorHelper("");
}

// copy constructor
TEST_F(StringMemberTest, CopyContructor) {
    ASSERT_EQ(1, 1); 
}

// assignment operator
TEST_F(StringMemberTest, AssignmentOperator) {
    ASSERT_EQ(1, 1); 
}

// destructor
TEST_F(StringMemberTest, Destructor) {
    ASSERT_EQ(1, 1); 
}

// c_str()
TEST_F(StringMemberTest, cStr) {
    ASSERT_EQ(1, 1); 
}

// size
TEST_F(StringMemberTest, size) {
    ASSERT_EQ(1, 1); 
}

// get_allocation
TEST_F(StringMemberTest, getAllocation) {
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

