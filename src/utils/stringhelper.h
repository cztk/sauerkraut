//
// Created by ztk on 2021-06-10.
//

#ifndef SAUERKRAUT_STRINGHELPER_H
#define SAUERKRAUT_STRINGHELPER_H

#include <cstdarg>
#include <string>
#include <sstream>
#include <vector>
#include <unordered_set>

namespace utils {

    class StringHelper {
    public:
        static const std::string vFormat(const std::string sFormat, ...) {

            const char *const zcFormat = sFormat.c_str();

            // initialize use of the variable argument array
            va_list vaArgs;
            va_start(vaArgs, sFormat);

            // reliably acquire the size from a copy of
            // the variable argument array
            // and a functionally reliable call
            // to mock the formatting
            va_list vaCopy;
            va_copy(vaCopy, vaArgs);
            const int iLen = std::vsnprintf(nullptr, 0, zcFormat, vaCopy);
            va_end(vaCopy);

            // return a formatted string without
            // risking memory mismanagement
            // and without assuming any compiler
            // or platform specific behavior
            std::vector<char> zc(iLen + 1);
            std::vsnprintf(zc.data(), zc.size(), zcFormat, vaArgs);
            va_end(vaArgs);
            return std::string(zc.data(), zc.size() - 1);
        }
        static std::vector<std::string> string_split_toVec(const std::string &str) {
            std::vector<std::string> result;
            std::istringstream iss(str);
            for (std::string s; iss >> s; )
                result.push_back(s);
            return result;
        }
        static std::unordered_set<std::string> string_split_toUset(const std::string &str) {
            std::unordered_set<std::string> result;
            std::istringstream iss(str);
            for (std::string s; iss >> s; )
                result.insert(s);
            return result;
        }
    };
}

#endif //SAUERKRAUT_STRINGHELPER_H
