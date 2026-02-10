#include "String.h"

#include "../utils/StringUtils.h"

namespace String
{

    char* BuildPath(const char* dir, const char* filename)
    {
        return StringUtils::BuildPath(dir, filename, ".bmp");
    }

    char* CreateStringCopy(const char* input)
    {
        return StringUtils::CopyString(input);
    }

} // namespace String
