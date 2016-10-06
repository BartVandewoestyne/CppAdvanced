#ifndef StaticMemoryPool_H
#define StaticMemoryPool_H

#include <iostream> // 4 verification

/**
 * @brief Pre C++11 naive, fast, generic StaticMemoryPool
 */
template<typename ObjectType, int NumObjects, typename EmptyPolicy>
class StaticMemoryPool
{
public: 
    StaticMemoryPool() : next(pool) {
        for (Entry* p=pool; p!= pool+NumObjects-1; ++p)
            p->next = p+1;
        pool[NumObjects-1].next = 0;

    }

    ObjectType* allocate() {
        std::cout << "StaticMemoryPool::allocate" << std::endl;
        
        if (EmptyPolicy::assert)
            assert(next!=0); // Out of memory?
        
        Entry* p = next;
        next = next->next;
        return &p->data;
    }
    
    void deallocate(ObjectType* p) {
        /*
         * Should add checks if p was one of the actual pointers delt
         * On the other hand, the standard memory allocator also has undefined behavior when given a bad pointer
         */
        std::cout << "StaticMemoryPool::deallocate" << std::endl;
        //Entry* e = reinterpret_cast<Entry*>(p+1);
        Entry* e = reinterpret_cast<Entry*>(p);
        e-> next = next;
        next = e;
    }

private:

    struct Entry 
    {
        ObjectType data;
        Entry* next;
    } pool[NumObjects];

    Entry* next;
};


#endif // StaticMemoryPool_H
