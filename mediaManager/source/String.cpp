#include <String.h>

#include <cstddef>
#include <cstring>
#include <iostream>

using std::cout;
using std::endl;
using std::istream;
using std::ostream;


// initialize static members
int  String::number           = 0;
int  String::total_allocation = 0; 
bool String::messages_wanted  = false;

// constructor
String::String(const char * in_cstr) {
    // calculate the sizes
    size_t strSize = strlen(in_cstr);
    myInternalCStrSize = strSize;
    myInternalCStrAllocation = strSize + 1;

    // create the internal buffer and copy the data
    myInternalCStr = new char[myInternalCStrAllocation];
    strncpy(myInternalCStr, in_cstr, myInternalCStrAllocation);

    // update the static members
    number++;
    total_allocation += myInternalCStrAllocation;

    // output message if wanted
    if(true == messages_wanted) {
        cout << "Ctor: \"" << in_cstr << "\"" << endl;
    }
}

String::String(const String& copy) {

}

String& String::operator=(const String& other) {

}

String& String::operator=(const char* other) {

}

String::~String() {

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

void String::swap(String& other) {

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

ostream& operator<< (ostream& os, const String& str) {

}

istream& operator>> (istream& is, String& str) {

}

istream& getline(istream& is, String& str) {

}

