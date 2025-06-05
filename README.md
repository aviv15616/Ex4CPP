# Ex4 – Custom Container with Iterators

## Overview

This project implements a generic container class `MyContainer<T>` in C++20, along with six custom iterators that traverse the container in various logical orders.

The assignment demonstrates use of:
- Templates and custom containers
- Iterator design patterns
- Safe iteration using version control
- Exception handling
- Full unit testing with doctest
- Memory safety (checked with Valgrind)

---

## Iterators Implemented

1. **AscendingOrder** – Elements are iterated in ascending value order.
2. **DescendingOrder** – Elements are iterated in descending value order.
3. **NormalOrder** – Elements are iterated in original insertion order.
4. **ReverseOrder** – Elements are iterated in reverse insertion order.
5. **MiddleOutOrder** – Elements are iterated from the middle outward.
6. **SideCrossOrder** – Alternates between smallest and largest remaining elements.

---

## Features

- `add(value)` – Adds a value to the container.
- `remove(value)` – Removes all occurrences of the value; throws if not found.
- Safe iterator invalidation: all iterators monitor the version of the container.
- Throws `std::runtime_error` on modification during iteration.
- Throws `std::out_of_range` if accessing beyond iterator bounds.
- All iterators are tested for behavior with:
  - Empty container
  - Single element
  - Modification during iteration
  - Out-of-bounds access

---

## Operators

The MyContainer<T> class implements several operators to enhance usability and integration with standard C++ patterns:


- `operator<<` – Overloaded to allow direct printing of the container’s contents using std::ostream. Displays elements in logical order (e.g., [1, 2, 3]).
Iterator Operators – All custom iterators support:

- `operator*` – Dereferences the current element.
- `operator++` – Advances to the next element; throws std::out_of_range if incremented past end.
- `operator== / operator!=` – Compares positions of iterators within the same container.
Exception Safety – operator* and operator++ throw if the container was structurally modified after the iterator was created.
These operators ensure compatibility with range-based for-loops and standard iteration practices.


---
## Project Structure

```
Ex4/
│
├── include/
│   ├── MyContainer.hpp
│   └── iterators/
│       ├── AscendingOrder.hpp
│       ├── DescendingOrder.hpp
│       ├── NormalOrder.hpp
│       ├── ReverseOrder.hpp
│       ├── SideCrossOrder.hpp
│       └── MiddleOutOrder.hpp
│
│
├── build/          # All compiled output will be placed here
│
├── Demo.cpp        # Sample demo run 
├── Tests.cpp       # Contains all doctest test cases
├── Makefile
└── README.md
```

---

## How to Build and Run

### ⚙️ Requirements

- GCC with C++20 support
- `make`
- `valgrind` (optional, for leak checks)


### 🛠️ Build and Test

```bash
make            # Builds and runs both the main demo and tests
make test       # Builds and runs only the test suite
make Main       # Builds and runs only the demo +
make valgrind   # Runs test suite through valgrind to check memory safe usage
make clean      # Cleans all build artifacts 
```

---

## Notes

- Iterators detect any structural modification of the container using a version number (`size_t version`).
- All comparisons between iterators check only the position (`current`) and assume the same container context.
- All code complies with `-Wall -Wextra -pedantic` and passes leak-checking via Valgrind.

---

## ⚠️ Important Note – Types Must Be Comparable

The `MyContainer<T>` class and its iterators assume that type `T` supports comparison operators (`<`, `>`, `==`, etc.).  
This is not enforced at compile time when adding elements, but attempting to use iterators like `AscendingOrder` or `SideCrossOrder` will result in a **compilation error** if `T` is not comparable.

✅ Examples of supported types: `int`, `double`, `std::string`  
❌ Unsupported: custom types like `X` that do **not** define comparison operators.

---

## Author

Aviv Neeman
anksilae@gmail.com