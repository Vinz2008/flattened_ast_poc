#include <vector>

class ArenaChunk {
    char* ptr;
public:
    int size;
    int used;
    ArenaChunk(int size);

    char* get_ptr(){
        return ptr;
    }
};


class Arena {
private:
    //void* ptr;
    std::vector<ArenaChunk> arenaChunks;
    
    ArenaChunk& add_chunk();

    // TODO : does returning a pair reduce performance (TODO : verify this ?)
    template <typename T> 
    std::pair<T*, int> allocate_internal(){
        ArenaChunk& last_chunk = this->arenaChunks.back();
        if (last_chunk.size <= last_chunk.used + sizeof(T)){
            last_chunk = this->add_chunk();
        }
        int offset = last_chunk.used;

        T* data = (T*) ((long)last_chunk.get_ptr() + (long)last_chunk.used);
        last_chunk.used += sizeof(T);

        return std::make_pair(data, offset);
    }

public:
    Arena();
    ~Arena();
    template <typename T>
    T* allocate(){
        return allocate_internal<T>().first;
    }
    template <typename T>
    int allocate_offset(){
        return allocate_internal<T>().second;
    }
    void* get_ptr(){
        //return ptr;
    }


    int get_offset(void* expr_ptr);
};