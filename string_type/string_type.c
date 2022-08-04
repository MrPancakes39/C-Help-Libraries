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
void String_delete(String *source)
{
    free((char *)source->data);
    source->length = 0;
    source->data = NULL;
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

    return String_from_parts(buffer, buf_size - 1);
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

///< defines isspace so no need to import ctype.h
#define isspace(c) (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\v' || c == 'f')

/**
 * Remove spaces at the beginning of a String object.
 * @note This function modifies the original string object.
 * @return Nothing.
 */
void String_trimLeft(String *const source)
{
    size_t start = 0;
    while (start < source->length && isspace(source->data[start]))
        start++;

    // shift source.data to the beginning.
    size_t len = source->length - start;
    char *trimmed = (char *)source->data;
    for (size_t i = 0; i < len; i++)
        trimmed[i] = (source->data + start)[i];
    trimmed[len] = '\0';

    trimmed = (char *)realloc(trimmed, (len + 1) * sizeof(char));
    trimmed[len] = '\0';

    *source = String_from_parts(trimmed, len);
}

/**
 * Remove spaces at the end of a String object.
 * @note This function modifies the original string object.
 * @return Nothing.
 */
void String_trimRight(String *const source)
{
    size_t end = 0;
    while (end < source->length && isspace(source->data[source->length - 1 - end]))
        end++;

    // remove the ending of source.data.
    size_t len = source->length - end;
    char *trimmed = (char *)source->data;
    trimmed = (char *)realloc(trimmed, (len + 1) * sizeof(char));
    trimmed[len] = '\0';

    *source = String_from_parts(trimmed, len);
}

/**
 * Remove spaces at the beginning and at the end of the string:
 * @note This function modifies the original string object.
 * @return Nothing.
 */
void String_trim(String *const source)
{
    String_trimLeft(source);
    String_trimRight(source);
}

void String_padLeft(String *const source, size_t length, char ch)
{
    // resize the sring.
    size_t len = source->length + length;
    char *padded = (char *)source->data;
    padded = (char *)realloc(padded, (len + 1) * sizeof(char));

    // shift all chars and append ch to start
    for (size_t i = len - 1; i >= length; i--)
        padded[i] = (padded - length)[i];
    for (size_t i = 0; i < length; i++)
        padded[i] = ch;

    *source = String_from_parts(padded, len);
}

void String_padRight(String *const source, size_t length, char ch)
{
    // resize the sring.
    size_t len = source->length + length;
    char *padded = (char *)source->data;
    padded = (char *)realloc(padded, (len + 1) * sizeof(char));

    // append ch to end
    for (size_t i = len - length; i < len; i++)
        padded[i] = ch;

    *source = String_from_parts(padded, len);
}

void String_pad(String *const source, size_t length, char ch)
{
    String_padLeft(source, length, ch);
    String_padRight(source, length, ch);
}