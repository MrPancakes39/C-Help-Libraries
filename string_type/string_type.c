#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include "string_type.h"

/**
 * Creates a String from a char-array and it's length.
 * @param[in] data the string literal.
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
 * Creates a String from a string literal.
 * @param[in] cstr a string literal.
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
 * @param[in] source the String object to copy.
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

/**
 * Remove spaces at the beginning of a String object.
 * @param[in] source the String object to trim.
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
 * @param[in] source the String object to trim.
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
 * @param[in] source the String object to trim.
 * @note This function modifies the original string object.
 * @return Nothing.
 */
void String_trim(String *const source)
{
    String_trimLeft(source);
    String_trimRight(source);
}

/**
 * Pads from the left the current string with a character N amount of times.
 * @param[in] source the String object to pad.
 * @note This function modifies the original string object.
 * @return Nothing.
 */
void String_padLeft(String *const source, size_t amount, char ch)
{
    // resize the sring.
    size_t len = source->length + amount;
    char *padded = (char *)source->data;
    padded = (char *)realloc(padded, (len + 1) * sizeof(char));

    // shift all chars and append ch to start
    for (size_t i = len - 1; i >= amount; i--)
        padded[i] = (padded - amount)[i];
    for (size_t i = 0; i < amount; i++)
        padded[i] = ch;

    *source = String_from_parts(padded, len);
}

/**
 * Pads from the right the current string with a character N amount of times.
 * @param[in] source the String object to pad.
 * @note This function modifies the original string object.
 * @return Nothing.
 */
void String_padRight(String *const source, size_t amount, char ch)
{
    // resize the sring.
    size_t len = source->length + amount;
    char *padded = (char *)source->data;
    padded = (char *)realloc(padded, (len + 1) * sizeof(char));

    // append ch to end
    for (size_t i = len - amount; i < len; i++)
        padded[i] = ch;

    *source = String_from_parts(padded, len);
}

/**
 * Pads from the left and right the current string with a character N amount of times.
 * @param[in] source the String object to pad.
 * @note This function modifies the original string object.
 * @return Nothing.
 */
void String_pad(String *const source, size_t amount, char ch)
{
    String_padLeft(source, amount, ch);
    String_padRight(source, amount, ch);
}

/**
 * Compares two Strings.
 * @param[in] str1 a String object.
 * @param[in] str2 a String object.
 * @return 0 -> if str1 == str2.
 * @return 1 -> if str1 > str2.
 * @return -1 -> if str1 < str2.
 */
int String_cmp(String str1, String str2)
{
    // minimum length
    size_t len = (str1.length < str2.length) ? str1.length : str2.length;
    // loop and compare chars
    for (size_t i = 0; i < len; i++)
    {
        int diff = str1.data[i] - str2.data[i];
        if (diff > 0)
            return 1;
        if (diff < 0)
            return -1;
    }
    // if they are equal
    return 0;
}

/**
 * Compares two Strings insensitively.
 * @param[in] str1 a String object.
 * @param[in] str2 a String object.
 * @return 0 -> if str1 == str2.
 * @return 1 -> if str1 > str2.
 * @return -1 -> if str1 < str2.
 */
int String_icmp(String str1, String str2)
{
    // minimum length
    size_t len = (str1.length < str2.length) ? str1.length : str2.length;
    // loop and compare chars
    for (size_t i = 0; i < len; i++)
    {
        int diff = tolower(str1.data[i]) - tolower(str2.data[i]);
        if (diff > 0)
            return 1;
        if (diff < 0)
            return -1;
    }
    // if they are equal
    return 0;
}

/**
 * Checks if a string starts with a specific prefix.
 * @param[in] source the String object to check.
 * @param[in] prefix the prefix String object.
 * @return true -> if source starts with the prefix.
 * @return false -> otherwise.
 */
bool String_startWith(const String source, const String prefix)
{
    if (prefix.length <= source.length)
    {
        String cmpStr = String_from_parts(source.data, prefix.length);
        return (String_cmp(prefix, cmpStr) == 0);
    }
    return false;
}

/**
 * Checks if a string starts with a specific prefix.
 * @param[in] source the String object to check.
 * @param[in] prefix the prefix string literal.
 * @return true -> if source starts with the prefix.
 * @return false -> otherwise.
 */
bool String_startWithL(const String source, const char *prefix)
{
    size_t i;
    // stops if we reach end of source or end of prefix
    for (i = 0; (i < source.length && prefix[i] != '\0'); i++)
        // compares if they don't have matching chars
        if (source.data[i] != prefix[i])
            return false;

    // if we reached end of prefix then it starts with it
    if (prefix[i] == '\0')
        return true;

    // else we reached end of source
    return false;
}

/**
 * Checks if a string ends with a specific suffix.
 * @param[in] source the String object to check.
 * @param[in] suffix the suffix String object.
 * @return true -> if source ends with the suffix.
 * @return false -> otherwise.
 */
bool String_endsWith(const String source, const String suffix)
{
    if (suffix.length <= source.length)
    {
        String cmpStr = String_from_parts(source.data + source.length - suffix.length, suffix.length);
        return (String_cmp(suffix, cmpStr) == 0);
    }
    return false;
}

/**
 * Checks if a string ends with a specific suffix.
 * @param[in] source the String object to check.
 * @param[in] suffix the suffix string literal.
 * @return true -> if source ends with the suffix.
 * @return false -> otherwise.
 */
bool String_endsWithL(const String source, const char *suffix)
{
    // convert suffix to String object.
    size_t len = 0;
    while (suffix[len] != '\0')
        len++;
    String suffixStr = String_from_parts(suffix, len);
    // use the previous function
    return String_endsWith(source, suffixStr);
}