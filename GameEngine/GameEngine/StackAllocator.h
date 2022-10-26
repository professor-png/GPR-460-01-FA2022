#pragma once

const int STACK_SIZE = 1024 * 1024 * 32;

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

    template <typename T>
    T* alloc()
    {
        size_t sizeToAllocate = sizeof(T);
        void* allocationPoint = base;

        base += sizeToAllocate;
        return allocationPoint;
    }

    template <typename T>
    T* alloc(size_t arrayCount)
    {
        size_t sizeToAllocate = sizeof(T) * arrayCount;
        void* allocationPoint = base;

        base += sizeToAllocate;
        return allocationPoint;
    }

    void clear()
    {
        base = buffer;
    }
};