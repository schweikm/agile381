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


// initialize static members
int  String::ourNumber          = 0;
int  String::ourTotalAllocation = 0;
bool String::ourMessagesWanted  = false;

// constructor
String::String(const char* const in_cstr) {
    // output message if wanted
    if (true == ourMessagesWanted) {
        printf("Ctor: \"%s\"\n", in_cstr);
    }

    // calculate the sizes
    const int strSize = static_cast<int>(strlen(in_cstr));
    myInternalCStrSize = strSize;
    myInternalCStrAllocation = strSize + 1;

    // create the internal buffer and copy the data
    try {
        myInternalCStr = new char[myInternalCStrAllocation];
        strncpy(myInternalCStr, in_cstr,
                  static_cast<size_t>(myInternalCStrAllocation));
    }
    catch(const bad_alloc& ex) {
        fprintf(stderr, "Caught exception while allocating String!\n");
        fprintf(stderr, "%s\n", ex.what());
        throw bad_alloc(ex);
    }

    // update the static members
    ourNumber++;
    ourTotalAllocation += myInternalCStrAllocation;
}

// copy constructor
String::String(const String& copy) {
    // output message if wanted
    if (true == ourMessagesWanted) {
        printf("Copy ctor: \"%s\"\n", copy.c_str());
    }

    // copy the primitives
    myInternalCStrSize = copy.size();
    myInternalCStrAllocation = copy.get_allocation();

    // deep copy the internal C string
    try {
        myInternalCStr = new char[myInternalCStrAllocation];
        strncpy(myInternalCStr, copy.c_str(),
                  static_cast<size_t>(myInternalCStrAllocation));
    }
    catch(const bad_alloc& ex) {
        fprintf(stderr, "Caught exception while allocating String!\n");
        fprintf(stderr, "%s\n", ex.what());
        throw bad_alloc(ex);
    }

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
}

void String::clear() {
}

void String::remove(const int i, const int len) {
}

void String::insert_before(const int i, const String& src) {
}

const String& String::operator += (const char rhs) {
}

const String& String::operator += (const char* const rhs) {
}

const String& String::operator += (const String& rhs) {
}

void String::swap(String& other) { // NOLINT
    std::swap(myInternalCStr,           other.myInternalCStr);
    std::swap(myInternalCStrSize,       other.myInternalCStrSize);
    std::swap(myInternalCStrAllocation, other.myInternalCStrAllocation);
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

