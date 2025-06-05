/// @file MyContainer.hpp
/// @brief Defines a generic container class with six different custom iterator types.
/// @author
/// anksilae@gmail.com

// anksilae@gmail.com


#pragma once
#include <vector>
#include <iostream>
#include <stdexcept>
#include <algorithm>

#include "iterators/AscendingOrder.hpp"
#include "iterators/DescendingOrder.hpp"
#include "iterators/SideCrossOrder.hpp"
#include "iterators/ReverseOrder.hpp"
#include "iterators/NormalOrder.hpp"
#include "iterators/MiddleOutOrder.hpp"

namespace containers
{

    template <typename T = int>
    class MyContainer
    {
    private:
        std::vector<T> items;
        size_t version = 0; // מזהה גרסה של הקונטיינר

    public:
        /// @brief Adds a value to the container and increments version.
        /// @param value The element to add.
        void add(const T &value)
        {
            items.push_back(value);
            version++;
        }

        /// @brief Removes all occurrences of a value from the container.
        /// @param value The element to remove.
        /// @throws std::runtime_error if the element does not exist.
        void remove(const T &value)
        {
            auto original_size = items.size();
            items.erase(std::remove(items.begin(), items.end(), value), items.end());
            if (items.size() == original_size)
            {
                throw std::runtime_error("Element not found");
            }
            version++;
        }

        /// @brief Returns the number of elements in the container.
        size_t size() const
        {
            return items.size();
        }

        /// @brief Returns a const reference to the underlying items vector.
        const std::vector<T> &get_items() const
        {
            return items;
        }

        /// @brief Returns a modifiable reference to the underlying items vector.
        std::vector<T> &get_items()
        {
            return items;
        }

        /// @brief Returns the current version of the container.
        size_t get_version() const
        {
            return version;
        }

        /// @brief Prints the container in [a, b, c] format.
        friend std::ostream &operator<<(std::ostream &os, const MyContainer<T> &container)
        {
            os << "[";
            for (size_t i = 0; i < container.items.size(); ++i)
            {
                os << container.items[i];
                if (i < container.items.size() - 1)
                    os << ", ";
            }
            os << "]";
            return os;
        }

        // פונקציה שמחזירה מופע של AscendingOrder<T>
        /// @brief Returns an AscendingOrder iterator over the container.
        AscendingOrder<T> Ascending() const
        {
            return AscendingOrder<T>(*this);
        }

        /// @brief Returns a DescendingOrder iterator over the container.
        DescendingOrder<T> Descending() const
        {
            return DescendingOrder<T>(*this);
        }
        /// @brief Returns a MiddleOutOrder iterator over the container.
        MiddleOutOrder<T> MiddleOut() const
        {
            return MiddleOutOrder<T>(*this);
        }
        /// @brief Returns a NormalOrder iterator over the container.
        NormalOrder<T> Normal() const
        {
            return NormalOrder<T>(*this);
        }
        /// @brief Returns a ReverseOrder iterator over the container.
        ReverseOrder<T> Reverse() const
        {
            return ReverseOrder<T>(*this);
        }
        /// @brief Returns a SideCrossOrder iterator over the container.
        SideCrossOrder<T> SideCross() const
        {
            return SideCrossOrder<T>(*this);
        }
    };

}
