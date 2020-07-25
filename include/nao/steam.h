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
#include <vector>

namespace nao::steam {
    /**
     * @return Current installation path for Steam
     */
    std::string path();

    /**
     * @return All folders steam has registered for game installs.
     */
    std::vector<std::string> install_folders();

    /**
     * @brief Retrieve the installation path for a specific game.
     * @param game - The game to retrieve
     * @note The parameter `game` refers to the game's install folder name.
     */
    std::string game_path(std::string_view game);
}
