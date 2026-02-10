#pragma once

namespace StringUtils
{

    /**
     * @brief Trims leading and trailing whitespace from a string in-place
     * @param str String to trim
     * @return Pointer to the trimmed string
     */
    inline char* TrimWhitespace(char* str)
    {
        if (!str)
            return nullptr;

        // Trim leading
        while (*str == ' ' || *str == '\t')
            ++str;

        if (*str == '\0')
            return str;

        // Trim trailing
        char* end = str + strlen(str) - 1;
        while (end > str && (*end == ' ' || *end == '\t'))
            *end-- = '\0';

        return str;
    }

    /**
     * @brief Checks if two strings are equal
     * @param a First string
     * @param b Second string
     * @return true if strings are equal, false otherwise
     */
    inline bool StringEquals(const char* a, const char* b)
    {
        if (!a || !b)
            return (a == b);
        return strcmp(a, b) == 0;
    }

} // namespace StringUtils
