//
//  main.cpp
//  utilitypp
//
//  Created by tabu on 15/12/16.
//  Copyright © 2015年 tabu. All rights reserved.
//

#include <iostream>
#include "strings.hpp"

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
    // format
    std::cout << sfmt("fmt int = " << 10 << ", float = " << 3.14 << ", string value = " << "xxxx") << std::endl;
    std::cout << strings::ftime(time(NULL)) << std::endl;
    //
    std::cout << "upper_case = " << strings::upper_case("abcd") << std::endl;
    std::cout << "lower_case = " << strings::lower_case("ABCD") << std::endl;
    
    std::string text = "   \t abcd    \n";
    std::cout << "ltrim = " << strings::ltrim(text) << std::endl;
    
    text = "   \t abcd    \n";
    std::cout << "rtrim = " << strings::rtrim(text) << std::endl;
    
    text = "   \t abcd    \n";
    std::cout << "trim = " << strings::trim(text) << std::endl;
    
    text = "0000abcd0";
    std::cout << "trim = " << strings::trim(text, "0") << std::endl;
    
    std::vector<std::string> items = {"a", "b", "c", "d"};
    std::string str = strings::join(items, ",");
    std::cout << str << std::endl;
    
    items = strings::split(str, std::string(","));
    
    std::string u8str = "utf-8字符串儿";
    std::cout << u8str << ", bytes = " << u8str.length()
              << ", length = " << strings::length(u8str.c_str())
              << ", substr 4:2 = " << strings::substr(u8str, 4, 2)
              << ", substr 5:-1 = " << strings::substr(u8str, 5) << std::endl;
    
    std::wstring ucsstr = strings::unicode(u8str);
    std::cout << u8str << ", lenght = " << ucsstr.length() << std::endl;
    
    return 0;
}
