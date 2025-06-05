///AscendingOrder iterator: iterates from smallest to largest.

// anksilae@gmail.com

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
    class AscendingOrder
    {
    private:
        const MyContainer<T> &container; ///< Reference to the container being iterated.

    public:
        /// @brief Constructs the AscendingOrder wrapper around the container.
        AscendingOrder(const MyContainer<T> &cont) : container(cont) {}

        class Iterator
        {
        private:
            const MyContainer<T> &container;
            std::vector<size_t> indices;      ///< Indices of elements in sorted ascending order.
            size_t current;                   ///< Current position in the sorted indices vector.
            size_t expected_version;          ///< Snapshot of container version to detect modifications.

        public:
            /// @brief Initializes iterator and builds sorted index map.
            /// @param is_end If true, positions the iterator at end.
            Iterator(const MyContainer<T> &cont, bool is_end = false)
                : container(cont), current(0), expected_version(cont.get_version())
            {
                const auto &items = container.get_items();
                size_t n = items.size();
                indices.resize(n);
                for (size_t i = 0; i < n; ++i)
                    indices[i] = i;

                // Sort indices by comparing container values
                std::sort(indices.begin(), indices.end(),
                          [&](size_t a, size_t b)
                          {
                              return items[a] < items[b];
                          });

                if (is_end)
                {
                    current = n;
                }
            }

            /// @brief Dereferences the iterator to return the current element.
            /// @throws std::runtime_error if container has been modified.
            /// @throws std::out_of_range if dereferencing past the end.
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

            /// @brief Moves the iterator to the next element.
            /// @throws std::runtime_error if container has been modified.
            /// @throws std::out_of_range if incrementing past the end.
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

            /// @brief Inequality comparison between iterators.
            bool operator!=(const Iterator &other) const
            {
                return current != other.current;
            }

            /// @brief Equality comparison between iterators.
            bool operator==(const Iterator &other) const
            {
                return current == other.current;
            }
        };

        /// @brief Returns an iterator pointing to the beginning of ascending order.
        Iterator begin() const
        {
            return Iterator(container, false);
        }

        /// @brief Returns an iterator representing the end.
        Iterator end() const
        {
            return Iterator(container, true);
        }
    };

}
