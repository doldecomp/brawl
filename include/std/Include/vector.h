#pragma once

#include <stddef.h>
#include <types.h>
#include <sr/sr_common.h>

template <typename T>
class Vector {

    // arr is the integer pointer
    // which stores the address of our vector
    T* arr;

    // capacity is the total storage
    // capacity of the vector
    int capacity;

    // current is the number of elements
    // currently present in the vector
    int current;

    HeapType heapType;

public:
    Vector()
    {
        this->heapType = Heaps::Tmp;
        arr = new (heapType) T[1];
        capacity = 1;
        current = 0;
    }

    Vector(HeapType heapType)
    {
        this->heapType = heapType;
        arr = new (heapType) T[1];
        capacity = 1;
        current = 0;
    }

    ~Vector()
    {
        delete[] arr;
    }

    /**
     * Clears the vector.
     */
    void clear()
    {
        delete[] arr;
        arr = new (heapType) T[1];
        current = 0;
    }

    /**
     * Removes an element at a specific index.
     *
     * @param index The index of the element to remove.
     */
    void removeAt(int index)
    {
        if (index < 0 || index >= current)
            return;

        arr[index] = arr[current - 1];
        pop();
    }

    // Function to add an element at the last
    void push(T data)
    {

        // if the number of elements is equal to the
        // capacity, that means we don't have space to
        // accommodate more elements. We need to double the
        // capacity
        if (current == capacity)
        {
            T* temp = new (heapType) T[2 * capacity];

            // copying old array elements to new array
            for (int i = 0; i < capacity; i++)
            {
                temp[i] = arr[i];
            }

            // deleting previous array
            delete[] arr;
            capacity *= 2;
            arr = temp;
        }

        // Inserting data
        arr[current] = data;
        current++;
    }

    // function to add element at any index
    void push(T data, int index)
    {

        // if index is equal to capacity then this
        // function is same as push defined above
        if (index == capacity)
        {
            push(data);
        }
        else
        {
            arr[index] = data;
            current++;
        }
    }

    // function to extract element at any index
    T get(int index)
    {
        // if index is within the range
        if (index < current)
            return arr[index];

        return NULL;
    }

    // function to delete last element
    void pop() { current--; }

    // function to get size of the vector
    int size() const { return current; }

    // function to get capacity of the vector
    int getcapacity() { return capacity; }

    T& operator[](int index)
    {
        return arr[index];
    }
};