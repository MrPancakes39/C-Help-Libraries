#include <stdlib.h>
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
 * Frees a String object from memory.
 * @param[in] source a String object to delete.
 * @return Nothing.
 */
void String_delete(String source)
{
    free((char *)source.data);
    source.length = 0;
    source.data = NULL;
}

/**
 * Creates a String from a c-string.
 * @param[in] cstr a c-string.
 * @return a String object.
 */
String String_from(const char *cstr)
{
    // create an empty string buffer
    size_t buf_size = 1;
    char *buffer = (char *)malloc(1 * sizeof(char));
    buffer[0] = '\0';

    // copy data from cstr to buffer
    while (cstr[buf_size - 1] != '\0')
    {
        ++buf_size;
        buffer = (char *)realloc(buffer, buf_size * sizeof(char));
        buffer[buf_size - 2] = cstr[buf_size - 2];
        buffer[buf_size - 1] = '\0';
    }

    return String_from_parts(cstr, buf_size - 1);
}

/**
 * Creates a copy of a String object.
 * @param[in] source a String object.
 * @return a String object.
 */
String String_copy(const String source)
{
    // copy source.data into a buffer
    size_t len = source.length;
    char *buffer = (char *)malloc((len + 1) * sizeof(char));
    for (size_t i = 0; i < len; i++)
        buffer[i] = source.data[i];
    buffer[len] = '\0';

    return String_from_parts(buffer, len);
}