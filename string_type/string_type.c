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
 * Casts a string literal to a String object.
 * This creates a static String object not a dynamic one.
 * Use String_from() method to create a dynamic String object.
 *
 * @param[in] cstr a string literal.
 * @return a static String object.
 */
String String_cast(const char *cstr)
{
    size_t len = 0;
    while (cstr[len] != '\0')
        len++;
    return String_from_parts(cstr, len);
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
 * Creates an array of String objects.
 * @param[in] length the length of the array.
 * @return a StringArray object.
 */
StringArray StringArray_create(size_t length)
{
    StringArray sarray;
    sarray.length = length;
    if (length == 0)
        sarray.data = NULL;
    else
    {
        sarray.data = (String *)malloc(length * sizeof(String));
        for (size_t i = 0; i < sarray.length; i++)
            sarray.data[i] = String_Empty;
    }
    return sarray;
}

/**
 * Frees a StringArray object from memory.
 * @param[in] sourceArray a StringArray object to delete.
 * @return Nothing.
 */
void StringArray_delete(StringArray *sourceArray)
{
    for (size_t i = 0; i < sourceArray->length; i++)
        String_delete((String *)&sourceArray->data[i]);
    sourceArray->length = 0;
    sourceArray->data = NULL;
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

bool String_includes(const String source, const String searchStr)
{
    if (searchStr.length > source.length)
        return false;

    for (size_t i = 0; i < source.length - searchStr.length + 1; i++)
    {
        bool included = true;
        for (size_t j = 0; j < searchStr.length; j++)
        {
            if (searchStr.data[j] != (source.data + i)[j])
            {
                included = false;
                break;
            }
        }
        if (included)
            return true;
    }
    return false;
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
 * Returns the lowest index in source where substring searchString is found.
 * Returns -1 on failure.
 * @param[in] source the source String object to search.
 * @param[in] searchString the search String object.
 * @return -1 on failure.
 * @return the first index of searchString in source string on success.
 */
size_t String_indexOf(const String source, const String searchString)
{
    for (size_t i = 0; i < source.length - searchString.length + 1; i++)
    {
        bool found = true;
        for (size_t j = 0; j < searchString.length; j++)
        {
            if (searchString.data[j] != (source.data + i)[j])
            {
                found = false;
                break;
            }
        }
        if (found)
            return i;
    }

    return -1;
}

/**
 * Returns the index of the last occurrence of substring searchString in source if found.
 * Returns -1 on failure.
 * @param[in] source the source String object to search.
 * @param[in] searchString the search String object.
 * @return -1 on failure.
 * @return the last index of searchString in source string on success.
 */
size_t String_lastIndexOf(const String source, const String searchString)
{
    // start at end and look for the string
    size_t end = source.length - searchString.length + 1;
    for (size_t i = 0; i < end; i++)
    {
        // get wanted index.
        size_t index = end - 1 - i;
        // search for substring.
        bool found = true;
        for (size_t j = 0; j < searchString.length; j++)
        {
            if (searchString.data[j] != (source.data + index)[j])
            {
                found = false;
                break;
            }
        }
        // return last index.
        if (found)
            return index;
    }
    // if not found.
    return -1;
}

/**
 * Converts a string to lowercase.
 * @param[in] source a String object.
 * @return Nothing.
 */
void String_lower(String *const source)
{
    char *tmp = (char *)source->data;
    for (size_t i = 0; i < source->length; i++)
        tmp[i] = tolower(tmp[i]);
}

/**
 * Converts a string to uppercase.
 * @param[in] source a String object.
 * @return Nothing.
 */
void String_upper(String *const source)
{
    char *tmp = (char *)source->data;
    for (size_t i = 0; i < source->length; i++)
        tmp[i] = toupper(tmp[i]);
}

/**
 * Converts a string to a capitalized version of itself.
 *
 * More specifically, makes the first character have upper case and the rest lower.
 * @param[in] source a String object.
 * @return Nothing.
 */
void String_capitalize(String *const source)
{
    char *tmp = (char *)source->data;
    String_lower(source);
    tmp[0] = toupper(tmp[0]);
}

/**
 * Converts a string to a version of the string where each word is titlecased.
 *
 * More specifically, words start with uppercased characters and all remaining cased characters have lower case.
 * @param[in] source a String object.
 * @return Nothing.
 */
void String_title(String *const source)
{
    size_t i = 0;
    char *tmp = (char *)source->data;
    tmp[0] = toupper(tmp[0]);
    for (i = 1; i < source->length; i++)
    {
        if (isspace(tmp[i]))
        {
            // move to next char and upper it
            ++i;
            tmp[i] = toupper(tmp[i]);
        }
        else
            tmp[i] = tolower(tmp[i]);
    }
}
/**
 * Convert uppercase characters to lowercase and lowercase characters to uppercase.
 * @param[in] source a String object.
 * @return Nothing.
 */
void String_swapcase(String *const source)
{
    char *tmp = (char *)source->data;
    for (size_t i = 0; i < source->length; i++)
        tmp[i] = isupper(tmp[i]) ? tolower(tmp[i]) : toupper(tmp[i]);
}

/**
 * Changed a string into a centered string of length width.
 * Padding is done using the specified fill character.
 * @param[in] source a String object.
 * @param[in] width the length to be centered as.
 * @param[in] fillchar the char to use for padding.
 * @return Nothing.
 */
void String_center(String *const source, size_t width, char fillchar)
{
    if (source->length < width)
    {
        // calculate fills.
        size_t diff = width - source->length, lfill, rfill;
        lfill = rfill = diff / 2;
        rfill += (diff % 2 == 0) ? 0 : 1;

        // resize string.
        char *tmp = (char *)source->data;
        tmp = (char *)realloc(tmp, width * sizeof(char));

        // copy chars.
        for (size_t i = 0; i < rfill; i++)
            tmp[width - 1 - i] = fillchar;
        for (size_t j = 0; j < source->length; j++)
            tmp[width - rfill - 1 - j] = tmp[source->length - 1 - j];
        for (size_t k = 0; k < lfill; k++)
            tmp[k] = fillchar;

        // update the string.
        *source = String_from_parts(tmp, width);
    }
}

/**
 * Modifies the string such that all tab characters are expanded using spaces.
 * @param[in] source a String object.
 * @param[in] tabsize the tabsize.
 * @return Nothing.
 */
void String_expandtabs(String *const source, size_t tabsize)
{
    // calculate occurances and spaces
    size_t occurances = 0;
    size_t current_column = 0;
    size_t spaces = 0;
    for (size_t i = 0; i < source->length; i++)
    {
        if (source->data[i] == '\t')
        {
            occurances++;
            spaces += tabsize - current_column;
            current_column = 0;
            continue;
        }

        current_column = (current_column + 1) % tabsize;

        // reset column counter if new line
        if (source->data[i] == '\n' || source->data[i] == '\r')
            current_column = 0;
    }

    // resize the string
    size_t len = source->length - occurances + spaces;
    char *tmp = (char *)source->data;
    tmp = (char *)realloc(tmp, (len + 1) * sizeof(char));
    tmp[len] = '\0';

    // shift data to end of string
    for (size_t i = 0; i < source->length; i++)
        tmp[len - 1 - i] = tmp[source->length - 1 - i];

    // expand tabs
    size_t src_i = len - source->length;
    current_column = 0;
    for (size_t t = 0; (t < len - 1); t++)
    {
        // we encounter a tab
        if (tmp[src_i] == '\t')
        {
            // copy spaces instead
            for (size_t j = 0; j < tabsize - current_column; j++)
                tmp[t++] = ' ';
            // move src pointer
            ++src_i;
            // fix t position
            --t;
            // reset column count
            current_column = 0;
            continue;
        }

        // increase column count
        current_column = (current_column + 1) % tabsize;

        // reset column counter if new line
        if (tmp[src_i] == '\n' || tmp[src_i] == '\r')
            current_column = 0;

        // copy from src to tmp
        tmp[t] = tmp[src_i++];
    }

    *source = String_from_parts(tmp, len);
}

/**
 * Pad a string with ASCII '0' digits on the left, to fill a field of the given width.
 * A leading sign prefix ('+'/'-') is handled by inserting the padding after the sign character rather than before.
 * The original string is not modified if width is less than or equal to length of the string.
 * @param[in] source the String object to be filled.
 * @param[in] width the desired string length.
 * @return Nothing.
 */
void String_zfill(String *const source, size_t width)
{
    if (source->length < width)
    {
        // resize the string.
        char *tmp = (char *)source->data;
        tmp = realloc(tmp, (width + 1) * sizeof(char));
        tmp[width] = '\0';

        // shift src to end.
        for (size_t i = 0; i < source->length; i++)
            tmp[width - 1 - i] = tmp[source->length - 1 - i];

        // start of original src in tmp.
        size_t start = width - source->length;

        // fill with zeros.
        for (size_t j = 0; j < start; j++)
            tmp[j] = '0';

        if (tmp[start] == '+' || tmp[start] == '-')
        {
            tmp[0] = tmp[start];
            tmp[start] = '0';
        }

        *source = String_from_parts(tmp, width);
    }
}

/**
 * Return the number of non-overlapping occurrences of substring in source.
 * @param[in] source the String object to search in.
 * @param[in] substring the Substring object to count number of.
 * @return the number of substring in source.
 */
size_t String_count(const String source, const String substring)
{
    if (substring.length > source.length)
        return -1;

    size_t count = 0;
    for (size_t i = 0; i < source.length - substring.length + 1; i++)
    {
        bool found = true;
        for (size_t j = 0; j < substring.length; j++)
        {
            if (substring.data[j] != (source.data + i)[j])
            {
                found = false;
                break;
            }
        }
        if (found)
        {
            ++count;
            i = i + substring.length - 1;
        }
    }
    return count;
}

/**
 * Modifies the String source such that all occurrences of substring old is replaced by new.
 * @param[in] source a String object.
 * @param[in] old the substring to replace.
 * @param[in] new the substring to replace with.
 * @return Nothing.
 */
void String_replace(String *const source, const String old, const String new)
{
    String_replaceC(source, old, new, -1);
}

/**
 * Modifies the String source such that count occurrences of substring old is replaced by new.
 * If count is -1 then all occurrences are replaced.
 * @param[in] source a String object.
 * @param[in] old the substring to replace.
 * @param[in] new the substring to replace with.
 * @param[in] count the maximum number of occurrences to replace.
 * @return Nothing.
 */
void String_replaceC(String *const source, const String old, const String new, int count)
{
    // get number of time old is in source.
    const size_t occurances = String_count(*source, old);
    // if it is zero we can't replace so exit.
    if (occurances == 0)
        return;

    // Else calculate total number to replace
    size_t total = (count == -1)                  ? occurances
                   : ((size_t)count < occurances) ? (size_t)count
                                                  : occurances;
    // and we calculate new length.
    size_t len = source->length + total * (new.length - old.length);
    char *new_str = (char *)source->data;

    // if new string is bigger than the old
    if (len > source->length)
    {
        // we increase the size
        new_str = (char *)realloc(new_str, (len + 1) * sizeof(char));
        new_str[len] = '\0';
        // indicies
        size_t src_i = source->length - 1;
        size_t nstr_i = len - 1;

        // if count < MAX
        if (occurances > total)
        {
            // get index of last occurance
            size_t lastIndex = 0, current_count = 0;
            for (; lastIndex <= src_i; lastIndex++)
            {
                if (current_count == total)
                    break;

                bool found = true;
                for (size_t j = 0; j < old.length; j++)
                {
                    if (old.data[j] != (new_str + lastIndex)[j])
                    {
                        found = false;
                        break;
                    }
                }
                if (found)
                {
                    ++current_count;
                    lastIndex += old.length - 1;
                }
            }

            // copy from end to last occurance
            for (; nstr_i > len - 1 - source->length + lastIndex;)
                new_str[nstr_i--] = new_str[src_i--];
        }

        for (size_t forw = 0; forw < nstr_i + 1; forw++)
        {
            // if we replaced them all quit
            if (total == 0)
                break;

            // calculate the wanted index
            size_t index = nstr_i - forw;

            // check if we encounter old
            bool found = true;
            for (size_t old_i = 0; old_i < old.length; old_i++)
            {
                if (old.data[old.length - 1 - old_i] != (new_str + src_i)[-old_i])
                {
                    found = false;
                    break;
                }
            }
            if (found)
            {
                // copy new instead of old
                for (size_t new_i = 0; new_i < new.length; new_i++)
                    (new_str + index)[-new_i] = new.data[new.length - 1 - new_i];

                forw += new.length - 1;
                src_i -= old.length;
                --total;
                continue;
            }
            // copy src string
            new_str[index] = new_str[src_i--];
        }
    }
    // new string is smaller than the original
    else
    {
        size_t src_i = 0;
        for (size_t nstr_i = 0; nstr_i < len; nstr_i++)
        {
            // if we replaced all total then stop check-replace
            if (total != 0)
            {
                bool found = true;
                for (size_t old_i = 0; old_i < old.length; old_i++)
                {
                    if (old.data[old_i] != (new_str + src_i)[old_i])
                    {
                        found = false;
                        break;
                    }
                }
                if (found)
                {
                    // copy new instead of old
                    for (size_t new_i = 0; new_i < new.length; new_i++)
                        (new_str + nstr_i)[new_i] = new.data[new_i];

                    nstr_i += new.length - 1;
                    src_i += old.length;
                    --total;
                    continue;
                }
            }
            // copy src string
            new_str[nstr_i] = new_str[src_i++];
        }

        // we decrease the size
        new_str = (char *)realloc(new_str, (len + 1) * sizeof(char));
        new_str[len] = '\0';
    }
    *source = String_from_parts(new_str, len);
}

/**
 * Divides a string into an array of strings using delim as the delimiter string.
 * @param[in] source a String object.
 * @param[in] delim a String object.
 * @return a StringArray object containing the substrings found.
 */
StringArray String_split(const String source, const String delim)
{
    // if empty delimiter
    if (delim.length == 0 || delim.data == NULL)
        return StringArray_create(0);

    // create the array
    StringArray sarr = StringArray_create(1);

    size_t start = 0, word = 0;
    size_t stop = source.length - delim.length + 1;
    for (size_t i = 0; i < stop; i++)
    {
        bool found = true;
        for (size_t j = 0; j < delim.length; j++)
        {
            if (delim.data[j] != (source.data + i)[j])
            {
                found = false;
                break;
            }
        }
        bool copy_end = (!found && i + 1 == stop);
        if (found || copy_end)
        {
            // if copy last part
            if (copy_end)
                i = source.length;

            // increase the size of the array
            if (!copy_end)
            {
                sarr.length++;
                sarr.data = (String *)realloc(sarr.data, (sarr.length) * sizeof(String));
                sarr.data[sarr.length - 1] = String_Empty;
            }

            // create slice
            size_t len = i - start;
            char *slice = (char *)malloc((len + 1) * sizeof(char));
            slice[len] = '\0';

            // copy from src to slice
            for (size_t k = 0; k < len; k++)
                slice[k] = (source.data + start)[k];

            // update string array
            sarr.data[word++] = String_from_parts(slice, len);

            i += delim.length - 1;
            start = i + 1;
            continue;
        }
    }

    return sarr;
}

/**
 * Concatenate an array of strings using joinStr.
 * @param[in] sourceArray a StringArray object.
 * @param[in] joinStr a String object.
 * @return a String object.
 */
String String_join(const StringArray sourceArray, const String joinStr)
{
    if (sourceArray.length == 0)
        return String_Empty;

    if (sourceArray.length == 1)
        return String_copy(sourceArray.data[0]);

    size_t len = 0;
    char *buffer = (char *)malloc((len + 1) * sizeof(char));
    buffer[len] = '\0';

    size_t t = 0;
    for (size_t i = 0; i < sourceArray.length - 1; i++)
    {
        // get new length
        len += sourceArray.data[i].length;
        len += joinStr.length;

        // resize buffer
        buffer = (char *)realloc(buffer, (len + 1) * sizeof(char));

        // copy src to buffer
        for (size_t j = 0; j < sourceArray.data[i].length;)
            buffer[t++] = sourceArray.data[i].data[j++];
        // copy delim to buffer
        for (size_t k = 0; k < joinStr.length;)
            buffer[t++] = joinStr.data[k++];
    }

    size_t lastIndex = sourceArray.length - 1;

    // get new length
    len += sourceArray.data[lastIndex].length;
    // resize buffer
    buffer = (char *)realloc(buffer, (len + 1) * sizeof(char));
    // copy src to buffer
    for (size_t j = 0; j < sourceArray.data[lastIndex].length;)
        buffer[t++] = sourceArray.data[lastIndex].data[j++];

    return String_from_parts(buffer, len);
}

/**
 * Partition the string into three parts using the given separator.
 *
 * This will search for the separator in the string.  If the separator is found,
 * returns a 3-tuple containing the part before the separator, the separator
 * itself, and the part after it.
 *
 * If the separator is not found, returns a 3-tuple containing the original string
 * and two empty strings.
 *
 * @param[in] source the String object to partition.
 * @param[in] sep the seperator string.
 * @return a partitioned StringArray object.
 */
StringArray String_partition(const String source, const String sep)
{
    // if empty delimiter
    if (sep.length == 0 || sep.data == NULL)
        return StringArray_create(0);

    // create StringArray.
    StringArray sarr = StringArray_create(3);

    // create buffer
    size_t len = 0;
    char *buffer = (char *)malloc((len + 1) * sizeof(char));
    buffer[len] = '\0';

    for (size_t i = 0; i < source.length; i++)
    {
        bool found = true;
        for (size_t j = 0; j < sep.length; j++)
        {
            if (sep.data[j] != (source.data + i)[j])
            {
                found = false;
                break;
            }
        }
        if (found)
        {
            size_t offset = len + sep.length;
            sarr.data[1] = String_copy(sep);
            sarr.data[2] = String_copy(String_from_parts(source.data + offset, source.length - offset));
            break;
        }

        // resize buffer
        len++;
        buffer = (char *)realloc(buffer, (len + 1) * sizeof(char));
        // copy src to buffer
        buffer[i] = source.data[i];
    }

    sarr.data[0] = String_from_parts(buffer, len);
    return sarr;
}

/**
 * Creates an array of the lines contained in the string, breaking at line boundaries.
 * Line breaks are not included in the resulting array.
 * @param[in] source a String object.
 * @return a StringArray with all lines in source.
 */
StringArray String_splitlines(const String source)
{
    /**
     * Universal Newlines Reference
     * Representation:    Description:
     * '\n':              Line Feed.
     * '\r':              Carriage Return.
     * "\r\n":            Carriage Return + Line Feed.
     * '\v' or '\x0b':    Line Tabulation.
     * '\f' or '\x0c':    Form Feed.
     * '\x1c':            File Separator.
     * '\x1d':            Group Separator.
     * '\x1e':            Record Separator.
     * '\x85':            Next Line (C1 Control Code).
     * '\U2028':          Line Separator.               (ignored)
     * '\U2029':          Paragraph Separator.          (ignored)
     */

    if (source.data == NULL || source.length == 0)
        return StringArray_create(0);

    // create the array
    size_t line = 0;
    StringArray sarr = StringArray_create(1);

    size_t start = 0;
    for (size_t i = 0; i < source.length; i++)
    {
        char ch = source.data[i];
        char ch_next = source.data[i + 1];
        if (ch == '\n' || ch == '\x0b' || ch == '\x0c' || ch == '\x1c' || ch == '\x1d' || ch == '\x1e' || ch == '\x85')
        {
            // copy to string array
            sarr.data[line++] = String_copy(String_from_parts(source.data + start, i - start));
            start = i + 1;
            if (ch_next != '\0')
            {
                // resize the string array
                sarr.length++;
                sarr.data = (String *)realloc(sarr.data, (sarr.length) * sizeof(String));
                sarr.data[sarr.length - 1] = String_Empty;
            }
        }
        else if (ch == '\r')
        {
            // copy to string array
            sarr.data[line++] = String_copy(String_from_parts(source.data + start, i - start));
            start = (ch_next != '\n') ? (i + 1) : (i + 2);
            bool shouldAdd = (ch_next != '\n') ? (ch_next != '\0') : (source.data[i + 2] != '\0');
            if (shouldAdd)
            {
                // resize the string array
                sarr.length++;
                sarr.data = (String *)realloc(sarr.data, (sarr.length) * sizeof(String));
                sarr.data[sarr.length - 1] = String_Empty;
            }
            i = start;
        }
        else if (ch_next == '\0')
        {
            // copy last line to string array
            sarr.data[line++] = String_copy(String_from_parts(source.data + start, i - start + 1));
        }
    }

    return sarr;
}

/**
 * Returns true if all characters in the string are alpha-numeric and there is at least one character in the string.
 * @param[in] source the source string.
 * @return true if the string is alpha-numeric.
 * @return false otherwise
 */
bool String_isalnum(const String source)
{
    // if string is empty.
    if (source.length == 0 || source.data == NULL)
        return false;
    // else check all chars.
    for (size_t i = 0; i < source.length; i++)
        if (!isalnum(source.data[i]))
            return false;
    // if all of the chars are alpha-numeric.
    return true;
}