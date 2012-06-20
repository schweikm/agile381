/*
 * Copyright 2012 Marc Schweikert
 */

#include "manager/String.h"

#include <cstddef>
#include <cstdio>
#include <cstring>


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
    myInternalCStr = new char[myInternalCStrAllocation];
    strncpy(myInternalCStr, in_cstr,
              static_cast<size_t>(myInternalCStrAllocation));

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
    myInternalCStr = new char[myInternalCStrAllocation];
    strncpy(myInternalCStr, copy.c_str(),
              static_cast<size_t>(myInternalCStrAllocation));

    // update the static members
    ourNumber++;
    ourTotalAllocation += myInternalCStrAllocation;
}

const String& String::operator=(const String& other) {
}

const String& String::operator=(const char* const other) {
}

// destructor
String::~String() {
    // output message if wanted
    if (true == ourMessagesWanted) {
        printf("Dtor: \"%s\"\n", myInternalCStr);
    }

    // free the allocated memory
    delete [] myInternalCStr;

    // update the static members
    ourNumber--;
    ourTotalAllocation -= myInternalCStrAllocation;
}

const char& String::operator[] (const int i) {
}

const char& String::operator[] (const int i) const {
}

const String String::substring(const int i, const int len) const {
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

void String::swap(const String& other) { // NOLINT
}

bool operator== (const String& lhs, const String& rhs) {
}

bool operator!= (const String& lhs, const String& rhs) {
}

bool operator< (const String& lhs, const String& rhs) {
}

bool operator> (const String& lhs, const String& rhs) {
}

const String operator+ (const String& lhs, const String& rhs) {
}

const String getline(const int fd) {
}

