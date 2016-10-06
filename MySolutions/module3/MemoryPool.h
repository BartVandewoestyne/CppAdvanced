template <typename ObjectType, int capacity>
class MemoryPool {

    PoolEntry memory[capacity];
public:
    ObjectType* allocate();
    void deallocate(ObjectType*);
};
