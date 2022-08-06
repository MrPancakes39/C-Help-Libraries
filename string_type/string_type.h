#ifndef STRING_TYPE_H_INCLUDED
#define STRING_TYPE_H_INCLUDED
#include <stdbool.h>

/**
 * Defines a String type.
 */
typedef struct
{
    const char *data;
    size_t length;
} String;

// ================== String Creation Functions ==================

String String_from_parts(const char *data, size_t length);
String String_from(const char *cstr);
String String_copy(const String source);
String String_cast(const char *cstr);
void String_delete(String *source);

// ===============================================================

// ======================= String Methods  =======================

void String_trimLeft(String *const source);
void String_trimRight(String *const source);
void String_trim(String *const source);

void String_padLeft(String *const source, size_t length, char ch);
void String_padRight(String *const source, size_t length, char ch);
void String_pad(String *const source, size_t length, char ch);

int String_cmp(String str1, String str2);
int String_icmp(String str1, String str2);
bool String_includes(const String source, const String searchStr);

bool String_startWith(const String source, const String prefix);
bool String_endsWith(const String source, const String suffix);

void String_lower(String *const source);
void String_upper(String *const source);
void String_capitalize(String *const source);
void String_title(String *const source);

size_t String_count(const String source, const String substring);
void String_replace(String *const source, const String old, const String new);
void String_replaceC(String *const source, const String old, const String new, int count);

// ===============================================================

// ====================== String Constants  ======================

///< Defines macro for creating an empty string.
#define String_Empty String_from_parts(NULL, 0)
#define STR_ASCII_UPPERCASE "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
#define STR_ASCII_LOWERCASE "abcdefghijklmnopqrstuvwxyz"
#define STR_ASCII_LETTERS STR_ASCII_UPPERCASE STR_ASCII_LOWERCASE
#define STR_DIGITS "0123456789"
#define STR_HEXDIGITS "0123456789abcdefABCDEF"
#define STR_OCTDIGITS "01234567"
#define STR_PUNCTUATION "!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~."
#define STR_WHITESPACE " \t\n\r\x0b\x0c"
#define STR_PRINTABLE STR_DIGITS STR_ASCII_LETTERS STR_PUNCTUATION STR_WHITESPACE

// ===============================================================

#define STR_FMT "%.*s"                       ///< Defines macro for printf.
#define STR_ARG(s) (int)(s).length, (s).data ///< Defines macro for printf.
#define STR_LEN(s) (int)(s).length           ///< Defines macro to get the length for printf.

///< Defines a macro to debug a string.
#define STR_DEBUG(s) printf("String(data: \"" STR_FMT "\", len: %d)\n", STR_ARG(s), STR_LEN(s));

#endif