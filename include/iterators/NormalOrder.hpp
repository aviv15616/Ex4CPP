// anksilae@gmail.com


/// @brief NormalOrder iterator: iterates in original insertion order.
/// @details For example, on [7, 15, 6, 1, 2], the order is: 7, 15, 6, 1, 2.
#pragma once
#include <vector>
#include <stdexcept>
#include "../MyContainer.hpp"

namespace containers {

template <typename T>
class NormalOrder {
private:
    const MyContainer<T>& container;

public:
    NormalOrder(const MyContainer<T>& cont) : container(cont) {}

    class Iterator {
    private:
        const MyContainer<T>& container;
        const std::vector<T>& items;
        size_t current;
        size_t expected_version;

    public:
            /// @brief Initializes the iterator.
            /// @param is_end Whether the iterator points to end.
        Iterator(const MyContainer<T>& cont, bool is_end = false)
            : container(cont), items(cont.get_items()),
              current(is_end ? items.size() : 0),
              expected_version(cont.get_version()) {}

            /// @brief Dereferences the iterator to get the current value.
            /// @throws std::runtime_error if modified during iteration.
            /// @throws std::out_of_range if out of bounds.
        T operator*() const {
            if (expected_version != container.get_version()) {
                throw std::runtime_error("Container modified during iteration");
            }
            if (current >= items.size()) {
                throw std::out_of_range("Iterator out of bounds");
            }
            return items[current];
        }

        Iterator& operator++() {
            if (expected_version != container.get_version()) {
                throw std::runtime_error("Container modified during iteration");
            }
             if(current>= container.get_items().size())
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
    };

        /// @brief Returns iterator to beginning.
    Iterator begin() const {
        return Iterator(container, false);
    }

        /// @brief Returns iterator to end.
    Iterator end() const {
        return Iterator(container, true);
    }
};

}
