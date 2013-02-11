#ifndef MEDIAMANAGER_MANAGER_STRING_H_
#define MEDIAMANAGER_MANAGER_STRING_H_


/*
 * Copyright 2012 Marc Schweikert
 */


#include "boost/shared_array.hpp"
#include "glog/logging.h"
#include "manager/Utility.h"


/**
 * @file String.h
 * @brief Declaration of String class.
 */


/**
 * @class String String.h manager/String.h
 *
 * @brief A subset of the C++ Standard Library string class.
 *
 * @details String objects contain a C-string in a dynamically allocated piece
 * of memory and supports input/output, comparisons, copy, assignment, and
 * concatenation, access to individual characters and substrings, and insertion
 * and removal of parts of the string.
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
 *
 * @author    Marc Schweikert
 * @date      29-Sep-2012
 * @version   1.0
 * @copyright TBD
 */
class String {
  public:
    /**
     * Enumeration that signals success or failure of ::String methods
     */
    enum Status {
        OK,     /**< Method executed successfully. */
        ERROR   /**< Method did not complete execution. */
    };

    /**
     * Constructor that initializes all member variables and nothing else.
     *
     * @pre  None.
     * @post All member variables have been initialized to sane values.
     */
    String();

    /**
     * Performs complex initialization of the object.
     * Default initialization is to contain an empty string; if a non-empty
     * C-string is supplied, this String gets minimum allocation.
     *
     * @pre  None.
     * @post Internal C-String has been allocated and characters copied.
     *
     * @warning If this method fails, the program will LOG and terminate.
     *
     * @param in_cstr C-String to be initialized from
     *
     * @return String::OK if successful, does not return on failure.
     */
    Status init(const char* const in_cstr = "");

    /**
     * Does not have to perform cleanup because of boost::shared_array.
     * Decrements static members.
     *
     * @pre  None.
     * @post Object has been destroyed.
     */
    ~String();

    /**
     * @pre  None.
     * @post Object remains unchanged.
     *
     * @return pointer to internal C-String
     */
    char* c_str() const;

    /**
     * @pre  None.
     * @post Object remains unchanged.
     *
     * @return size of internal C-string in this String
     */
    int size() const;

    /**
     * @pre  None.
     * @post Object remains unchanged.
     *
     * @return current allocation for this String
     */
    int get_allocation() const;

    /**
     * Retrieves the character as position i.
     * Acts as a replacement for operator[](const int).
     *
     * @pre  i >= 0
     * @pre  i < this.size
     * @post Object remains unchanged.
     *
     * @param i   Position of the string to get.
     * @param val Pointer to char that stores the value.
     *
     * @return String::ERROR if i is out-of-bounds, otherwise String::OK
     */
    Status get(const int i,
               char* val) const;

    /**
     * Gets a String starting with i and extending for len characters.
     * If both i = size and len = 0, the input is valid and the result is an
     * empty string.
     *
     * @pre  i >= 0
     * @pre  i <= this.size
     * @pre  len >= 0
     * @pre  len < this.size
     * @pre  (i + len) <= this.size
     * @post Object remains unchanged.
     *
     * @param i   Starting position.
     * @param len Length of substring to get.
     * @param str Pointer to String to store result.
     *
     * @return String::ERROR if i and/or len is out-of-bounds. otherwise String::OK
     */
    Status substring(const int i,
                     const int len,
                     String* str) const;

    /**
     * Set to an empty string with minimum allocation by create/swap
     * with an empty string.
     *
     * @pre  None.
     * @post Object has default allocation.
     */
    void clear();

    /**
     * Remove the len characters starting at i; allocation is unchanged.
     * The removed characters must be contained within the String.
     *
     * @pre  i >= 0
     * @pre  i <= this.size
     * @pre  len >= 0
     * @pre  len < this.size
     * @pre  (i + len) <= this.size
     * @post Object retains memory allocation and requested chars are removed.
     *
     * @param i   Starting position.
     * @param len Number of chars to remove.
     *
     * @return String::ERROR if i and/or len is out-of-bounds, otherwise String::OK
     */
    Status remove(const int i,
                  const int len);

    /**
     * Insert the supplied source String before character i
     * pushing the rest of the contents back and reallocating as needed.
     * If i == size, the inserted string is added to the end of this String.
     * This String retains the final allocation.
     *
     * @pre  i >= 0
     * @pre  i <= this.size
     * @post Object has requested chars inserted.
     *
     * @param i   Position in current String to insert before.
     * @param src Source String.
     *
     * @return String::ERROR if i is out-of-bounds, otherwise String::OK
     */
    Status insert_before(const int i,
                         const String& src);

    /**
     * Swap the contents of this String with another one.
     * The member variable values are interchanged, along with the pointers to
     * the allocated C-strings, but the two C-strings are neither copied nor
     * modified. No memory allocation/deallocation is done.
     *
     * @pre  None.
     * @post Member variables of two Strings are swapped.
     *
     * @param other String to swap contents with
     */
    void swap(String& other);  // NOLINT(build/include_what_you_use)

    /**
     * @return the total number of Strings in existence
     */
    static int get_number();

    /**
     * @return total bytes allocated for all Strings in existence
     */
    static int get_total_allocation();

  private:
    /**
     * Resize the internal C-String.
     *
     * @pre  alloc > this.allocation
     * @post Internal C-String resized and chars retained.
     *
     * @param alloc New size of internal buffer.
     *
     * @return String::ERROR if new fails, otherwise String::OK
     */
    Status resizeCStrBuffer(const int alloc);

    /**
     * Internal C-String using Boost.
     */
    boost::shared_array<char> myCStr;

    /**
     * Size of internal C-String.
     */
    int myCStrSize;

    /**
     * Total bytes allocated for the internal C-String.
     */
    int myCStrAllocation;

    /**
     * Counts the number of String objects in existence.
     */
    static int ourNumber;

    /**
     * Counts the total amount of memory allocated.
     */
    static int ourTotalAllocation;

    /**
     * Remove copy constructor and assignment operator.
     */
    DISALLOW_COPY_AND_ASSIGN(String);
};


////////////////////////
//  INLINE FUNCTIONS  //
////////////////////////


inline char* String::c_str() const {
    VLOG(1) << "Method Entry:  String::c_str";
    VLOG(1) << "Method Exit :  String::c_str";
    return myCStr.get();
}

inline int String::size() const {
    VLOG(1) << "Method Entry:  String::size";
    VLOG(1) << "Method Exit :  String::size";
    return myCStrSize;
}

inline int String::get_allocation() const {
    VLOG(1) << "Method Entry:  String::get_allocation";
    VLOG(1) << "Method Exit :  String::get_allocation";
    return myCStrAllocation;
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


#endif  // MEDIAMANAGER_MANAGER_STRING_H_
