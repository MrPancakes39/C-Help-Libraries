#include <stddef.h>
#include <string.h>
#include "string_type.h"

/**
 * Creates a String from a char-array and it's length.
 * @param[in] data the c-string.
 * @param[in] length the length of the string.
 * @return a String object.
 */
String String_from_parts(const char *data, size_t length)
{
    String s;
    s.data = data;
    s.length = length;
    return s;
}

/**
 * Creates a String from a c-string.
 * @param[in] cstr a c-string.
 * @return a String object.
 */
String String_from(const char *cstr)
{
    return String_from_parts(cstr, strlen(cstr));
}