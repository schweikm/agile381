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
          : myCStrSize(0),
            myCStrAllocation(0) {
    VLOG(1) << "Method Entry:  String::String";
    VLOG(1) << "Method Exit :  String::String";
}

// init
String::Status String::init(const char* const in_cstr) {
    VLOG(1) << "Method Entry:  String::init";
    VLOG(2) << "Called with arguments\tin_cstr = ->" << in_cstr << "<-";

    // create the internal buffer
    myCStrSize = static_cast<int>(strlen(in_cstr));

    if (OK != resizeCStrBuffer(myCStrSize + 1)) {
        LOG(FATAL) << "Call to String::resizeCStrBuffer failed!";
        return ERROR;
    }

    // copy the data
    strncpy(myCStr.get(), in_cstr,
            static_cast<size_t>(myCStrAllocation));

    // update the static members
    ourNumber++;
    ourTotalAllocation += myCStrAllocation;

    VLOG(1) << "Method Exit :  String::init";
    return OK;
}

// destructor
String::~String() {
    VLOG(1) << "Method Entry:  String::~String";

    // update the static members
    ourNumber--;
    ourTotalAllocation -= myCStrAllocation;

    VLOG(1) << "Method Exit :  String::~String";
}

// get
String::Status String::get(const int i,
                           char* val) const {
    VLOG(1) << "Method Entry:  String::get";
    VLOG(2) << "Called with arguments\ti = ->" << i << "<-";

    if ((i < 0) || (i >= myCStrSize)) {
        LOG(ERROR) << "Subscript out of range";
        return ERROR;
    }

    *val = myCStr[i];
    VLOG(1) << "Method Exit :  String::get";
    return OK;
}

// substring
String::Status String::substring(const int i,
                                 const int len,
                                 String* str) const {
    VLOG(1) << "Method Entry:  String::substring";
    VLOG(2) << "Called with arguments\ti = ->" << i
            << "<-\tlen = ->" << len << "<-";

    if ((i < 0) || (len < 0) || (i > myCStrSize) ||
       ((i + len) > myCStrSize)) {
        LOG(ERROR) << "Substring bounds invalid";
        return ERROR;
    }

    // copy the values to the new String object
    str->clear();
    str->resizeCStrBuffer(len + 1);

    str->myCStrSize = len;
    strncpy(str->myCStr.get(),
            myCStr.get() + i,
            static_cast<size_t>(len));
    str->myCStr[len] = '\0';

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
String::Status String::remove(const int i,
                              const int len) {
    VLOG(1) << "Method Entry:  String::remove";
    VLOG(2) << "Called with arguments\ti = ->" << i
            << "<-\tlen = ->" << len << "<-";

    if ((i < 0) || (len < 0) || (i > myCStrSize) ||
       ((i + len) > myCStrSize)) {
        LOG(ERROR) << "Remove bounds invalid";
        return ERROR;
    }

    // move the characters down starting at i len times
    for (int index = 0; index < myCStrSize - len - i; index++) {
        myCStr[index + i] = myCStr[index + i + len];
    }

    // update the size and restore the NULL character
    myCStrSize -= len;
    myCStr[myCStrSize] = '\0';

    VLOG(1) << "Method Exit :  String::remove";
    return OK;
}

// insert_before
String::Status String::insert_before(const int i,
                                     const String& src) {
    VLOG(1) << "Method Entry:  String::insert_before";
    VLOG(2) << "Called with arguments\ti = ->" << i
            << "<-\tsrc = ->" << src.c_str() << "<-";

    if ((i < 0) || (i > myCStrSize)) {
        LOG(ERROR) << "Insertion point out of range";
        return ERROR;
    }

    // create a new buffer if needed
    const int alloc = myCStrSize + src.size() + 1;
    if (alloc >= myCStrAllocation) {
        resizeCStrBuffer(2 * alloc);
    }

    // make space for the new chars
    for (int index = 0; index < myCStrSize - i; index++) {
        myCStr[index + i + src.myCStrSize] =
          myCStr[index + i];
    }

    // need a little magic to suppress a compiler warning
    const size_t sizetI = static_cast<size_t>(i);

    // then copy the src characters
    strncpy(myCStr.get() + (sizeof(char) * sizetI),  // NOLINT
            src.myCStr.get(),
            static_cast<size_t>(src.myCStrSize));

    // then change the instance variables
    myCStrSize += src.myCStrSize;
    myCStr[myCStrSize] = '\0';

    VLOG(1) << "Method Exit :  String::insert_before";
    return OK;
}

// swap
void String::swap(String& other) {
    VLOG(1) << "Method Entry:  String::swap";
    VLOG(2) << "Called with arguments\tother = ->" << other.c_str() << "<-";

    std::swap(myCStr,           other.myCStr);
    std::swap(myCStrSize,       other.myCStrSize);
    std::swap(myCStrAllocation, other.myCStrAllocation);

    VLOG(1) << "Method Exit :  String::swap";
}

// resizeCStrBuffer
String::Status String::resizeCStrBuffer(const int alloc) {
    VLOG(1) << "Method Entry:  String::resizeCStrBuffer";
    VLOG(2) << "Called with arguments\talloc = ->" << alloc << "<-";

    if (alloc < myCStrAllocation) {
        LOG(ERROR) << "Requested allocation ->" << alloc << "<- is less than"
                   << " current allocation ->" << myCStrAllocation
                   << "<-";
        return ERROR;
    }

    if (alloc == myCStrAllocation) {
        LOG(WARNING) << "Requested allocation is same as current.  "
                     << "Performing no work";
        return OK;
    }

    // we have to break convention in order to use Boost and no exceptions
    myCStrAllocation = alloc;
    char* const buffer = new(nothrow) char[myCStrAllocation];

    // if new fails then we fail
    if (0 == buffer) {
        LOG(FATAL) << "String::resizeCStrBuffer - call to new[] failed!";
        return ERROR;  // unreachable
    }

    shared_array<char> temp(buffer);

    // copy the chars over
    if (0 != myCStr) {
        strncpy(temp.get(), myCStr.get(),
                static_cast<size_t>(myCStrAllocation));
    }

    myCStr = temp;
    VLOG(1) << "Method Exit :  String::resizeCStrBuffer";
    return OK;
}

