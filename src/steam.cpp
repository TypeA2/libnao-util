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

#define _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING

#include "nao/steam.h"
#include "nao/strings.h"

#include <windows.h>

#include <filesystem>
#include <stdexcept>

#include "vdf_parser.h"

namespace {
    // Simple auto-destructor
    struct hkey_lock {
        HKEY key = nullptr;
        ~hkey_lock() {
            if (key) {
                RegCloseKey(key);
            }
        }
    };
}

namespace nao::steam {
    std::string path() {
        hkey_lock key;
        LSTATUS status = RegOpenKeyExW(HKEY_CURRENT_USER,
            L"Software\\Valve\\Steam", 0, KEY_READ, &key.key);

        if (status != ERROR_SUCCESS) {
            throw std::runtime_error(__FUNCTION__": Key opening failed");
        }

        DWORD type, size;
        status = RegQueryValueExW(key.key,
            L"SteamPath", nullptr,
            &type, nullptr, &size);

        if (status != ERROR_SUCCESS) {
            throw std::runtime_error(__FUNCTION__": Key length retrieval failed");
        }

        if (type != REG_SZ) {
            throw std::runtime_error(__FUNCTION__": Expected REG_SZ");
        }

        if (size == 0) {
            throw std::runtime_error(__FUNCTION__": No size");
        }

        // Size includes null terminator
        std::wstring str((size / sizeof(WCHAR)) - 1, 0);
        status = RegQueryValueExW(key.key, L"SteamPath",
            nullptr, nullptr, reinterpret_cast<uint8_t*>(str.data()), &size);

        if (status != ERROR_SUCCESS) {
            throw std::runtime_error(__FUNCTION__": Key retrieval failed");
        }

        return to_utf8(str);
    }

    std::vector<std::string> install_folders() {
        auto vdf_path = std::filesystem::path {
            (path() + "\\SteamApps\\libraryfolders.vdf").c_str() }.lexically_normal();

        std::ifstream in { vdf_path };
        tyti::vdf::object root = tyti::vdf::read(in);

        std::vector<std::string> folders { root.attribs.size() - 1 };

        folders[0] = path();

        auto transform = [](const auto& path) {
            return std::filesystem::absolute(path.c_str()).lexically_normal().string();
        };

        for (size_t i = 1; i < folders.size(); ++i) {
            folders[i] = transform(root.attribs.at(std::to_string(i)));
        }

        return folders;
    }

    std::string game_path(std::string_view game) {
        for (std::string_view dir : install_folders()) {
            try {
                std::filesystem::directory_iterator it { std::string{ dir } + "\\SteamApps\\common" };
                for (const auto& entry : it) {
                    if (is_directory(entry) && entry.path().filename() == game) {
                        return absolute(entry).lexically_normal().string();
                    }
                }
            } catch (const std::filesystem::filesystem_error&) {
                // Directory does not exist
            }
        }

        // Fuck the STL's lack of operator+ for string_view, really
        throw std::runtime_error(std::string { __FUNCTION__": Path not found:" }.append(game));
    }

}