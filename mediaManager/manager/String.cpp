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

#include "boost/shared_array.hpp"
  using boost::shared_array;

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
    VLOG(1) << "Method Entry:  String::String";
    VLOG(2) << "Called with arguments\tin_cstr = ->" << in_cstr << "<-";

    // output message if wanted
    if (true == ourMessagesWanted) {
        printf("Ctor: \"%s\"\n", in_cstr);
    }

    // create the internal buffer and copy the data
    myInternalCStrSize = static_cast<int>(strlen(in_cstr));
    resizeCStrBuffer(myInternalCStrSize + 1);
    strncpy(myInternalCStr.get(), in_cstr,
            static_cast<size_t>(myInternalCStrAllocation));

    // update the static members
    ourNumber++;
    ourTotalAllocation += myInternalCStrAllocation;

    VLOG(1) << "Method Exit :  String::String";
}

// copy constructor
String::String(const String& copy)
          : myInternalCStr(0),
            myInternalCStrSize(0),
            myInternalCStrAllocation(0) {
    VLOG(1) << "Method Entry:  String::String(const String&)";
    VLOG(2) << "Called with arguments\tcopy = ->" << copy.c_str() << "<-";

    // output message if wanted
    if (true == ourMessagesWanted) {
        printf("Copy ctor: \"%s\"\n", copy.c_str());
    }

    // deep copy the internal C string
    resizeCStrBuffer(copy.myInternalCStrAllocation);
    myInternalCStrSize = copy.myInternalCStrSize;
    strncpy(myInternalCStr.get(), copy.c_str(),
            static_cast<size_t>(myInternalCStrAllocation));

    // update the static members
    ourNumber++;
    ourTotalAllocation += myInternalCStrAllocation;

    VLOG(1) << "Method Exit :  String::String(const String&)";
}

String& String::operator=(const String& other) {
    VLOG(1) << "Method Entry:  String::operator=(const String&)";
    VLOG(2) << "Called with arguments\tother = ->" << other.c_str() << "<-";

    if (true == ourMessagesWanted) {
        printf("Assign from String:  \"%s\"\n", other.c_str());
    }

    String temp(other);  // Copy-constructor -- RAII
    temp.swap(*this);    // Non-throwing swap

    VLOG(1) << "Method Exit :  String::operator=(const String&)";
    return *this;
}

String& String::operator=(const char* const other) {
    VLOG(1) << "Method Entry:  String::operator=(const char* const)";
    VLOG(2) << "Called with arguments\tother = ->" << other << "<-";

    if (true == ourMessagesWanted) {
        printf("Assign from C-string:  \"%s\"\n", other);
    }

    String temp(other);  // Copy-constructor -- RAII
    temp.swap(*this);    // Non-throwing swap

    VLOG(1) << "Method Exit :  String::operator=(const char* const)";
    return *this;
}

// destructor
String::~String() {
    VLOG(1) << "Method Entry:  String::~String";

    // output message if wanted
    if (true == ourMessagesWanted) {
        printf("Dtor: \"%s\"\n", myInternalCStr.get());
    }

    // no need to delete the array - hooray Boost!

    // update the static members
    ourNumber--;
    ourTotalAllocation -= myInternalCStrAllocation;

    VLOG(1) << "Method Exit :  String::~String";
}

String String::substring(const int i, const int len) const {
    VLOG(1) << "Method Entry:  String::substring";
    VLOG(2) << "Called with arguments\ti = ->" << i
            << "<-\tlen = ->" << len << "<-";

    if ((i < 0) || (len < 0) || (i > myInternalCStrSize) ||
       ((i + len) > myInternalCStrSize)) {
        const String_exception ex("Substring bounds invalid");
        LOG(ERROR) << ex.msg;
        throw ex;
    }

    // create a buffer and copy the chars
    const size_t buffSize = static_cast<size_t>(len) + 1;
    char* const buffer = new char[buffSize];
    strncpy(buffer, myInternalCStr.get() + i, static_cast<size_t>(len));
    buffer[len] = '\0';

    // create a new String and delete the buffer
    String temp(buffer);
    delete [] buffer;

    VLOG(1) << "Method Exit :  String::substring";
    return temp;
}

void String::clear() {
    VLOG(1) << "Method Entry:  String::clear";

    String temp("");
    swap(temp);

    VLOG(1) << "Method Exit :  String::clear";
}

void String::remove(const int i, const int len) {
    VLOG(1) << "Method Entry:  String::remove";
    VLOG(2) << "Called with arguments\ti = ->" << i
            << "<-\tlen = ->" << len << "<-";

    if ((i < 0) || (len < 0) || (i > myInternalCStrSize) ||
       ((i + len) > myInternalCStrSize)) {
        const String_exception ex("Remove bounds invalid");
        LOG(ERROR) << ex.msg;
        throw ex;
    }

    // move the characters down starting at i len times
    for (int index = 0; index < myInternalCStrSize - len - i; index++) {
        myInternalCStr[index + i] = myInternalCStr[index + i + len];
    }

    // update the size and restore the NULL character
    myInternalCStrSize -= len;
    myInternalCStr[myInternalCStrSize] = '\0';

    VLOG(1) << "Method Exit :  String::remove";
}

