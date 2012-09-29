/*
 * Copyright 2012 Marc Schweikert
 */


#include "manager/String.h"

#include <algorithm>
#include <cstddef>
#include <cstdio>
#include <cstring>
#include <new>
  using std::nothrow;

#include "boost/shared_array.hpp"
  using boost::shared_array;

#include "glog/logging.h"

#include "manager/Utility.h"


// initialize static members
int  String::ourNumber          = 0;
int  String::ourTotalAllocation = 0;


// constructor
String::String()
          : myInternalCStr(0),
            myInternalCStrSize(0),
            myInternalCStrAllocation(0) {
    VLOG(1) << "Method Entry:  String::String";
    VLOG(1) << "Method Exit :  String::String";
}

// init
StringStatus String::init(const char* const in_cstr) {
    VLOG(1) << "Method Entry:  String::init";
    VLOG(2) << "Called with arguments\tin_cstr = ->" << in_cstr << "<-";

    // create the internal buffer
    myInternalCStrSize = static_cast<int>(strlen(in_cstr));

    if (OK != resizeCStrBuffer(myInternalCStrSize + 1)) {
        LOG(FATAL) << "Call to String::resizeCStrBuffer failed!";
        return ERROR;
    }

    // copy the data
    strncpy(myInternalCStr.get(), in_cstr,
            static_cast<size_t>(myInternalCStrAllocation));

    // update the static members
    ourNumber++;
    ourTotalAllocation += myInternalCStrAllocation;

    VLOG(1) << "Method Exit :  String::init";
    return OK;
}

// destructor
String::~String() {
    VLOG(1) << "Method Entry:  String::~String";

    // update the static members
    ourNumber--;
    ourTotalAllocation -= myInternalCStrAllocation;

    VLOG(1) << "Method Exit :  String::~String";
}

// get
StringStatus String::get(const int i, char* val) const {
    VLOG(1) << "Method Entry:  String::get";
    VLOG(2) << "Called with arguments\ti = ->" << i << "<-";

    if ((i < 0) || (i >= myInternalCStrSize)) {
        LOG(ERROR) << "Subscript out of range";
        return ERROR;
    }

    *val = myInternalCStr[i];
    VLOG(1) << "Method Exit :  String::get";
    return OK;
}

// substring
StringStatus String::substring(const int i, const int len, String* str) const {
    VLOG(1) << "Method Entry:  String::substring";
    VLOG(2) << "Called with arguments\ti = ->" << i
            << "<-\tlen = ->" << len << "<-";

    if ((i < 0) || (len < 0) || (i > myInternalCStrSize) ||
       ((i + len) > myInternalCStrSize)) {
        LOG(ERROR) << "Substring bounds invalid";
        return ERROR;
    }

    // copy the values to the new String object
    str->clear();
    str->resizeCStrBuffer(len + 1);

    str->myInternalCStrSize = len;
    strncpy(str->myInternalCStr.get(),
            myInternalCStr.get() + i,
            static_cast<size_t>(len));
    str->myInternalCStr[len] = '\0';

    VLOG(1) << "Method Exit :  String::substring";
    return OK;
}

// clear
void String::clear() {
    VLOG(1) << "Method Entry:  String::clear";

    String temp;
    temp.init("");
    swap(temp);

    VLOG(1) << "Method Exit :  String::clear";
}

// remove
StringStatus String::remove(const int i, const int len) {
    VLOG(1) << "Method Entry:  String::remove";
    VLOG(2) << "Called with arguments\ti = ->" << i
            << "<-\tlen = ->" << len << "<-";

    if ((i < 0) || (len < 0) || (i > myInternalCStrSize) ||
       ((i + len) > myInternalCStrSize)) {
        LOG(ERROR) << "Remove bounds invalid";
        return ERROR;
    }

    // move the characters down starting at i len times
    for (int index = 0; index < myInternalCStrSize - len - i; index++) {
        myInternalCStr[index + i] = myInternalCStr[index + i + len];
    }

    // update the size and restore the NULL character
    myInternalCStrSize -= len;
    myInternalCStr[myInternalCStrSize] = '\0';

    VLOG(1) << "Method Exit :  String::remove";
    return OK;
}

// insert_before
StringStatus String::insert_before(const int i, const String& src) {
    VLOG(1) << "Method Entry:  String::insert_before";
    VLOG(2) << "Called with arguments\ti = ->" << i
            << "<-\tsrc = ->" << src.c_str() << "<-";

    if ((i < 0) || (i > myInternalCStrSize)) {
        LOG(ERROR) << "Insertion point out of range";
        return ERROR;
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

    // need a little magic to suppress a compiler warning
    const size_t sizetI = static_cast<size_t>(i);

    // then copy the src characters
    strncpy(myInternalCStr.get() + (sizeof(char) * sizetI),  // NOLINT
            src.myInternalCStr.get(),
            static_cast<size_t>(src.myInternalCStrSize));

    // then change the instance variables
    myInternalCStrSize += src.myInternalCStrSize;
    myInternalCStr[myInternalCStrSize] = '\0';

    VLOG(1) << "Method Exit :  String::insert_before";
    return OK;
}

// swap
void String::swap(String& other) {
    VLOG(1) << "Method Entry:  String::swap";
    VLOG(2) << "Called with arguments\tother = ->" << other.c_str() << "<-";

    std::swap(myInternalCStr,           other.myInternalCStr);
    std::swap(myInternalCStrSize,       other.myInternalCStrSize);
    std::swap(myInternalCStrAllocation, other.myInternalCStrAllocation);

    VLOG(1) << "Method Exit :  String::swap";
}

// resizeCStrBuffer
StringStatus String::resizeCStrBuffer(const int alloc) {
    VLOG(1) << "Method Entry:  String::resizeCStrBuffer";
    VLOG(2) << "Called with arguments\talloc = ->" << alloc << "<-";

    // no need for extra work
    if (alloc == myInternalCStrAllocation) {
        return OK;
    }

    // we have to break convention in order to use Boost and no exceptions
    myInternalCStrAllocation = alloc;
    char* const buffer = new(nothrow) char[myInternalCStrAllocation];

    // if new fails then we fail
    if (0 == buffer) {
        LOG(FATAL) << "String::resizeCStrBuffer - call to new[] failed!";
        return ERROR;  // unreachable
    }

    shared_array<char> temp(buffer);

    // copy the chars over
    if (0 != myInternalCStr) {
        strncpy(temp.get(), myInternalCStr.get(),
                static_cast<size_t>(myInternalCStrAllocation));
    }

    myInternalCStr = temp;
    VLOG(1) << "Method Exit :  String::resizeCStrBuffer";
    return OK;
}

