#ifndef FOO_H
#define FOO_H

class Foo {
public:
    void* operator new(size_t size);
    void operator delete(void* p, size_t size);
};

#endif  // FOO_H
