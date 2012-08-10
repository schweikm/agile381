/*
 * Copyright 2012 Marc Schweikert
 */

#include "manager/Utility.h"

#include <cstdio>
#include <exception>

#include "manager/String.h"

// print an error message to stderr with standard exception
void printError(const char* const file, const int line,
                const char* const msg, const std::exception& ex) {
    fprintf(stderr, "ERROR!\t%s  [%d]\t%s\n", file, line, msg);
    fprintf(stderr, "Exception text:  \"%s\"\n", ex.what());
}

// print an error message to stderr with String_exception
void printError(const char* const file, const int line,
                const String_exception& ex) {
    fprintf(stderr, "ERROR!\t%s  [%d]  - \"%s\"\n", file, line, ex.msg);
}
