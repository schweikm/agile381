#ifndef TRUNK_MEDIAMANAGER_MANAGER_UTILITY_H_
#define TRUNK_MEDIAMANAGER_MANAGER_UTILITY_H_


/*
 * Copyright 2012 Marc Schweikert
 */


/**
 * @file Utility.h
 * @brief Utility functions, constants, and classes used by other modules
 */


/**
 * @def DISALLOW_COPY_AND_ASSIGN(TypeName)
 * A macro to disallow the copy constructor and operator= functions
 */
#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
  TypeName(const TypeName&);               \
  void operator=(const TypeName&)


// define a function template named "swapem" that interchanges the values of
// two variables use in Ordered_list and String where convenient


#endif  // TRUNK_MEDIAMANAGER_MANAGER_UTILITY_H_
