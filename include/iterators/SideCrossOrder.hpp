// anksilae@gmail.com


/// @brief SideCrossOrder iterator: alternates between smallest and largest values.
/// @details For example, on [7, 15, 6, 1, 2], the order is: 1, 15, 2, 7, 6.
#pragma once
#include <vector>
#include <algorithm>
#include <stdexcept>
#include "../MyContainer.hpp"

namespace containers
{

    template <typename T>
    class SideCrossOrder
    {
    private:
        const MyContainer<T> &container;

    public:
        SideCrossOrder(const MyContainer<T> &cont) : container(cont) {}

        class Iterator
        {
        private:
            const MyContainer<T> &container;
            const std::vector<T> &items;
            std::vector<size_t> indices;
            size_t current;
            size_t expected_version;

        public:
            /// @brief Initializes the iterator.
            /// @param is_end Whether the iterator points to end.
            Iterator(const MyContainer<T> &cont, bool is_end = false)
                : container(cont), items(cont.get_items()), current(0),
                  expected_version(cont.get_version())
            {

                size_t n = items.size();
                if (n == 0) return;  // אם אין פריטים, אין צורך להמשיך
                std::vector<size_t> sorted_indices(n);
                for (size_t i = 0; i < n; ++i)
                    sorted_indices[i] = i;

                std::sort(sorted_indices.begin(), sorted_indices.end(),
                          [&](size_t a, size_t b)
                          {
                              return items[a] < items[b];
                          });

                // בניית סדר cross: מינימום, מקסימום, 2nd min, 2nd max...
                size_t left = 0, right = n - 1;
                while (left <= right)
                {
                    if (left == right)
                    {
                        indices.push_back(sorted_indices[left]);
                    }
                    else
                    {
                        indices.push_back(sorted_indices[left]);
                        indices.push_back(sorted_indices[right]);
                    }
                    ++left;
                    if (right > 0)
                        --right;
                }

                if (is_end)
                {
                    current = indices.size();
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

                return items[indices[current]];
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
                if (current >= indices.size())
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
