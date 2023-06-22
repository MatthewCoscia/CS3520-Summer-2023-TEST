#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <iostream>
#include <vector>
#include <algorithm>

template<typename T>
class Repository {
private:
    std::vector<T> entries;

public:
    // Default constructor
    Repository() {}

    // Destructor
    ~Repository() {}

    // Copy constructor
    Repository(const Repository& other) {
        entries = other.entries;
    }

    // Move constructor
    Repository(Repository&& other) noexcept {
        entries = std::move(other.entries);
    }

    // Copy assignment operator
    Repository& operator=(const Repository& other) {
        if (this != &other) {
            entries = other.entries;
        }
        return *this;
    }

    // Move assignment operator
    Repository& operator=(Repository&& other) noexcept {
        if (this != &other) {
            entries = std::move(other.entries);
        }
        return *this;
    }

    // Add a new item to the repository or update if already present
    void addOrUpdate(const T& item) {
        auto it = std::find(entries.begin(), entries.end(), item);
        if (it != entries.end()) {
            *it = item;
        } else {
            entries.push_back(item);
        }
    }

    // Add a list of items to the repository or update if already present
    template<typename Container>
    void addOrUpdate(const Container& items) {
        for (const auto& item : items) {
            addOrUpdate(item);
        }
    }

    // Determine the order (position) of the item in the repository
    // Return -1 if item not found
    int getOrder(const T& item) const {
        auto it = std::find(entries.begin(), entries.end(), item);
        if (it != entries.end()) {
            return std::distance(entries.begin(), it);
        }
        return -1;
    }

    // Remove an item from the repository
    void remove(const T& item) {
        entries.erase(std::remove(entries.begin(), entries.end(), item), entries.end());
    }

    // Remove a list of items from the repository
    template<typename Container>
    void remove(const Container& items) {
        for (const auto& item : items) {
            remove(item);
        }
    }

    // Get the number of items in the repository
    size_t getCount() const {
        return entries.size();
    }

    // Overload the insertion operator for printing the repository
    friend std::ostream& operator<<(std::ostream& os, const Repository& repo) {
        for (const auto& item : repo.entries) {
            os << item << std::endl;
        }
        return os;
    }
};

#endif

