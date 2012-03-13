#include <String.h>
#include <gtest/gtest.h>

#include <cstddef>
#include <iostream>
#include <string>

using std::cout;
using std::streambuf;
using std::ostream;
using std::ostringstream;

using std::string;

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

    // Declares the variables your tests want to use.
};


// smart class that will swap streambufs and replace them 
// when object goes out of scope. 
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


// constructor
TEST_F(StringMemberTest, Contructor) {
    // turn on diagnostic messages
    String::set_messages_wanted(true);

    // capture stdout
    string testMessage;
    string result;
    size_t runningLength = 0;
    char newline = '\n';


    // ************ //
    // Normal Cases //
    // ************ //


    // TEST 1
    {
        ostringstream output; 
        StreamSwapper swapper(cout, output);
        testMessage = "alpha";
        result = "Ctor: \"" + testMessage +  "\"" + newline;
        runningLength = testMessage.length() + 1;

        String test1(testMessage.c_str());

        ASSERT_STREQ(result.c_str(), output.str().c_str());
        ASSERT_EQ(1, String::get_number());
        ASSERT_EQ(runningLength, String::get_total_allocation());
    }


    // TEST 2
    {
        ostringstream output; 
        StreamSwapper swapper(cout, output);
        testMessage = "Hello, world!";
        result = "Ctor: \"" + testMessage +  "\"" + newline;
        runningLength += testMessage.length() + 1;

        String test2(testMessage.c_str());

        ASSERT_STREQ(result.c_str(), output.str().c_str());
        ASSERT_EQ(2, String::get_number());
        ASSERT_EQ(runningLength, String::get_total_allocation());
    }


    // TEST 3
    {
        ostringstream output; 
        StreamSwapper swapper(cout, output);
        testMessage = "The!quick@brown#fox$jumped^over&the*lazy.dog";
        result = "Ctor: \"" + testMessage +  "\"" + newline;
        runningLength += testMessage.length() + 1;

        String test3(testMessage.c_str());

        ASSERT_STREQ(result.c_str(), output.str().c_str());
        ASSERT_EQ(3, String::get_number());
        ASSERT_EQ(runningLength, String::get_total_allocation());
    }


    // ************ //
    // Corner Cases //
    // ************ //


    // TEST 4
    {
        ostringstream output; 
        StreamSwapper swapper(cout, output);
        testMessage = "";
        result = "Ctor: \"" + testMessage +  "\"" + newline;
        runningLength += testMessage.length() + 1;

        String test4(testMessage.c_str());

        ASSERT_STREQ(result.c_str(), output.str().c_str());
        ASSERT_EQ(4, String::get_number());
        ASSERT_EQ(runningLength, String::get_total_allocation());
    }
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

