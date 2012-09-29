#ifndef TRUNK_MEDIAMANAGER_MANAGER_STRING_H_
#define TRUNK_MEDIAMANAGER_MANAGER_STRING_H_


/*
 * Copyright 2012 Marc Schweikert
 */


#include "boost/shared_array.hpp"
#include "glog/logging.h"
#include "manager/Utility.h"


/*
 * String class - a subset of the C++ Standard Library <string> class
 * String objects contain a C-string in a dynamically allocated piece of memory
 * and support input/output, comparisons, copy, assignment, and concatenation,
 * access to individual characters and substrings, and insertion and removal
 * of parts of the string.
 *
 * Individual characters in the string are indexed the same as an array, 0
 * through length - 1.  The "size" of the string is the length of the internal
 * C-string, as defined by std::strlen and does not count the null byte marking
 * the end of the C-string. The "allocation" does count the null byte. Thus
 * allocation must be >= size + 1.
 *
 * Most operations result in a string that occupies the minimum amount of
 * memory (allocation = size + 1), but for efficiency, the operations that
 * involve adding characters to the string such as += use a doubling rule for
 * allocation to avoid frequent reallocation of memory and data copying.
 *
 * The doubling rule: If n characters are to be added to a string, and the
 * current allocation is  not large enough to hold the result
 * (allocation < size + n + 1), a new piece of memory is allocated whose size
 * is 2 * (size + n + 1).
 *
 * The doubling rule is a way to prevent excessive reallocation and copying
 * work as the internal contents of a String are expanded - thus it only
 * applies in cases where more characters are being added to the String.
 * In particular:
 *
 * - The concatenation operators += follow the doubling rule.
 * - Any operator that should be implemented in terms of +=, such as operator+
 *   and operator>>, and the function getline, will then also follow the
 *   doubling rule as a result.
 * - The insert_before function follows the doubling rule.
 * - All other functions and operators either leave the allocation unchanged
 *   (e.g. swap) or result in the minimum allocation (size +1).
 *
 * For those operations that involve indexing into the string such as
 * operator[], an exception is thrown with an error message if the index is not
 * within a valid range.
 *
 * For testing and demonstration purposes, this class contains static members
 * that record the current number of Strings in existence and their total
 * memory allocation.  If the messages_wanted variable is true, the
 * constructors, destructor, and assignment operators output a message to
 * demonstrate when these functions are called. The message is output before
 * the function does the actual work.  To help identify the String involved,
 * the message includes the relevant string data as follows:
 * - Constructors - the string data used to initialize this String.
 * - Destructor - the current string data being held in this String.
 * - Assignment operators - the string data from the right-hand-side
 *   (either a C-string or another String).
 * Note that only these functions output the messages. Other mumber functions
 * may result in these messages being output, but only because they call a
 * Constructor, Destructor, or Assignment operator as part of their work.
 */


// enum values for signalling error
enum StringStatus { OK, ERROR };


class String {
  public:
    // Default initialization is to contain an empty string; if a non-empty
    // C-string is supplied, this String gets minimum allocation.
    String();

    // method to perform complex initialization of constructor
    StringStatus init(const char* const in_cstr = "");

    // destructor
    ~String();

    // Accesssors
    // Return a pointer to the internal C-string
    char* c_str() const;

    // Return size of internal C-string in this String
    int size() const;

    // Return current allocation for this String
    int get_allocation() const;

    // Return a reference to character i in the string.
    // Throw exception if 0 <= i < size is false.
    StringStatus get(const int i, char* val) const;

    // Return a String starting with i and extending for len characters
    // The substring must be contained within the string.
    // Values of i and len for valid input are as follows:
    // i >= 0 && len >= 0 && i <= size && (i + len) <= size.
    // If both i = size and len = 0, the input is valid and the result is an
    // empty string.
    // Throw exception if the input is invalid.
    StringStatus substring(const int i, const int len, String* str) const;

    // Modifiers
    // Set to an empty string with minimum allocation by create/swap with an
    // empty string.
    void clear();

    // Remove the len characters starting at i; allocation is unchanged.
    // The removed characters must be contained within the String.
    // Valid values for i and len are the same as for substring.
    StringStatus remove(const int i, const int len);

    // Insert the supplied source String before character i
    // Pushing the rest of the contents back, reallocating as needed.
    // If i == size, the inserted string is added to the end of this String.
    // This String retains the final allocation.
    // Throw exception if 0 <= i <= size is false
    StringStatus insert_before(const int i, const String& src);

    // Swap the contents of this String with another one.
    // The member variable values are interchanged, along with the
    // pointers to the allocated C-strings, but the two C-strings
    // are neither copied nor modified. No memory allocation/deallocation is
    // done.
    void swap(String& other);  // NOLINT(build/include_what_you_use)

    // Return the total number of Strings in existence
    static int get_number();

    // Return total bytes allocated for all Strings in existence
    static int get_total_allocation();

  private:
    // resize the internal c string
    StringStatus resizeCStrBuffer(const int alloc);


    // internal C string
    boost::shared_array<char> myInternalCStr;

    // size of internal C string
    int myInternalCStrSize;

    // total bytes allocated for the internal C string
    int myInternalCStrAllocation;

    // counts number of String objects in existence
    static int ourNumber;

    // counts total amount of memory allocated
    static int ourTotalAllocation;

    // remove copy constructor and assignment operator
    DISALLOW_COPY_AND_ASSIGN(String);
};


////////////////////////
//  INLINE FUNCTIONS  //
////////////////////////


inline char* String::c_str() const {
    VLOG(1) << "Method Entry:  String::c_str";
    VLOG(1) << "Method Exit :  String::c_str";
    return myInternalCStr.get();
}

inline int String::size() const {
    VLOG(1) << "Method Entry:  String::size";
    VLOG(1) << "Method Exit :  String::size";
    return myInternalCStrSize;
}

inline int String::get_allocation() const {
    VLOG(1) << "Method Entry:  String::get_allocation";
    VLOG(1) << "Method Exit :  String::get_allocation";
    return myInternalCStrAllocation;
}

inline int String::get_number() {
    VLOG(1) << "Method Entry:  String::get_number";
    VLOG(1) << "Method Exit :  String::get_number";
    return ourNumber;
}

inline int String::get_total_allocation() {
    VLOG(1) << "Method Entry:  String::get_total_allocation";
    VLOG(1) << "Method Exit :  String::get_total_allocation";
    return ourTotalAllocation;
}


#endif  // TRUNK_MEDIAMANAGER_MANAGER_STRING_H_
