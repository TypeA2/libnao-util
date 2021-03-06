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

#include "nao/strings.h"

#include <windows.h>

#include <sstream>
#include <iomanip>
#include <chrono>

namespace nao {
    std::string bytes(size_t n) {
        std::stringstream ss;
        ss << std::setprecision(3) << std::fixed;

        std::string_view suffix;
        if (n > 0x1000000000000000) {
            ss << ((n >> 50) / 1024.);
            suffix = "EiB";
        } else if (n > 0x4000000000000) {
            ss << ((n >> 40) / 1024.L);
            suffix = "PiB";
        } else if (n > 0x10000000000) {
            ss << ((n >> 30) / 1024.);
            suffix = "TiB";
        } else if (n > 0x40000000) {
            ss << ((n >> 20) / 1024.);
            suffix = "GiB";
        } else if (n > 0x100000) {
            ss << ((n >> 10) / 1024.);
            suffix = "MiB";
        } else if (n > 0x400) {
            ss << (n / 1024.);
            suffix = "KiB";
        } else {
            ss << n;
            suffix = "bytes";
        }

        // Remove trailing whitespace and zeroes
        std::string s = ss.str();

        // string_view does not support operator+
        // https://stackoverflow.com/a/47735624/8662472
        return (s.erase(s.find_last_not_of("0.") + 1) + ' ').append(suffix);
    }

    std::string bits(size_t n) {
        std::stringstream ss;
        ss << std::setprecision(3) << std::fixed;

        std::string_view suffix;
        if (n > 0x1000000000000000) {
            ss << ((n >> 50) / 1024.);
            suffix = "Eibit";
        } else if (n > 0x4000000000000) {
            ss << ((n >> 40) / 1024.L);
            suffix = "Pibit";
        } else if (n > 0x10000000000) {
            ss << ((n >> 30) / 1024.);
            suffix = "Tibit";
        } else if (n > 0x40000000) {
            ss << ((n >> 20) / 1024.);
            suffix = "Gibit";
        } else if (n > 0x100000) {
            ss << ((n >> 10) / 1024.);
            suffix = "Mibit";
        } else if (n > 0x400) {
            ss << (n / 1024.);
            suffix = "Kibit";
        } else {
            ss << n;
            suffix = "bits";
        }

        // Remove trailing whitespace and zeroes
        std::string s = ss.str();

        // string_view does not support operator+
        // https://stackoverflow.com/a/47735624/8662472
        return (s.erase(s.find_last_not_of("0.") + 1) + ' ').append(suffix);
    }

    std::string percent(double v) {
        return std::to_string(static_cast<int64_t>(round(v * 100.))) + '%';
    }

    std::string time_hours(uint64_t nanoseconds, bool add_ms) {
        std::stringstream ss;
        ss.fill('0');

        std::chrono::nanoseconds ns { nanoseconds };

        auto hours = std::chrono::duration_cast<std::chrono::hours>(ns);
        ns -= hours;
        auto minutes = std::chrono::duration_cast<std::chrono::minutes>(ns);
        ns -= minutes;
        auto seconds = std::chrono::duration_cast<std::chrono::seconds>(ns);


        ss << hours.count() << ':'
            << std::setw(2)
            << minutes.count() << ':'
            << seconds.count();

        if (add_ms) {
            ns -= seconds;
            auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(ns);

            ss << '.' << std::setw(3) << milliseconds.count();
        }

        return ss.str();
    }

    std::string time_minutes(uint64_t nanoseconds, bool add_ms) {
        std::stringstream ss;
        ss.fill('0');

        std::chrono::nanoseconds ns { nanoseconds };

        auto minutes = std::chrono::duration_cast<std::chrono::minutes>(ns);
        ns -= minutes;
        auto seconds = std::chrono::duration_cast<std::chrono::seconds>(ns);
        ss << minutes.count() << ':'
            << std::setw(2) << seconds.count();

        if (add_ms) {
            ns -= seconds;
            auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(ns);

            ss << '.' << std::setw(3) << milliseconds.count();
        }

        return ss.str();
    }

    std::wstring to_utf16(std::string_view str) {
        int size = MultiByteToWideChar(
            CP_UTF8, MB_ERR_INVALID_CHARS,
            str.data(), static_cast<int>(str.size()),
            nullptr, 0);

        std::wstring result(size, '\0');

        int converted = MultiByteToWideChar(
            CP_UTF8, MB_ERR_INVALID_CHARS,
            str.data(), static_cast<int>(str.size()),
            result.data(), size);

        if (converted != size) {
            throw std::runtime_error("failed converting narrow string to wide string");
        }

        return result;
    }

    std::string to_utf8(std::wstring_view str) {
        int size = WideCharToMultiByte(
            CP_UTF8, WC_COMPOSITECHECK | WC_NO_BEST_FIT_CHARS,
            str.data(), static_cast<int>(str.size()),
            nullptr, 0, nullptr, nullptr);

        std::string result(size, '\0');

        int converted = WideCharToMultiByte(
            CP_UTF8, WC_COMPOSITECHECK | WC_NO_BEST_FIT_CHARS,
            str.data(), static_cast<int>(str.size()),
            result.data(), size, nullptr, nullptr);

        if (converted != size) {
            throw std::runtime_error("failed converting wide string to narrow string");
        }

        return result;
    }
}
