/**
 * Helper functions for converting stuff (source)
 */

#include "helpers/conversion.hpp"

#include <cmath>
#include <cstddef>
#include <cstdint>
#include <string>

namespace helpers::conversion {

bool isStdStringValidUnsignedInt(std::string string) {
    for (char c : string) {
        switch (c) {
            case '1':
                break;
            case '2':
                break;
            case '3':
                break;
            case '4':
                break;
            case '5':
                break;
            case '6':
                break;
            case '7':
                break;
            case '8':
                break;
            case '9':
                break;
            default:
                return false;
        }
    }
    return true;
}
std::uint32_t stdStringToInt(std::string string) {
    std::uint32_t returnable {};
    for (std::size_t i {}; i < string.length(); ++i) {
        int number {string[i] - 48};
        double placeValue {std::pow(10.0, i)};
        number *= placeValue;
        returnable += number;
    }
    return returnable;
}

}
