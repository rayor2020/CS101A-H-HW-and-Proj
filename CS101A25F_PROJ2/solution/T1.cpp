#include <iostream>
#include <string>
#include <utility>
#include <vector>

template <typename K>
class HashTable {
public:
    struct Entry {
        K key;
        bool isOccupied;

        Entry()
            : isOccupied(false)
        {
        }
    };

    size_t capacity, size;
    std::vector<Entry> table;
    const double LOAD_FACTOR_THRESHOLD = 0.5;

    size_t hash(const K& key) const
    {
        return std::hash<K> {}(key) % capacity;
    }

    size_t findSlot(const K& key) const
    {
        size_t index = hash(key);
        size_t originalIndex = index;

        do {
            if (!table[index].isOccupied || table[index].key == key) {
                return index;
            }
            index = (index + 1) % capacity;
        } while (index != originalIndex);

        return -1; // Table is full
    }

    void rehash()
    {
        std::vector<Entry> oldTable = std::move(table);

        // Double the capacity
        capacity *= 2;
        table = std::vector<Entry>(capacity);
        size = 0;

        // Reinsert all existing elements
        for (const auto& entry : oldTable) {
            if (entry.isOccupied) {
                size_t index = findSlot(entry.key);
                table[index].key = entry.key;
                table[index].isOccupied = true;
                size++;
            }
        }
    }

public:
    HashTable(size_t initialCapacity = 16)
        : capacity(initialCapacity)
        , size(0)
    {
        table.resize(capacity);
    }

    void insert(const K& key)
    {
        size_t index = findSlot(key);

        // Insert new entry
        if (table[index].isOccupied) {
            std::cout << key << " already exists at " << index << std::endl;
            // std::cout << key << " already exists" << std::endl;
            return;
        }
        table[index].key = key;
        table[index].isOccupied = true;
        size++;
        if ((double)size / capacity > LOAD_FACTOR_THRESHOLD) {
            rehash();
        }
        std::cout << key << " inserted at " << index << std::endl;
        // std::cout << key << " inserted" << std::endl;
    }

    void get(const K& key) const
    {
        size_t index = hash(key);
        size_t originalIndex = index;

        do {
            if (!table[index].isOccupied) {
                break;
            }

            if (table[index].key == key) {
                std::cout << key << " found at " << index << std::endl;
                // std::cout << key << " found" << std::endl;
                return;
            }
            index = (index + 1) % capacity;
        } while (index != originalIndex);

        std::cout << key << " does not exist" << std::endl;
    }

    void remove(const K& key)
    {
        size_t index = hash(key);
        size_t originalIndex = index;

        do {
            if (!table[index].isOccupied) {
                break; // Key not found
            }

            if (table[index].key == key) {
                std::cout << table[index].key << " erased at " << index;
                // std::cout << table[index].key << " erased";

                size--;

                // Shift elements to fill the gap
                size_t curr = index;
                size_t next = (curr + 1) % capacity;

                while (table[next].isOccupied) {
                    size_t nextHash = hash(table[next].key);
                    // If the element can be moved back (is part of the same probe sequence)
                    if ((next > curr && (nextHash <= curr || nextHash > next)) || (next < curr && (nextHash <= curr && nextHash > next))) {
                        std::cout << ", moving " << table[next].key << " from " << next;
                        table[curr] = table[next];
                        curr = next;
                    }
                    next = (next + 1) % capacity;
                }

                // Clear the last slot in the chain
                table[curr].isOccupied = false;
                std::cout << std::endl;
                return;
            }
            index = (index + 1) % capacity;
        } while (index != originalIndex);

        std::cout << key << " does not exist" << std::endl;
        return;
    }

    size_t getSize() const
    {
        return size;
    }

    bool isEmpty() const
    {
        return size == 0;
    }
};

int main()
{
#ifndef ONLINE_JUDGE
    freopen("1-1.in", "r", stdin);
    freopen("hash.out", "w", stdout);
#endif

    HashTable<std::string> ht;
    int command;
    std::string key;
    // int i;
    while (true) {
        // std::cerr << ++i << std::endl;
        std::cin >> command;
        if (command == 0) {
            break;
        }

        std::cin >> key;
        // std::cout << "Hash(key)=" << ht.hash(key) << ' ';
        if (command == 1) {
            ht.insert(key);
        } else if (command == 2) {
            ht.get(key);
        } else {
            ht.remove(key);
        }
    }

    return 0;
}
