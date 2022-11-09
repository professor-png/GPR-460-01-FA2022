#pragma once

const int STACK_SIZE = 1024 * 1024 * 5;

class StackAllocator
{
private:
    char* buffer;
    char* base;

public:
    StackAllocator() :
        buffer(new char[STACK_SIZE]),
        base(buffer)
    {}

    ~StackAllocator()
    {
        clear();
        delete[] buffer;
    }

    template <typename T>
    T* alloc()
    {
        size_t sizeToAllocate = sizeof(T);
        T* allocationPoint = (T*)base;

        if (base + sizeToAllocate > buffer + STACK_SIZE)
            return nullptr;
        base += sizeToAllocate;
        return allocationPoint;
    }

    template <typename T>
    T* alloc(size_t arrayCount)
    {
        size_t sizeToAllocate = sizeof(T) * arrayCount;
        T* allocationPoint = (T*)base;

        if (base + sizeToAllocate > buffer + STACK_SIZE)
            return nullptr;
        base += sizeToAllocate;
        return allocationPoint;
    }

    void clear()
    {
        base = buffer;
    }
};