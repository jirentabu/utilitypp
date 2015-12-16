//
//  strings.hpp
//  utilitypp
//  -- fmt
//  -- codecvt
//  -- uppercase, lowercase, join, split,trim
//  Created by tabu on 15/12/16.
//  Copyright © 2015年 tabu. All rights reserved.
//

#ifndef __UTILITYPP_STRINGS_H__
#define __UTILITYPP_STRINGS_H__

#include "platform.h"
#include <string>
#include <vector>
#include <algorithm>
#include <strstream>
#include <locale>
#include <codecvt>

#define sfmt(exp) (strings::fmt() << exp).str()

namespace strings
{
    typedef std::ostrstream fmt;
    
    inline std::string format(const char* fmt, ...)
    {
        va_list args;
        va_start(args, fmt);
        int bufsize  = vsnprintf(NULL, 0, fmt, args);
        va_end(args);
        
        va_start(args, fmt);
        std::string str(bufsize, '\0');
        vsnprintf(&str[0], bufsize + 1, fmt, args);
        va_end(args);
        
        return str;
    }

    inline std::string ftime(time_t val, const char* fmt = "%Y-%m-%d %H:%M:%S")
    {
        std::string result;
        result.resize(32, '\0');
        struct tm newtime;
#ifdef __PLATFORM_WINDOWS__
        errno_t err = localtime_s(&newtime, &val);
#else
        localtime_r(&val, &newtime);
#endif
        strftime(&result[0], 32, fmt, &newtime);
        return result;
    }
    
    
    inline std::string& lower_case(std::string &ss)
    {
        std::locale loc;
        for_each(ss.begin(), ss.end(), [&loc](char& ch){ ch = std::tolower(ch, loc); });
        return ss;
    }
    
    inline std::string lower_case(const char* s)
    {
        std::string str(s);
        return lower_case(str);
    }
    
    inline std::string& upper_case(std::string &ss)
    {
        std::locale loc;
        for_each(ss.begin(), ss.end(), [&loc](char& ch){ ch = std::toupper(ch, loc); });
        return ss;
    }
    
    inline std::string upper_case(const char* s)
    {
        std::string str(s);
        return upper_case(str);
    }
    
    inline std::string& ltrim(std::string& str, const char* chars = " \t\r\n")
    {
        const char* last = chars + ::strlen(chars);
        std::string::iterator p = std::find_if(str.begin(), str.end(), [=](char c){
            return std::find(chars, last, c) == last;
        });
        str.erase(str.begin(), p);
        return str;
    }
    
    inline std::string& rtrim(std::string& str, const char* chars = " \t\r\n")
    {
        const char* last = chars + ::strlen(chars);
        std::string::reverse_iterator p = std::find_if(str.rbegin(), str.rend(), [=](char c){
            return std::find(chars, last, c) == last;
        });
        str.erase(p.base(), str.end());
        return str;
    }
    
    inline std::string& trim(std::string& ss, const char* chars = " \t\r\n")
    {
        ltrim(rtrim(ss, chars), chars);
        return ss;
    }
    
    template<class _Elem>
    std::vector<std::basic_string<_Elem>> split(const std::basic_string<_Elem> &src, const std::basic_string<_Elem>& delimit)
    {
        __ASSERT(!delimit.empty());
        typedef typename std::basic_string<_Elem>::size_type size_type;
        std::vector<std::basic_string<_Elem>> v;
        if(src.empty()) return v;
        
        
        size_type deli_len = delimit.length();
        size_type index = src.npos, last_search_position = 0;
        while( (index = src.find(delimit, last_search_position)) != src.npos )
        {
            if(index != last_search_position)
                v.push_back( src.substr(last_search_position, index - last_search_position) );
            last_search_position = index + deli_len;
        }
        std::basic_string<_Elem> last_one = src.substr(last_search_position);
        if(!last_one.empty())
            v.push_back(last_one);
        
        return v;
    }
    
    template<class _Elem>
    std::basic_string<_Elem> join(const std::vector<std::basic_string<_Elem>>& v, const _Elem* delimit)
    {
        __ASSERT(delimit != NULL);
        
        std::basic_string<_Elem> str;
        if(v.empty()) return str;
        typename std::vector<std::basic_string<_Elem>>::const_iterator it   = v.begin();
        typename std::vector<std::basic_string<_Elem>>::const_iterator last = v.end() - 1;
        for (;it != last;++it)
        {
            str.append(*it);
            str.append(delimit);
        }
        str.append(*last);
        return str;
    }
    
    inline std::string utf8(const wchar_t* src)
    {
        std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>, wchar_t> utf16conv;
        return utf16conv.to_bytes(src);
    }
    
    inline std::string utf8(const std::wstring& src)
    {
        return utf8(src.c_str());
    }
    
    inline std::wstring unicode(const char* src)
    {
        std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>, wchar_t> utf16conv;
        return utf16conv.from_bytes(src);
    }
    
    inline std::wstring unicode(const std::string& src)
    {
        return unicode(src.c_str());
    }
}

#endif /* __UTILITYPP_STRINGS_H__ */
