/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef NATIVEMESSAGESTRINGS_H_
#define NATIVEMESSAGESTRINGS_H_

// Single file to contain the message strings

#ifdef NATIVEMESSAGESTRINGS_DEF_VALUE
#define N_MESSAGESTRINGS_CONST_DEF(T,N,V) const T N=V
#else  // NATIVEMESSAGESTRINGS_DEF_VALUE
#define N_MESSAGESTRINGS_CONST_DEF(T,N,V) extern const T N
#endif // NATIVEMESSAGESTRINGS_DEF_VALUE

namespace Native
{
namespace Msg
{

N_MESSAGESTRINGS_CONST_DEF(char*, An_error_occurred_converting_to_int, "An error occurred converting to int");
N_MESSAGESTRINGS_CONST_DEF(char*, Expected_argument_of_type_double, "Expected argument of type double");
N_MESSAGESTRINGS_CONST_DEF(char*, Expected_argument_of_type_integer, "Expected argument of type integer");
N_MESSAGESTRINGS_CONST_DEF(char*, Expected_argument_of_type_object_or_external, "Expected argument of type object or external");
N_MESSAGESTRINGS_CONST_DEF(char*, Expected_argument_of_type_string, "Expected argument of type string");
N_MESSAGESTRINGS_CONST_DEF(char*, Expected_argument_of_type_unsigned_integer, "Expected argument of type unsigned integer");
N_MESSAGESTRINGS_CONST_DEF(char*, Failed_to_convert_font_size_to_float_with_value, "Failed to convert font size to float with value");
N_MESSAGESTRINGS_CONST_DEF(char*, INTERNAL__An_error_occurred_while_parsing_the_format_string, "INTERNAL: An error occurred while parsing the format string");
N_MESSAGESTRINGS_CONST_DEF(char*, Numbered_argument_exceeds_the_length_of_provided_arguments, "Numbered argument exceeds the length of provided arguments");
N_MESSAGESTRINGS_CONST_DEF(char*, Unknown_key_value_received, "Unknown key:value received");
N_MESSAGESTRINGS_CONST_DEF(char*, Unknown_value_received, "Unknown value received");

}
}

#endif // NATIVEMESSAGESTRINGS_H_
