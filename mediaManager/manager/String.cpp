/*
 * Copyright 2012 Marc Schweikert
 */

#include "manager/String.h"

#include <algorithm>
#include <cstddef>
#include <cstdio>
#include <cstring>
#include <new>
  using std::bad_alloc;

#include "manager/Utility.h"


// initialize static members
int  String::ourNumber          = 0;
int  String::ourTotalAllocation = 0;
bool String::ourMessagesWanted  = false;

// constructor
String::String(const char* const in_cstr)
          : myInternalCStr(0),
            myInternalCStrSize(0),
            myInternalCStrAllocation(0) {
    // output message if wanted
    if (true == ourMessagesWanted) {
        printf("Ctor: \"%s\"\n", in_cstr);
    }

    // create the internal buffer and copy the data
    myInternalCStrSize = static_cast<int>(strlen(in_cstr));
    resizeCStrBuffer(myInternalCStrSize + 1);
    strncpy(myInternalCStr, in_cstr,
            static_cast<size_t>(myInternalCStrAllocation));

    // update the static members
    ourNumber++;
    ourTotalAllocation += myInternalCStrAllocation;
}

// copy constructor
String::String(const String& copy)
          : myInternalCStr(0),
            myInternalCStrSize(0),
            myInternalCStrAllocation(0) {
    // output message if wanted
    if (true == ourMessagesWanted) {
        printf("Copy ctor: \"%s\"\n", copy.c_str());
    }

    // deep copy the internal C string
    resizeCStrBuffer(copy.myInternalCStrAllocation);
    myInternalCStrSize = copy.myInternalCStrSize;
    strncpy(myInternalCStr, copy.c_str(),
            static_cast<size_t>(myInternalCStrAllocation));

    // update the static members
    ourNumber++;
    ourTotalAllocation += myInternalCStrAllocation;
}

String& String::operator=(const String& other) {
    if (true == ourMessagesWanted) {
        printf("Assign from String:  \"%s\"\n", other.c_str());
    }

    String temp(other);  // Copy-constructor -- RAII
    temp.swap(*this);    // Non-throwing swap
    return *this;
}

String& String::operator=(const char* const other) {
    if (true == ourMessagesWanted) {
        printf("Assign from C-string:  \"%s\"\n", other);
    }

    String temp(other);  // Copy-constructor -- RAII
    temp.swap(*this);    // Non-throwing swap
    return *this;
}

// destructor
String::~String() {
    // output message if wanted
    if (true == ourMessagesWanted) {
        printf("Dtor: \"%s\"\n", myInternalCStr);
    }

    // free the allocated memory
    delete [] myInternalCStr;
    myInternalCStr = 0;

    // update the static members
    ourNumber--;
    ourTotalAllocation -= myInternalCStrAllocation;
}

String String::substring(const int i, const int len) const {
    if ((i < 0) || (len < 0) || (i > myInternalCStrSize) ||
       ((i + len) > myInternalCStrSize)) {
        const String_exception ex("Substring bounds invalid");
        printError(__FILE__, __LINE__, ex);
        throw ex;
    }

    // create a buffer and copy the chars
    const size_t buffSize = static_cast<size_t>(len) + 1;
    char* const buffer = new char[buffSize];
    strncpy(buffer, myInternalCStr + i, static_cast<size_t>(len));
    buffer[len] = '\0';

    // create a new String and delete the buffer
    String temp(buffer);
    delete [] buffer;

    return temp;
}

void String::clear() {
    String temp("");
    swap(temp);
}

void String::remove(const int i, const int len) {
    if ((i < 0) || (len < 0) || (i > myInternalCStrSize) ||
       ((i + len) > myInternalCStrSize)) {
        const String_exception ex("Remove bounds invalid");
        printError(__FILE__, __LINE__, ex);
        throw ex;
    }

    // move the characters down starting at i len times
    for (int index = 0; index < myInternalCStrSize - len - i; index++) {
        myInternalCStr[index + i] = myInternalCStr[index + i + len];
    }

    // update the size and restore the NULL character
    myInternalCStrSize -= len;
    myInternalCStr[myInternalCStrSize] = '\0';
}

void String::insert_before(const int i, const String& src) {
    if ((i < 0) || (i > myInternalCStrSize)) {
        const String_exception ex("Insertion point out of range");
        printError(__FILE__, __LINE__, ex);
        throw ex;
    }
    // create a new buffer if needed
    const int alloc = myInternalCStrSize + src.size() + 1;
    if (alloc >= myInternalCStrAllocation) {
        resizeCStrBuffer(2 * alloc);
    }

    // make space for the new chars
    for (int index = 0; index < myInternalCStrSize - i; index++) {
        myInternalCStr[index + i + src.myInternalCStrSize] =
          myInternalCStr[index + i];
    }

    // then copy the src characters
    strncpy(myInternalCStr + (sizeof(char) * i), src.myInternalCStr,  // NOLINT
              src.myInternalCStrSize);

    // then change the instance variables
    myInternalCStrSize += src.myInternalCStrSize;
    myInternalCStr[myInternalCStrSize] = '\0';
}

const String& String::operator += (const char rhs) {
    char str[2];
    str[0] = rhs;
    str[1] = '\0';
    this->operator+=(str);
}

const String& String::operator += (const char* const rhs) {
    // resize the buffer if needed
    const int alloc = myInternalCStrSize + strlen(rhs) + 1;
    if (alloc >= myInternalCStrAllocation) {
        resizeCStrBuffer(2 * alloc);
    }

    // then add the chars to the end
    strncpy(myInternalCStr + (sizeof(char) * myInternalCStrSize), rhs,  // NOLINT
              strlen(rhs));
    myInternalCStrSize += strlen(rhs);
}

const String& String::operator += (const String& rhs) {
    this->operator+=(rhs.c_str());
}

void String::swap(String& other) { // NOLINT
    std::swap(myInternalCStr,           other.myInternalCStr);
    std::swap(myInternalCStrSize,       other.myInternalCStrSize);
    std::swap(myInternalCStrAllocation, other.myInternalCStrAllocation);
}

void String::resizeCStrBuffer(const int alloc) {
    // redundant - but faster than reallocating a buffer
    if (alloc == myInternalCStrAllocation) {
        return;
    }

    try {
        myInternalCStrAllocation = alloc;
        char* buffer = new char[myInternalCStrAllocation];

        // copy the chars over
        if (0 != myInternalCStr) {
            strncpy(buffer, myInternalCStr,
                    static_cast<size_t>(myInternalCStrAllocation));
            delete [] myInternalCStr;
        }

        myInternalCStr = buffer;
    }
    catch(const bad_alloc& ex) {
        printError(__FILE__, __LINE__,
                   "Caught exception while resizing internal c string!", ex);
        throw bad_alloc(ex);
    }
}

bool operator== (const String& lhs, const String& rhs) {
}

bool operator!= (const String& lhs, const String& rhs) {
}

bool operator< (const String& lhs, const String& rhs) {
}

bool operator> (const String& lhs, const String& rhs) {
}

String operator+ (const String& lhs, const String& rhs) {
}

String getline(const int fd) {
}

