#include <String.h>
#include <iostream>

using std::istream;
using std::ostream;

// initialize static members
bool String::messages_wanted = false;

String::String(const char * in_cstr) {

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

