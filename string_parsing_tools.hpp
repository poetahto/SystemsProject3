// String parsing tools
// Date: 6-Nov-23
// Author: Daniel Walls
// RedID: 825776127

#ifndef ASSIG2_STRING_PARSING_TOOLS_HPP
#define ASSIG2_STRING_PARSING_TOOLS_HPP

#include <string>
#include <sstream>
#include <iomanip>

// Generic utilities for de-serializing a text based file.
namespace StringParsingTools
{
    std::string getBetween(const std::string& value, char delimiter);
    bool tryGetArg(const std::string& line, size_t index, std::string* outResult, char delimiter = ' ');
    bool tryGetInt(const std::string& hex, int& outResult);

    template<typename T>
    std::string getHex(T value, bool padZeros = true)
    {
        std::ostringstream ss {};
        if (padZeros) {
            ss << std::hex << std::setfill('0') << std::setw(4) << std::uppercase << value;
        }
        else {
            ss << std::hex << std::uppercase << value;
        }
        return ss.str();
    }
}

#endif // ASSIG2_STRING_PARSING_TOOLS_HPP