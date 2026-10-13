#pragma once

#include <vector.h>

/**
 * @brief A simple key-value map implementation.
 *
 * @note The insertion order of the items in the map is not preserved
 */
template <typename Key, typename Value>
class Map {
private:
    struct Pair {
        Key key;
        Value value;

        Pair() {}
        Pair(const Key& k, const Value& v) : key(k), value(v) {}
    };

    Vector<Pair> pairs;

public:
    Map() {}

    /**
     * @brief Inserts a key-value pair into the map.
     *
     * If the key already exists, the value is updated.
     *
     * @param key The key to insert.
     * @param value The value to associate with the key.
     */
    void insert(const Key& key, const Value& value)
    {
        for (int i = 0; i < pairs.size(); i++)
        {
            if (pairs[i].key == key)
            {
                pairs[i].value = value;
                return;
            }
        }
        pairs.push(Pair(key, value));
    }

    /**
     * @brief Finds the value associated with a key in the map.
     */
    Value* find(const Key& key)
    {
        for (int i = 0; i < pairs.size(); i++)
        {
            if (pairs[i].key == key)
            {
                return &pairs[i].value;
            }
        }
        return NULL;
    }

    /**
     * @brief Removes a key-value pair from the map.
     *
     * @param key The key of the pair to remove.
     * @return true if the pair was removed, false otherwise.
     */
    bool remove(const Key& key)
    {
        for (int i = 0; i < pairs.size(); i++)
        {
            if (pairs[i].key == key)
            {
                pairs[i] = pairs[pairs.size() - 1];
                pairs.pop();
                return true;
            }
        }
        return false;
    }

    /**
     * @brief Returns whether a specified key is present in the map
     *
     * @param key The key to search for.
     * @return true if the key is found, false otherwise.
     */
    bool contains(const Key& key) const
    {
        for (int i = 0; i < pairs.size(); i++)
        {
            if (pairs[i].key == key)
            {
                return true;
            }
        }
        return false;
    }

    /**
     * @brief Returns the number of items in the map.
     */
    int size() const
    {
        return pairs.size();
    }

    /**
     * @brief Returns whether the map is empty.
     */
    bool empty() const
    {
        return pairs.size() == 0;
    }

    /**
     * @brief Clears the map of all entries
     */
    void clear()
    {
        pairs.clear();
    }

    Value& operator[](const Key& key)
    {
        for (int i = 0; i < pairs.size(); i++)
        {
            if (pairs[i].key == key)
            {
                return pairs[i].value;
            }
        }
        pairs.push(Pair(key, Value()));
        return pairs[pairs.size() - 1].value;
    }
};