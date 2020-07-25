/*  This file is part of libnao-util.

    libnao-util is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    libnao-util is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with libnao-util.  If not, see <https://www.gnu.org/licenses/>.   */

#pragma once

#include <string>

namespace nao {
    /**
     * @brief Converts a byte count into a human-readable format.
     * @param n - The number of bytes.
     */
    std::string bytes(size_t n);

    /**
     * @brief Converts a bit count into a human-readable format.
     * @param n - The number of bits.
     */
    std::string bits(size_t n);

    /**
     * @brief Formats the fraction `v` as a percentage.
     */
    std::string percent(double v);

    /**
     * @brief Formats the specified amount of nanoseconds with the hh:mm:ss format.
     * @param add_ms - If true, the amount of milliseconds is also included.
     */
    std::string time_hours(uint64_t nanoseconds, bool add_ms = true);

    /**
     * @brief Formats the specified amount of nanoseconds with the mm:ss format.
     * @param add_ms - If true, the amount of milliseconds is also included.
     */
    std::string time_minutes(uint64_t nanoseconds, bool add_ms = true);

    /**
     * @brief Converts a UTF-8 encoded string_view to a UTF-16 encoded string.
     */
    std::wstring to_utf16(std::string_view str);

    /**
     * @brief Converts a UTF-16 encoded string_view to a UTF-8 encoded string.
     */
    std::string to_utf8(std::wstring_view str);
}
