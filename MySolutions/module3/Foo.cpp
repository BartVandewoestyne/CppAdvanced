#include "Foo.h"

#include "MemoryPool.h"

MemoryPool<Foo> foopool;

void* Foo::operator new(size_t size) {
    return foopool.allocate();
}

void Foo::operator delete(void* p, size_t size) {
    foopool.deallocate(static_cast<Foo*>(p));
}