void String::insert_before(const int i, const String& src) {
    VLOG(1) << "Method Entry:  String::insert_before";
    VLOG(2) << "Called with arguments\ti = ->" << i
            << "<-\tsrc = ->" << src.c_str() << "<-";

    if ((i < 0) || (i > myInternalCStrSize)) {
        const String_exception ex("Insertion point out of range");
        LOG(ERROR) << ex.msg;
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
}

const String& String::operator+= (const char rhs) {
    VLOG(1) << "Method Entry:  String::operator+=(const char)";
    VLOG(2) << "Called with arguments\trhs = ->" << rhs << "<-";

    char str[2];
    str[0] = rhs;
    str[1] = '\0';

    VLOG(1) << "Method Exit :  String::operator+=(const char)";
    return this->operator+=(str);
}

const String& String::operator+= (const char* const rhs) {
    VLOG(1) << "Method Entry:  String::operator+=(const char* const)";
    VLOG(2) << "Called with arguments\trhs = ->" << rhs << "<-";

    // resize the buffer if needed
    const int alloc = myInternalCStrSize + static_cast<int>(strlen(rhs)) + 1;
    if (alloc >= myInternalCStrAllocation) {
        resizeCStrBuffer(2 * alloc);
    }

    // need a little magic to suppress a compiler warning
    const size_t cStrSizet = static_cast<size_t>(myInternalCStrSize);

    // then add the chars to the end
    strncpy(myInternalCStr.get() + (sizeof(char) * cStrSizet),  // NOLINT
            rhs,
            strlen(rhs));
    myInternalCStrSize += static_cast<int>(strlen(rhs));

    VLOG(1) << "Method Exit :  String::operator+=(const char* const)";
    return *this;
}

const String& String::operator+= (const String& rhs) {
    VLOG(1) << "Method Entry:  String::operator+=(const String&)";
    VLOG(2) << "Called with arguments\trhs = ->" << rhs.c_str() << "<-";

    const String& str = this->operator+=(rhs.c_str());

    VLOG(1) << "Method Exit :  String::operator+=(const String&)";
    return str;
}

void String::swap(String& other) { // NOLINT
    VLOG(1) << "Method Entry:  String::swap";
    VLOG(2) << "Called with arguments\tother = ->" << other.c_str() << "<-";

    std::swap(myInternalCStr,           other.myInternalCStr);
    std::swap(myInternalCStrSize,       other.myInternalCStrSize);
    std::swap(myInternalCStrAllocation, other.myInternalCStrAllocation);

    VLOG(1) << "Method Exit :  String::swap";
}

void String::resizeCStrBuffer(const int alloc) {
    VLOG(1) << "Method Entry:  String::resizeCStrBuffer";
    VLOG(2) << "Called with arguments\talloc = ->" << alloc << "<-";

    // redundant - but faster than reallocating a buffer
    if (alloc == myInternalCStrAllocation) {
        return;
    }

    try {
        myInternalCStrAllocation = alloc;
        shared_array<char> buffer =
          shared_array<char>(new char[myInternalCStrAllocation]);

        // copy the chars over
        if (0 != myInternalCStr) {
            strncpy(buffer.get(), myInternalCStr.get(),
                    static_cast<size_t>(myInternalCStrAllocation));
        }

        myInternalCStr = buffer;
    }
    catch(const bad_alloc& ex) {
        LOG(ERROR) << "Caught exception while resizing internal c string!";
        throw bad_alloc(ex);
    }

    VLOG(1) << "Method Exit :  String::resizeCStrBuffer";
}

bool operator== (const String& lhs, const String& rhs) {
    VLOG(1) << "Method Entry:  operator==";
    VLOG(2) << "Called with arguments\tlhs = ->" << lhs.c_str()
            << "<-\trhs = ->" << rhs.c_str() << "<-";

    int val = strcmp(lhs.c_str(), rhs.c_str());
    if (0 == val) {
        return true;
    }

    VLOG(1) << "Method Exit:  operator==";
    return false;
}

bool operator!= (const String& lhs, const String& rhs) {
    VLOG(1) << "Method Entry:  operator!=";
    VLOG(2) << "Called with arguments\tlhs = ->" << lhs.c_str()
            << "<-\trhs = ->" << rhs.c_str() << "<-";

    int val = strcmp(lhs.c_str(), rhs.c_str());
    if (0 != val) {
        return true;
    }

    VLOG(1) << "Method Exit :  operator!=";
    return false;
}

bool operator< (const String& lhs, const String& rhs) {
    VLOG(1) << "Method Entry:  operator<";
    VLOG(2) << "Called with arguments\tlhs = ->" << lhs.c_str()
            << "<-\trhs = ->" << rhs.c_str() << "<-";

    int val = strcmp(lhs.c_str(), rhs.c_str());
    if (val < 0) {
        return true;
    }

    VLOG(1) << "Method Exit :  operator<";
    return false;
}

bool operator> (const String& lhs, const String& rhs) {
    VLOG(1) << "Method Entry:  operator>";
    VLOG(2) << "Called with arguments\tlhs = ->" << lhs.c_str()
            << "<-\trhs = ->" << rhs.c_str() << "<-";

    int val = strcmp(lhs.c_str(), rhs.c_str());
    if (val > 0) {
        return true;
    }

    VLOG(1) << "Method Exit :  operator>";
    return false;
}

String operator+ (const String& lhs, const String& rhs) {
    VLOG(1) << "Method Entry:  operator+";
    VLOG(2) << "Called with arguments\tlhs = ->" << lhs.c_str()
            << "<-\trhs = ->" << rhs.c_str() << "<-";

    String temp(lhs);
    temp += rhs;

    VLOG(1) << "Method Exit :  operator+";
    return temp;
}
