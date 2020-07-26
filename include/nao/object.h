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

#include <memory>

namespace nao {
    class event;

    /**
     * @brief Base class for objects that deal with events.
     * @note Root elements can be stack- or heap-allocated,
     *       children must be heap-allocated through the add_child function
     */
    class object {
        class object_private;
        std::unique_ptr<object_private> _d;

        public:
        object(const object&) = delete;
        object& operator=(const object&) = delete;

        /**
         * @brief Construct with an optional parent object
         * @param parent - The parent object to attach to
         * @note If a parent is supplied, the parent takes ownership of `this`
         *          through a unique_ptr. The created object must not be owned
         *          anywhere else.
        */
        object(object* parent = nullptr);

        virtual ~object();

        /**
         * @brief Handles an event.
         * @return Whether the event was actually handled.
         */
        virtual bool event(event& ev);

        /**
         * @return Parent object of this object (or nullptr if there is none)
         */
        object* parent() const;

        /**
         * @brief Add a child object to this object, to be deleted when this object is deleted.
         */
        void add_child(std::unique_ptr<object> child);

        /**
         * @brief Constructs a new instance of a derived class, takes ownership
         *          and adds it as a child.
         * @param args - parameters for the object's constructor
         * @return Non-owning pointer to the newly created object
         * @note The constructor should take the parent object as last argument.
         */
        template <std::derived_from<object> T, typename... Args>
        T* add_child(Args&&... args) {
            return new T(std::forward<Args>(args)..., this);
        }
    };
}
