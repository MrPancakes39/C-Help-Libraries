#ifndef STRING_TYPE_H_INCLUDED
#define STRING_TYPE_H_INCLUDED

/**
 * Defines a String type.
 */
typedef struct
{
    const char *data;
    size_t length;
} String;

String String_from_parts(const char *data, size_t length);
String String_from(const char *cstr);
String String_copy(const String source);

///< Defines macro for creating an empty string.
#define String_Empty String_from_parts(NULL, 0)

#define STR_FMT "\"%.*s\""                   ///< Defines macro for printf.
#define STR_ARG(s) (int)(s).length, (s).data ///< Defines macro for printf.

#endif