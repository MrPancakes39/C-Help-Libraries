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

/**
 * Creates a copy of a String object.
 * @param[in] source a String object.
 * @return a String object.
 */
String String_copy(const String source)
{
    // copy source.data into a buffer
    char buffer[source.length + 1];
    for (size_t i = 0; i < source.length; i++)
        buffer[i] = source.data[i];
    buffer[source.length] = '\0';

    String copy;
    copy.length = source.length;
    copy.data = buffer;
    return copy;
}