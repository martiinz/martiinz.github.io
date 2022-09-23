---
title: "Templates Example"
excerpt: "Example as elaborated in 'Professional C++, Marc Gregoire'"
tags:
  - cpp
categories:
  - cpp
---

## Basic Template Example

```c++
#include <iostream>
#include <chrono>
#include <thread>
#include <optional>
#include <vector>
#include <utility>

template <typename T>
class Grid
{
public:
    explicit Grid(size_t width = DefaultWidth,
        size_t height = DefaultHeight);
    virtual ~Grid() = default;

    // Explicitly default a copy constructor and assignment operator.
    Grid(const Grid& src) = default;
    Grid& operator=(const Grid& rhs) = default;

    // Explicitly default a move constructor and assignment operator.
    Grid(Grid&& src) = default;
    Grid& operator=(Grid&& rhs) = default;

    std::optional<T>& at(size_t x, size_t y);
    const std::optional<T>& at(size_t x, size_t y) const;

    size_t getHeight() const { return m_height; }
    size_t getWidth() const { return m_width; }

    static const size_t DefaultWidth { 10 };
    static const size_t DefaultHeight { 10 };

private:
    void verifyCoordinate(size_t x, size_t y) const;
    std::vector<std::vector<std::optional<T>>> m_cells;
    size_t m_width { 0 }, m_height { 0 };
};

template <typename T>
Grid<T>::Grid(size_t width, size_t height)
    : m_width { width }, m_height { height }
{
    m_cells.resize(m_width);
    for (auto& column : m_cells) {
        column.resize(m_height);
    }
}

template <typename T>
void Grid<T>::verifyCoordinate(size_t x, size_t y) const
{
    if (x >= m_width) {
        throw std::out_of_range {
            "{x} must be less than {m_width}."}; // x, m_width) 
    }
    if (y >= m_height) {
        throw std::out_of_range {
            "{y} must be less than {m_height}."}; //, y, m_height) };
    }
}

template <typename T>
const std::optional<T>& Grid<T>::at(size_t x, size_t y) const
{
    verifyCoordinate(x, y);
    return m_cells[x][y];
}

template <typename T>
std::optional<T>& Grid<T>::at(size_t x, size_t y)
{
    return const_cast<std::optional<T>&>(std::as_const(*this).at(x, y));
}

// Explicit template instantiation helps with finding errors,
// as it forces all your class template methods to be compiled
// even when unused.
template class Grid<int>;
template class Grid<std::string>;
template class Grid<std::vector<int>>;

int main()
{
    std::cout << "start" << std::endl; 

    Grid<int> myIntGrid; // Declares a grid that stores ints,

    // using default arguments for the constructor.
    Grid<double> myDoubleGrid { 11, 11 }; // Declares an 11x11 Grid of doubles.
    
    auto d = myDoubleGrid.at(10, 0).value_or(0);
    std::cout << "doublegrid range: " << d << std::endl;

    myIntGrid.at(0, 0) = 10;

    int x { myIntGrid.at(0, 0).value_or(0) };

    std::cout << "grid (0,0) = " << x << std::endl;

    Grid<int> grid2 { myIntGrid }; // Copy constructor
    Grid<int> anotherIntGrid;

    anotherIntGrid = grid2; // Assignment operator

}
```

## Method Template Example

