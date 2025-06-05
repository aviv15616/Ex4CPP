// anksilae@gmail.com


/// @brief MiddleOutOrder iterator: starts from the middle and alternates left/right.
/// @details For odd-sized [7, 15, 6, 1, 2], the order is: 6, 15, 1, 7, 2.
/// For even-sized, the middle index is rounded down.
#pragma once
#include <vector>
#include <stdexcept>
#include "../MyContainer.hpp"

namespace containers {

template<typename T>
class MiddleOutOrder {
private:
    const MyContainer<T>& container;

public:
    MiddleOutOrder(const MyContainer<T>& cont) : container(cont) {}

    class Iterator {
    private:
        const MyContainer<T>& container;
        const std::vector<T>& items;
        std::vector<size_t> indices;
        size_t current;
        size_t expected_version;

    public:
            /// @brief Initializes the iterator.
            /// @param is_end Whether the iterator points to end.
        Iterator(const MyContainer<T>& cont, bool is_end = false)
            : container(cont), items(cont.get_items()), current(0), expected_version(cont.get_version()) {

            size_t n = items.size();
            if (n == 0) return;

            int mid = n / 2;
            int left = mid - 1;
            int right = mid + 1;

            indices.push_back(mid);
            bool go_left = true;
            while (left >= 0 || right < static_cast<int>(n)) {
                if (go_left && left >= 0) {
                    indices.push_back(left--);
                } else if (!go_left && right < static_cast<int>(n)) {
                    indices.push_back(right++);
                }
                go_left = !go_left;
            }

            if (is_end)
                current = indices.size();
        }

            /// @brief Dereferences the iterator to get the current value.
            /// @throws std::runtime_error if modified during iteration.
            /// @throws std::out_of_range if out of bounds.
        T operator*() const {
            if (expected_version != container.get_version()) {
                throw std::runtime_error("Container modified during iteration");
            }
            if (current >= indices.size()) {
                throw std::out_of_range("Iterator out of bounds");
            }
            return items[indices[current]];
        }

        Iterator& operator++() {
            if (expected_version != container.get_version()) {
                throw std::runtime_error("Container modified during iteration");
            }
             if(current>= indices.size())
                {
                    throw std::out_of_range("Iterator out of bounds");
                }
            ++current;
            return *this;
        }

            /// @brief Checks inequality between two iterators.
        bool operator!=(const Iterator& other) const {
            return current != other.current;
        }

            /// @brief Checks equality between two iterators.
        bool operator==(const Iterator& other) const {
            return current == other.current;
        }
    }; // סיום class Iterator

        /// @brief Returns iterator to beginning.
    Iterator begin() const {
        return Iterator(container, false);
    }

        /// @brief Returns iterator to end.
    Iterator end() const {
        return Iterator(container, true);
    }
}; // סיום class MiddleOutOrder

}
