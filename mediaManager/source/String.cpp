#include <String.h>

#include <cstddef>
#include <cstdio>
#include <cstring>


// initialize static members
int  String::ourNumber          = 0;
int  String::ourTotalAllocation = 0;
bool String::ourMessagesWanted  = false;

// constructor
String::String(const char* in_cstr) {
    // output message if wanted
    if (true == ourMessagesWanted) {
        printf("Ctor: \"%s\"\n", in_cstr);
    }

    // calculate the sizes
    size_t strSize = strlen(in_cstr);
    myInternalCStrSize = strSize;
    myInternalCStrAllocation = strSize + 1;

    // create the internal buffer and copy the data
    myInternalCStr = new char[myInternalCStrAllocation];
    strncpy(myInternalCStr, in_cstr, myInternalCStrAllocation);

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
    strncpy(myInternalCStr, copy.c_str(), myInternalCStrAllocation);

    // update the static members
    ourNumber++;
    ourTotalAllocation += myInternalCStrAllocation;
}

String& String::operator=(const String& other) {
}

String& String::operator=(const char* other) {
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

char& String::operator[] (int i) {
}

const char& String::operator[] (int i) const {
}

String String::substring(int i, int len) const {
}

void String::clear() {
}

void String::remove(int i, int len) {
}

void String::insert_before(int i, const String& src) {
}

String& String::operator += (char rhs) {
}

String& String::operator += (const char * rhs) {
}

String& String::operator += (const String& rhs) {
}

void String::swap(String& other) { // NOLINT
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

