#include <String.h>
#include <gtest/gtest.h>


// To use a test fixture, derive a class from testing::Test.
class StringTest : public testing::Test {
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

// constructor
TEST_F(StringTest, Contructor) {
    ASSERT_EQ(1, 1);
}

// copy constructor
TEST_F(StringTest, CopyContructor) {
    ASSERT_EQ(1, 1); 
}

// assignment operator
TEST_F(StringTest, AssignmentOperator) {
    ASSERT_EQ(1, 1); 
}

// destructor
TEST_F(StringTest, Destructor) {
    ASSERT_EQ(1, 1); 
}

// c_str()
TEST_F(StringTest, cStr) {
    ASSERT_EQ(1, 1); 
}

// size
TEST_F(StringTest, size) {
    ASSERT_EQ(1, 1); 
}

// get_allocation
TEST_F(StringTest, getAllocation) {
    ASSERT_EQ(1, 1); 
}

// operator[]
TEST_F(StringTest, OperatorAccessor) {
    ASSERT_EQ(1, 1); 
}

// substring
TEST_F(StringTest, substring) {
    ASSERT_EQ(1, 1); 
}

// clear
TEST_F(StringTest, clear) {
    ASSERT_EQ(1, 1); 
}

// remove
TEST_F(StringTest, remove) {
    ASSERT_EQ(1, 1); 
}

// insert_before
TEST_F(StringTest, insertBefore) {
    ASSERT_EQ(1, 1); 
}

// operator+=
TEST_F(StringTest, operatorConcatenation) {
    ASSERT_EQ(1, 1); 
}

// swap
TEST_F(StringTest, swap) {
    ASSERT_EQ(1, 1); 
}




// To use a test fixture, derive a class from testing::Test.
class StringNonMemberTest : public testing::Test {
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

// operator<<
TEST_F(StringNonMemberTest, operatorStreamInput) {
    ASSERT_EQ(1, 1); 
}

// operator<<
TEST_F(StringNonMemberTest, operatorStreamOutput) {
    ASSERT_EQ(1, 1); 
}

// getline
TEST_F(StringNonMemberTest, getline) {
    ASSERT_EQ(1, 1); 
}

