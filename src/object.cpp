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

#include "nao/object.h"

#include <vector>

namespace nao {
    class object::object_private {
        public:
        object_private(object* parent) : parent { parent } { }

        object* parent;
        std::vector<std::unique_ptr<object>> children;
    };

    object::object(object* parent) : _d { std::make_unique<object_private>(parent) } {
        if (parent) {
            parent->add_child(std::unique_ptr<object> { this });
        }
    }

    object::~object() {
        
    }

    bool object::event(nao::event& ev) {
        return false;
    }

    object* object::parent() const {
        return _d->parent;
    }

    void object::add_child(std::unique_ptr<object> child) {
        (void) this;
        _d->children.emplace_back(std::move(child));
    }
}
