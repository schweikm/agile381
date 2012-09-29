#ifndef TRUNK_MEDIAMANAGER_MANAGER_UTILITY_H_
#define TRUNK_MEDIAMANAGER_MANAGER_UTILITY_H_


/*
 * Copyright 2012 Marc Schweikert
 */


/* Utility functions, constants, and classes used by other modules */


// A macro to disallow the copy constructor and operator= functions
#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
  TypeName(const TypeName&);               \
  void operator=(const TypeName&)


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

#endif  // TRUNK_MEDIAMANAGER_MANAGER_UTILITY_H_
