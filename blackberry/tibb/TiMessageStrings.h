/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TIMESSAGESTRINGS_H_
#define TIMESSAGESTRINGS_H_

// Single file to contain the message strings

#ifdef TIMESSAGESTRINGS_DEF_VALUE
#define TIMESSAGESTRINGS_CONST_DEF(T,N,V) const T N=V
#else  // TIMESSAGESTRINGS_DEF_VALUE
#define TIMESSAGESTRINGS_CONST_DEF(T,N,V) extern const T N
#endif // TIMESSAGESTRINGS_DEF_VALUE

namespace Ti
{
namespace Msg
{

TIMESSAGESTRINGS_CONST_DEF(char*, ERROR__Cannot_load_bootstrap_js, "ERROR: Cannot load bootstrap.js");
TIMESSAGESTRINGS_CONST_DEF(char*, Include_file_not_found, "Include file not found");
TIMESSAGESTRINGS_CONST_DEF(char*, INTERNAL__Global_String_symbol_is_not_an_object, "INTERNAL: Global String symbol is not an object");
TIMESSAGESTRINGS_CONST_DEF(char*, INTERNAL__args0_is_not_a_number, "args[0] is not a number.");
TIMESSAGESTRINGS_CONST_DEF(char*, Missing_argument, "Missing argument");
TIMESSAGESTRINGS_CONST_DEF(char*, Too_many_arguments, "Too many arguments");

}
}

#endif // TIMESSAGESTRINGS_H_
