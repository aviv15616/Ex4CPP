// anksilae@gmail.com


/// @brief DescendingOrder iterator: iterates from largest to smallest.
/// @details For example, on [7, 15, 6, 1, 2], the order is: 15, 7, 6, 2, 1.
#pragma once
#include <vector>
#include <algorithm>
#include <stdexcept>

namespace containers
{
    template <typename T>
    class MyContainer;
}

namespace containers
{

    template <typename T>
    class DescendingOrder
    {
    private:
        const MyContainer<T> &container;

    public:
        DescendingOrder(const MyContainer<T> &cont) : container(cont) {}

        class Iterator
        {
        private:
            const MyContainer<T> &container;
            std::vector<size_t> indices;
            size_t current;
            size_t expected_version;

        public:
            /// @brief Initializes the iterator.
            /// @param is_end Whether the iterator points to end.
            Iterator(const MyContainer<T> &cont, bool is_end = false)
                : container(cont), current(0), expected_version(cont.get_version())
            {
                const auto &items = container.get_items();
                size_t n = items.size();
                indices.resize(n);
                for (size_t i = 0; i < n; ++i)
                    indices[i] = i;

                std::sort(indices.begin(), indices.end(),
                          [&](size_t a, size_t b)
                          {
                              return items[a] > items[b];
                          });

                if (is_end)
                {
                    current = n;
                }
            }

            /// @brief Dereferences the iterator to get the current value.
            /// @throws std::runtime_error if modified during iteration.
            /// @throws std::out_of_range if out of bounds.
            T operator*() const
            {
                if (expected_version != container.get_version())
                {
                    throw std::runtime_error("Container modified during iteration");
                }
                if (current >= indices.size())
                {
                    throw std::out_of_range("Iterator out of bounds");
                }
                return container.get_items()[indices[current]];
            }

            /// @brief Advances to the next element.
            /// @throws std::runtime_error if modified during iteration.
            /// @throws std::out_of_range if out of bounds.
            Iterator &operator++()
            {
                if (expected_version != container.get_version())
                {
                    throw std::runtime_error("Container modified during iteration");
                }
                 if(current >= indices.size())
                {
                    throw std::out_of_range("Iterator out of bounds");
                }
                ++current;
                return *this;
            }

            /// @brief Checks inequality between two iterators.
            bool operator!=(const Iterator &other) const
            {
                return current != other.current;
            }

            /// @brief Checks equality between two iterators.
            bool operator==(const Iterator &other) const
            {
                return current == other.current;
            }
        };

        /// @brief Returns iterator to beginning.
        Iterator begin() const
        {
            return Iterator(container, false);
        }

        /// @brief Returns iterator to end.
        Iterator end() const
        {
            return Iterator(container, true);
        }
    };

}
