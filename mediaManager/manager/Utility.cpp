/*
 * Copyright 2012 Marc Schweikert
 */


#include "manager/Utility.h"

#include <exception>

#include "boost/throw_exception.hpp"
#include "glog/logging.h"

// user-defined exception handler
namespace boost {
    void throw_exception(const std::exception&) {
        LOG(FATAL) << "Caught Boost exception!";
    }
}

