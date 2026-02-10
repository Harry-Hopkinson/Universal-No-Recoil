#pragma once

namespace String
{

    /**
     * @brief Concatenates directory path, filename, and .bmp extension
     * @param dir The directory path
     * @param filename The filename without extension
     * @return A newly allocated string with the full path
     */
    char* BuildPath(const char* dir, const char* filename);

    /**
     * @brief Creates a copy of the input string
     * @param input The string to copy
     * @return A newly allocated copy of the string
     */
    char* CreateStringCopy(const char* input);


} // namespace String
