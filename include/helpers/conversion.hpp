/**
 * Helper functions for converting stuff (header)
 */

#ifndef HELPERS_CONVERSION_HPP
#define HELPERS_CONVERSION_HPP

#include <cstdint>
#include <string>

namespace helpers::conversion {

bool isStdStringValidUnsignedInt(const std::string& string);
std::uint32_t stdStringToInt(const std::string& string);

}

#endif
