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

bool String_startWith(const String source, const String prefix);
bool String_startWithL(const String source, const char *prefix);
bool String_endsWith(const String source, const String suffix);
bool String_endsWithL(const String source, const char *suffix);

// ===============================================================

///< Defines macro for creating an empty string.
#define String_Empty String_from_parts(NULL, 0)

#define STR_FMT "%.*s"                       ///< Defines macro for printf.
#define STR_ARG(s) (int)(s).length, (s).data ///< Defines macro for printf.
#define STR_LEN(s) (int)(s).length           ///< Defines macro for printf.

#endif