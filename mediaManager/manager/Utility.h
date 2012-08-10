#ifndef TRUNK_MEDIAMANAGER_MANAGER_UTILITY_H_
#define TRUNK_MEDIAMANAGER_MANAGER_UTILITY_H_

/*
 * Copyright 2012 Marc Schweikert
 */

#include <exception>
class String_exception;

/* Utility functions, constants, and classes used by other modules */

// a simple class for error exceptions - msg points to a C-string error message
struct Error {
    explicit Error(const char * in_msg = "")
      :msg(in_msg) {
    }

    const char * msg;
};

// define a function template named "swapem" that interchanges the values of
// two variables use in Ordered_list and String where convenient

/* add any other functions declarations here and define in Utility.cpp */

// print an error message to stderr with standard exception
void printError(const char* const file, const int line,
                const char* const msg, const std::exception& ex);

// print an error message to stderr with String_exception
void printError(const char* const file, const int line,
                const String_exception& ex);

#endif  // TRUNK_MEDIAMANAGER_MANAGER_UTILITY_H_
