//
//  MyTImmerSystem.hpp
//  ScrollerDemo
//
//  Created by Knight on 15/10/28.
//
//

#ifndef ___StringUtils_H___
#define ___StringUtils_H___

#include <stdlib.h>

namespace StringUtils
{
    std::string format(const char* format, ...)
    {
#define CC_MAX_STRING_LENGTH (1024*100)
        
        std::string ret;
        
        va_list ap;
        va_start(ap, format);
        
        char* buf = (char*)malloc(CC_MAX_STRING_LENGTH);
        if (buf != nullptr)
        {
            vsnprintf(buf, CC_MAX_STRING_LENGTH, format, ap);
            ret = buf;
            free(buf);
        }
        va_end(ap);
        
        return ret;
    }
    
} // namespace StringUtils {

#endif /* ___SystemRoot_H___ */
