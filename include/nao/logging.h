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

#include <sstream>

/**
 * Asynchronous logging, function interface
 */

namespace nao {
    /**
     * @brief Prints a string to the standard output stream.
     * @param str - The string to print.
     */
    void cout(std::string str);

    /**
     * @brief Variadic version of cout, for printing multiple arguments, formatted with a stringstream.
     */
    template <typename... Args>
    void cout(Args&&... args) {
        std::stringstream ss;
        ((ss << args << ' '), ...);
        auto str = ss.str();
        // Select the correct overload and remove the trailing space
        static_cast<void(*)(std::string)>(cout)(str.substr(0, str.size() - 1));
    }

    /**
     * @brief Variadic version of cout, which additionally automatically ads a newline at the end.
     */
    template <typename... Args>
    void coutln(Args&&... args) {
        cout(args..., '\n');
    }
}