```c++
#include <iostream>
#include <chrono>
#include <thread>
#include <optional>
#include <vector>
#include <utility>

template <typename T>
class Grid
{
public:
    explicit Grid(size_t width = DefaultWidth,
        size_t height = DefaultHeight);
    virtual ~Grid() = default;

    // Explicitly default a copy constructor and assignment operator.
    Grid(const Grid& src) = default;
    Grid& operator=(const Grid& rhs) = default;

    // Explicitly default a move constructor and assignment operator.
    Grid(Grid&& src) = default;
    Grid& operator=(Grid&& rhs) = default;

    std::optional<T>& at(size_t x, size_t y);
    const std::optional<T>& at(size_t x, size_t y) const;

    // templatized copy constructor to convert types
    template <typename E>
    Grid(const Grid<E>& src);

    // templatized assignment constructor to convert
    template <typename E>
    Grid& operator=(const Grid<E>& rhs);

    void swap(Grid& other) noexcept;

    size_t getHeight() const { return m_height; }
    size_t getWidth() const { return m_width; }

    static const size_t DefaultWidth { 10 };
    static const size_t DefaultHeight { 10 };

private:
    void verifyCoordinate(size_t x, size_t y) const;
    std::vector<std::vector<std::optional<T>>> m_cells;
    size_t m_width { 0 }, m_height { 0 };
};

template <typename T>
Grid<T>::Grid(size_t width, size_t height)
    : m_width { width }, m_height { height }
{
    m_cells.resize(m_width);
    for (auto& column : m_cells) {
        column.resize(m_height);
    }
}

template <typename T>
void Grid<T>::verifyCoordinate(size_t x, size_t y) const
{
    if (x >= m_width) {
        throw std::out_of_range {
            "{x} must be less than {m_width}."}; // x, m_width) 
    }
    if (y >= m_height) {
        throw std::out_of_range {
            "{y} must be less than {m_height}."}; //, y, m_height) };
    }
}

template <typename T>
const std::optional<T>& Grid<T>::at(size_t x, size_t y) const
{
    verifyCoordinate(x, y);
    return m_cells[x][y];
}

template <typename T>
std::optional<T>& Grid<T>::at(size_t x, size_t y)
{
    return const_cast<std::optional<T>&>(std::as_const(*this).at(x, y));
}

template <typename T>
template <typename E>
Grid<T>::Grid(const Grid<E>& src)
    : Grid { src.getWidth(), src.getHeight() }
{
    std::cout << "templ{}" << std::endl;
    // The ctor-initializer of this constructor delegates first to the
    // non-copy constructor to allocate the proper amount of memory.
    // The next step is to copy the data.
    for (size_t i { 0 }; i < m_width; i++) {
        for (size_t j { 0 }; j < m_height; j++) {
            m_cells[i][j] = src.at(i, j);
        }
    }
}

template <typename T>
void Grid<T>::swap(Grid& other) noexcept
{
    std::swap(m_width, other.m_width);
    std::swap(m_height, other.m_height);
    std::swap(m_cells, other.m_cells);
}

template <typename T>
template <typename E>
Grid<T>& Grid<T>::operator=(const Grid<E>& rhs)
{
    std::cout << "tmpl =" << std::endl;
    // Copy-and-swap idiom
    Grid<T> temp { rhs }; // Do all the work in a temporary instance.
    swap(temp); // Commit the work with only non-throwing operations.
    return *this;
}

// Explicit template instantiation helps with finding errors,
// as it forces all your class template methods to be compiled
// even when unused.
template class Grid<int>;
template class Grid<std::string>;
template class Grid<std::vector<int>>;

int main()
{
    std::cout << "start" << std::endl; 

    Grid<int> myIntGrid; // Declares a grid that stores ints,

    // using default arguments for the constructor.
    Grid<double> myDoubleGrid { 11, 11 }; // Declares an 11x11 Grid of doubles.
    
    auto d = myDoubleGrid.at(10, 0).value_or(0);
    std::cout << "doublegrid range: " << d << std::endl;

    myIntGrid.at(0, 0) = 10;

    int x { myIntGrid.at(0, 0).value_or(0) };

    std::cout << "grid (0,0) = " << x << std::endl;

    Grid<int> grid2 { myIntGrid }; // Copy constructor
    Grid<int> anotherIntGrid;

    anotherIntGrid = grid2; // Assignment operator

    std::cout << "***=***" << std::endl;
    myIntGrid = myDoubleGrid;

    std::cout << "***{}***" << std::endl;
    Grid<int> anotherGrid{myDoubleGrid};

}
```
